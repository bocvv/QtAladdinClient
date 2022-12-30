#include "data_listmodel.h"
#include "cls_config.h"
#include "cls_stardict.h"
#include <QDebug>
 
Data::Data(const QString &word, const QString &explain)
    :m_word(word), m_explain(explain) {
}
 
QString Data::word() const {
    return m_word;
}
 
QString Data::explain() const {
    return m_explain;
}
 
DataListModel::DataListModel(QObject *parent)
    : QAbstractListModel(parent) {
    // read the client conf file
    redis_addr = conf->Read("redis_addr", redis_addr);
    redis_port = conf->Read("redis_port", 6379);
    redis_pass = conf->Read("redis_pass", redis_pass);
    device_id = conf->Read("device_id", device_id);

    // init redis context
    ctx = redisConnect(redis_addr.c_str(), redis_port);
    if (ctx->err) {
        qDebug() << "Connect to redisServer fail";
        ctx = nullptr;
    } else {
        qDebug() << "Connect to redisServer Success";

        // auth redis password
        redisReply* r = (redisReply*)redisCommand(ctx, "AUTH %s", redis_pass.c_str());
        if (r->type == REDIS_REPLY_ERROR) {
            qDebug() << "redis auth fail!";
        } else {
            qDebug() << "redis auth success!";
        }
        freeReplyObject(r);
    }
}

DataListModel::~DataListModel() {
    redisFree(ctx);
}
 
void DataListModel::insert(int index, const Data &data) {
    if(index < 0 || index > m_list.count()) {
        return;
    }
 
    emit beginInsertRows(QModelIndex(), index, index);
    m_list.insert(index, data);
    emit endInsertRows();
    emit countChanged(m_list.count());
}
 
void DataListModel::remove(int index) {
    if(index < 0 || index >= m_list.count()) {
        return;
    }
 
    emit beginRemoveRows(QModelIndex(), index, index);
    m_list.removeAt( index );
    emit endRemoveRows();
    emit countChanged(m_list.count());
}
 
void DataListModel::append(const Data &data) {
    insert(count(), data);
}
 
void DataListModel::append(const QVariantMap map) {
    QString word = map["word"].toString();
    QString explain = map["explain"].toString();
 
    Data data(word, explain);
 
    insert(count(), data);
}
 
void DataListModel::clear() {
    if (m_list.count() <=0) {
        return;
    }

    // delete all elements at the index'th row
    emit beginRemoveRows(QModelIndex(), 0, m_list.count() - 1);
    m_list.clear();  // clear QList<Data> var
    emit endRemoveRows();
    emit countChanged(0);
    curr_elements = 0;
}

void DataListModel::init_from_redis(std::string order) {
    if (ctx == nullptr) {
        append( Data("服务器暂时关闭", "") );
        return;
    }

    std::string cmd = "zrevrange " + device_id + ":" + order + ": 0 -1";
    redisReply* r = (redisReply*)redisCommand(ctx, cmd.c_str());

    // TODO: 如果中间网络断开或者其他原因导致redis请求出错，则对该错误进行处理

    curr_elements = r->elements;

    ClsSDict cls_dict;
    std::string dict_dirname;
    cls_dict.load_dics(conf->Read("dict_dirname", dict_dirname));

    for (int i = 0; i < curr_elements; i++) {
        std::string _word = r->element[i]->str;
        std::string _explain = cls_dict.lookup(_word);
        append( Data(QString::fromStdString(_word), QString::fromStdString(_explain)) );
    }
}

void DataListModel::sort_by_frequency() {
    if (!time_order) {
        return;
    }

    clear();
    init_from_redis("frequency");
    time_order = false;
}
 
void DataListModel::sort_by_time() {
    if (time_order) {
        return;
    }

    clear();
    init_from_redis();
    time_order = true;
}

int DataListModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_list.count();
}
 
QVariant DataListModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_list.count())
        return QVariant();
 
    const Data &data = m_list[index.row()];
    // qDebug() << "row: " << index.row();
    if (role == WordRole)
        return data.word();
    else if (role == ExplainRole1)
        return data.explain();
    return QVariant();
}

QHash<int, QByteArray> DataListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[WordRole] = "word";
    roles[ExplainRole1] = "explain";
    return roles;
}
 
int DataListModel::count() const {
    return rowCount(QModelIndex());
}
