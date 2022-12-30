#ifndef _JPG_HTTP_REQ_H
#define _JPG_HTTP_REQ_H

#include <string>

enum class HttpMethod {
    GET    = 1,
    POST   = 2,
    PUT    = 3,
    DELETE = 4
};

class JpgRequestManager {
public:
    JpgRequestManager();
    JpgRequestManager(std::string host, std::string port);
    ~JpgRequestManager();
 
    int sync_http(HttpMethod method, std::string & target, \
        std::string & request_body, std::string & response_body);

private:
    std::string _host;
    std::string _port;
};


#endif
