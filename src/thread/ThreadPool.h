#pragma once
#include <Utility.h>
#include <condition_variable>
#include <functional>
#include <thread/SafeQueue.h>
#include <thread>
#include <vector>

namespace MyEngine {

    class ThreadPool {
    public:
        class Task {
        public:
            typedef shared_ptr<Task> Ptr;

            Task() = default;
            Task(std::function<void(void *)> func, void *arg);

        public:
            std::function<void(void *)> function;
            void *arg = nullptr;
        };

    public:
        explicit ThreadPool(unsigned int threadCount);
        ThreadPool(const ThreadPool &)  = delete;
        ThreadPool(const ThreadPool &&) = delete;

        ThreadPool &operator=(const ThreadPool &) = delete;
        ThreadPool &operator=(ThreadPool &&) = delete;

        void init();
        void commit(Task::Ptr task);
        void shutdown();

    private:
        void worker();

        bool isShutdown;
        std::mutex mutex;
        SafeQueue<Task::Ptr> tasks;
        std::vector<std::thread> threads;
        std::condition_variable conditionVariable;
    };

}// namespace MyEngine
