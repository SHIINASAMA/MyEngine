#pragma once

#ifdef __linux__
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
    typedef int socket_t;
#endif

namespace MyEngine {

    class Socket {
    public:
        explicit Socket(socket_t socket);
        Socket(const char *ipaddr, unsigned short port);
        ~Socket();

        static bool socket(int domain, int type, int protocol);
        bool good() const;
        bool bind(const struct sockaddr *address, socklen_t address_len) const;
        bool listen(int backlog) const;
        Socket accept(struct sockaddr *address, socklen_t *address_len) const;
        bool close();
        bool shutdown(int how) const;
        bool setsockopt(int level, int opt_name, const void *opt_value, socklen_t opt_len) const;
        bool getsockopt(int level, int opt_name, void *opt_value, socklen_t *opt_len) const;
        ssize_t recv(void *buf, size_t len, int flags) const;
        ssize_t send(const void *buf, size_t len, int flags) const;

    protected:
        socket_t fd{-1};
        sockaddr_in address{0};
    };
}