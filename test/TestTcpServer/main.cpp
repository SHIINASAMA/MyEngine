#include <cstdio>
#include <socket/TcpServer.h>

using namespace MyEngine;

const char string[32] = {"This message from server\0"};

int main() {
    auto server = TcpServer();
    server.createTcpSocket();
    server.bind();
    server.listen(10);
    auto client = server.accept();
    auto len = client.send(string, 32, 0);
    client.close();
    printf("send message %ld : %s\n", len, string);
    return 0;
}