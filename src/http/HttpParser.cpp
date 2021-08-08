#include <cassert>
#include <cstring>
#include <http/HttpParser.h>
#include <sstream>

#define BUFFER_MAX_LENGTH 1024

using std::string;

bool MyEngine::HttpParser::RequestParser(TcpClient &sock, HttpRequest *request) {
    char buffer[BUFFER_MAX_LENGTH]{0};
    ssize_t length;

#pragma region "METHOD URL VERSION \r\n"
    length = GetLine(sock, buffer, BUFFER_MAX_LENGTH);
    if (length == -1) {
        return false;
    }
    auto v = Split(buffer, " ");
    if (v[0] == "GET") {
        request->setMethod(HttpMethod::GET);
    } else if (v[0] == "POST") {
        request->setMethod(HttpMethod::POST);
    } else {
        request->setMethod(HttpMethod::NONSUPPORT);
    }

    auto url = Split(v[1], "?");
    request->setUrl(url[0]);
    if (url.size() == 2) {
        request->setQueryString(url[1]);
    }

    if (v[2] == "HTTP/1.1\n") {
        request->setHttpVersion(11);
    } else {
        request->setHttpVersion(-1);
        return false;
    }
#pragma endregion
#pragma region HEADERS
    ssize_t body_length = 0;
    while (true) {
        length = GetLine(sock, buffer, BUFFER_MAX_LENGTH);
        if (length == -1) {
            break;
        }
        auto argv = Split(buffer, ": ");
        if (argv[0] == "\n") {
            break;
        } else if (strcasecmp("content-length", argv[0].c_str()) == 0) {
            body_length = strtol(argv[1].c_str(), nullptr, 10);
        }
        request->setHeader(new HttpHeader{argv[0], argv[1].substr(0, argv[1].length() - 1)});
    }
#pragma endregion
#pragma region BODY
    if (body_length != 0) {
        std::stringstream stream;
        while (true) {
            if (body_length == 0) {
                break;
            }
            length = sock.recv(buffer, BUFFER_MAX_LENGTH, 0);
            stream.write(buffer, length);
            body_length -= length;
        }
        request->setBody(stream.str());
    }
#pragma endregion
    return true;
}

bool MyEngine::HttpParser::ResponseParser(TcpClient &sock, HttpResponse *response) {
    char buffer[BUFFER_MAX_LENGTH]{0};
    ssize_t length;

#pragma "VERSION STATUS_CODE DES"
    length = GetLine(sock, buffer, BUFFER_MAX_LENGTH);
    if (length == -1) {
        return false;
    }
    auto v = Split(buffer, " ");
    if (v[0] == "HTTP/1.1") {
        response->setHttpVersion(11);
    } else {
        response->setHttpVersion(-1);
    }
    response->setStateCode((int) strtol(v[1].c_str(), nullptr, 10));
#pragma endregion
#pragma HEADSERS
    ssize_t body_length = 0;
    while (true) {
        length = GetLine(sock, buffer, BUFFER_MAX_LENGTH);
        if (length == -1) {
            break;
        }
        auto argv = Split(buffer, ": ");
        if (argv[0] == "\n") {
            break;
        } else if (strcasecmp("content-length", argv[0].c_str()) == 0) {
            body_length = strtol(argv[1].c_str(), nullptr, 10);
        }
        response->setHeader(new HttpHeader{argv[0], argv[1].substr(0, argv[1].length() - 1)});
    }
#pragma endregion
#pragma region BODY
    if (body_length != 0) {
        std::stringstream stream;
        while (true) {
            if (body_length == 0) {
                break;
            }
            length = sock.recv(buffer, BUFFER_MAX_LENGTH, 0);
            stream.write(buffer, length);
            body_length -= length;
        }
        response->setBody(stream.str());
    }
#pragma endregion
    return true;
}

ssize_t MyEngine::HttpParser::GetLine(MyEngine::TcpClient &sock, char *buf, int size) {
    ssize_t i = 0;
    ssize_t n;

    char c = '\0';
    while (true) {
        n = sock.recv(&c, 1, 0);
        if (n == -1) {
            return -1;
        }

        if (c != '\r') {
            buf[i] = c;
            i++;
        } else {
            buf[i] = '\n';
            sock.recv(&c, 1, 0);
            break;
        }
    }
    buf[i + 1] = '\0';

    return i;
}

std::vector<std::string> MyEngine::HttpParser::Split(const std::string &str, const std::string &pattern) {
    std::vector<std::string> res;
    std::string::size_type pos1, pos2;
    pos2 = str.find(pattern);
    pos1 = 0;
    while (std::string::npos != pos2) {
        res.push_back(str.substr(pos1, pos2 - pos1));
        pos1 = pos2 + pattern.size();
        pos2 = str.find(pattern, pos1);
    }
    if (pos1 != str.length())
        res.push_back(str.substr(pos1));

    return res;
}
