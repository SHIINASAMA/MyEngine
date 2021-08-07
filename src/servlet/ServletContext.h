#pragma once
#include <servlet/Servlet.h>

namespace MyEngine{

    class ServletContext {
    public:
        ServletContext(const string &servlet_name, const string &url, Servlet *servlet);
        virtual ~ServletContext();

        string getName() const;
        string getUrl() const;
        string getServletClassName() const;
        const Servlet &getServlet() const;

        void servletInit();
        void servletService(HttpRequest &request, HttpResponse &response);
        void ServletDestroy();

    private:
        string name;
        string url;
        Servlet *servlet;
    };
}