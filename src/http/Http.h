#pragma once
#include <cstring>
#include <map>
#include <string>

using std::string;

namespace MyEngine {

    template<class T = std::string>
    struct strcmp {
        bool operator()(const T &lv, const T &rv) const {
            return strcasecmp(lv.c_str(), rv.c_str());
        }
    };

    enum class HttpMethod {
        GET,
        POST,
        NONSUPPORT
    };

    class HttpHeader {
    public:
        string key;
        string value;
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
        ~HttpRequest() = default;

        bool getHeader(const string &key, HttpHeader *header);
        /**
         * 设置 Http Header
         * @param header 目标 Header
         * @return 为 true 表示这是一次插入操作， 为 false 则表示这是一次更改操作
         */
        bool setHeader(const HttpHeader &header);

        HttpMethod getMethod() const;
        void setMethod(HttpMethod method);
        string getUrl() const;
        void setUrl(const string &url);
        string getQueryString() const;
        void setQueryString(const string &query_string);
        int getHttpVersion() const;
        void setHttpVersion(int version);
        string getBody() const;
        void setBody(const string &body);

        std::stringstream dump() const;

        const std::map<string, HttpHeader, strcmp<>> &getHeaders() const;

    protected:
        HttpMethod method = HttpMethod::NONSUPPORT;
        int version       = 11;
        string url;
        string query_string;
        string body;
        std::map<string, HttpHeader, strcmp<>> headers;
    };

    class HttpResponse {
    public:
        HttpResponse()                      = default;
        HttpResponse(const HttpResponse &)  = delete;
        HttpResponse(const HttpResponse &&) = delete;
        HttpResponse(int version, int state_code);
        ~HttpResponse() = default;

        bool getHeader(const string &key, HttpHeader *header);
        /**
         * 设置 Http Header
         * @param header 目标 Header
         * @return 为 true 表示这是一次插入操作， 为 false 则表示这是一次更改操作
         */
        bool setHeader(const HttpHeader &header);

        int getHttpVersion() const;
        void setHttpVersion(int version);
        int getStateCode() const;
        void setStateCode(int code);
        string getBody() const;
        void setBody(const string &body);

        std::stringstream dump() const;

        const std::map<string, HttpHeader, strcmp<>> &getHeaders() const;

    protected:
        int version{11};
        int state_code{200};
        string body;
        std::map<string, HttpHeader, strcmp<>> headers;
    };
}// namespace MyEngine