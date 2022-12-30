 /*************************************************************************
      > File Name: fingertip_search.cpp
      > Author: Bowei Wang
      > Mail: wangbw@rd.netease.com
      > Created Time: 六  12/1 15:39:05 2020
  ************************************************************************/

#include <QDebug>
#include <sys/time.h>
#include <unistd.h>

#include "fingertip_search.h"
#include "json/json.h"

using namespace std;

static bool is_file_exists(std::string name) {
    return (access(name.c_str(), F_OK ) != -1 );
}

static std::string remove_string_punct(std::string &input) {
    std::string output;

    // Process this string
    for (string::size_type i = 0; i < input.size(); i++)
    {
        if (!ispunct(input[i]))
        {
            output += input[i];
        }
    }

    return output;
}

static int get_unix_timestamp() {
    struct timeval now_time;
    gettimeofday(&now_time, NULL);
    return now_time.tv_sec;
}

static void redis_request(redisContext* ctx, const char* cmd) {
    redisReply* r = (redisReply*)redisCommand(ctx, cmd);
    if (r == NULL) {
        cout << "Execut command failure." << endl;
        return;
    }

    freeReplyObject(r);
    return;
}

static void search_and_speech(std::string word) {
    std::string lower_word = word;
    lower_word[0] = std::tolower(lower_word[0]);

    std::string speech_file_path; 
    speech_file_path = conf->Read("speech_file_path", speech_file_path);
    std::string word_path = speech_file_path + lower_word[0] + "/" + word + ".wav";

    // if this word do not exist in voice db, then lower it's first alpha
    if (!is_file_exists(word_path)) {
        word_path = speech_file_path + lower_word[0] + "/" + lower_word + ".wav";
	cout << "word_path = " << word_path << endl;
	// if word with lower first alpha also do not exist, then skip speech
	if (!is_file_exists(word_path)) {
	    return;
	}
    }

    call_sound_alert_async(word_path);
}

FintipSearch::FintipSearch(QObject *parent)
     : QObject(parent)
 {
     qDebug() << "start with FintipSearch constructed!";
 }

FintipSearch::~FintipSearch() {
    udp_mgr.Close();
}

void FintipSearch::set_stop_flag(bool flag) {
    m_stop = flag;
}

void FintipSearch::setup(int PORT) {
    qDebug() << "Listen on udp PORT: " << PORT;

    // create the socket and bind to porti[default = 8080].
    ofxUDPSettings settings;
    settings.receiveOn(PORT);
    settings.blocking = true;
    settings.receiveTimeout = 1;

    udp_mgr.Setup(settings);
}

void FintipSearch::parse_ocr_json(std::string& ocr_json) {
    // parse ocr udp json body
    Json::Value data;
    Json::Reader reader;
    reader.parse(ocr_json, data);

    // update the signal and emit to the parent controller class instance
    m_finger_triggered = data["finger_triggered"].asBool();
    std::string s = data["update_word"].toStyledString();
    s = s.substr(1, s.length() - 3);
    m_det_result = QString::fromStdString(s);

    return;
}

void FintipSearch::update() {
    // check for incoming messages
    size_n = udp_mgr.Receive(udp_message, UDP_MSG_LENGTH);

    if (size_n > 0) {
        // accept the incoming proto
        std::string s = udp_message;
#ifdef Q_DEBUG
        qDebug() << QString::fromStdString(s);
#endif

        // parse the udp json msg and do something
        parse_ocr_json(s);

        // emit detected signal to fintipcontroller examplar
        emit currDetWord(m_finger_triggered, m_det_result);
    } else {
        m_det_result = "";
    }
}

// Receive the udp word and search in out dictionary 
// while switch trigger this function.
void FintipSearch::process() {
    // initialize the udp setup between aladdin client and fingertip server
    qDebug() << "start to setup fintip's udp port!";
    setup(conf->Read("fintip_port", 8765));
    qDebug() << "finish setup fintip's udp port!";

    // start processing
    qDebug() << "start process() funciton of fingertip searching!";
    while (!m_stop) {
        // qDebug() << "recv json udp!";
        update();
    }

    // emit sglFinished();
    return;
}

void FintipSearch::stop() {
    qDebug() << "set fingertop searching stop";
    m_stop = true;
}

FintipController::AvailableDict FintipController::dictionary() const {
    return m_dict;
}

void FintipController::setDict(AvailableDict dict) {
    m_dict = dict;
}

void FintipController::init() {
    redis_addr = conf->Read("redis_addr", redis_addr);
    redis_port = conf->Read("redis_port", 6379);
    redis_pass = conf->Read("redis_pass", redis_pass);

    // youdao dict api params
    appkey = conf->Read("youdao_api_key", appkey);
    app_sk = conf->Read("youdao_api_sk", app_sk);

    // offline dict params
    dict_dirname = conf->Read("dict_dirname", dict_dirname);
    dict_typo_txt = conf->Read("dict_typo_txt", dict_typo_txt);

    device_id = conf->Read("device_id", device_id);

    // create a new redis context
    ctx = redisConnect(redis_addr.c_str(), redis_port);
    if (ctx->err) {
        redisFree(ctx);
        ctx = nullptr;
        qDebug() << "Connect to redisServer fail";
        return ;
    }
    qDebug() << "Connect to redisServer Success";

    // auth by redis password
    redisReply* r = (redisReply*)redisCommand(ctx, "AUTH %s", redis_pass.c_str());
    if (r->type == REDIS_REPLY_ERROR) {
        qDebug() << "redis auth fail!";
        return;
    } else {
        qDebug() << "redis auth success!";
    }
    freeReplyObject(r);
}

void FintipController::record_word(const std::string &word, std::string &explain) {
    /*
     * param word: search word
     * param explain: explanation of the word
     */
    std::string word_id = device_id + ":word:" + word;
    std::string cmd = "HGET " + word_id + " frequency";

    // 判断该单词是否已记录，如记录则频率+1，否则置为1
    int frequency{1};
    redisReply* r = (redisReply*)redisCommand(ctx, cmd.c_str());
    if (r->type == REDIS_REPLY_NIL) {
        std::string enc_explain = z_base.Encode(explain.c_str(), explain.length());
        cmd = "HMSET " + word_id + " frequency 1 explain \"" + enc_explain + "\"";
        freeReplyObject(r);
        r = (redisReply*)redisCommand(ctx, cmd.c_str());
    } else {
        frequency += stoi(r->str);
        cmd = "HINCRBY " + word_id + " frequency 1";
        freeReplyObject(r);
        r = (redisReply*)redisCommand(ctx, cmd.c_str());
    }
    freeReplyObject(r);

    // 存储此单词的查询次数到有序集合
    std::string zset_freq = device_id + ":frequency: ";
    cmd = "ZADD " + zset_freq + std::to_string(frequency) + " " + word;
    r = (redisReply*)redisCommand(ctx, cmd.c_str());
    freeReplyObject(r);

    // 存储此单词的最后一次查询unix时间戳到有序集合
    std::string zset_time = device_id + ":time: ";
    cmd = "ZADD " + zset_time + std::to_string(get_unix_timestamp()) + " " + word;
    r = (redisReply*)redisCommand(ctx, cmd.c_str());
    freeReplyObject(r);
}

void FintipController::select_dict() {
    switch (m_dict) {
        case YoudaoOnlineDict: {
            // init youdao api module
            if (req_mgr == nullptr) {
                req_mgr = new JpgRequestManager("openapi.youdao.com", "80");
            }
            if (yd_api == nullptr) {
                yd_api = new YoudaoApi(appkey, app_sk);
            }
            break;
        }
        case LangdaoOfflineDict: {
            // init langdao offline api module
            if (cls_dict == nullptr) {
                cls_dict = new ClsSDict();
                cls_dict->load_dics(dict_dirname);
                cls_dict->read_typo_txt(dict_typo_txt);
            }
            break;
        }
        default: {
        }
    }
}

void FintipController::start() {
    // init fingertip ocr udp module
    fin_search = new FintipSearch();
    workerThread = new QThread;
    fin_search->moveToThread(workerThread);

    connect(this, SIGNAL(startProcess()), fin_search, SLOT(process()));
    connect(fin_search, SIGNAL(currDetWord(bool, const QString)), \
            this, SLOT(handleDetWord(bool, const QString)));
    connect(workerThread, SIGNAL(finished()), fin_search, SLOT(deleteLater()));

    workerThread->start();
    system("systemctl restart fintip-ocr");
    emit startProcess();
}

void FintipController::delete_dict() {
    if (req_mgr != nullptr) {
        delete req_mgr;
        req_mgr = nullptr;
    }
    if (yd_api != nullptr) {
        delete yd_api;
        yd_api = nullptr;
    }
    if (cls_dict != nullptr) {
        delete cls_dict;
        cls_dict = nullptr;
    }
}

void FintipController::stop() {
    system("systemctl stop fintip-ocr");
    system("ssh toybrick@192.168.180.8 \"sudo bash /home/toybrick/tipdict_server/stop_all.sh\"");
    fin_search->set_stop_flag(true);

    workerThread->quit();
    // workerThread->wait();
}

void FintipController::search_youdao_dict(const std::string &word, \
        std::string &explain) {
    // single request
    std::string target;
    yd_api->set_q(word);
    yd_api->gen_target_uri(target);

    std::string req_body = "";
    std::string resp_body;
    int r = req_mgr->sync_http(HttpMethod::GET, target, req_body, resp_body);

    // parse json body
    Json::Value data;
    Json::Reader reader;
    reader.parse(resp_body, data);    

    if (!data["isWord"].asBool()) {
        explain = "词库暂未收录此词";
	    return;
    }

    /* std::string results; */
    for (auto & i: data["basic"]["explains"]) {
        std::string res = i.toStyledString();
        res = res.substr(1, res.length() - 3);
        explain += res;
        explain += "\n";

        /*
        int n_line = res.length() / 60 + 1;
        for (int l = 1; l <= n_line; l++) {
            int pos = res.find("；", l * 60);
            if (pos != std::string::npos) {
                res = res.insert(pos + 6, "\n");
            }
        }

        results += res;
        results += "\n";
        */
    }

}

void FintipController:: search_offline_dict(std::string &word, \
        std::string &explain) {
    explain = cls_dict->lookup(word);

    /*
    if (explain.empty()) {
        // this step maybe change the original word to a new fuzzy word
        explain = cls_dict->fuzzy_lookup(word);
    }
    */
}

void FintipController::search_word(std::string &word, \
        std::string &explain) {
    switch (m_dict) {
        case YoudaoOnlineDict: {
            search_youdao_dict(word, explain);
            break;
        }
        case LangdaoOfflineDict: {
            search_offline_dict(word, explain);
            break;
        }
        default: {
            break;
        }
    }
}

void FintipController::handleDetWord(bool finger_triggered, const QString &strDetWord) {
#ifdef Q_DEBUG
    qDebug() << "finger_triggered = " << finger_triggered;
#endif
    if (finger_triggered) {
        emit fingerTriggered(true);
    } else {
        emit fingerTriggered(false);
    }

    // if isEmpty == true, then we do not do anything for LCD display
    if (strDetWord.isEmpty()) {
        return;
    }

    // search this detected word in our dictionary
    m_word_raw = strDetWord;
    // if we use offline dict, its unnecessary to emit this sgl
    /* emit wordDetTriggered(m_word_raw, "已捕捉到单词\n开始查询字典, 请稍候~"); */

    std::string word = m_word_raw.toStdString();
    std::string explain;  // copy from results without split lines

    // 去除部分ocr结果可能携带的标点符号
    word = remove_string_punct(word);

    // find the word and get it's explain in dictionary
    search_word(word, explain);

    QString strWordTrans; 
    m_word_raw = QString::fromStdString(word);
    if (!explain.empty()) {
        // store word and explain to Redis Server
        // TODO: 添加一个redis连接池或者线程池来异步得做这件事，不然
        // 在网络不太好的时候这个操作会阻塞后续的屏幕显示
        /*
        if (ctx != nullptr) {
            std::string enc_explain = z_base.Encode(explain.c_str(), explain.length());
            record_word(word, enc_explain);
        }
        */

        // use for QT Display
        strWordTrans = QString::fromStdString(explain);
        search_and_speech(word);
        // qDebug() << "The triggered word is: " << m_word_raw;
        // qDebug() << "word's explain is: " << strWordTrans;
    } else {
        // m_word_raw = "";
        strWordTrans = "词库中没有收录该词!";
    }

    // emit signal to trigger text after changing the property
    emit wordDetTriggered(m_word_raw, strWordTrans);
    return;
}

