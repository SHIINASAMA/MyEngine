/**
 * @file HttpHeader.cpp
 * @author kaoru
 * @date 2021.8.8
 * @brief Http 报头元素
 * @version 0.1
 */
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
