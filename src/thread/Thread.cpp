/**
 * @file Thread.cpp
 * @author kaoru
 * @date 2021/8/11
 * @version 0.1
 * @brief 部分线程相关实现
 */
#include <thread/ThreadPool.h>

thread_local std::string thread_name{"Main"};

std::string MyEngine::GetThreadName() noexcept {
    return thread_name;
}

void MyEngine::SetThreadName(const std::string &name) noexcept {
    thread_name = name;
}

pid_t MyEngine::GetThreadId() noexcept {
    return syscall(SYS_gettid);
}