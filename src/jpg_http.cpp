#include <iostream>
#include <vector>
#include <unistd.h>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "jpg_http.h"
// #include "json/json.h"

using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
namespace http = boost::beast::http;    // from <boost/beast/http.hpp>

JpgRequestManager::JpgRequestManager() {}

JpgRequestManager::JpgRequestManager(std::string host, std::string port)
    : _host{host}, _port{port} {
}
 
JpgRequestManager::~JpgRequestManager() {}

int JpgRequestManager::sync_http(HttpMethod method, std::string &target, \
    std::string &request_body, std::string &response_body) {
    try
    {
    auto const uri_target = target;    // 要获取的文档
    int version = 11;        

    // The io_context is required for all I/O
    boost::asio::io_context ioc;

    // These objects perform our I/O
    tcp::resolver resolver{ ioc };
    tcp::socket socket{ ioc };

    // Look up the domain name
    auto const results = resolver.resolve(_host, _port);

    // Make the connection on the IP address we get from a lookup
    boost::asio::connect(socket, results.begin(), results.end());

    // Set up an HTTP POST request message
    http::request<http::string_body> req;
    switch (method) {
        case HttpMethod::GET:
            req = { http::verb::get, uri_target, version };
            break;
        case HttpMethod::POST:
            req = { http::verb::post, uri_target, version };
            break;
        default:
            req = { http::verb::post, uri_target, version };
    }
    req.set(http::field::host, _host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    // req body
    if (!request_body.empty()) {
        http::string_body::value_type body;
        body = request_body;
        req.body() = std::move(body);
        req.prepare_payload();
    }
    // Send the HTTP request to the remote host
    http::write(socket, req);

    // This buffer is used for reading and must be persisted
    boost::beast::flat_buffer buffer;

    // Declare a container to hold the response
    http::response<http::string_body> res;

    // Receive the HTTP response
    http::read(socket, buffer, res);

    
    // Write the message to standard out
    // std::cout << res.body() << std::endl;
    response_body = res.body();

    // Gracefully close the socket
    boost::system::error_code ec;
    socket.shutdown(tcp::socket::shutdown_both, ec);

    // not_connected happens sometimes
    // so don't bother reporting it.
    //
    if (ec && ec != boost::system::errc::not_connected)
        throw boost::system::system_error{ ec };

    // If we get here then the connection is closed gracefully
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

