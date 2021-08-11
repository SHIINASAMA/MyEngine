#pragma once
#include <plugin/Plugin.h>

void *Create();

class TestServlet : public MyEngine::HttpServlet {
public:
    void doGet(const MyEngine::HttpRequest::Ptr &request, const MyEngine::HttpResponse::Ptr &response) override;
};

extern "C" struct MyEngine::Manifest manifest { "my plugin", 1, "kaoru", 1628681178, Create };
