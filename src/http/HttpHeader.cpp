#include <http/Http.h>
#include <sstream>

MyEngine::HttpHeader::HttpHeader(::string &key, ::string &value) {
    this->key   = std::move(key);
    this->value = std::move(value);
}

std::stringstream MyEngine::HttpHeader::dump() const {
    std::stringstream stream;
    stream << key << ": " << value << "\r\n";
    return stream;
}
