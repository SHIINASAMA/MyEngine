#include <thread/ThreadPool.h>

MyEngine::ThreadPool::ThreadPool(unsigned int threadCount)
    : threads(std::vector<std::thread>(threadCount)), isShutdown(false) {
}

void MyEngine::ThreadPool::init() {
    for (auto &i : this->threads) {
        i = std::thread(&ThreadPool::worker, this);
    }
}


void MyEngine::ThreadPool::shutdown() {
    this->isShutdown = true;
    this->conditionVariable.notify_all();
    for (auto &thread : this->threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void MyEngine::ThreadPool::worker() {
    Task::Ptr task;
    bool rt;
    while (!isShutdown) {
        std::unique_lock<std::mutex> lock(mutex);
        if (tasks.empty()) {
            conditionVariable.wait(lock);
        }
        rt = tasks.dequeue(task);
    }
    if (rt) {
        task->function(task->arg);
    }
}

void MyEngine::ThreadPool::commit(Task::Ptr task) {
    this->tasks.enqueue(task);
    this->conditionVariable.notify_one();
}

MyEngine::ThreadPool::Task::Task(std::function<void(void *)> func, void *arg) {
    this->function = std::move(func);
    this->arg      = arg;
}
