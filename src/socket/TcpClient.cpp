/**
 * @file TcpClient.cpp
 * @author kaoru
 * @date 2021.8.8
 * @brief TCP 协议套接字实现
 * @version 0.1
 */

#include "socket/TcpClient.h"

MyEngine::TcpClient::TcpClient(socket_t socket, sockaddr_in address) noexcept : MyEngine::Socket(socket, address) {
}

MyEngine::TcpClient::TcpClient(const char *ipaddress, unsigned short port) noexcept : Socket(ipaddress, port) {
}

MyEngine::TcpClient::~TcpClient() noexcept = default;

bool MyEngine::TcpClient::createTcpSocket() noexcept {
    return Socket::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

bool MyEngine::TcpClient::connect() const noexcept {
    return Socket::connect((sockaddr *) &address, sizeof(address));
}

bool MyEngine::TcpClient::bind() const noexcept {
    return Socket::bind((sockaddr *) &address, sizeof(address));
}

MyEngine::TcpClient::TcpClient(socket_t socket) noexcept : Socket(socket) {
}

MyEngine::TcpClient::TcpClient() noexcept = default;
