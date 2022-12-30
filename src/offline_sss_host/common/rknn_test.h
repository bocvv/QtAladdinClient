#ifndef __RKNN_TEST_H_
#define __RKNN_TEST_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <fstream>
#include <iostream>
#include <sys/time.h>
#include <mutex>
#include "rknn_sock.h"

#include "rknn_opencv.h"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "aladdin_client.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))
#endif

class rknn_test {
private:
    bool is_model_load;
    std::mutex mtx;
    
    class rknn_sock rknn_api;
    const char *win_name;
    cv::VideoCapture cap;
    int *output_size;
    
    int input_index;
    int img_width;
    int img_height;
    int img_channels;
    unsigned int num_output;
    
    unsigned long detect_time;
    unsigned long detect_count;
    unsigned long show_time;
    unsigned long show_count;
    
    void *user_data;
    int (AladdinClient::*post_process) (void *data, cv::Mat & img, float fps,
                 struct rknn_out_data * out_data);
    static AladdinClient *aladdin_ptr;

    //[Xiao]
    std::string action_and_score;
    std::string pose_and_score;

    static unsigned long get_time(void);
    static int get_img(void *ctx, cv::Mat & origin, cv::Mat & resize);
    static int detect_img(void *ctx, char * input_data_buf,
              struct rknn_out_data *out_data);
    static int show_img(void *ctx, cv::Mat & img, float fps,
                struct rknn_out_data *out_data);

    int common_run(int (AladdinClient::*func)
               (void *data, cv::Mat & img, float fps,
            struct rknn_out_data * out_data), void *data,
                bool *stop, AladdinClient* a_ptr);
public:
    rknn_test(const char *test_name);
    ~rknn_test();
    int load_model(const char *path);
    int set_input_info(int width, int height, int channels);
    int run(int video_node,
        int (AladdinClient::*func) (void *data, cv::Mat & img, float fps,
            struct rknn_out_data * out_data), void *data,
            bool *stop, AladdinClient* a_ptr);
    int run(const char *video_name,
        int (AladdinClient::*func) (void *data, cv::Mat & img, float fps,
            struct rknn_out_data * out_data), void *data,
        bool *stop, AladdinClient* a_ptr);
};

#endif
