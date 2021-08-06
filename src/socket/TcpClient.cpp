#include "socket/TcpClient.h"

MyEngine::TcpClient::TcpClient(socket_t socket, sockaddr_in address) : MyEngine::Socket(socket, address) {
}

MyEngine::TcpClient::TcpClient(const char *ipaddress, unsigned short port) : Socket(ipaddress, port) {
}

MyEngine::TcpClient::~TcpClient() = default;

bool MyEngine::TcpClient::createTcpSocket() {
    return Socket::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

bool MyEngine::TcpClient::connect() const {
    return Socket::connect((sockaddr *) &address, sizeof(address));
}

bool MyEngine::TcpClient::bind() const {
    return Socket::bind((sockaddr *) &address, sizeof(address));
}