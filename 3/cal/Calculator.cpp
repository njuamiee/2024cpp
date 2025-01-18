#include "Calculator.h"
#include <sstream>
#include <stack>
#include <stdexcept>
#include <cctype>
#include <functional>
#include <iostream>

using namespace std;

// 初始化Calculator
Calculator::Calculator() {
  // 运算符优先级
  precedenceTable['+'] = 6;
  precedenceTable['-'] = 6;
  precedenceTable['*'] = 5;
  precedenceTable['/'] = 5;

  // 运算符功能
  functionTable['+'] = [](double a, double b) { return a + b; };
  functionTable['-'] = [](double a, double b) { return a - b; };
  functionTable['*'] = [](double a, double b) { return a * b; };
  functionTable['/'] = [](double a, double b) { if (b == 0) throw runtime_error("Division by zero"); return a / b; };
}

// 解析表达式并构建表达式树
TreeNode* Calculator::buildTree(vector<string>& tokens) {
    stack<TreeNode*> nodes;
    stack<char> ops;

    auto applyOp = [&](char op) {
        TreeNode* right = nodes.top(); nodes.pop();
        TreeNode* left = nodes.top(); nodes.pop();
        nodes.push(new TreeNode(functionTable[op], string(1, op), left, right));
    };

    for (const auto& token : tokens) {
        if (isdigit(token[0]) || isalpha(token[0])) {  // 操作数
            nodes.push(new TreeNode(token));
        } else if (token == "(") {  // 左括号直接入栈
            ops.push('(');
        } else if (token == ")") {  // 右括号，应用直到匹配左括号
            while (!ops.empty() && ops.top() != '(') {
                applyOp(ops.top());
                ops.pop();
            }
            ops.pop();  // 弹出左括号
        } else {  // 操作符
            char op = token[0];
            while (!ops.empty() && ops.top() != '(' &&
                   precedenceTable[ops.top()] <= precedenceTable[op]) {  // 修复优先级比较
                applyOp(ops.top());
                ops.pop();
            }
            ops.push(op);
        }
    }

    // 清空剩余的操作符
    while (!ops.empty()) {
        applyOp(ops.top());
        ops.pop();
    }

    return nodes.top();
}

// 计算表达式树的值
double Calculator::getVal(TreeNode* node) {
  if (!node->operate) {  // 叶节点
    if (isdigit(node->element[0])) {
      return stod(node->element);
    } else if (constantTable.count(node->element)) {
      return constantTable[node->element];
    } else {
      throw runtime_error("Undefined constant: " + node->element);
    }
  }
  return node->operate(getVal(node->left), getVal(node->right));
}

// 注册常数
void Calculator::registerConstant(const string& symbol, double val) {
  constantTable[symbol] = val;
}

// 注册自定义运算符
void Calculator::registerOperator(const string& expr, int precedence) {
  string lhs, rhs, op, equals, body;
  istringstream ss(expr);
  ss >> lhs >> op >> rhs >> equals;
  getline(ss, body);

  if (equals != "=") throw runtime_error("Invalid operator definition");

  precedenceTable[op[0]] = precedence;

  functionTable[op[0]] = [=](double left, double right) {
    string expression = body;
    size_t pos;
    while ((pos = expression.find(lhs)) != string::npos) expression.replace(pos, lhs.size(), to_string(left));
    while ((pos = expression.find(rhs)) != string::npos) expression.replace(pos, rhs.size(), to_string(right));
    return calculate(expression);
  };
}

// 计算表达式
double Calculator::calculate(const string& expr) {
  vector<string> tokens = tokenize(expr);
  // for (const auto& token : tokens) {
  //     cout << token << " ";
  // }
  // cout << endl;

  TreeNode* root = buildTree(tokens);
  // printTree(root);  // 递归打印表达式树（需要实现）

  double result = getVal(root);
  deleteTree(root);
  return result;
}

void Calculator::printTree(TreeNode* node, int depth) {
    if (!node) return;
    printTree(node->right, depth + 1);
    cout << string(depth * 4, ' ') << node->element << endl;
    printTree(node->left, depth + 1);
}


void Calculator::deleteTree(TreeNode* node) {
  if (!node) return;
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}


vector<string> Calculator::tokenize(const string& expr) {
  vector<string> tokens;
  size_t i = 0;
  while (i < expr.length()) {
    if (isspace(expr[i])) {
      ++i;
    } else if (isdigit(expr[i]) || expr[i] == '.') {
      size_t j = i;
      while (j < expr.length() && (isdigit(expr[j]) || expr[j] == '.')) ++j;
      tokens.push_back(expr.substr(i, j - i));
      i = j;
    } else if (isalpha(expr[i])) {
      size_t j = i;
      while (j < expr.length() && isalpha(expr[j])) ++j;
      tokens.push_back(expr.substr(i, j - i));
      i = j;
    } else {
      tokens.push_back(string(1, expr[i]));
      ++i;
    }
  }
  return tokens;
}

