/**
 * @file Servlet.h
 * @author kaoru
 * @date 2021.8.8
 * @brief Servlet 类部分实现
 * @version 0.1
 */
#ifdef __GNUC__
#include <cxxabi.h>
#endif
#include <servlet/Servlet.h>
#include <typeinfo>

string MyEngine::Servlet::getClassName() const noexcept {
#ifdef __GNUC__
    return {abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, nullptr)};
#endif
}