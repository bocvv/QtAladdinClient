#ifndef __RKNN_H__
#define __RKNN_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "rknn_api.h"
#include "tcp_comm.h"

class rknn_sock {
private:
    int output_state;
    class tcp_comm tcp_client;
    std::vector <rknn_tensor_attr >attrs;
    std::vector <rknn_output >float_outs;
    rknn_input_output_num in_out_num;

public:
    rknn_sock();

    ~rknn_sock();

    int load_model(const char *model_path, uint32_t flag);

    int inference(void *in_buf, int in_len, float **out_data);

    int get_in_out_num(rknn_input_output_num *in_out);

    int get_outsize(int index, int *size);

    int get_outputs_data(int index, float *data, int size);
};

#endif
