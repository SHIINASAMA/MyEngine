#pragma once
#include <http/Http.h>
#include <socket/TcpServer.h>
#include <thread>

using std::string;
using std::thread;

namespace MyEngine{

    class HttpServer : TcpServer{
    public:
        HttpServer(const HttpServer &) = delete;
        HttpServer(const HttpServer &&) = delete;
        HttpServer(const string &ipaddress, unsigned short port);
        ~HttpServer() override = default;

    public:
        bool init(int backlog);
        TcpClient accept();
        void exec(TcpClient client);
        void shutdown();

        virtual void onRequest(HttpRequest* request, HttpResponse* response) {};

    protected:
    };
}
