/**
 * @file HttpHeader.cpp
 * @author kaoru
 * @date 2021.8.8
 * @brief Http 报头定义
 * @version 0.1
 */
#include <http/HttpHeader.h>
#include <memory>
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
    SET_STRING("Accept");
}

void MyEngine::HttpHeader::setAcceptEncoding(const string &value) {
    SET_STRING("Accept-Encoding");
}

void MyEngine::HttpHeader::setAcceptLanguage(const string &value) {
    SET_STRING("Accept-Language");
}

void MyEngine::HttpHeader::setContentLength(ssize_t value) {
    this->setHeader(make_shared<HttpHeaderElement>("Content-Length", std::to_string(value)));
}

void MyEngine::HttpHeader::setContentType(const string &value) {
    SET_STRING("Content-Type");
}

void MyEngine::HttpHeader::setConnection(const string &value) {
    SET_STRING("Connection");
}

void MyEngine::HttpHeader::setHost(const string &value) {
    SET_STRING("Host");
}

void MyEngine::HttpHeader::setPragma(const string &value) {
    SET_STRING("Pragma");
}

void MyEngine::HttpHeader::setUserAgent(const string &value) {
    SET_STRING("User-Agent");
}

void MyEngine::HttpHeader::setServer(const string &value) {
    SET_STRING("Server");
}

void MyEngine::HttpHeader::setLocation(const string &value) {
    SET_STRING("Location");
}

#undef SET_STRING

time_t MyEngine::HttpHeader::getDate() {
    HttpHeaderElement::Ptr element = this->getHeader("Date");
    if (element) {
        return String2Time(element->value);
    }
    return 0;
}

void MyEngine::HttpHeader::setDate(time_t &value) {
    string time = Time2String(value);
    this->setHeader(MAKE_ELEMENT("Date", time));
}

string MyEngine::HttpHeader::Time2String(time_t &t) {
    auto tm = localtime(&t);
    char buffer[64];
    strftime(buffer, 64, "%a, %d %b %Y %X %Z", tm);
    return {buffer};
}

time_t MyEngine::HttpHeader::String2Time(const string &str) {
    tm tm{0};
    strptime(str.c_str(), "%a, %d %b %Y %X %Z", &tm);
    return mktime(&tm);
}

time_t MyEngine::HttpHeader::getLastModified() {
    HttpHeaderElement::Ptr element = this->getHeader("Last-Modified");
    if (element) {
        return String2Time(element->value);
    }
    return 0;
}

void MyEngine::HttpHeader::setLastModified(time_t &value) {
    string time = Time2String(value);
    this->setHeader(MAKE_ELEMENT("Last-Modified", time));
}

MyEngine::HttpRange::Ptr MyEngine::HttpHeader::getRange() {
    HttpHeaderElement::Ptr element = this->getHeader("Range");
    if (element) {
        return make_shared<HttpRange>(element->value);
    }
    return nullptr;
}

void MyEngine::HttpHeader::setContentRange(ssize_t startPos, ssize_t endPos, ssize_t size) {
    setHeader(MAKE_ELEMENT("Content-Range", HttpRange::MakeContentRange(startPos, endPos, size)));
}
