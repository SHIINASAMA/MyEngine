/**
 * @file Http.h
 * @author kaoru
 * @date 2021.8.8
 * @brief Http 公共声明
 * @version 0.1
 */
#pragma once
#include <cstring>
#include <map>
#include <sstream>
#include <string>

using std::string;

namespace MyEngine {

    /**
     * @brief 字符串忽略大小写比较
     * @tparam T 默认为 std::string
     */
    template<class T = std::string>
    struct strcmp {
        bool operator()(const T &lv, const T &rv) const {
            return strcasecmp(lv.c_str(), rv.c_str()) < 0;
        }
    };

    /**
     * @brief HTTP 请求方法枚举
     */
    enum class HttpMethod {
        /**
         * GET 方法
         */
        GET,
        /**
         * POST 方法
         */
        POST,
        /**
         * 其他未支持的方法
         */
        NONSUPPORT
    };

    /**
     * @brief HTTP 报头元素
     */
    class HttpHeader {
    public:
        string key{};
        string value{};
        /**
         * 默认初始化报头元素
         */
        HttpHeader() = default;
        /**
         * 初始化一个报头元素
         * @param key 键
         * @param value 值
         */
        HttpHeader(const string &key, const string &value);
        /**
         * 报头元素转储
         * @return 字符流
         */
        std::stringstream dump() const;
    };

    /**
     * @brief HTTP 请求类
     */
    class HttpRequest {
    public:
        /**
         * 默认构造函数
         */
        HttpRequest()                     = default;
        HttpRequest(const HttpRequest &)  = delete;
        HttpRequest(const HttpRequest &&) = delete;
        /**
         * 初始化一个 HTTP 请求
         * @param method 方法
         * @param url 请求URL
         * @param query_string 参数
         * @param version HTTP 版本
         */
        HttpRequest(HttpMethod method, const string &url, const string &query_string, int version);
        /**
         * 默认析构函数
         */
        ~HttpRequest();

        /**
         * 获取报头元素
         * @param key 键
         * @param header 报头元素
         * @return 是否获取成功
         */
        bool getHeader(const string &key, HttpHeader *header);
        /**
         * 设置 Http Header
         * @param header 目标 Header
         * @return 为 true 表示这是一次插入操作， 为 false 则表示这是一次更改操作
         */
        bool setHeader(HttpHeader *header);

        /**
         * 获取请求方法
         * @return 请求方法
         */
        HttpMethod getMethod() const;
        /**
         * 设置请求方法
         * @param _method 请求方法
         */
        void setMethod(HttpMethod _method);
        /**
         * 获取请求 URL
         * @return 请求 URL
         */
        string getUrl() const;
        /**
         * 设置请求 URL
         * @param _url 请求URL
         */
        void setUrl(const string &_url);
        /**
         * 获取参数字符串
         * @return 参数字符串
         */
        string getQueryString() const;
        /**
         * 设置参数字符串
         * @param _query_string 参数字符串
         */
        void setQueryString(const string &_query_string);
        /**
         * 获取 HTTP 版本
         * @return HTTP 版本
         */
        int getHttpVersion() const;
        /**
         * 设置 HTTP 版本
         * @param _version HTTP 版本
         */
        void setHttpVersion(int _version);
        /**
         * 获取 BODY
         * @return BODY
         */
        string getBody() const;
        /**
         * 设置 BODY
         * @param _body BODY
         */
        void setBody(const string &_body);

        /**
         * 获取 “Accept” 值
         * @return “Accept” 值
         */
        string getAccept();
        /**
         * 获取 “Accept-Encoding” 值
         * @return “Accept-Encoding” 值
         */
        string getAcceptEncoding();
        /**
         * 获取 “Accept-Language” 值
         * @return “Accept-Language” 值
         */
        string getAcceptLanguage();
        /**
         * 获取 “Content-Length” 值
         * @return “Content-Length” 值
         */
        ssize_t getContentLength();
        /**
         * 获取 “Content-Type” 值
         * @return “Content-Type” 值
         */
        string getContentType();
        /**
         * 获取 “Connection” 值
         * @return “Connection” 值
         */
        string getConnection();
        /**
         * 获取 “Host” 值
         * @return “Host” 值
         */
        string getHost();
        /**
         * 获取 “Pragma” 值
         * @return “Pragma” 值
         */
        string getPragma();
        /**
         * 获取 “User-Agent” 值
         * @return “User-Agent” 值
         */
        string getUserAgent();
        /**
         * 获取 “Server” 值
         * @return “Server” 值
         */
        string getServer();

        /**
         * 设置 “Accept” 值
         * @param value “Accept” 值
         */
        void setAccept(const string &value);
        /**
         * 设置 “Accept-Encoding” 值
         * @param value “Accept-Encoding” 值
         */
        void setAcceptEncoding(const string &value);
        /**
         * 设置 “Accept-Language” 值
         * @param value “Accept-Language” 值
         */
        void setAcceptLanguage(const string &value);
        /**
         * 设置 “Content-Language” 值
         * @param value “Content-Language” 值
         */
        void setContentLength(ssize_t value);
        /**
         * 设置 “Content-Type” 值
         * @param value “Content-Type” 值
         */
        void setContentType(const string &value);
        /**
         * 设置 “Connection” 值
         * @param value “Connection” 值
         */
        void setConnection(const string &value);
        /**
         * 设置 “Pragma” 值
         * @param value “Pragma” 值
         */
        void setHost(const string &value);
        /**
         * 设置 “User-Agent” 值
         * @param value “User-Agent” 值
         */
        void setPragma(const string &value);
        /**
         * 设置 “User-Agent” 值
         * @param value “User-Agent” 值
         */
        void setUserAgent(const string &value);
        /**
         * 设置 “Server” 值
         * @param value “Server” 值
         */
        void setServer(const string &value);

        /**
         * 报头转储
         * @return value 字符流
         */
        std::stringstream dump() const;

        /**
         * 获取报头 Map
         * @return 报头 Map
         */
        const std::map<string, HttpHeader *, strcmp<>> &getHeaders() const;

    protected:
        HttpMethod method = HttpMethod::NONSUPPORT;
        int version       = 11;
        string url{};
        string query_string{};
        string body{};
        std::map<string, HttpHeader *, strcmp<>> headers;
    };

    /**
     * @brief HTTP 回报类
     */
    class HttpResponse {
    public:
        /**
         * 默认构造函数
         */
        HttpResponse()                      = default;
        HttpResponse(const HttpResponse &)  = delete;
        HttpResponse(const HttpResponse &&) = delete;
        /**
         * 初始化一个 HTTP 回报
         * @param version HTTP 版本
         * @param state_code 状态码
         */
        HttpResponse(int version, int state_code);
        /**
         * 默认析构函数
         */
        ~HttpResponse();

        /**
         * 获取 Http Header
         * @param key 键
         * @param header 报头元素
         * @return 是否获取成功
         */
        bool getHeader(const string &key, HttpHeader *header);
        /**
         * 设置 Http Header
         * @param header 目标 Header
         * @return 为 true 表示这是一次插入操作， 为 false 则表示这是一次更改操作
         */
        bool setHeader(HttpHeader *header);

        /**
         * 获取 HTTP 版本
         * @return HTTP 版本
         */
        int getHttpVersion() const;
        /**
         * 设置 HTTP 版本
         * @param version HTTP 版本
         */
        void setHttpVersion(int version);
        /**
         * 获取状态码
         * @return 状态码
         */
        int getStateCode() const;
        /**
         * 设置状态码
         * @param code 状态码
         */
        void setStateCode(int code);
        /**
         * 设置 BODY
         * @return BODY
         */
        string getBody() const;
        /**
         * 获取 BODY
         * @param body BODY
         */
        void setBody(const string &body);

        /**
         * 获取 “Accept” 值
         * @return “Accept” 值
         */
        string getAccept();
        /**
         * 获取 “Accept-Encoding” 值
         * @return “Accept-Encoding” 值
         */
        string getAcceptEncoding();
        /**
         * 获取 “Accept-Language” 值
         * @return “Accept-Language” 值
         */
        string getAcceptLanguage();
        /**
         * 获取 “Content-Length” 值
         * @return “Content-Length” 值
         */
        ssize_t getContentLength();
        /**
         * 获取 “Content-Type” 值
         * @return “Content-Type” 值
         */
        string getContentType();
        /**
         * 获取 “Connection” 值
         * @return “Connection” 值
         */
        string getConnection();
        /**
         * 获取 “Host” 值
         * @return “Host” 值
         */
        string getHost();
        /**
         * 获取 “Pragma” 值
         * @return “Pragma” 值
         */
        string getPragma();
        /**
         * 获取 “User-Agent” 值
         * @return “User-Agent” 值
         */
        string getUserAgent();
        /**
         * 获取 “Server” 值
         * @return “Server” 值
         */
        string getServer();

        /**
         * 设置 “Accept” 值
         * @param value “Accept” 值
         */
        void setAccept(const string &value);
        /**
         * 设置 “Accept-Encoding” 值
         * @param value “Accept-Encoding” 值
         */
        void setAcceptEncoding(const string &value);
        /**
         * 设置 “Accept-Language” 值
         * @param value “Accept-Language” 值
         */
        void setAcceptLanguage(const string &value);
        /**
         * 设置 “Content-Language” 值
         * @param value “Content-Language” 值
         */
        void setContentLength(ssize_t value);
        /**
         * 设置 “Content-Type” 值
         * @param value “Content-Type” 值
         */
        void setContentType(const string &value);
        /**
         * 设置 “Connection” 值
         * @param value “Connection” 值
         */
        void setConnection(const string &value);
        /**
         * 设置 “Pragma” 值
         * @param value “Pragma” 值
         */
        void setHost(const string &value);
        /**
         * 设置 “User-Agent” 值
         * @param value “User-Agent” 值
         */
        void setPragma(const string &value);
        /**
         * 设置 “User-Agent” 值
         * @param value “User-Agent” 值
         */
        void setUserAgent(const string &value);
        /**
         * 设置 “Server” 值
         * @param value “Server” 值
         */
        void setServer(const string &value);

        /**
         * 报头转储
         * @return value 字符流
         */
        std::stringstream dump() const;

        /**
         * 获取报头 Map
         * @return 报头 Map
         */
        const std::map<string, HttpHeader *, strcmp<>> &getHeaders() const;

    protected:
        int version{11};
        int state_code{200};
        string body{};
        std::map<string, HttpHeader *, strcmp<>> headers;
    };
}// namespace MyEngine