/**
 * @file HttpServer.cpp
 * @author kaoru
 * @date 2021.8.8
 * @brief Http 服务器类实现
 * @version 0.1
 */
#include <cstring>
#include <http/HttpParser.h>
#include <http/HttpServer.h>

using MyEngine::HttpHeader;
using MyEngine::HttpMethod;
using MyEngine::HttpRequest;
using MyEngine::HttpResponse;
using MyEngine::HttpServer;
using std::string;

HttpServer::HttpServer(const string &ipaddress, unsigned short port) : TcpServer(ipaddress.c_str(), port) {
}

bool HttpServer::init(int backlog) {
    if (!Socket::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) {
        return false;
    }
    int opt = 1;
    if (!this->setsockopt(SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        return false;
    }
    if (!this->bind()) {
        return false;
    }
    if (!this->listen(backlog)) {
        return false;
    }
    return true;
}

MyEngine::TcpClient HttpServer::accept() {
    return TcpServer::accept();
}

void HttpServer::shutdown() {
    this->close();
}