/**
 * @file TcpServer.h
 * @author kaoru
 * @date 2021.8.8
 * @brief TCP 协议服务器套接字
 * @version 0.1
 */
#pragma once
#include "socket/TcpClient.h"

namespace MyEngine {

    /**
     * @brief TCP 协议服务器套接字
     */
    class TcpServer : public TcpClient {
    public:
        /**
         * 初始化一个服务器套接字
         * @param ipaddress IP 地址
         * @param port 端口
         */
        explicit TcpServer(const char *ipaddress = "127.0.0.1", unsigned short port = 80);
        TcpServer(const TcpServer &) = delete;

        /**
         * 接收一个客户端 TCP 协议套接字
         * @return TCP 客户端套接字
         */
        TcpClient accept() const;
    };
}// namespace MyEngine