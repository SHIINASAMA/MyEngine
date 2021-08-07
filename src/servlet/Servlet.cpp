#include <cxxabi.h>
#include <servlet/Servlet.h>
#include <typeinfo>

string MyEngine::Servlet::getClassName() const {
    return {abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, nullptr)};
}