#pragma once
#include "socket/TcpClient.h"

namespace MyEngine {

    class TcpServer : public TcpClient {
    public:
        explicit TcpServer(const char *ipaddress = "127.0.0.1", unsigned short port = 80);
        TcpServer(const TcpServer &) = delete;

        TcpClient accept() const;
    };
}// namespace MyEngine