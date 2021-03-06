/**
 * @file HttpServlet.cpp
 * @author kaoru
 * @date 2021.8.8
 * @brief Http Servlet 实现
 * @version 0.1
 */
#include <servlet/HttpServlet.h>

bool MyEngine::HttpServlet::service(const HttpRequest::Ptr &request, const HttpResponse::Ptr &response) noexcept {
    if (request->getMethod() == HttpMethod::GET) {
        init();
        doGet(request, response);
        destroy();
        return true;
    } else if (request->getMethod() == HttpMethod::POST) {
        init();
        doPost(request, response);
        destroy();
        return true;
    } else {
        // DO NOTTING...
        return false;
    }
}

void MyEngine::HttpServlet::init() noexcept {
}

void MyEngine::HttpServlet::destroy() noexcept {
}

void MyEngine::HttpServlet::doGet(const MyEngine::HttpRequest::Ptr &request, const MyEngine::HttpResponse::Ptr &response) noexcept {
}

void MyEngine::HttpServlet::doPost(const MyEngine::HttpRequest::Ptr &request, const MyEngine::HttpResponse::Ptr &response) noexcept {
}
