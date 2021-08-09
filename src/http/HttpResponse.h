/**
 * @file HttpResponse.h
 * @author kaoru
 * @date 2021.8.9
 * @version 0.1
 * @brief Http 回报
 */
#pragma once
#include <http/HttpHeader.h>

namespace MyEngine {
    /**
     * @brief Http 回报类
     */
    class HttpResponse : public HttpHeader {
    public:
        /**
         * @brief 智能指针对象
         */
        typedef shared_ptr<HttpResponse> Ptr;

        /**
          * 默认构造函数
          */
        HttpResponse() = default;
        /**
          * 初始化一个 HTTP 回报
          * @param version HTTP 版本
          * @param stateCode 状态码
          */
        HttpResponse(int version, int stateCode);
        /**
          * 默认析构函数
          */
        ~HttpResponse() override = default;

        /**
         * 获取状态码
         * @return 状态码
         */
        int getStateCode() const { return this->stateCode; }
        /**
         * 设置状态码
         * @param code 状态码
         */
        void setStateCode(int code) { this->stateCode = code; }

        /**
         * 报头导出
         * @return 字符串
         */
        string dump() const;

    protected:
        int stateCode{200};
    };
}// namespace MyEngine
