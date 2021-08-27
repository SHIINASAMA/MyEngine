/**
 * @file Servlet.h
 * @author kaoru
 * @date 2021.8.9
 * @brief Servlet 类
 * @version 0.1
 */
#pragma once
#include <http/HttpRequest.h>
#include <http/HttpResponse.h>

namespace MyEngine{

    /**
     * @brief Servlet 类
     */
    class Servlet {
    public:
        /**
         * @brief 智能指针对象
         */
        typedef shared_ptr<Servlet> Ptr;

        /**
         * 默认构造函数
         */
        Servlet() noexcept = default;
        /**
         * 默认析构函数
         */
        virtual ~Servlet() noexcept = default;

        /**
         * 执行前
         */
        virtual void init() noexcept = 0;
        /**
         * 执行服务
         * @param request 请求
         * @param response 回报
         * @return 执行结果
         */
        virtual bool service(const HttpRequest::Ptr &request, const HttpResponse::Ptr &response) noexcept = 0;
        /**
         * 执行后
         */
        virtual void destroy() noexcept = 0;

        /**
         * 获取 Servlet 实例名称
         * @return
         */
        std::string getClassName() const noexcept;
    };
}