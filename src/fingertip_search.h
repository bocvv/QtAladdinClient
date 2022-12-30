/*************************************************************************
     > File Name: fingertip_search.h
     > Author: Bowei Wang
     > Mail: wangbw@rd.neteasy.com
     > Created Time: 六  12/1 15:39:05 2020
 ************************************************************************/

#ifndef _FINGERTIP_SEARCH_H
#define _FINGERTIP_SEARCH_H 

#include <QObject>
#include <QThread>

#include "ofxUDPManager.h"
#include "jpg_http.h"
#include "youdao_api.h"
#include "hiredis/hiredis.h"
#include "cls_config.h"
#include "cls_stardict.h"
#include "utils.h"

#define UDP_MSG_LENGTH 1000

class FintipSearch: public QObject{
    Q_OBJECT
public:
    FintipSearch(QObject *parent = 0);
    ~FintipSearch();

    // udp manager module
    void setup(int PORT);
    void parse_ocr_json(std::string& str_json);
    void update();
    ofxUDPManager udp_mgr;
    char udp_message[UDP_MSG_LENGTH];
    int size_n;

    void set_stop_flag(bool flag);

private:
    QString m_det_result{""};
    bool m_finger_triggered{false};
    bool m_stop{false};

signals:
    void currDetWord(bool finger_triggered, const QString &strDetWord);  // detection result of one word by fingetip researching
    void sglFinished();

public slots:
    void process();
    void stop();
};

// controller of the class<FintipSearch>
class FintipController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString wordRaw MEMBER m_word_raw) 
    Q_PROPERTY(QString wordClass MEMBER m_word_class) 
    Q_PROPERTY(QString wordChinese MEMBER m_word_chinese) 
    Q_ENUMS(AvailableDict)

    QThread *workerThread{nullptr};

public:
    FintipController() {
        // init aladdin redis conn and youdaoapi params from conf file
        init();

        select_dict();
    }

    ~FintipController() {
        delete_dict();

        redisFree(ctx);
        ctx = nullptr;
    }

    enum AvailableDict {
        YoudaoOnlineDict,
        LangdaoOfflineDict
    };

    Q_INVOKABLE AvailableDict dictionary() const;
    Q_INVOKABLE void setDict(AvailableDict dict);

private:
    QString m_word_raw;
    QString m_word_class;
    QString m_word_chinese;
    AvailableDict m_dict{LangdaoOfflineDict};
    
    // fingertip ocr manager obj
    FintipSearch *fin_search{nullptr};

    /* dictionary manager obj */
    // youdao online dictionary
    JpgRequestManager *req_mgr{nullptr};
    YoudaoApi *yd_api{nullptr};
    // offline dictionary
    ClsSDict *cls_dict{nullptr};

    // config param
    std::string redis_addr;
    int redis_port;
    std::string redis_pass;
    redisContext* ctx{nullptr};

    std::string device_id;

    std::string appkey;
    std::string app_sk;

    std::string dict_dirname;
    std::string dict_typo_txt;

    ZBase64 z_base;

    void init();
    void search_youdao_dict(const std::string &word, std::string &explain);
    void search_offline_dict(std::string &word, std::string &explain);
    void search_word(std::string &word, std::string &explain);
    void record_word(const std::string &word, std::string &explain);

    // about dictionary manager
    void select_dict();
    void delete_dict();

public slots:
    void start();
    void stop();
    void handleDetWord(bool finger_triggered, const QString &strDetWord);

signals:
    void startProcess();
    // void stopProcess();
    void wordDetTriggered(const QString &strWordRaw, const QString &strWordTrans);
    void fingerTriggered(bool isTriggered);
};


#endif
