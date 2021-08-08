/**
 * @file HttpRequest.cpp
 * @author kaoru
 * @date 2021.8.8
 * @brief Http 请求实现
 * @version 0.1
 */
#include <http/Http.h>
#include <sstream>

using MyEngine::HttpHeader;
using MyEngine::HttpMethod;
using MyEngine::HttpRequest;
using std::string;

MyEngine::HttpRequest::HttpRequest(HttpMethod method, const string &url, const string &query_string, int version) {
    this->method       = method;
    this->url          = url;
    this->query_string = query_string;
    this->version      = version;
}

bool HttpRequest::getHeader(const string &key, HttpHeader *header) {
    auto i = headers.find(key);
    if (i != headers.end()) {
        *header = *i->second;
        return true;
    } else {
        return false;
    }
}

bool HttpRequest::setHeader(HttpHeader *header) {
    auto i = headers.find(header->key);
    if (i != headers.end()) {
        i->second->value = header->value;
        return false;
    } else {
        headers.emplace(header->key, header);
        return true;
    }
}

std::stringstream HttpRequest::dump() const {
    std::stringstream stream;
    if (method == HttpMethod::GET) {
        stream << "GET ";
    } else if (method == HttpMethod::POST) {
        stream << "POST ";
    }

    stream << url;
    if (!query_string.empty()) {
        stream << "?" << query_string;
    }

    if (version == 11) {
        stream << " HTTP/1.1\r\n";
    }

    for (const auto &i : headers) {
        stream << i.second->dump().str();
    }
    stream << "\r\n";

    if (!body.empty()) {
        stream << body;
    }
    return stream;
}

HttpMethod MyEngine::HttpRequest::getMethod() const {
    return method;
}

string HttpRequest::getUrl() const {
    return url;
}

string HttpRequest::getQueryString() const {
    return query_string;
}

int HttpRequest::getHttpVersion() const {
    return version;
}

string HttpRequest::getBody() const {
    return body;
}

void HttpRequest::setBody(const string &_body) {
    this->body = _body;
}

void MyEngine::HttpRequest::setMethod(HttpMethod _method) {
    this->method = _method;
}

void MyEngine::HttpRequest::setUrl(const string &_url) {
    this->url = _url;
}

void MyEngine::HttpRequest::setQueryString(const string &_query_string) {
    this->query_string = _query_string;
}

void MyEngine::HttpRequest::setHttpVersion(int _version) {
    this->version = _version;
}

const std::map<string, HttpHeader *, MyEngine::strcmp<>> &MyEngine::HttpRequest::getHeaders() const {
    return this->headers;
}

#define UNKNOWN \
    { "UNKNOWN" }

#define GET_STRING(key)                  \
    HttpHeader header;                   \
    if (this->getHeader(key, &header)) { \
        return header.value;             \
    } else {                             \
        return UNKNOWN;                  \
    }

string MyEngine::HttpRequest::getAccept() {
    GET_STRING("accept");
}

string MyEngine::HttpRequest::getContentType() {
    GET_STRING("content-type");
}

ssize_t MyEngine::HttpRequest::getContentLength() {
    HttpHeader header;
    if (this->getHeader("content-length", &header)) {
        return strtol(header.value.c_str(), nullptr, 0);
    } else {
        return -1;
    }
}

string MyEngine::HttpRequest::getAcceptEncoding() {
    GET_STRING("Accept-Encoding");
}

string MyEngine::HttpRequest::getAcceptLanguage() {
    GET_STRING("Accept-Language");
}

string MyEngine::HttpRequest::getConnection() {
    GET_STRING("Connection");
}

string MyEngine::HttpRequest::getHost() {
    GET_STRING("Host");
}

string MyEngine::HttpRequest::getPragma() {
    GET_STRING("Pragma");
}

string MyEngine::HttpRequest::getUserAgent() {
    GET_STRING("User-Agent");
}

string MyEngine::HttpRequest::getServer() {
    GET_STRING("server");
}

#undef GET_STRING

#define SET_STRING(key) \
    this->setHeader(new HttpHeader{key, value});

void MyEngine::HttpRequest::setAccept(const string &value) {
    SET_STRING("accept");
}

void MyEngine::HttpRequest::setAcceptEncoding(const string &value) {
    SET_STRING("accept-encoding");
}

void MyEngine::HttpRequest::setAcceptLanguage(const string &value) {
    SET_STRING("accept-language");
}

void MyEngine::HttpRequest::setContentLength(ssize_t value) {
    this->setHeader(new HttpHeader{"content-length", std::to_string(value)});
}

void MyEngine::HttpRequest::setContentType(const string &value) {
    SET_STRING("content-type");
}

void MyEngine::HttpRequest::setConnection(const string &value) {
    SET_STRING("connection");
}

void MyEngine::HttpRequest::setHost(const string &value) {
    SET_STRING("host");
}

void MyEngine::HttpRequest::setPragma(const string &value) {
    SET_STRING("pragma");
}

void MyEngine::HttpRequest::setUserAgent(const string &value) {
    SET_STRING("user-agent");
}

void MyEngine::HttpRequest::setServer(const string &value) {
    SET_STRING("server");
}

MyEngine::HttpRequest::~HttpRequest() {
    for(const auto& header : headers){
        delete header.second;
    }
}

#undef SET_STRING
