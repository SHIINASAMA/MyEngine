#include <http/Http.h>
#include <sstream>

using MyEngine::HttpHeader;
using MyEngine::HttpMethod;
using MyEngine::HttpRequest;
using std::string;

MyEngine::HttpResponse::HttpResponse(int version, int state_code) {
    this->version = version;
    this->state_code = state_code;
}

bool MyEngine::HttpResponse::getHeader(const string &key, HttpHeader *header) {
    auto i = headers.find(key);
    if(i != headers.end()){
        *header = i->second;
        return true;
    }else{
        return false;
    }
}

bool MyEngine::HttpResponse::setHeader(const HttpHeader &header) {
    auto i = headers.find(header.key);
    if(i != headers.end()){
        i->second = header;
        return false;
    }else{
        headers.emplace(header.key, header);
        return true;
    }
}

int MyEngine::HttpResponse::getHttpVersion() const {
    return version;
}

void MyEngine::HttpResponse::setHttpVersion(int version) {
    this->version = version;
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

void MyEngine::HttpResponse::setBody(const string &body) {
    this->body = body;
}

std::stringstream MyEngine::HttpResponse::dump() const {
    std::stringstream stream;
    if(version == 11){
        stream << "HTTP/1.1 ";
    }
    stream << state_code << "\r\n";

    for (const auto &i : headers) {
        stream << i.second.dump().str();
    }
    stream << "\r\n";

    if(!body.empty()){
        stream << body;
    }
    return stream;
}

const std::map<string, HttpHeader, MyEngine::strcmp<>> &MyEngine::HttpResponse::getHeaders() const {
    return headers;
}
