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
#include <http/HttpRange.h>

/**
 * @anchor MAKE_ELEMENT
 * @brief 生成 Http 报头元素
 */
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

        /**
         * 键
         */
        string key{};
        /**
         * 值
         */
        string value{};
        /**
          * 默认初始化报头元素
          */
        HttpHeaderElement() noexcept = default;
        /**
          * 初始化一个报头元素
          * @param key 键
          * @param value 值
          */
        HttpHeaderElement(const string &key, const string &value) noexcept;
        /**
          * 报头导出
          * @return 字符串
          */
        string dump() const noexcept;
    };

    /**
     * @brief 字符串忽略大小写比较
     * @tparam T 默认为 std::string
     */
    template<class T = std::string>
    struct strcmp {
        /**
         * 重载()运算符
         * @param lv 左值
         * @param rv 右值
         * @return 比较结果
         */
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
        HttpHeader() noexcept = default;
        /**
         * 默认析构函数
         */
        virtual ~HttpHeader() noexcept;

        /**
         * 获取 HTTP 版本
         * @return HTTP 版本
         */
        int getHttpVersion() const noexcept { return this->version; };
        /**
         * 设置 HTTP 版本
         * @param _version HTTP 版本
         */
        void setHttpVersion(int _version) noexcept { this->version = _version; };
        /**
         * 获取 BODY
         * @return BODY
         */
        string getBody() const noexcept { return this->body; };
        /**
         * 设置 BODY
         * @param _body BODY
         */
        void setBody(const string &_body) noexcept { this->body = _body; };

        /**
         * 获取 Http Header
         * @param key 键
         * @return 报头元素
         */
        MyEngine::HttpHeaderElement::Ptr getHeader(const string &key) noexcept;
        /**
         * 设置 Http Header，可使用 @ref MAKE_ELEMENT 快速生成报头元素对象
         * @param headerElement 目标报头元素
         * @return 为 true 表示这是一次插入操作， 为 false 则表示这是一次更改操作
         */
        bool setHeader(const HttpHeaderElement::Ptr &headerElement) noexcept;

        /**
         * 获取 “Accept” 值
         * @return “Accept” 值
         */
        string getAccept() noexcept;
        /**
         * 获取 “Accept-Encoding” 值
         * @return “Accept-Encoding” 值
         */
        string getAcceptEncoding() noexcept;
        /**
         * 获取 “Accept-Language” 值
         * @return “Accept-Language” 值
         */
        string getAcceptLanguage() noexcept;
        /**
         * 获取 “Content-Length” 值
         * @return “Content-Length” 值
         */
        ssize_t getContentLength() noexcept;
        /**
         * 获取 “Content-Type” 值
         * @return “Content-Type” 值
         */
        string getContentType() noexcept;
        /**
         * 获取 “Connection” 值
         * @return “Connection” 值
         */
        string getConnection() noexcept;
        /**
         * 获取 “Host” 值
         * @return “Host” 值
         */
        string getHost() noexcept;
        /**
         * 获取 “Pragma” 值
         * @return “Pragma” 值
         */
        string getPragma() noexcept;
        /**
         * 获取 “User-Agent” 值
         * @return “User-Agent” 值
         */
        string getUserAgent() noexcept;
        /**
         * 获取 “Server” 值
         * @return “Server” 值
         */
        string getServer() noexcept;
        /**
         * 获取 “Location” 值
         * @return “Location” 值
         */
        string getLocation() noexcept;
        /**
         * 获取 “Date” 值
         * @return “Date” 值
         */
        time_t getDate() noexcept;
        /**
         * 获取 “Last-Modified” 值
         * @return “Last-Modified” 值
         */
        time_t getLastModified() noexcept;
        /**
         * 获取 “Range” 值
         * @return “Range” 值
         */
        HttpRange::Ptr getRange() noexcept;


        /**
         * 设置 “Accept” 值
         * @param value “Accept” 值
         */
        void setAccept(const string &value) noexcept;
        /**
         * 设置 “Accept-Encoding” 值
         * @param value “Accept-Encoding” 值
         */
        void setAcceptEncoding(const string &value) noexcept;
        /**
         * 设置 “Accept-Language” 值
         * @param value “Accept-Language” 值
         */
        void setAcceptLanguage(const string &value) noexcept;
        /**
         * 设置 “Content-Language” 值
         * @param value “Content-Language” 值
         */
        void setContentLength(ssize_t value) noexcept;
        /**
         * 设置 “Content-Type” 值
         * @param value “Content-Type” 值
         */
        void setContentType(const string &value) noexcept;
        /**
         * 设置 “Connection” 值
         * @param value “Connection” 值
         */
        void setConnection(const string &value) noexcept;
        /**
         * 设置 “Pragma” 值
         * @param value “Pragma” 值
         */
        void setHost(const string &value) noexcept;
        /**
         * 设置 “User-Agent” 值
         * @param value “User-Agent” 值
         */
        void setPragma(const string &value) noexcept;
        /**
         * 设置 “User-Agent” 值
         * @param value “User-Agent” 值
         */
        void setUserAgent(const string &value) noexcept;
        /**
         * 设置 “Server” 值
         * @param value “Server” 值
         */
        void setServer(const string &value) noexcept;
        /**
         * 设置 “Location” 值
         * @param value “Location” 值
         */
        void setLocation(const string &value) noexcept;
        /**
         * 设置 “Date” 值
         * @param value “Date” 值
         */
        void setDate(time_t &value) noexcept;
        /**
         * 设置 “Last-Modified” 值
         * @param value “Last-Modified”
         */
        void setLastModified(time_t &value) noexcept;
        /**
         * 设置 “Content-Range” 值
         * @param startPos 文件起点
         * @param endPos 文件终点
         * @param size 文件大小
         */
        void setContentRange(ssize_t startPos, ssize_t endPos, ssize_t size) noexcept;

        /**
         * 获取报头集合
         * @return 报头集合
         */
        std::map<string, HttpHeaderElement::Ptr, strcmp<>> getElements() const noexcept { return this->elements; }

    public:
        static string Time2String(time_t &t) noexcept;
        static time_t String2Time(const string &str) noexcept;

    protected:
        /**
         * Http 版本
         */
        int version{11};
        /**
         * Http 报文
         */
        string body{};
        /**
         * 报头元素 map
         */
        std::map<string, HttpHeaderElement::Ptr, strcmp<>> elements;
    };
}// namespace MyEngine