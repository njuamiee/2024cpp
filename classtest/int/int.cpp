#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>

class IntStream {
 public:
  // 构造函数，单参数构造流从 first 开始
  explicit IntStream(int first) : current_(first), last_(first), stride_(1) {}

  // 构造函数，两个参数：流从 first 开始，到 last 结束
  IntStream(int first, int last) : current_(first), last_(last), stride_(1) {}

  // 构造函数，三个参数：流从 first 开始，到 last 结束，步长为 stride
  IntStream(int first, int last, int stride)
      : current_(first), last_(last), stride_(stride) {
    if (stride == 0) {
      stride_ = 1;  // 步长不能为 0
    }
  }

  // 前置自增运算符
  IntStream& operator++() {
    if (stride_ > 0) {
      current_ += stride_;
      if (current_ >= last_) {
        current_ = last_;  // 越界时将值设为 last_
      }
    } else if (stride_ < 0) {
      current_ += stride_;
      if (current_ <= last_) {
        current_ = last_;  // 越界时将值设为 last_
      }
    }
    return *this;
  }

  // 后置自增运算符
  IntStream operator++(int) {
    IntStream temp = *this;
    ++(*this);  // 调用前置自增
    return temp;
  }

  // 解引用运算符，返回当前值
  int operator*() const {
    return current_;
  }

  // 布尔转换运算符，判断流是否有效
  operator bool() const {
    return (stride_ > 0 && current_ < last_) || (stride_ < 0 && current_ > last_);
  }

 private:
  int current_;  // 当前值
  int last_;     // 结束值
  int stride_;   // 步长
};

void print_answer(const IntStream &s, int expect) {
  std::cout << std::boolalpha;
  if (s) {
    std::cout << (*s == expect) << ' ' << *s << std::endl;
  } else {
    std::cout << false << std::endl;
  }
}

/**
 * @brief 测试 IntStream(int)
 */
void test_1() {
  IntStream s(0);
  for (size_t i = 0; i < 10; i++) {
    ++s;
  }
  print_answer(s, 10);
}

/**
 * @brief 测试 IntStream(int, int)
 */
void test_2() {
  IntStream s(0, 10);
  for (size_t i = 0; i < 9; i++) {
    s++;
  }
  print_answer(s, 9);
}

/**
 * @brief 测试 IntStream(int, int, int) - 不考虑溢出
 */
void test_3() {
  IntStream s(0, 10, 2);
  for (size_t i = 0; i < 4; i++) {
    ++s;
  }
  print_answer(s, 8);
}

/**
 * @brief 测试 IntStream(int, int, int) - 步长为负数
 */
void test_4() {
  IntStream s(10, 0, -1);
  for (size_t i = 0; i < 10; i++) {
    s++;
  }
  print_answer(s, 0);
}

/**
 * @brief 测试 IntStream(int, int, int) - 考虑溢出，大于最大值
 */
void test_5() {
  IntStream s(std::numeric_limits<int>::max() - 10000,
              std::numeric_limits<int>::max(), 123);
  for (size_t i = 0; i < 50; i++) {
    ++s;
  }
  print_answer(s, 2147479797);
}

/**
 * @brief 测试 IntStream(int, int, int) - 考虑溢出，小于最小值
 */
void test_6() {
  IntStream s(std::numeric_limits<int>::min() + 10000,
              std::numeric_limits<int>::min(), -123);
  for (size_t i = 0; i < 50; i++) {
    s++;
  }
  print_answer(s, -2147479798);
}

/**
 * @brief 测试步长为 0 的情况
 */
void test_7() {
  IntStream s(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(),
              0);
  for (size_t i = 0; i < 10000; i++) {
    s++;
  }
  print_answer(s, std::numeric_limits<int>::min());
}

/**
 * @brief 测试范围 [first, last) 非常大的情况
 */
void test_8() {
  IntStream s(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
  for (size_t i = 0; i < 10000; i++) {
    s++;
  }
  print_answer(s, std::numeric_limits<int>::min() + 10000);
}

int main() {
  std::unordered_map<std::string, std::function<void()>> test_cases_by_name = {
      {"test_1", test_1}, {"test_2", test_2}, {"test_3", test_3},
      {"test_4", test_4}, {"test_5", test_5}, {"test_6", test_6},
      {"test_7", test_7}, {"test_8", test_8},
  };
  std::string tname;
  std::cin >> tname;
  auto it = test_cases_by_name.find(tname);
  if (it == test_cases_by_name.end()) {
    std::cout << "输入只能是 test_<N>，其中 <N> 可取整数 1 到 8." << std::endl;
    return 1;
  }
  (it->second)();
}
