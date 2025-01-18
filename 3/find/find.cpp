#include <iostream>
#include <vector>
#include <functional>
using namespace std;

const int MAXN = 1005;

// 树的邻接表存储
vector<int> tree[MAXN];
vector<int> value;
int n, p, q, k;

// 深度优先搜索通用函数
int dfs(int node, int parent, function<bool(int, int)> predicate) {
    if (!predicate(node, parent)) {
        return 0; // 不满足条件，剪枝
    }

    int sum = value[node - 1]; // 当前节点的价值
    for (int child : tree[node]) {
        if (child != parent) {
            sum += dfs(child, node, predicate);
        }
    }
    return sum;
}

// 策略定义
bool kingStrategy(int node, int parent) {
    return value[node - 1] > p;
}

bool huStrategy(int node, int parent) {
    if (node == 1) return true; // 根节点总是访问
    return value[node - 1] > q && value[node - 1] + value[parent - 1] > k;
}

bool xieStrategy(int node, int parent) {
    if (node == 1) return true; // 根节点总是访问
    return value[node - 1] % 2 == 0;
}

int main() {
    cin >> n >> p >> q >> k;

    // 输入树结构
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    // 输入宝藏点价值
    value.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> value[i];
    }

    // 分别计算每种策略的宝藏价值总和
    int kingResult = dfs(1, -1, kingStrategy);
    int huResult = dfs(1, -1, huStrategy);
    int xieResult = dfs(1, -1, xieStrategy);

    // 输出结果
    cout << kingResult << " " << huResult << " " << xieResult << endl;

    return 0;
}
