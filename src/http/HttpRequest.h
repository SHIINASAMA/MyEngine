/**
 * @file HttpRequest.h
 * @author kaoru
 * @date 2021.8.8
 * @brief Http 请求
 * @version 0.1
 */
#pragma once
#include <http/HttpHeader.h>

namespace MyEngine {
    /**
     * @brief Http 请求类
     */
    class HttpRequest : public HttpHeader {
    public:
        /**
         * @brief 智能指针对象
         */
        typedef shared_ptr<HttpRequest> Ptr;

        /**
         * 默认构造函数
         */
        HttpRequest() noexcept = default;
        /**
         * 初始化一个 HTTP 请求
         * @param method 方法
         * @param url 请求URL
         * @param query_string 参数
         * @param version HTTP 版本
         */
        HttpRequest(HttpMethod method, const string &url, const string &query_string, int version) noexcept;
        /**
         * 默认析构函数
         */
        ~HttpRequest() noexcept override;

        /**
         * 获取请求方法
         * @return 请求方法
         */
        HttpMethod getMethod() const noexcept { return this->method; }
        /**
         * 设置请求方法
         * @param _method 请求方法
         */
        void setMethod(HttpMethod _method) noexcept { this->method = _method; }
        /**
         * 获取 Url
         * @return Url
         */
        string getUrl() const noexcept { return this->url; }
        /**
         * 设置 Url
         * @param _url 设置 Url
         */
        void setUrl(const string &_url) noexcept { this->url = _url; }
        /**
         * 获取查询字符串
         * @return 查询字符串
         */
        string getQueryString() const noexcept { return this->query_string; }
        /**
         * 设置查询字符串
         * @param queryString 查询字符串
         */
        void setQueryString(const string &queryString) noexcept { this->query_string = queryString; }

        /**
         * 请求导出
         * @return 字符串
         */
        std::string dump() const noexcept;

    protected:
        HttpMethod method = HttpMethod::NONSUPPORT;
        string url{};
        string query_string{};
    };
}// namespace MyEngine