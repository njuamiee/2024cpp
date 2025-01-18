#include <iostream>
#include <algorithm>
using namespace std;

int n;
int associations[1005][3];
int first[1005];
int last[1005];

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d %d", &associations[i][0], &associations[i][1]);
        associations[i][2] = 0;  // 初始化标记位
        first[i] = i;
        last[i] = i;
    }
    sort(first, first  + n, [&](int i, int j) {
        return associations[i][0] < associations[j][0];  // 使用下标比较数组中的值，按降序排列
    });
    sort(last, last  + n, [&](int i, int j) {
        return associations[i][1] < associations[j][1];  // 使用下标比较数组中的值，按降序排列
    });
    int index = 0;
    int times = 0;
    int current_position = 0;
    for(int i = 0; i < n; i++){
        int ascend = (associations[last[i]][1] - current_position) / 27;
        if(ascend < 1){
            times++;
            current_position = associations[last[i]][1];
        }else {
            while(current_position < associations[last[i]][0]){
                times++;
                current_position += 27;
            }
            if(current_position > associations[last[i]][1]){
                current_position = associations[last[i]][1];
            }
        //     times += ascend;
        //     current_position += 27 * ascend;
        // }
        // if(current_position < associations[last[i]][0]){
        //     times++;
        //     current_position = associations[last[i]][1];
        }
        for(; index < n; index++){
            if(associations[first[index]][0] > current_position){
                break;
            }else{
                associations[first[index]][2] = 1;
            }
        }
        for(; i < n; i++){
            if(associations[last[i]][2] == 0){
                break;
            }
        }
        i--;
    }
    printf("%dT\n", times);
}
