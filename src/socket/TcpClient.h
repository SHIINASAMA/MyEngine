#pragma once
#include <native/Socket.h>

namespace MyEngine {

    class TcpClient : public Socket {
    public:
        TcpClient(socket_t socket, sockaddr_in address);
        TcpClient(const char *ipaddress, unsigned short port);
        TcpClient();
        ~TcpClient() override;

        bool createTcpSocket();
        bool connect() const;
        bool bind() const;
    };

}// namespace MyEngine
