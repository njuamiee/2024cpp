#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// 检查在得分限制为score时最多能选择多少张不相邻的卡片
int getMaxCards(const vector<int>& cards, int score) {
    int n = cards.size();
    vector<int> dp(n + 1, 0);  // dp[i]表示前i张卡片中能选择的最大数量
    
    // 只考虑小于等于score的卡片
    dp[0] = 0;
    dp[1] = (cards[0] <= score) ? 1 : 0;
    
    for (int i = 2; i <= n; i++) {
        // 不选第i张卡片
        dp[i] = dp[i-1];
        
        // 如果当前卡片值小于等于score，可以考虑选择它
        if (cards[i-1] <= score) {
            dp[i] = max(dp[i], dp[i-2] + 1);
        }
    }
    
    return dp[n];
}

int findMinScore(const vector<int>& cards, int k) {
    int n = cards.size();
    
    // 二分查找的范围是数组中的最小值到最大值
    int left = *min_element(cards.begin(), cards.end());
    int right = *max_element(cards.begin(), cards.end());
    int result = right;  // 初始化为最大值
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // 计算在得分限制为mid时最多能选多少张卡片
        int maxCards = getMaxCards(cards, mid);
        
        if (maxCards >= k) {
            // 如果能选够k张卡片，尝试降低得分
            result = mid;
            right = mid - 1;
        } else {
            // 如果不能选够k张卡片，需要提高得分
            left = mid + 1;
        }
    }
    
    return result;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> cards(n);
    for (int i = 0; i < n; i++) {
        cin >> cards[i];
    }
    
    int result = findMinScore(cards, k);
    cout << result << endl;
    
    return 0;
}