/*************************************************************************
	> File Name: utils.h
	> Author: Bowei Wang
	> Mail: wangbw@rd.neteasy.com
	> Created Time: 六  9/26 17:08:05 2020
 ************************************************************************/

#ifndef _UTILS_H
#define _UTILS_H

#include <string>

// alert sound module
extern void sound_alert(std::string sound_path);
extern void call_sound_alert_async(std::string sound_path);

//编码表
const char EncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//解码表
const char DecodeTable[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    62, // '+'
    0, 0, 0,
    63, // '/'
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, // '0'-'9'
    0, 0, 0, 0, 0, 0, 0,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
    13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, // 'A'-'Z'
    0, 0, 0, 0, 0, 0,
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
    39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, // 'a'-'z'
};

#include <string>
using namespace std;

class ZBase64 {
public:
    /*编码
    DataByte
        [in]输入的数据长度,以字节为单位
    */
    string Encode(const char* Data, int DataByte);
    /*解码
    DataByte
        [in]输入的数据长度,以字节为单位
    OutByte
        [out]输出的数据长度,以字节为单位,请不要通过返回值计算
        输出数据的长度
    */
    string Decode(const char* Data, int DataByte, int& OutByte);
};

#endif
