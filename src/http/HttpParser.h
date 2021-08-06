#include <http/Http.h>
#include <socket/TcpClient.h>

namespace MyEngine{

    class HttpParser{
    public:
        static bool RequestParser(TcpClient &sock, HttpRequest *request);
        static bool ResponseParser(TcpClient &sock, HttpResponse *response);

    private:
        static ssize_t GetLine(TcpClient &sock, char *buf, int size);
        static std::vector<std::string> Split(const std::string &string, const std::string &pattern);
    };
}