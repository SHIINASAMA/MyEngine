/**
 * @file Socket.h
 * @author kaoru
 * @date 2021.8.8
 * @brief 系统 Socket API 接口
 * @version 0.1
 */
#pragma once

#ifdef __linux__

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <memory>

typedef int socket_t;
#endif

namespace MyEngine {

    /**
     * @brief Socket 系统基类
     */
    class Socket {
    public:
        /**
         * @brief 智能指针对象
         */
        typedef std::shared_ptr<Socket> Ptr;
        /**
         * 创建临时对象
         * @param socket 文件描述符
         */
        explicit Socket(socket_t socket);
        /**
         * 初始化 Socket
         * @param socket 文件描述符
         * @param address 地址信息
         */
        Socket(socket_t socket, sockaddr_in address);
        /**
         * 初始化 Socket
         * @param ipaddr ip地址
         * @param port 端口
         */
        Socket(const char *ipaddr, unsigned short port);
        /**
         * 默认初始化 Socket
         */
        Socket() = default;
        /**
         * 默认析构
         */
        virtual ~Socket();

        /**
         * 创建 Socket 文件描述符
         * @param 域名
         * @param type 类型
         * @param protocol 协议
         * @return 是否创建成功
         */
        bool socket(int domain, int type, int protocol);
        /**
         * 判断当前文件描述符是否可用
         * @return 当前文件描述符是否可用
         */
        bool good() const;
        /**
         * 尝试连接主机
         * @param _address 目标地址
         * @param address_len 地址大小
         * @return 是否连接成功
         */
        bool connect(const sockaddr *_address, socklen_t address_len) const;
        /**
         * 绑定地址
         * @param address 目标地址
         * @param address_len 地址大小
         * @return 是否绑定成功
         */
        bool bind(const struct sockaddr *address, socklen_t address_len) const;
        /**
         * 设置监听队列
         * @param backlog 队列大小
         * @return 是否设置成功
         */
        bool listen(int backlog) const;
        /**
         * 接收一个客户端 Socket
         * @param _address 客户端地址
         * @param address_len 客户端地址大小
         * @return Socket 客户端
         */
        Socket accept(struct sockaddr *_address, socklen_t *address_len) const;
        /**
         * 关闭当前连接
         * @return 是否关闭成功
         */
        bool close();
        /**
         * 关闭当前连接
         * @param how 关闭方式
         * @return 是否关闭成功
         */
        bool shutdown(int how) const;
        /**
         * 设置 Socket 属性
         * @param level 等级
         * @param opt_name 属性名称
         * @param opt_value 属性值
         * @param opt_len 属性大小
         * @return 是否设置成功
         */
        bool setsockopt(int level, int opt_name, const void *opt_value, socklen_t opt_len) const;
        /**
         * 获取 Socket 属性
         * @param level 等级
         * @param opt_name 属性名称
         * @param opt_value 属性值
         * @param opt_len 属性大小
         * @return 是否获取成功
         */
        bool getsockopt(int level, int opt_name, void *opt_value, socklen_t *opt_len) const;
        /**
         * 接收字节
         * @param buf 缓存块
         * @param len 缓存大小
         * @param flags 接收标志
         * @return 实际接收大小
         */
        ssize_t recv(void *buf, size_t len, int flags) const;
        /**
         * 发送字节
         * @param buf 缓存块
         * @param len 缓存大小
         * @param flags 接收标志
         * @return 实际接收大小
         */
        ssize_t send(const void *buf, size_t len, int flags) const;

        /**
         * 获取当前文件描述符
         * @return Socket 文件描述符
         */
        socket_t getSocket() const;
        /**
         * 获取当前地址
         * @return 当前地址
         */
        sockaddr_in getAddress() const;

    protected:
        socket_t fd{-1};
        sockaddr_in address{0};
    };
}// namespace MyEngine