#pragma once
#include <cstring>
#include <map>
#include <sstream>
#include <string>

using std::string;

namespace MyEngine {

    template<class T = std::string>
    struct strcmp {
        bool operator()(const T &lv, const T &rv) const {
            return strcasecmp(lv.c_str(), rv.c_str()) < 0;
        }
    };

    enum class HttpMethod {
        GET,
        POST,
        NONSUPPORT
    };

    class HttpHeader {
    public:
        string key{};
        string value{};
        HttpHeader() = default;
        HttpHeader(const string &key, const string &value);
        std::stringstream dump() const;
    };

    class HttpRequest {
    public:
        HttpRequest()                     = default;
        HttpRequest(const HttpRequest &)  = delete;
        HttpRequest(const HttpRequest &&) = delete;
        HttpRequest(HttpMethod method, const string &url, const string &query_string, int version);
        ~HttpRequest();

        bool getHeader(const string &key, HttpHeader *header);
        /**
         * 设置 Http Header
         * @param header 目标 Header
         * @return 为 true 表示这是一次插入操作， 为 false 则表示这是一次更改操作
         */
        bool setHeader(HttpHeader *header);

        HttpMethod getMethod() const;
        void setMethod(HttpMethod _method);
        string getUrl() const;
        void setUrl(const string &_url);
        string getQueryString() const;
        void setQueryString(const string &_query_string);
        int getHttpVersion() const;
        void setHttpVersion(int _version);
        string getBody() const;
        void setBody(const string &_body);

        string getAccept();
        string getAcceptEncoding();
        string getAcceptLanguage();
        ssize_t getContentLength();
        string getContentType();
        string getConnection();
        string getHost();
        string getPragma();
        string getUserAgent();
        string getServer();

        void setAccept(const string &value);
        void setAcceptEncoding(const string &value);
        void setAcceptLanguage(const string &value);
        void setContentLength(ssize_t value);
        void setContentType(const string &value);
        void setConnection(const string &value);
        void setHost(const string &value);
        void setPragma(const string &value);
        void setUserAgent(const string &value);
        void setServer(const string &value);

        std::stringstream dump() const;

        const std::map<string, HttpHeader *, strcmp<>> &getHeaders() const;

    protected:
        HttpMethod method = HttpMethod::NONSUPPORT;
        int version       = 11;
        string url{};
        string query_string{};
        string body{};
        std::map<string, HttpHeader *, strcmp<>> headers;
    };

    class HttpResponse {
    public:
        HttpResponse()                      = default;
        HttpResponse(const HttpResponse &)  = delete;
        HttpResponse(const HttpResponse &&) = delete;
        HttpResponse(int version, int state_code);
        ~HttpResponse();

        bool getHeader(const string &key, HttpHeader *header);
        /**
         * 设置 Http Header
         * @param header 目标 Header
         * @return 为 true 表示这是一次插入操作， 为 false 则表示这是一次更改操作
         */
        bool setHeader(HttpHeader *header);

        int getHttpVersion() const;
        void setHttpVersion(int version);
        int getStateCode() const;
        void setStateCode(int code);
        string getBody() const;
        void setBody(const string &body);

        string getAccept();
        string getAcceptEncoding();
        string getAcceptLanguage();
        ssize_t getContentLength();
        string getContentType();
        string getConnection();
        string getHost();
        string getPragma();
        string getUserAgent();
        string getServer();

        void setAccept(const string &value);
        void setAcceptEncoding(const string &value);
        void setAcceptLanguage(const string &value);
        void setContentLength(ssize_t value);
        void setContentType(const string &value);
        void setConnection(const string &value);
        void setHost(const string &value);
        void setPragma(const string &value);
        void setUserAgent(const string &value);
        void setServer(const string &value);

        std::stringstream dump() const;

        const std::map<string, HttpHeader *, strcmp<>> &getHeaders() const;

    protected:
        int version{11};
        int state_code{200};
        string body{};
        std::map<string, HttpHeader *, strcmp<>> headers;
    };
}// namespace MyEngine