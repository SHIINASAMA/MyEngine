#pragma once
#include <http/Http.h>
#include <http/HttpClient.h>
#include <socket/TcpServer.h>

using std::string;

namespace MyEngine {

    class HttpServer : public TcpServer {
    public:
        HttpServer(const string &ipaddress, unsigned short port);
        ~HttpServer() override = default;

    public:
        bool init(int backlog);
        TcpClient accept();
        void shutdown();
    };
}// namespace MyEngine
