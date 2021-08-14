/**
 * @file ThreadPool.h
 * @date 2021.8.10
 * @author kaoru
 * @version 0.1
 * @brief 固定线程池
 * @warning 需要至少 CPP17 才能编译通过
 */
#pragma once
#include <Utility.h>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <queue>
#include <syscall.h>
#include <thread>
#include <unistd.h>
#include <vector>

namespace MyEngine {

    /**
     * 获取当前线程名称
     * @return 线程名称
     */
    std::string GetThreadName();
    /**
     * 设置当前线程名称
     * @param name 线程名称
     */
    void SetThreadName(const std::string &name);
    /**
     * 获取当前线程 PID
     * @return 线程 PID
     */
    pid_t GetThreadId();

    /**
     * @brief 绑定参数和右值引用
     * @tparam F 函数模板
     */
    template<class F>
    class BindArgsMover {
    public:
        /**
         * 默认构造函数
         * @param f 函数模板
         */
        explicit BindArgsMover(F &&f) : f_(std::forward<F>(f)) {}

        template<class... Args>
        auto operator()(Args &&...args) {
            f_(std::move(args)...);
        }

    private:
        F f_;
    };

    /**
     * 简化绑定用的临时函数
     * @tparam F 函数模板
     * @tparam Args 参数模板
     * @param f 函数
     * @param args 参数
     * @return 包装后对象
     */
    template<class F, class... Args>
    auto bind_simple(F &&f, Args &&...args) {
        return std::bind(BindArgsMover<F>(std::forward<F>(f)), std::forward<Args>(args)...);
    }

    /**
     * @brief 固定线程池
     */
    class ThreadPool {
    public:
        /**
         * 智能指针对象
         */
        typedef std::shared_ptr<ThreadPool> Ptr;

        /**
         * 默认构造函数
         */
        ThreadPool()              = default;
        /**
         * 拷贝构造函数
         */
        ThreadPool(ThreadPool &&) = default;
        /**
         * 析构函数
         */
        ~ThreadPool() {
            shutdown();
        }

        /**
         * 初始化一个线程池
         * @param thread_pool_name 线程池名称
         * @param thread_count 线程内线程数量
         */
        explicit ThreadPool(const std::string &thread_pool_name, size_t thread_count) : data_(std::make_shared<data>()) {
            data_->thread_pool_name_ = thread_pool_name;
            for (size_t i = 0; i < thread_count; ++i) {
                data_->threads_.emplace_back(std::thread([data = data_, number = i] {
                    SetThreadName(data->thread_pool_name_ + "_" + std::to_string(number));
                    std::unique_lock<std::mutex> lk(data->mtx_);
                    for (;;) {// 获取任务互斥,执行任务并发。
                        if (!data->tasks_.empty()) {
                            auto current = std::move(data->tasks_.front());
                            data->tasks_.pop();
                            lk.unlock();
                            current();
                            lk.lock();
                        } else if (data->is_shutdown_) {
                            break;
                        } else {
                            data->cond_.wait(lk);
                        }
                    }
                }));
            }
        }

        /**
         * 处理事务
         * @tparam F 函数模板
         * @tparam Args 参数模板
         * @param f 函数
         * @param args 参数
         */
        template<class F, class... Args>
        void execute(F &&f, Args &&...args) {
            //  解决知乎答主提出的第五点小问题。
            auto task = bind_simple(f, args...);
            {
                std::lock_guard<std::mutex> lk(data_->mtx_);
                data_->tasks_.emplace(task);
            }
            data_->cond_.notify_one();
        }

        /**
         * 判断任务队列是否为空
         * @return 任务队列是否为空
         */
        bool empty() { return data_->tasks_.empty(); }

        /**
         * 结束线程池，这是一个阻塞方法
         */
        void shutdown() {
            if ((bool) data_) {
                {
                    std::lock_guard<std::mutex> lk(data_->mtx_);
                    data_->is_shutdown_ = true;
                }

                data_->cond_.notify_all();
                for (auto &th : data_->threads_) {
                    if (th.joinable()) {
                        th.join();
                    }
                }
            }
        }

    private:
        struct data {
            std::mutex mtx_;
            std::condition_variable cond_;
            std::atomic_bool is_shutdown_ = false;
            std::queue<std::function<void()>> tasks_;
            std::vector<std::thread> threads_;
            std::string thread_pool_name_;
        };

        std::shared_ptr<data> data_;
    };

}// namespace MyEngine