#pragma ide diagnostic ignored "EmptyDeclOrStmt"
/**
 * @file HttpHeader.cpp
 * @author kaoru
 * @date 2021.8.8
 * @brief Http 报头定义
 * @version 0.1
 */
#include <http/HttpHeader.h>
#include <sstream>

MyEngine::HttpHeaderElement::HttpHeaderElement(const string &key, const string &value) {
    this->key   = key;
    this->value = value;
}

string MyEngine::HttpHeaderElement::dump() const {
    std::stringstream stream;
    stream << key << ": " << value << "\r\n";
    return stream.str();
}

MyEngine::HttpHeaderElement::Ptr MyEngine::HttpHeader::getHeader(const string &key) {
    auto i = elements.find(key);
    if (i != elements.end()) {
        return i->second;
    } else {
        return nullptr;
    }
}

bool MyEngine::HttpHeader::setHeader(const MyEngine::HttpHeaderElement::Ptr &headerElement) {
    auto i = elements.find(headerElement->key);
    if (i != elements.end()) {
        i->second->value = headerElement->value;
        return false;
    } else {
        elements.emplace(headerElement->key, headerElement);
        return true;
    }
}

MyEngine::HttpHeader::~HttpHeader() {
    this->elements.clear();
}

#define UNKNOWN \
    { "UNKNOWN" }

#define GET_STRING(key)                                    \
    HttpHeaderElement::Ptr element = this->getHeader(key); \
    if (element) {                                         \
        return element->value;                             \
    } else {                                               \
        return UNKNOWN;                                    \
    }

string MyEngine::HttpHeader::getAccept() {
    GET_STRING("accept");
}

string MyEngine::HttpHeader::getContentType() {
    GET_STRING("content-type");
}

ssize_t MyEngine::HttpHeader::getContentLength() {
    HttpHeaderElement::Ptr element = this->getHeader("content-length");
    if (element) {
        return strtol(element->value.c_str(), nullptr, 0);
    } else {
        return -1;
    }
}

string MyEngine::HttpHeader::getAcceptEncoding() {
    GET_STRING("Accept-Encoding");
}

string MyEngine::HttpHeader::getAcceptLanguage() {
    GET_STRING("Accept-Language");
}

string MyEngine::HttpHeader::getConnection() {
    GET_STRING("Connection");
}

string MyEngine::HttpHeader::getHost() {
    GET_STRING("Host");
}

string MyEngine::HttpHeader::getPragma() {
    GET_STRING("Pragma");
}

string MyEngine::HttpHeader::getUserAgent() {
    GET_STRING("User-Agent");
}

string MyEngine::HttpHeader::getServer() {
    GET_STRING("server");
}

string MyEngine::HttpHeader::getLocation() {
    GET_STRING("Location");
}

#undef GET_STRING

#define SET_STRING(key) \
    this->setHeader(make_shared<HttpHeaderElement>(key, value));

void MyEngine::HttpHeader::setAccept(const string &value) {
    SET_STRING("accept");
}

void MyEngine::HttpHeader::setAcceptEncoding(const string &value) {
    SET_STRING("accept-encoding");
}

void MyEngine::HttpHeader::setAcceptLanguage(const string &value) {
    SET_STRING("accept-language");
}

void MyEngine::HttpHeader::setContentLength(ssize_t value) {
    this->setHeader(make_shared<HttpHeaderElement>("content-length", std::to_string(value)));
}

void MyEngine::HttpHeader::setContentType(const string &value) {
    SET_STRING("content-type");
}

void MyEngine::HttpHeader::setConnection(const string &value) {
    SET_STRING("connection");
}

void MyEngine::HttpHeader::setHost(const string &value) {
    SET_STRING("host");
}

void MyEngine::HttpHeader::setPragma(const string &value) {
    SET_STRING("pragma");
}

void MyEngine::HttpHeader::setUserAgent(const string &value) {
    SET_STRING("user-agent");
}

void MyEngine::HttpHeader::setServer(const string &value) {
    SET_STRING("server");
}

void MyEngine::HttpHeader::setLocation(const string &value) {
    SET_STRING("location");
}

#undef SET_STRING