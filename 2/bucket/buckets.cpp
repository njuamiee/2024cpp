#include <iostream>
using namespace std;

int fund[100005];

int main(){
    int n;
    double target, k;
    cin >> n >> target >> k;
    // cout << n << k << '\n';
    for (int i = 0; i < n; i++){
        cin >> fund[i];
        // cout << fund[i] <<" ";
    }
    int max = -1;
    int current_max_price = 2;
    double current_buckets = 0;
    double current_remaining_money = 0;
    while (1){
        for (int i = 0; i < n; i++){
            current_buckets += fund[i] / current_max_price;
            current_remaining_money += fund[i] % current_max_price;
            if (current_buckets >= target){
                max = current_max_price;
                // cout << max;
                current_max_price++;
                current_buckets = 0;
                current_remaining_money = 0;
                i = -1;
            }
        }
        if (current_max_price != 1){
            current_buckets += current_remaining_money / ((double)current_max_price - k);
        }
        if (current_buckets >= target){
            max = current_max_price;
            current_max_price++;
            current_buckets = 0;
            current_remaining_money = 0;
        }else {
            // cout << current_remaining_money << ' ' << current_buckets << " ";
            cout << max << endl;
            break;
        }
    }
}