/**
 * @file HttpClient.cpp
 * @author kaoru
 * @date 2021.8.9
 * @brief Http 客户端实现
 * @version 0.1
 */
#include <http/HttpClient.h>
#include <http/HttpParser.h>
#include <sstream>
#include <utility>

using namespace MyEngine;

bool MyEngine::HttpClient::Get(const string &ipaddress, unsigned short port, const HttpRequest::Ptr& request, HttpResponse::Ptr response) {
    request->setMethod(HttpMethod::GET);
    request->setHttpVersion(11);
    auto baseString = request->dump();
    auto client = make_shared<TcpClient>(ipaddress.c_str(), port);
    client->createTcpSocket();
    if (client->connect()) {
        auto send_len = client->send(baseString.c_str(), baseString.length(), 0);
        if (send_len != baseString.length()) {
            client->close();
            return false;
        }
        if (!HttpParser::ResponseParser(client, std::move(response))) {
            client->close();
            return false;
        }
        client->close();
        return true;
    } else {
        return false;
    }
}

bool HttpClient::Post(const string &ipaddress, unsigned short port, const HttpRequest::Ptr& request, HttpResponse::Ptr response) {
    request->setMethod(HttpMethod::POST);
    request->setHttpVersion(11);
    auto baseString = request->dump();
    auto client = make_shared<TcpClient>(ipaddress.c_str(), port);
    client->createTcpSocket();
    if (client->connect()) {
        auto send_len = client->send(baseString.c_str(), baseString.length(), 0);
        if (send_len != baseString.length()) {
            client->close();
            return false;
        }
        if (!HttpParser::ResponseParser(client, std::move(response))) {
            client->close();
            return false;
        }
        client->close();
        return true;
    } else {
        return false;
    }
}
