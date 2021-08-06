#pragma once
#include <string>
#include <vector>

using std::string;

namespace MyEngine {

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

        HttpHeader getHeader(const string &key);
        void setHeader(const HttpHeader &header);

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

        const std::vector<HttpHeader> &getHeaders() const;

    protected:
        HttpMethod method = HttpMethod::NONSUPPORT;
        int version       = 11;
        string url;
        string query_string;
        string body;
        std::vector<HttpHeader> headers;
    };

    class HttpResponse {
    public:
        HttpResponse()                      = default;
        HttpResponse(const HttpResponse &)  = delete;
        HttpResponse(const HttpResponse &&) = delete;
        HttpResponse(int version, int state_code);
        ~HttpResponse() = default;

        HttpHeader getHeader(const string &key);
        void setHeader(const HttpHeader &header);

        int getHttpVersion() const;
        void setHttpVersion(int version);
        int getStateCode() const;
        void setStateCode(int code);
        string getBody() const;
        void setBody(const string &body);

        std::stringstream dump() const;

        const std::vector<HttpHeader> &getHeaders() const;

    protected:
        int version{11};
        int state_code{200};
        string body;
        std::vector<HttpHeader> headers;
    };
}// namespace MyEngine