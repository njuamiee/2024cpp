#include <map>
#include <vector>
#include <string>
#include "TreeNode.h"

class Calculator {
 private:
  std::map<char, int> precedenceTable;          // 运算符优先级表
  std::map<char, BINARY_OP> functionTable;      // 函数表
  std::map<std::string, double> constantTable;  // 常数表

  TreeNode* buildTree(std::vector<std::string>& tokens);

  double getVal(TreeNode* node);

  std::vector<std::string> tokenize(const std::string& expr);

 public:
  Calculator();

  void registerOperator(const std::string& expr, int precedence);

  void registerConstant(const std::string& symbol, double val);

  double calculate(const std::string& expr);

  void printTree(TreeNode* node, int depth = 0);

  void deleteTree(TreeNode* node);
};
