/*************************************************************************
	> File Name: aladin_client.cpp
	> Author: Bowei Wang
	> Mail: wangbw@rd.netease.com
	> Created Time: 六  9/26 17:08:12 2020
 ************************************************************************/ 
#include <QDebug>
#include <QSqlQuery>
#include <QApplication>
#include <algorithm>
#include "aladdin_client.h"
#include "utils.h"
#include "cls_config.h"
#include "rknn_test.h"

#define NUM_RESULTS     1917
#define THRESHOLD       0.35
#define ACTION_NUM      6
#define BACK_NUM        3
#define HEAD_NUM        5

using namespace std;
using namespace cv;

template<class ForwardIterator>
inline size_t argmin(ForwardIterator first, ForwardIterator last)
{
    return std::distance(first, std::min_element(first, last));
}

template<class ForwardIterator>
inline size_t argmax(ForwardIterator first, ForwardIterator last)
{
    return std::distance(first, std::max_element(first, last));
}

namespace {
    int loadLabelName(string locationFilename, string * labels)
    {
        ifstream fin(locationFilename);
        string line;
        int lineNum = 0;

        while (getline(fin, line)) {
                labels[lineNum] = line;
                lineNum++;
        }

        return 0;
    }
}

struct aladdin_labels {
    string backs[BACK_NUM + 1];
    string heads[HEAD_NUM + 1];
    string actions[ACTION_NUM + 1];
    string back_and_score = "None";
    string head_and_score = "None";
    string action_and_score = "None";
};

AladdinClient::AladdinClient(QObject *parent) 
    : QObject(parent)
{
    qDebug() << "start with aladdin_client constructed!";
}

AladdinClient::~AladdinClient() {
    qDebug() << "exit with aladdin_client deconstructed!";

    udp_mgr.Close();

    if (wrapper != nullptr) {
        delete wrapper;
        wrapper = nullptr;
    }
}

void AladdinClient::set_stop_flag(bool flag) {
    m_stop = flag;
}

void AladdinClient::setup(int PORT) {
}

// 解析每一次推理的结果
void AladdinClient::update() {
}

// calculate every pose's cost time and store these data to our local DB
void AladdinClient::gen_pose_time_rate() {
}

int AladdinClient::init(string bad_pose_path, string use_phone_path) {
    if (bad_pose_path.empty() || use_phone_path.empty()) {
        return -1;
    }

    pose_mp3_file = bad_pose_path;
    phone_mp3_file = use_phone_path;

    return 0;
}

// 基本只需要修改这里即可
int AladdinClient::post_process(void *data, cv::Mat & img, float fps,
		 struct rknn_out_data *out_data)
{
    struct aladdin_labels *user_data = (struct aladdin_labels *)data;

    /* transform */
    if (out_data->out[0] != 0x0) { // 如果不是新值，这个地址就在 rknn_test::show_img 中被赋为了0
        float *pred = (float *)out_data->out[0];

        size_t back_idx = argmax(pred, pred+3);
        size_t head_idx = argmax(pred+3, pred+8);
        size_t action_idx = argmax(pred+8, pred+14);

        string back_str = user_data->backs[back_idx];
        string head_str = user_data->heads[head_idx];
        string action_str = user_data->actions[action_idx];

        float _back_score = pred[back_idx];
        float _head_score = pred[3 + head_idx];
        float _action_score = pred[8 + action_idx];
	string back_score = std::to_string(_back_score);
        string head_score = std::to_string(_head_score);
        string action_score = std::to_string(_action_score);

        user_data->back_and_score = back_str + " " + back_score;
        user_data->head_and_score = head_str + " " + head_score;
        user_data->action_and_score = action_str + " " + action_score;

        if (_back_score < THRESHOLD) {
            user_data->back_and_score = "Back None";
        }
        if (_head_score < THRESHOLD) {
            user_data->head_and_score = "Head None";
        }
        if (_action_score < THRESHOLD) {
            user_data->action_and_score = "Action None";
        }
    }

    {
	string sss = user_data->back_and_score + "\n" + user_data->head_and_score + "\n" + user_data->action_and_score;
        QString strStudyStatus = QString::fromStdString(sss);
        emit currentStudyStatus(strStudyStatus);
        // call_sound_alert_async(phone_mp3_file);
    }

    return 0;
}

void AladdinClient::process() {
    qDebug() << "start processing aladdin_client!";

    /* sound alert */
    std::string bad_pose_path, use_phone_path;
    bad_pose_path = conf->Read("bad_pose_mp3", bad_pose_path);
    use_phone_path = conf->Read("use_phone_mp3", use_phone_path);
    init(bad_pose_path, use_phone_path);

    /* some rknn config params init */
    video_node = conf->Read("video_node", 2);
    input_width = conf->Read("input_width", 288);
    input_height = conf->Read("input_height", 192);
    input_channel = conf->Read("input_channel", 3);
    back_label_path = conf->Read("back_label_path", back_label_path);
    head_label_path = conf->Read("head_label_path", head_label_path);
    action_label_path = conf->Read("action_label_path", action_label_path);

    /* start processing */
    // 用于初始化阶段
    int ret;
    // [> load label and boxPriors <]
    struct aladdin_labels data;
    loadLabelName(back_label_path, data.backs);
    loadLabelName(head_label_path, data.heads);
    loadLabelName(action_label_path, data.actions);

    class rknn_test test(" ");

    std::string MODEL_PATH = "../models/ssd/mobilenet_ssd.rknn";
    ret = test.load_model(MODEL_PATH.c_str()); // 其实没有真的遥控1808去加载模型
    if (ret < 0) {
        qDebug() << "load_model error!!!";
        return;
    }

    ret = test.set_input_info(input_width, input_height, input_channel);
    if (ret < 0) {
        qDebug() << "set_input_info error!!!";
        return;
    }

    // 用于update阶段
    typedef int (AladdinClient::*func)(void*, cv::Mat&, float,
		 struct rknn_out_data*);
    func post_process_ptr = (func)&AladdinClient::post_process;
    ret = test.run(video_node, post_process_ptr, &data, &m_stop, this);

    qDebug() << "generate the simple study status report...";

    return;
}

void AladdinClient::stop() {
    qDebug() << "set stop";
    m_stop = true;
}

void AladdinController::start() {
    client = new AladdinClient();
    workerThread = new QThread();
    client->moveToThread(workerThread);

    connect(this, SIGNAL(startProcess()), client, SLOT(process()));
    connect(client, SIGNAL(currentStudyStatus(const QString)), this, SLOT(handleStudyStatus(const QString)));
    connect(workerThread, SIGNAL(finished()), client, SLOT(deleteLater()));
    // connect(client, SIGNAL(sglFinished()), client, SLOT(deleteLater()));

    workerThread->start();

    emit startProcess();
}

void AladdinController::stop() {
    client->set_stop_flag(true);

    workerThread->quit();
    //workerThread->wait();
}

void AladdinController::handleStudyStatus(const QString &strStudyStatus) {
    emit studyStatus(strStudyStatus);
    return;
}
