/**
 * @file HttpServer.h
 * @author kaoru
 * @date 2021.8.8
 * @brief Http 服务器类
 * @version 0.1
 */
#pragma once
#include <http/HttpClient.h>
#include <http/HttpRequest.h>
#include <socket/TcpServer.h>

using std::string;

namespace MyEngine {

    /**
     * @brief Http 服务器
     */
    class HttpServer : public TcpServer {
    public:
        /**
         * 初始化服务器
         * @param ipaddress 地址
         * @param port 端口
         */
        HttpServer(const string &ipaddress, unsigned short port);
        /**
         * 默认析构函数
         */
        ~HttpServer() override = default;

    public:
        /**
         * 配置服务器
         * @param backlog 队列大小
         * @return 是否配置成功
         */
        bool init(int backlog);
        /**
         * 接收一个 TCP 客户端
         * @return TCP 客户端
         */
        TcpClient::Ptr accept();
        /**
         * 关闭服务器
         */
        void shutdown();
    };
}// namespace MyEngine
