#pragma once
#include <http/HttpServer.h>
#include <servlet/ServletContext.h>

namespace MyEngine {

    class App : public HttpServer {
    public:
        static void CreateApp(const std::string &ipaddress, unsigned port);
        static App *GetApp();

        void regServlet(const string &servlet_name, const string &url, Servlet *servlet);
        [[noreturn]] void exec();

    private:
        App(const string &ipaddress, unsigned short port);
        ~App() override;
        static App *app;
        std::map<string, ServletContext, strcmp<>> servletMap;

        auto getMap() const;
        void *onRequest(TcpClient client);
    };
}// namespace MyEngine