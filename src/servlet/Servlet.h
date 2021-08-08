/**
 * @file Servlet.h
 * @author kaoru
 * @date 2021.8.8
 * @brief Servlet 类
 * @version 0.1
 */
#pragma once
#include <http/Http.h>

namespace MyEngine{

    /**
     * @brief Servlet 类
     */
    class Servlet {
    public:
        /**
         * 默认构造函数
         */
        Servlet() = default;
        /**
         * 默认析构函数
         */
        virtual ~Servlet() = default;

        /**
         * 执行前
         */
        virtual void init() = 0;
        /**
         * 执行服务
         * @param request 请求
         * @param response 回报
         * @return 执行结果
         */
        virtual bool service(HttpRequest *request, HttpResponse *response) = 0;
        /**
         * 执行后
         */
        virtual void destroy() = 0;

        /**
         * 获取 Servlet 实例名称
         * @return
         */
        std::string getClassName() const;
    };
}