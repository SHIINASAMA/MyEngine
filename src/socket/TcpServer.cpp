/**
 * @file TcpServer.cpp
 * @author kaoru
 * @date 2021.8.8
 * @brief TCP 协议服务器套接字实现
 * @version 0.1
 */
#include "socket/TcpServer.h"

MyEngine::TcpServer::TcpServer(const char *ipaddress, unsigned short port) noexcept : TcpClient(ipaddress, port) {
}

MyEngine::TcpClient::Ptr MyEngine::TcpServer::accept() const noexcept {
    sockaddr_in address = this->getAddress();
    socklen_t socklen   = sizeof(address);
    socket_t fd         = ::accept(this->fd, (sockaddr *) &address, &socklen);
    return std::make_shared<TcpClient>(fd, address);
}