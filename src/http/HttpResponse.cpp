/**
 * @file HttpResponse.h
 * @author kaoru
 * @date 2021.8.8
 * @brief Http 回报实现
 * @version 0.1
 */
#include <http/HttpResponse.h>
#include <sstream>

using MyEngine::HttpHeader;
using MyEngine::HttpMethod;
using std::string;

MyEngine::HttpResponse::HttpResponse(int version, int stateCode) noexcept {
    this->version    = version;
    this->stateCode  = stateCode;
}

std::string MyEngine::HttpResponse::dump() const noexcept {
    std::stringstream stream;
    if (version == 11) {
        stream << "HTTP/1.1 ";
    }
    stream << stateCode << "\r\n";

    for (const auto &i : elements) {
        stream << i.second->dump();
    }
    stream << "\r\n";

    if (!body.empty()) {
        stream << body;
    }
    return stream.str();
}