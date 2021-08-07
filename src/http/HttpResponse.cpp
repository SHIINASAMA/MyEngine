#include <http/Http.h>
#include <sstream>

using MyEngine::HttpHeader;
using MyEngine::HttpMethod;
using MyEngine::HttpRequest;
using std::string;

MyEngine::HttpResponse::HttpResponse(int version, int state_code) {
    this->version    = version;
    this->state_code = state_code;
}

bool MyEngine::HttpResponse::getHeader(const string &key, HttpHeader *header) {
    auto i = headers.find(key);
    if (i != headers.end()) {
        *header = *i->second;
        return true;
    } else {
        return false;
    }
}

bool MyEngine::HttpResponse::setHeader(HttpHeader *header) {
    auto i = headers.find(header->key);
    if (i != headers.end()) {
        i->second->value = header->value;
        return false;
    } else {
        headers.emplace(header->key, header);
        return true;
    }
}

int MyEngine::HttpResponse::getHttpVersion() const {
    return version;
}

void MyEngine::HttpResponse::setHttpVersion(int _version) {
    this->version = _version;
}

int MyEngine::HttpResponse::getStateCode() const {
    return state_code;
}

void MyEngine::HttpResponse::setStateCode(int code) {
    this->state_code = code;
}

string MyEngine::HttpResponse::getBody() const {
    return body;
}

void MyEngine::HttpResponse::setBody(const string &_body) {
    this->body = _body;
}

std::stringstream MyEngine::HttpResponse::dump() const {
    std::stringstream stream;
    if (version == 11) {
        stream << "HTTP/1.1 ";
    }
    stream << state_code << "\r\n";

    for (const auto &i : headers) {
        stream << i.second->dump().str();
    }
    stream << "\r\n";

    if (!body.empty()) {
        stream << body;
    }
    return stream;
}

const std::map<string, HttpHeader *, MyEngine::strcmp<>> &MyEngine::HttpResponse::getHeaders() const {
    return headers;
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

string MyEngine::HttpResponse::getAccept() {
    GET_STRING("accept");
}

string MyEngine::HttpResponse::getContentType() {
    GET_STRING("content-type");
}

ssize_t MyEngine::HttpResponse::getContentLength() {
    HttpHeader header;
    if (this->getHeader("content-length", &header)) {
        return strtol(header.value.c_str(), nullptr, 0);
    } else {
        return -1;
    }
}

string MyEngine::HttpResponse::getAcceptEncoding() {
    GET_STRING("Accept-Encoding");
}

string MyEngine::HttpResponse::getAcceptLanguage() {
    GET_STRING("Accept-Language");
}

string MyEngine::HttpResponse::getConnection() {
    GET_STRING("Connection");
}

string MyEngine::HttpResponse::getHost() {
    GET_STRING("Host");
}

string MyEngine::HttpResponse::getPragma() {
    GET_STRING("Pragma");
}

string MyEngine::HttpResponse::getUserAgent() {
    GET_STRING("User-Agent");
}

string MyEngine::HttpResponse::getServer() {
    GET_STRING("server");
}

#undef GET_STRING

#define SET_STRING(key) \
    this->setHeader(new HttpHeader{key, value});

void MyEngine::HttpResponse::setAccept(const string &value) {
    SET_STRING("accept");
}

void MyEngine::HttpResponse::setAcceptEncoding(const string &value) {
    SET_STRING("accept-encoding");
}

void MyEngine::HttpResponse::setAcceptLanguage(const string &value) {
    SET_STRING("accept-language");
}

void MyEngine::HttpResponse::setContentLength(ssize_t value) {
    this->setHeader(new HttpHeader{"content-length", std::to_string(value)});
}

void MyEngine::HttpResponse::setContentType(const string &value) {
    SET_STRING("content-type");
}

void MyEngine::HttpResponse::setConnection(const string &value) {
    SET_STRING("connection");
}

void MyEngine::HttpResponse::setHost(const string &value) {
    SET_STRING("host");
}

void MyEngine::HttpResponse::setPragma(const string &value) {
    SET_STRING("pragma");
}

void MyEngine::HttpResponse::setUserAgent(const string &value) {
    SET_STRING("user-agent");
}

void MyEngine::HttpResponse::setServer(const string &value) {
    SET_STRING("server");
}

MyEngine::HttpResponse::~HttpResponse() {
    for(const auto& header : headers){
        delete header.second;
    }
}

#undef SET_STRING
