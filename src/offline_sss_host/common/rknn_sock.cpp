#include "rknn_sock.h"
#include <cstring>

#define CHECK_NULL(x)     do {\
                if (!(x))\
                    return RKNN_ERR_PARAM_INVALID;\
            } while (0)
enum {
    OUT_INVALID = 0,
    OUT_SYNC,
    OUT_OKAY,
};

rknn_sock::rknn_sock()
{
    output_state = OUT_INVALID;
}

rknn_sock::~rknn_sock()
{
    for (auto i:float_outs) {
        free(i.buf);
    }
}

int rknn_sock::load_model(const char *model_path, uint32_t flag)
{
    int ret = 0;

    CHECK_NULL(model_path);

    /* Load model to bufffer */
    printf("loading model...\n");

    ret = tcp_client.tcpc_connect();
    if (ret < 0) {
        printf("connect server fail! ret=%d\n", ret);
        goto exit;
    }

    ret = tcp_client.recv_data(&in_out_num, sizeof(in_out_num));
    if (ret != sizeof(in_out_num))
        goto exit;

    printf("input num = %u, output = num = %u\n",
           in_out_num.n_input, in_out_num.n_output);

    for (int i = 0; i < in_out_num.n_output; i++) {
        rknn_tensor_attr tmp_attr;
        tmp_attr.index = i;
        ret = tcp_client.recv_data(&tmp_attr, sizeof(tmp_attr));
        if (ret != sizeof(tmp_attr)) {
            goto exit;
        }
        printf("tensor index %d is %s, type = %02x, qnt_type = %02x\n",
               i, tmp_attr.name, tmp_attr.type, tmp_attr.qnt_type);
        attrs.push_back(tmp_attr);

        rknn_output out;
        memset(&out, 0x00, sizeof(out));
        out.index = i;
        out.size = tmp_attr.n_elems * sizeof(float);

        float *data = (float *)malloc(out.size);
        memset(data, 0x00, out.size);
        out.buf = data;

        float_outs.push_back(out);
    }

exit:
    return ret;
}

int rknn_sock::inference(void *in_buf, int in_len, float **out_data)
{
    int ret = 0;
    int recv_len = 0;

    CHECK_NULL(in_buf);

    ret = tcp_client.send_data(&in_len, sizeof(in_len));
    if (ret != sizeof(in_len))
        return -1;

    ret = tcp_client.send_data(in_buf, in_len);
    if (ret != in_len)
        return -1;

    for (int i = 0; i < in_out_num.n_output; i++) {
        recv_len = 0;
        ret = tcp_client.recv_data(float_outs[i].buf, float_outs[i].size);
        if (ret != float_outs[i].size) {
            return -1;
        }
        // printf("out_data[%d] = %p\n", i, out_data[i]);
        memcpy(out_data[i], float_outs[i].buf, float_outs[i].size);
    }

    return 0;
}

int rknn_sock::get_in_out_num(rknn_input_output_num *in_out)
{
    CHECK_NULL(in_out);

    memset(in_out, 0x00, sizeof(*in_out));

    in_out->n_input = in_out_num.n_input;
    in_out->n_output = in_out_num.n_output;

    return 0;
}

int rknn_sock::get_outsize(int index, int *size)
{

    CHECK_NULL(size);

    *size = 0;

    if (index > float_outs.size())
        return RKNN_ERR_OUTPUT_INVALID;

    *size = float_outs[index].size;

    return 0;
}

int rknn_sock::get_outputs_data(int index, float *data, int size)
{
    CHECK_NULL(data);

    if (size < float_outs[index].size)
        return RKNN_ERR_PARAM_INVALID;

    if (index >= in_out_num.n_output || output_state == OUT_INVALID)
        return RKNN_ERR_OUTPUT_INVALID;

    memcpy(data, float_outs[index].buf, float_outs[index].size);

    return 0;
}

