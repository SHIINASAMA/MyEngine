/**
 * @file SafeQueue.h
 * @author kaoru
 * @version 0.1
 * @brief 线程安全的队列模板
 */
#pragma once
#include <mutex>
#include <queue>

namespace MyEngine {
    /**
     * @brief 线程安全队列
     * @tparam T 队列元素
     */
    template<class T>
    class SafeQueue {
    public:
        /**
         * 默认构造函数
         */
        SafeQueue() = default;
        /**
         * 默认析构函数
         */
        virtual ~SafeQueue() = default;

        /**
         * 判断队列是否为空
         */
        bool empty() {
            std::unique_lock<std::mutex> lock(this->mutex);
            return this->queue.empty();
        }

        /**
         * 获取队列大小
         * @return 队列大小
         */
        int size() {
            std::unique_lock<std::mutex> lock(this->mutex);
            return this->queue.size();
        }
        /**
         * 入队
         * @param t 目标元素
         */
        void enqueue(T &t){
            std::unique_lock<std::mutex> lock(this->mutex);
            this->queue.push(t);
        }
        /**
         * 出队
         * @param t 出队元素
         * @return 是否出队成功
         */
        bool dequeue(T &t){
            std::unique_lock<std::mutex> lock(this->mutex);
            if (this->queue.empty()) {
                return false;
            }
            t = std::move(this->queue.front());
            this->queue.pop();
            return true;
        }

    private:
        std::queue<T> queue;
        std::mutex mutex;
    };
}// namespace MyEngine