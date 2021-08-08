/**
 * @file HttpClient.h
 * @author kaoru
 * @date 2021.8.8
 * @brief Http 客户端
 * @version 0.1
 */
#pragma once
#include <http/Http.h>

namespace MyEngine{

    /**
     * @brief Http 客户端
     */
    class HttpClient{
    public:
        /**
         * 发送 GET 请求
         * @param ipaddress 目标 IP
         * @param port 端口
         * @param request 请求
         * @param response 回报
         * @return 是否成功
         */
        static bool Get(const string &ipaddress, unsigned short port, HttpRequest &request, HttpResponse *response);
        /**
         * 发送 POST 请求
         * @param ipaddress 目标 IP
         * @param port 端口
         * @param request 请求
         * @param response 回报
         * @return 是否成功
         */
        static bool Post(const string &ipaddress, unsigned short port, HttpRequest &request, HttpResponse *response);
    };
}