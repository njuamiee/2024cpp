#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int dist[105][105];
int n, m;
int rest[6], cust[6];
const int INF = 1e9;

void floydWarshall() {
    for (int k = 0; k < m; ++k) {//中间节点
        for (int i = 0; i < m; ++i) {//所有起点
            for (int j = 0; j < m; ++j) {//所有终点
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int dfs(int current, int visited, vector<vector<int>>& dp) {
    if (visited == (1 << (2 * n)) - 1) {
        return 0;  // 返回到起点
    }
    if (dp[current][visited] != -1) {
        return dp[current][visited];
    }
    int result = INF;
    for (int i = 0; i < n; ++i) {
        int pick_rest = 1 << (2 * i);    // 取餐的标记
        int pick_cust = 1 << (2 * i + 1); // 送餐的标记
        // 如果没有取餐，则先取餐
        if ((visited & pick_rest) == 0) {
            result = min(result, dist[current][rest[i]] + dfs(rest[i], visited | pick_rest, dp));
        }
        // 如果已经取了餐但没有送餐，则送餐
        else if ((visited & pick_cust) == 0) {
            result = min(result, dist[current][cust[i]] + dfs(cust[i], visited | pick_cust, dp));
        }
    }
    dp[current][visited] = result;
    return result;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> dist[i][j];
            if(dist[i][j] == -1) dist[i][j] = INF;
        }
    }
    floydWarshall();  // 计算任意两点之间的最短路径
    for (int i = 0; i < n; ++i) {
        cin >> rest[i] >> cust[i];
        rest[i]--;  // 调整为0-indexed
        cust[i]--;
    }
    vector<vector<int>> dp(m, vector<int>(1 << (2 * n), -1));  // 状态压缩dp表
    int result = dfs(0, 0, dp);
    cout << result << endl;
    return 0;
}
