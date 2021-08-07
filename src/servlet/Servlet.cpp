#include <cxxabi.h>
#include <servlet/Servlet.h>
#include <typeinfo>

void MyEngine::Servlet::service(MyEngine::HttpRequest &request, MyEngine::HttpResponse &response) {
}

string MyEngine::Servlet::getClassName() const {
    return {abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, nullptr)};
}