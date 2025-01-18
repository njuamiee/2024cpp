#ifndef SIMPLE_GTEST_H
#define SIMPLE_GTEST_H

#include <cassert>
#include <iostream>
#include <string>
#include <fmt/core.h>
#include <fmt/format.h>

// 定义辅助宏用于输出失败信息
#define REPORT_FAILURE(msg) \
    std::cerr << "Test failed at " << __FILE__ << ":" << __LINE__ << " - " << msg << std::endl;

// 定义通用断言模板
#define EXPECT_TRUE(condition) \
    if (!(condition)) { \
        REPORT_FAILURE("EXPECT_TRUE failed: " #condition); \
    }

#define ASSERT_TRUE(condition) \
    if (!(condition)) { \
        REPORT_FAILURE("ASSERT_TRUE failed: " #condition); \
        assert(condition); \
    }

#define EXPECT_FALSE(condition) \
    if (condition) { \
        REPORT_FAILURE("EXPECT_FALSE failed: " #condition); \
    }

#define ASSERT_FALSE(condition) \
    if (condition) { \
        REPORT_FAILURE("ASSERT_FALSE failed: " #condition); \
        assert(!(condition)); \
    }

// 相等断言
#define EXPECT_EQ(val1, val2) \
    if (!((val1) == (val2))) { \
        REPORT_FAILURE("EXPECT_EQ failed: " #val1 " == " #val2 << ", actual values: " << (val1) << " != " << (val2)); \
    }

#define ASSERT_EQ(val1, val2) \
    if (!((val1) == (val2))) { \
        REPORT_FAILURE("ASSERT_EQ failed: " #val1 " == " #val2 << ", actual values: " << (val1) << " != " << (val2)); \
        assert((val1) == (val2)); \
    }

#define ASSERT_EQ_NO_REPORT(val1, val2) \
    if (!((val1) == (val2))) { \
        assert((val1) == (val2)); \
    }

// 不相等断言
#define EXPECT_NE(val1, val2) \
    if ((val1) == (val2)) { \
        REPORT_FAILURE("EXPECT_NE failed: " #val1 " != " #val2 << ", actual values: " << (val1) << " == " << (val2)); \
    }

#define ASSERT_NE(val1, val2) \
    if ((val1) == (val2)) { \
        REPORT_FAILURE("ASSERT_NE failed: " #val1 " != " #val2 << ", actual values: " << (val1) << " == " << (val2)); \
        assert((val1) != (val2)); \
    }

#define ASSERT_NE_NO_REPORT(val1, val2) \
    if ((val1) == (val2)) { \
        assert((val1) != (val2)); \
    }
    
// 较小断言
#define EXPECT_LT(val1, val2) \
    if (!((val1) < (val2))) { \
        REPORT_FAILURE("EXPECT_LT failed: " #val1 " < " #val2 << ", actual values: " << (val1) << " >= " << (val2)); \
    }

#define ASSERT_LT(val1, val2) \
    if (!((val1) < (val2))) { \
        REPORT_FAILURE("ASSERT_LT failed: " #val1 " < " #val2 << ", actual values: " << (val1) << " >= " << (val2)); \
        assert((val1) < (val2)); \
    }

// 较大断言
#define EXPECT_GT(val1, val2) \
    if (!((val1) > (val2))) { \
        REPORT_FAILURE("EXPECT_GT failed: " #val1 " > " #val2 << ", actual values: " << (val1) << " <= " << (val2)); \
    }

#define ASSERT_GT(val1, val2) \
    if (!((val1) > (val2))) { \
        REPORT_FAILURE("ASSERT_GT failed: " #val1 " > " #val2 << ", actual values: " << (val1) << " <= " << (val2)); \
        assert((val1) > (val2)); \
    }

#define TEST(TestSuite, TestName) \
    void TestSuite##_##TestName()

#endif // SIMPLE_GTEST_H
