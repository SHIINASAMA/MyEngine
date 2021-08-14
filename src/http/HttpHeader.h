/**
 * @file HttpHeader.h
 * @author kaoru
 * @date 2021.8.9
 * @version 0.1
 * @brief Http 报头
 */
#pragma once
#include <Utility.h>
#include <map>

#define MAKE_ELEMENT(key, value) make_shared<MyEngine::HttpHeaderElement>(key, value)

namespace MyEngine {

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
     * @brief Http 报头元素
     */
    class HttpHeaderElement {
    public:
        /**
         * @brief 智能指针对象
         */
        typedef shared_ptr<HttpHeaderElement> Ptr;

        string key{};
        string value{};
        /**
          * 默认初始化报头元素
          */
        HttpHeaderElement() = default;
        /**
          * 初始化一个报头元素
          * @param key 键
          * @param value 值
          */
        HttpHeaderElement(const string &key, const string &value);
        /**
          * 报头导出
          * @return 字符串
          */
        string dump() const;
    };

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
     * @brief Http 报头类
     */
    class HttpHeader {
    public:
        /**
         * @brief 智能指针对象
         */
        typedef shared_ptr<HttpHeader> Ptr;

        /**
         * 默认构造函数
         */
        HttpHeader() = default;
        /**
         * 默认析构函数
         */
        virtual ~HttpHeader();

        /**
         * 获取 HTTP 版本
         * @return HTTP 版本
         */
        int getHttpVersion() const { return this->version; };
        /**
         * 设置 HTTP 版本
         * @param _version HTTP 版本
         */
        void setHttpVersion(int _version) { this->version = _version; };
        /**
         * 获取 BODY
         * @return BODY
         */
        string getBody() const { return this->body; };
        /**
         * 设置 BODY
         * @param _body BODY
         */
        void setBody(const string &_body) { this->body = _body; };

        /**
         * 获取 Http Header
         * @param key 键
         * @return 报头元素
         */
        MyEngine::HttpHeaderElement::Ptr getHeader(const string &key);
        /**
         * 设置 Http Header
         * @param headerElement 目标报头元素
         * @return 为 true 表示这是一次插入操作， 为 false 则表示这是一次更改操作
         */
        bool setHeader(const HttpHeaderElement::Ptr &headerElement);

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
         * 获取 “Location” 值
         * @return “Location” 值
         */
        string getLocation();

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
         * 设置 “Location” 值
         * @param value “Location” 值
         */
        void setLocation(const string &value);

        /**
         * 获取报头集合
         * @return 报头集合
         */
        std::map<string, HttpHeaderElement::Ptr, strcmp<>> getElements() const { return this->elements; }

    protected:
        int version{11};
        string body{};
        std::map<string, HttpHeaderElement::Ptr, strcmp<>> elements;
    };
}// namespace MyEngine