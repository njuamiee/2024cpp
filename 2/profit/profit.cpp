#pragma GCC optimize(2)
#include <iostream>
#include <unordered_map>
// #include <stack>
#include <queue>
using namespace std;

int matrix[2005][2005];
int color;
int n, m;
unordered_map<int, pair<int, int>> rear;  // 使用哈希表来存储列的最小、最大行

void vinish(int x, int y) {
    // stack<pair<int, int>> s;
    // s.push({x, y});
    queue<pair<int, int>> q;
    q.push({x, y});

    matrix[x][y] = 0;

    // while (!s.empty()) {
    while (!q.empty()) {
        // auto [cx, cy] = s.top();
        // s.pop();
        auto [cx, cy] = q.front();
        q.pop();

        // 更新 rear 数组
        if (rear.find(cy) == rear.end()) {
            rear[cy] = {cx, cx};
        } else {
            rear[cy].first = min(rear[cy].first, cx);
            rear[cy].second = max(rear[cy].second, cx);
        }

        // 遍历四个方向的相邻节点
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i], ny = cy + dy[i];
            if (nx > 0 && ny > 0 && nx <= n && ny <= m && matrix[nx][ny] == color) {
                // s.push({nx, ny});
                q.push({nx, ny});
                matrix[nx][ny] = 0;
            }
        }
    }
}

void drop(int y){
    int counts = 0;
    int bottom = rear[y].second;
    for(int i = bottom; i >= 1; i--){
        if(matrix[i][y] == 0){
            counts++;
        }else {
            matrix[i + counts][y] = matrix[i][y];
            matrix[i][y] = 0;
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            scanf("%d", &matrix[i][j]);
        }
    }

    int x, y;
    scanf("%d %d", &x, &y);
    color = matrix[x][y];
    vinish(x, y);

    for (const auto& entry : rear) {
        int y = entry.first;
        drop(y);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("%d\n", matrix[i][m]);
    }

    return 0;
}