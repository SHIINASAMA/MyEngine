/**
 * @file ServletContext.cpp
 * @author kaoru
 * @date 2021.8.8
 * @brief Servlet 上下文类实现
 * @version 0.1
 */
#include <servlet/ServletContext.h>

#include <utility>

MyEngine::ServletContext::ServletContext(const string &servlet_name, const string &url, const MyEngine::Servlet::Ptr &servlet) {
    this->name    = servlet_name;
    this->url     = url;
    this->servlet = servlet;
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

MyEngine::Servlet::Ptr MyEngine::ServletContext::getServlet() const {
    return servlet;
}

void MyEngine::ServletContext::servletInit() {
    servlet->init();
}

void MyEngine::ServletContext::servletService(const MyEngine::HttpRequest::Ptr& request, const MyEngine::HttpResponse::Ptr& response) {
    servlet->service(request, response);
}

void MyEngine::ServletContext::ServletDestroy() {
    servlet->destroy();
}
