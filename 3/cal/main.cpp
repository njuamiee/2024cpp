#include "Calculator.h"
#include <iostream>

using namespace std;

int main() {
  Calculator calculator;

  // Part 1: 基础四则运算
  cout << calculator.calculate("5 + 3 * ( 6 + 7 ) - 2") << endl;  // 输出: 42

  // Part 2: 自定义常数
  calculator.registerConstant("pi", 3.1415);
  cout << calculator.calculate("2 * 2 * pi") << endl;  // 输出: 12.566

  // Part 3: 自定义运算符
  calculator.registerConstant("x", 2);
  calculator.registerOperator("h ^ l = h * l / x", 5);
  calculator.registerConstant("h", 2);
  calculator.registerConstant("l", 2);
  cout << calculator.calculate("h ^ l") << endl;  // 输出: 2

  calculator.registerConstant("h", 3);
  calculator.registerConstant("l", 3);
  cout << calculator.calculate("h ^ l") << endl;  // 输出: 4.5

  return 0;
}
