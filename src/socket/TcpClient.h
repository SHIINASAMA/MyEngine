/**
 * @file TcpClient.h
 * @author kaoru
 * @date 2021.8.8
 * @brief TCP 协议套接字
 * @version 0.1
 */
#pragma once
#include <native/Socket.h>

namespace MyEngine {

    /**
     * @brief TCP 协议套接字
     */
    class TcpClient : public Socket {
    public:
        /**
         * @brief 智能指针对象
         */
        typedef std::shared_ptr<TcpClient> Ptr;
        /**
         * 初始化一个 TCP 套接字
         * @param socket Socket 文件描述符
         * @param address 地址
         */
        TcpClient(socket_t socket, sockaddr_in address) noexcept;
        /**
         * 初始化一个 TCP 套接字
         * @param ipaddress IP 地址
         * @param port 端口
         */
        TcpClient(const char *ipaddress, unsigned short port) noexcept;
        /**
         * 创建临时对象
         * @param socket 文件描述符
         */
        explicit TcpClient(socket_t socket) noexcept;
        /**
         * 默认初始化函数
         */
        TcpClient() noexcept;
        /**
         * 默认析构函数
         */
        ~TcpClient() noexcept override;

        /**
         * 配置当前 Socket
         * @return
         */
        bool createTcpSocket() noexcept;
        /**
         * 连接
         * @return 是否连接成功
         */
        bool connect() const noexcept;
        /**
         * 绑定地址
         * @return 绑定是否成功
         */
        bool bind() const noexcept;
    };

}// namespace MyEngine
