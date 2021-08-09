/**
 * @file HttpRequest.cpp
 * @author kaoru
 * @date 2021.8.8
 * @brief Http 请求实现
 * @version 0.1
 */
#include <http/HttpRequest.h>
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

string HttpRequest::dump() const {
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

    for (const auto &i : elements) {
        stream << i.second->dump();
    }
    stream << "\r\n";

    if (!body.empty()) {
        stream << body;
    }
    return stream.str();
}

MyEngine::HttpRequest::~HttpRequest() {
    this->elements.clear();
}

#undef SET_STRING
