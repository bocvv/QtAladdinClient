#include <cstdlib>
#include <sys/time.h>
#include <ctime>
#include <iostream>
#include <sstream>

#include "youdao_api.h"
#include "sha256.h"

static int tik_tok(void)
{
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec;
}

YoudaoApi::YoudaoApi(std::string _appkey, std::string _app_secret) 
    : appkey(_appkey), app_secret(_app_secret) {
}

YoudaoApi::~YoudaoApi() {

}

void YoudaoApi::set_q(const std::string &s) {
    q = s;
}

void YoudaoApi::set_appkey(std::string s) {
    appkey = s;
}

void YoudaoApi::set_app_secret(std::string s) {
    app_secret = s;
}

void YoudaoApi::set_from(std::string s) {
    from = s;
}

void YoudaoApi::set_to(std::string s) {
    to = s;
}

void YoudaoApi::set_salt() {
    srand((unsigned)time(NULL));
    salt = std::to_string(rand() % 10);
}

void YoudaoApi::set_curtime() {
    curtime = std::to_string(tik_tok());
}

void YoudaoApi::cal_input() {
    // len(q) <= 20
    if (q.length() <= 20) {
        input = q;
	return;
    }

    // len(q) > 20
    input = q.substr(0, 10) + std::to_string(q.length()) + q.substr(q.length() - 10, 10);
}

void YoudaoApi::cal_sign() {
    // prepare required key&value for target uri
    cal_input();
    set_salt();
    set_curtime();

    std::string sha256_str = appkey + input + salt + curtime + app_secret;
    // cout << "sha256_str = " << sha256_str << endl;
    sign = sha256(sha256_str);
    // cout << "sign = " << sign << endl;
}

void YoudaoApi::gen_target_uri(std::string &target_uri) {
    cal_sign();

    ostringstream os;
    os << "/api?appKey=" << appkey << "&q=" \
       << q << "&from=" << from << "&to=" << to << "&sign=" << sign \
       << "&salt=" << salt << "&curtime=" << curtime << "&signType=" << sign_type;
    target_uri = os.str();

    // cout << "target_uri:" << target_uri << endl;
}
