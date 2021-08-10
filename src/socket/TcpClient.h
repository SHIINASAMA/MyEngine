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
        TcpClient(socket_t socket, sockaddr_in address);
        /**
         * 初始化一个 TCP 套接字
         * @param ipaddress IP 地址
         * @param port 端口
         */
        TcpClient(const char *ipaddress, unsigned short port);
        /**
         * 创建临时对象
         * @param socket 文件描述符
         */
        TcpClient(socket_t socket);
        /**
         * 默认初始化函数
         */
        TcpClient();
        /**
         * 默认析构函数
         */
        ~TcpClient() override;

        /**
         * 配置当前 Socket
         * @return
         */
        bool createTcpSocket();
        /**
         * 连接
         * @return 是否连接成功
         */
        bool connect() const;
        /**
         * 绑定地址
         * @return 绑定是否成功
         */
        bool bind() const;
    };

}// namespace MyEngine
