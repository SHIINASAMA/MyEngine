#include <fcntl.h>
#include <native/Socket.h>
#include <unistd.h>

MyEngine::Socket::Socket(socket_t socket, sockaddr_in address) {
    this->fd      = socket;
    this->address = address;
}

MyEngine::Socket::Socket(const char *ipaddr, unsigned short port) {
    this->address.sin_family      = AF_INET;
    this->address.sin_port        = htons(port);
    this->address.sin_addr.s_addr = inet_addr(ipaddr);
}

MyEngine::Socket::~Socket() {
    if (fd != -1) {
        this->close();
    }
}

MyEngine::Socket MyEngine::Socket::accept(struct sockaddr *_address, socklen_t *address_len) const {
    socket_t client_sock = ::accept(this->fd, _address, address_len);
    auto *temp           = (sockaddr_in *) &(*_address);
    return Socket(client_sock, *temp);
}

#define XX(context) \
    return (context) != -1 ? true : false

bool MyEngine::Socket::good() const {
    XX(this->fd);
}

bool MyEngine::Socket::socket(int domain, int type, int protocol) {
    //    XX((this->fd = ::socket(domain, type, protocol)));
    auto temp  = (this->fd = ::socket(domain, type, protocol)) != -1;
    auto flags = fcntl(fd, F_GETFL, 0);    //获取文件的flags值。
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);//设置成非阻塞模式；
    return temp;
}

bool MyEngine::Socket::bind(const struct sockaddr *_address, socklen_t address_len) const {
    XX(::bind(this->fd, _address, address_len));
}

bool MyEngine::Socket::listen(int backlog) const {
    XX(::listen(this->fd, backlog));
}

bool MyEngine::Socket::close() {
    int rt = ::close(this->fd);
    XX(rt);
}

bool MyEngine::Socket::getsockopt(int level, int opt_name, void *opt_value, socklen_t *opt_len) const {
    XX(::getsockopt(this->fd, level, opt_name, opt_value, opt_len));
}

bool MyEngine::Socket::setsockopt(int level, int opt_name, const void *opt_value, socklen_t opt_len) const {
    XX(::setsockopt(this->fd, level, opt_name, opt_value, opt_len));
}

bool MyEngine::Socket::shutdown(int how) const {
    XX(::shutdown(this->fd, how));
}

bool MyEngine::Socket::connect(const sockaddr *_address, socklen_t address_len) const {
    XX(::connect(this->fd, _address, address_len));
}

#undef XX

ssize_t MyEngine::Socket::recv(void *buf, size_t len, int flags) const {
    return ::recv(this->fd, buf, len, flags);
}

ssize_t MyEngine::Socket::send(const void *buf, size_t len, int flags) const {
    return ::send(this->fd, buf, len, flags);
}

sockaddr_in MyEngine::Socket::getAddress() const {
    return address;
}

socket_t MyEngine::Socket::getSocket() const {
    return this->fd;
}
