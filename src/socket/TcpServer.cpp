#include "socket/TcpServer.h"

MyEngine::TcpServer::TcpServer(const char *ipaddress, unsigned short port) : TcpClient(ipaddress, port) {
}

MyEngine::TcpClient MyEngine::TcpServer::accept() const {
    sockaddr_in address = this->getAddress();
    socklen_t socklen   = sizeof(address);
    socket_t fd         = ::accept(this->fd, (sockaddr *) &address, &socklen);
    return {fd, address};
}