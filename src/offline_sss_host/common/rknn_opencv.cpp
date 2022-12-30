#include <chrono>
#include "rknn_opencv.h"

static const std::chrono::milliseconds con_var_time_out(100);

unsigned long rknn_opencv::get_time(void)
{
    struct timeval ts;
    gettimeofday(&ts, NULL);
    return (ts.tv_sec * 1000 + ts.tv_usec / 1000);
}

void *rknn_opencv::get_img_task(void *data)
{
    int ret;
    rknn_opencv *pd = (rknn_opencv *) data;
    printf("%s thread start...\n", __func__);

    // 反正这个线程只起一次，那就干脆在这记录一下当前帧idx吧
    int interval_frame = 6;//11;
    int cur_read_frame_id_mod_interval = 0;

    while (pd->is_running) {
        cv::Mat tmp_origin;
        cv::Mat tmp_resize;

        ret = (*pd->get_img_func) (pd->user_ctx_ptr,
                       tmp_origin, tmp_resize);
        if (ret < 0) {
            printf("get_img_func error[%d], stop demo...\n", ret);
            pd->is_running = false;
        }

        std::unique_lock < std::mutex > lock(pd->mtx_idle);

        if (pd->idle_queue.empty()) {
        // if (pd->idle_queue.size() < 8) {
            continue;
        }

        auto img = pd->idle_queue.front();
        pd->idle_queue.pop();
        lock.unlock();

        *(img->img_origin) = tmp_origin;
        *(img->img_resize) = tmp_resize;
        // 下面根据已经读取的帧数，确定当前帧是否被采样用于推理
        if (cur_read_frame_id_mod_interval == 0) {
            img->pick = true;
        } else {
            img->pick = false;
        }
        cur_read_frame_id_mod_interval = (cur_read_frame_id_mod_interval + 1) % interval_frame;

        pd->mtx_input.lock();
        pd->input_queue.push(img);
        // if (pd->input_queue.size() >= 8) {
        pd->cond_input_not_empty.notify_all();
        // }
        pd->mtx_input.unlock();
    }

    printf("%s thread terminate...\n", __func__);
    return NULL;
}

void *rknn_opencv::detect_img_task(void *data)
{
    int ret{0};
    rknn_opencv *pd = (rknn_opencv *) data;
    printf("%s thread start...\n", __func__);

        // 记录一下当前推理窗口中已经放了几帧。凑够8帧就进行推理。
        int index_in_infer_window = 0;

    while (pd->is_running) {
        std::unique_lock < std::mutex > lock(pd->mtx_input);

        if (pd->input_queue.empty()) {
        // if (pd->input_queue.size() < 8) {
            pd->cond_input_not_empty.wait_for(lock,
                              con_var_time_out);
            continue;
        }


        cv::Mat tmp_origin;


        auto img = pd->input_queue.front(); // 元素类型为 rknn_queue_data
        pd->input_queue.pop();

        // 必须是被选中用于推理的帧，才会被拷出来
        if (img->pick) {
            int _offset = index_in_infer_window * pd->one_frame_size;
            memcpy(pd->input_data_buf + _offset, img->img_resize->data, pd->one_frame_size);
            index_in_infer_window += 1; // 8帧拿去推理
        }

        pd->mtx_output.lock();
        pd->output_queue.push(img);
        pd->cond_output_not_empty.notify_all();
        pd->mtx_output.unlock();
        lock.unlock();

        if (index_in_infer_window == 8) {
            ret = (*pd->detect_img_func) (pd->user_ctx_ptr,
                    pd->input_data_buf,
                    // input_item->input_data_buf,
                    &pd->out_data);
            index_in_infer_window = 0;
        }
        if (ret < 0) {
            printf("detect_img_func error[%d], stop demo...\n",
                   ret);
            pd->is_running = false;
        }
    }

    printf("%s thread terminate...\n", __func__);
    return NULL;
}

rknn_opencv::rknn_opencv()
{
    // mat_count = 8;
    mat_count = 32;
    is_running = false;
    fps = 0.0;
    user_ctx_ptr = NULL;

    mats_queue = new rknn_queue_data[mat_count];
    mats_origin = new cv::Mat[mat_count];
    mats_resize = new cv::Mat[mat_count];

    for (int i = 0; i < mat_count; i++) {
        mats_queue[i].img_origin = &mats_origin[i];
        mats_queue[i].img_resize = &mats_resize[i];
        idle_queue.push(&mats_queue[i]);
    }

    frame_count = 0;

    // TSM
    one_frame_size = 192 * 288 * 3;
    input_data_buf = (char*)malloc(8 * one_frame_size);
    memset(&out_data, 0x00, sizeof(out_data));
}

rknn_opencv::~rknn_opencv()
{
    delete[]mats_origin;
    delete[]mats_resize;
    delete[]mats_queue;
    free(input_data_buf);
}

int rknn_opencv::start(int (*get_img) (void *, cv::Mat &, cv::Mat &),
               // int (*detect_img) (void *, cv::Mat &,
               int (*detect_img) (void *, char * ,
                      struct rknn_out_data *),
               int (*show_img) (void *, cv::Mat &, float,
                    struct rknn_out_data *), void *user_ctx)
{
    if (!get_img || !detect_img || !show_img)
        return -1;

    get_img_func = get_img;
    detect_img_func = detect_img;
    show_img_func = show_img;
    user_ctx_ptr = user_ctx;

    is_running = true;
    last_time = get_time();
    thread_get_img = std::thread(get_img_task, this); // this 被作为参数传入 get_img_task 方法
    thread_detect_img = std::thread(detect_img_task, this);

    return 0;
}

int rknn_opencv::update_show(void)
{
    int ret;
    std::unique_lock < std::mutex > lock(mtx_output);

    if (output_queue.empty()) {
        if (is_running) {
            cond_output_not_empty.wait_for(lock, con_var_time_out);
            return 0;
        } else {
            return -1;
        }
    }

    auto img = output_queue.front();
    output_queue.pop();
    lock.unlock();

    frame_count++;
    unsigned long cur_time = get_time();
    if (cur_time - last_time > 1000) {
        float sec_time = (cur_time - last_time) / 1000.0;
        fps = frame_count / sec_time;
        printf("%f, %5.2f\n", fps, fps);
        last_time = cur_time;
        frame_count = 0;
    }

    ret =
        (*show_img_func) (user_ctx_ptr, *(img->img_origin), fps,
                  &out_data);

    mtx_idle.lock();
    idle_queue.push(img);
    mtx_idle.unlock();

    return ret;
}

int rknn_opencv::stop(void)
{
    is_running = false;
    usleep(10000);

    cond_input_not_empty.notify_all();
    cond_output_not_empty.notify_all();

    thread_get_img.join();
    thread_detect_img.join();

    return 0;
}
