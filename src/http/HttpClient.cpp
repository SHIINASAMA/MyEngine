#include <http/HttpClient.h>
#include <http/HttpParser.h>
#include <sstream>

using namespace MyEngine;

bool MyEngine::HttpClient::Get(const string &ipaddress, unsigned short port, HttpRequest &request, HttpResponse *response) {
    request.setMethod(HttpMethod::GET);
    request.setHttpVersion(11);
    auto baseString = request.dump().str();
    TcpClient client(ipaddress.c_str(), port);
    client.createTcpSocket();
    if (client.connect()) {
        auto send_len = client.send(baseString.c_str(), baseString.length(), 0);
        if (send_len != baseString.length()) {
            client.close();
            return false;
        }
        if (!HttpParser::ResponseParser(client, response)) {
            client.close();
            return false;
        }
        client.close();
        return true;
    } else {
        return false;
    }
}
bool HttpClient::Post(const string &ipaddress, unsigned short port, HttpRequest &request, HttpResponse *response) {
    request.setMethod(HttpMethod::POST);
    request.setHttpVersion(11);
    auto baseString = request.dump().str();
    TcpClient client(ipaddress.c_str(), port);
    client.createTcpSocket();
    if (client.connect()) {
        auto send_len = client.send(baseString.c_str(), baseString.length(), 0);
        if (send_len != baseString.length()) {
            client.close();
            return false;
        }
        if (!HttpParser::ResponseParser(client, response)) {
            client.close();
            return false;
        }
        client.close();
        return true;
    } else {
        return false;
    }
}