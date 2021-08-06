#include <http/Http.h>
#include <sstream>

MyEngine::HttpHeader::HttpHeader(const string &key, const string &value) {
    this->key   = key;
    this->value = value;
}

std::stringstream MyEngine::HttpHeader::dump() const {
    std::stringstream stream;
    stream << key << ": " << value << "\r\n";
    return stream;
}
