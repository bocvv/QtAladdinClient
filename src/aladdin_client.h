/*************************************************************************
	> File Name: aladin_client.h
	> Author: Bowei Wang
	> Mail: wangbw@rd.neteasy.com
	> Created Time: 六  9/26 17:08:05 2020
 ************************************************************************/

#ifndef _ALADDIN_CLIENT_H
#define _ALADDIN_CLIENT_H

#include <QObject>
#include <QThread>
#include <QSqlDatabase>

#include "ofxUDPManager.h"
#include "wrapper_client.pb.h"
#include "opencv2/core/core.hpp"

struct PoseNum {
    int play_phone_num;
    int look_lamp_num;
    int look_monitor_num;
    int look_book_num;
    int look_other_num;
    int look_none_num;
    int total_frames;
};

struct PoseRate {
    double play_phone_rate;
    double look_lamp_rate;
    double look_monitor_rate;
    double look_book_rate;
    double look_other_rate;
    double look_none_rate;
};
Q_DECLARE_METATYPE(PoseRate);

class AladdinClient : public QObject {
    Q_OBJECT

public:
    AladdinClient(QObject *parent = 0);
    ~AladdinClient();

    // main process function: recieve the protobuffer from aladin_server,
    // thne play tts to alert the student about the bad poses, low attention,
    // and if using cell phone.
    int init(std::string bad_pose_path, std::string use_phone_path);

    std::string pose_mp3_file;
    std::string phone_mp3_file;
    // some rknn config params
    int video_node;
    int input_width;
    int input_height;
    int input_channel;
    std::string back_label_path;
    std::string head_label_path;
    std::string action_label_path;

    // udp manager module
    void setup(int PORT);
    void update();
    ofxUDPManager udp_mgr;
    char udp_message[1000];
    int size_n;

    void set_stop_flag(bool flag);

    // protobuf data blob
    ::mediapipe::WrapperClient* wrapper{nullptr};
    bool bad_pose{false};
    bool low_attention{false};
    bool use_phone{false};
    // PoseNum pose_num;
    // PoseRate pose_rate;
    void gen_pose_time_rate();

    int post_process(void *data, cv::Mat & img, float fps,
		 struct rknn_out_data *out_data);

private:
    QSqlDatabase db;
    bool m_stop{false};

signals:
    void currentStudyStatus(const QString &strStudyStatus);
    void sglSendPoseRate(const QVariant &varPoseRate);

public slots:
    void process();
    void stop();
};


class AladdinController : public QObject {
    Q_OBJECT
    QThread *workerThread;
    AladdinClient *client; 

public:
    AladdinController() {}
    ~AladdinController() {}

public slots:
    void start();
    void stop();
    void handleStudyStatus(const QString &strStudyStatus);

signals:
    void startProcess();
    void stopProcess();
    void studyStatus(const QString &strStudyStatus);
};

#endif
