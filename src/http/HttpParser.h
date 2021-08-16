/**
 * @file HttpParser.h
 * @author kaoru
 * @date 2021.8.8
 * @brief Http 数据转换器
 * @version 0.1
 */
#pragma once
#include <http/HttpRequest.h>
#include <http/HttpResponse.h>
#include <socket/TcpClient.h>
#include <vector>

namespace MyEngine {

    /**
     * @brief Http 数据转换器
     */
    class HttpParser {
    public:
        /**
         * 读取请求
         * @param sock Tcp 连接
         * @param request 请求
         * @return 是否获取成功
         */
        static bool RequestParser(const TcpClient::Ptr& sock, const HttpRequest::Ptr& request);
        /**
         * 读取回报
         * @param sock Tcp 连接
         * @param response 回报
         * @return 是否获取成功
         */
        static bool ResponseParser(const TcpClient::Ptr& sock, const HttpResponse::Ptr& response);

    private:
        /**
         * 读取一行
         * @param sock Tcp 连接
         * @param buf 缓存块
         * @param size 缓存块大小
         * @return 实际接收大小
         */
        static ssize_t GetLine(const TcpClient::Ptr& sock, char *buf, int size);

    public:
        /**
         * 分割字符串
         * @param string 目标字符串
         * @param pattern 模式字符串
         * @return 字符串集合
         */
        static std::vector<std::string> Split(const std::string &string, const std::string &pattern);
    };
}// namespace MyEngine