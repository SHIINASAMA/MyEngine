#include <cstdio>
#include <socket/TcpClient.h>

using namespace MyEngine;

int main(){
    char string[32];
    auto client = TcpClient("127.0.0.1", 80);
    client.createTcpSocket();
    client.connect();
    auto len = client.recv(string, 32, 0);
    client.close();
    printf("recv message %ld : %s\n", len, string);
    return 0;
}