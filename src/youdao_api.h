#ifndef _YOUDAO_API_H
#define _YOUDAO_API_H

#include <string>

using namespace std;

class YoudaoApi {
public:
    YoudaoApi();
    YoudaoApi(std::string _appkey, std::string _app_secret);
    ~YoudaoApi();

    void set_q(const string &s);
    void set_appkey(string s);
    void set_app_secret(string s);
    void set_from(string s);
    void set_to(string s);
    void set_salt();
    void set_curtime();
    void cal_input();
    void cal_sign();
    void gen_target_uri(string &target_uri);

private:
    string q;
    string input;
    string appkey;
    string app_secret;
    string from{"EN"};
    string to{"zh-CHS"};
    string salt;
    string curtime;
    string sign;
    string sign_type{"v3"};
};

#endif
