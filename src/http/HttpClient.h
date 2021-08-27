/**
 * @file HttpClient.h
 * @author kaoru
 * @date 2021.8.8
 * @brief Http 客户端
 * @version 0.1
 */
#pragma once
#include <http/HttpRequest.h>
#include <http/HttpResponse.h>

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
        static bool Get(const string &ipaddress, unsigned short port, const HttpRequest::Ptr& request, HttpResponse::Ptr response) noexcept;
        /**
         * 发送 POST 请求
         * @param ipaddress 目标 IP
         * @param port 端口
         * @param request 请求
         * @param response 回报
         * @return 是否成功
         */
        static bool Post(const string &ipaddress, unsigned short port, const HttpRequest::Ptr& request, HttpResponse::Ptr response) noexcept;
    };
}