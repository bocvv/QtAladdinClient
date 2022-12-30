#include <sys/time.h>
#include "jpg_http.h"
#include "youdao_api.h"
#include "json/json.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // init module
    JpgRequestManager jpg_req_mgr("openapi.youdao.com", "80");
    std::string appkey = "7c1bb7b2bc145acc";
    std::string app_sk = "CY7ky2TPUIvWZQ7f0SgK51CeyxhYnBSF";
    YoudaoApi yd_api(appkey, app_sk);

    // single request
    std::string word = argv[1];
    std::string target;
    yd_api.set_q(word);
    yd_api.gen_target_uri(target);

    std::string req_body = "";
    std::string resp_body;
    int r = jpg_req_mgr.sync_http(HttpMethod::GET, target, req_body, resp_body);


    // parse json body
    Json::Value data;
    Json::Reader reader;
    reader.parse(resp_body, data);    

    // std::cout << data["basic"]["explains"][0] << std::endl;;
    std::string res = data["basic"]["explains"][0].toStyledString();
    if (!data["isWord"].asBool()) {
        res = "没有这个词";
    }
    std::cout  << res << std::endl;

    return r;
}
