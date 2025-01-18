#include <iostream>
using namespace std;

int main(){
    long long n;
    cin >> n;

    long long arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    long long target;
    cin >> target;
    
    long long l = 0;
    long long r = 0;
    long long distance = n;
    long long sign_total = -1;
    long long total = 0;
    for (r = l; r < n; r++){
        // cout << "l=" << l << "r=" << r << '\n';
        total += arr[r];
        if (total >= target){
            if (r - l < distance){
                // cout << "\ntotal = " << total;
                // cout << "l=" << l << "r=" << r;
                if (r == l) {
                    cout << l << endl;
                    return 0;
                }
                distance = r - l;
                // cout << distance << '\n';
                sign_total = l + r;
            }
            // 走左边
            for (l = l + 1;l <= r; l++) {
                total -= arr[l - 1];
                if (total >= target) {
                    if (r - l < distance){
                        if (r == l) {
                            cout << l << endl;
                            return 0;
                        }else {
                            distance = r - l;
                            // cout << distance << '\n';
                            sign_total = l + r;
                        }
                    }
                } else {
                    break;
                }
            }
        }
        if ((r == n - 1) && (sign_total == -1)){
            cout << 0 << endl;
            return 0; 
        } else if(r == n - 1){
            if (total >= target) {
                for (l = l + 1;l <= r; l++) {
                    total -= arr[l - 1];
                    if (total >= target) {
                        if (r - l < distance){
                            if (r == l) {
                                cout << l << endl;
                                return 0;
                            }else {
                                distance = r - l;
                                // cout << distance << '\n';
                                sign_total = l + r;
                            }
                        }
                    } else {
                        break;
                    }
                }
            }
        }
    }
    cout << sign_total << endl;
    return 0;
}