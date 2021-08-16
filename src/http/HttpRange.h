/**
 * @file HttpRange.h
 * @author kaoru
 * @date 2021/8/15
 * @version 0.1
 * @brief Http 文件分块解析
 */
#pragma once
#include <Utility.h>
#include <vector>
/**
 * @author MAKE_RANGE
 * @brief 快速定义一个区间
 */
#define MAKE_RANGE(i, j) Range(i, j)

namespace MyEngine {

    /**
     * @brief 表示一个区间，可以使用 @ref MAKE_RANGE 定义一个区间
     */
    typedef std::pair<ssize_t, ssize_t> Range;

    /**
     * @brief Http 文件分块区间集合
     */
    class HttpRange {
    public:
        /**
         * @brief 智能指针对象
         */
        typedef shared_ptr<HttpRange> Ptr;

        /**
         * 默认构造函数
         * @param str 待解析的字符串
         */
        explicit HttpRange(const string &str);

        /**
         * 获取区间集合
         * @details 外部遍历用
         * @return 区间集合
         */
        auto getRanges() const { return this->ranges; }

        /**
         * 将字符串格式化为 “bytes startPos-endPos/size” 的格式
         * @param startPos 左端点
         * @param endPos 右端点
         * @param size 文件总大大小
         * @return 格式化后字符串
         */
        static string MakeContentRange(ssize_t startPos, ssize_t endPos, ssize_t size);

    private:
        std::vector<Range> ranges;
    };
}// namespace MyEngine
