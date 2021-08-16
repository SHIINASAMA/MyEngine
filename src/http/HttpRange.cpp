/**
 * @file HttpRange.cpp
 * @author kaoru
 * @date 2021/8/15
 * @version 0.1
 * @brief Http 文件分块解析实现
 */
#include <http/HttpParser.h>
#include <http/HttpRange.h>
#include <sstream>

/**
 * bytes=0-100,500-800,-700,500-
 * 0-100 0 至 100 字节 0，100
 * -700  最后 700 字节 -1，700
 * 500-  500至最后     500，-1
 */

MyEngine::HttpRange::HttpRange(const string &str) {
    auto dataStr = HttpParser::Split(str, "=")[1];
    auto rs      = HttpParser::Split(dataStr, ",");
    for (const auto &i : rs) {
        if (i[0] == '-') {
            ssize_t endPos = strtol(i.c_str() + 1, nullptr, 10);
            this->ranges.emplace_back(MAKE_RANGE(-1, endPos));
        } else {
            auto pair = HttpParser::Split(i, "-");
            if (pair.size() == 1) {
                ssize_t startPos = strtol(pair[0].c_str(), nullptr, 10);
                this->ranges.emplace_back(MAKE_RANGE(startPos, -1));
            } else {
                ssize_t startPos = strtol(pair[0].c_str(), nullptr, 10);
                ssize_t endPos   = strtol(pair[1].c_str(), nullptr, 10);
                this->ranges.emplace_back(MAKE_RANGE(startPos, endPos));
            }
        }
    }
}

string MyEngine::HttpRange::MakeContentRange(ssize_t startPos, ssize_t endPos, ssize_t size) {
    std::stringstream stream;
    stream << "bytes " << startPos << "-" << endPos << "/" << size;
    return stream.str();
}