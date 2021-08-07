#include <servlet/ServletContext.h>

MyEngine::ServletContext::ServletContext(const string &servlet_name, const string &url, MyEngine::Servlet *servlet) {
    this->name = servlet_name;
    this->url = url;
    this->servlet = servlet;
}

MyEngine::ServletContext::~ServletContext() {
    if(!servlet){
        delete servlet;
    }
}

string MyEngine::ServletContext::getName() const {
    return name;
}

string MyEngine::ServletContext::getUrl() const {
    return url;
}

string MyEngine::ServletContext::getServletClassName() const {
    return servlet->getClassName();
}

const MyEngine::Servlet &MyEngine::ServletContext::getServlet() const {
    return *servlet;
}

void MyEngine::ServletContext::servletInit() {
    servlet->init();
}

void MyEngine::ServletContext::servletService(MyEngine::HttpRequest &request, MyEngine::HttpResponse &response) {
    servlet->service(request, response);
}

void MyEngine::ServletContext::ServletDestroy() {
    servlet->destroy();
}
