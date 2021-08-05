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

HttpHeader HttpRequest::getHeader(const string &key) {
    for (auto i : headers) {
        if (key == i.key) {
            return i;
        }
    }
    return {};
}

void HttpRequest::setHeader(const HttpHeader &header) {
    headers.emplace_back(header);
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

    if(version == 11){
        stream << " HTTP/1.1\r\n";
    }

    for (const auto &i : headers) {
        stream << i.dump().str();
    }
    stream << "\r\n";

    if(!body.empty()){
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

void HttpRequest::setBody(const string &body) {
    this->body = body;
}

void MyEngine::HttpRequest::setMethod(HttpMethod method) {
    this->method = method;
}

void MyEngine::HttpRequest::setUrl(const string &url) {
    this->url = url;
}

void MyEngine::HttpRequest::setQueryString(const string &query_string) {
    this->query_string = query_string;
}

void MyEngine::HttpRequest::setHttpVersion(int version) {
    this->version = version;
}
