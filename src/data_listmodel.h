#ifndef DATALISTMODEL_H
#define DATALISTMODEL_H
 
#include <QAbstractListModel>
#include <QStringList>
#include "hiredis/hiredis.h"
 
class Data {
public:
    Data(const QString &word, const QString &explain);
 
    QString word() const;
    QString explain() const;
 
private:
    QString m_word;
    QString m_explain;
};
 
class DataListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum SearchRoles {
        WordRole = Qt::UserRole + 1,
        ExplainRole1
    };
 
    DataListModel(QObject *parent = 0);
    ~DataListModel();
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE void insert(int index, const Data &data);
    Q_INVOKABLE void append(const Data &data);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void append(const QVariantMap map);
    Q_INVOKABLE void clear();

    Q_INVOKABLE void init_from_redis(std::string order = "time");  // sort by time reverse default
    Q_INVOKABLE void sort_by_frequency();
    Q_INVOKABLE void sort_by_time();
 
signals:
    void countChanged(int arg);
 
private:
    int count() const;
 
protected:
    QHash<int, QByteArray> roleNames() const;
 
private:
    QList<Data> m_list;
    redisContext* ctx;
    std::string redis_addr;
    std::string redis_pass;
    int redis_port;
    std::string device_id;

    int curr_elements;  // save the current word entries number
    bool time_order{true};
};
 
#endif // DATALISTMODEL_H
