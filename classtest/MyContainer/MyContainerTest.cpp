#include "MyContainer.h"
#include <cassert>
#include <functional>
#include <iostream>

// === TEST_CASES ===
void TEST_1();
void TEST_2();
void TEST_3();
void TEST_4();
void TEST_5();

#define REGISTER_TEST_CASE(name) {#name, name}

int main() {
  std::unordered_map<std::string, std::function<void()>>
      test_functions_by_name = {
          REGISTER_TEST_CASE(TEST_1),
          REGISTER_TEST_CASE(TEST_2),
          REGISTER_TEST_CASE(TEST_3),
          REGISTER_TEST_CASE(TEST_4),
          REGISTER_TEST_CASE(TEST_5),
      };

  std::string test_case_name;
  std::cin >> test_case_name;
  auto it = test_functions_by_name.find(test_case_name);
  assert(it != test_functions_by_name.end());
  auto fn = it->second;
  fn();
  return 0;
}

void TEST_1() {
  MyContainer m(5);
  std::cout << m.count() << std::endl;

  MyContainer m2(m);
  std::cout << m2.count() << std::endl;

  MyContainer m3 = m2;
  std::cout << m3.count() << std::endl;
}

void TEST_2() {
  MyContainer m1(5);
  std::cout << m1.count() << std::endl;

  MyContainer m2 = m1;
  std::cout << m2.count() << std::endl;
  std::cout << (m2.data() == m1.data()) << std::endl;
}

void TEST_3() {
  MyContainer m1(3);
  std::cout << m1.count() << std::endl;

  MyContainer m2 = m1;
  std::cout << m2.count() << std::endl;
  std::cout << (m2.data() == m1.data()) << std::endl;

  m1 = m2;
  std::cout << m1.count() << std::endl;
  std::cout << (m2.data() == m1.data()) << std::endl;

  m2 = m1;
  std::cout << m2.count() << std::endl;
  std::cout << (m2.data() == m1.data()) << std::endl;

  int *prev_ptr = m1.data();
  m1 = m1;
  std::cout << m1.count() << std::endl;
  std::cout << (m1.data() == prev_ptr) << std::endl;
}

void TEST_4() {
  MyContainer m1(3);
  std::cout << m1.count() << std::endl;

  {
    MyContainer m2 = m1;
    std::cout << m2.count() << std::endl;
    std::cout << (m2.data() == m1.data()) << std::endl;

    m1 = m2;
    std::cout << m1.count() << std::endl;
    std::cout << (m2.data() == m1.data()) << std::endl;

    m2 = m1;
    std::cout << m2.count() << std::endl;
    std::cout << (m2.data() == m1.data()) << std::endl;
  }

  std::cout << m1.count() << std::endl;
}

void TEST_5() {
  int x, y;
  std::cin >> x >> y;
  MyContainer m1(x);
  {
    std::cout << m1.count() << std::endl;
    MyContainer m2(y);
    std::cout << m1.count() << std::endl;
    std::cout << m1.size() << " " << m2.size() << std::endl;

    m2 = m1;
    std::cout << m1.count() << std::endl;
    std::cout << m1.size() << " " << m2.size() << std::endl;
    int *prev_ptr = m2.data();

    MyContainer m3(x + y);
    std::cout << m2.count() << std::endl;

    m2 = m2;
    std::cout << m2.count() << std::endl;
    std::cout << m1.size() << " " << m2.size() << std::endl;
    std::cout << (m2.data() == prev_ptr) << std::endl;
    std::cout << (m2.data() == m1.data()) << std::endl;
    m1 = m3;
  }
  std::cout << m1.count() << std::endl;
  std::cout << m1.size() << std::endl;
}