#include <cstring>
#include <http/HttpServer.h>

using std::string;
using std::thread;

using MyEngine::HttpHeader;
using MyEngine::HttpMethod;
using MyEngine::HttpRequest;
using MyEngine::HttpResponse;
using MyEngine::HttpServer;

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

void HttpServer::exec(TcpClient client) {
}

void HttpServer::shutdown() {
    this->close();
}
