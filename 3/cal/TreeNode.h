#include <functional>
#include <string>

// 函数类型别名
typedef std::function<double(double, double)> BINARY_OP;

struct TreeNode {
  TreeNode* left{nullptr};
  TreeNode* right{nullptr};
  BINARY_OP operate{nullptr};
  std::string element;

  // 叶节点构造函数
  TreeNode(std::string e)
      : element(e) {}

  // 非叶节点构造函数
  TreeNode(BINARY_OP o, std::string e, TreeNode* l, TreeNode* r)
      : operate(o), element(e), left(l), right(r) {}
};