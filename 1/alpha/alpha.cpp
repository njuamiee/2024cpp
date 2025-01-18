#include <iostream>
using namespace std;

int main(){
    int q;
    cin >> q;
    cin.ignore();

    int alpha[53] = {0};
    for (int i = 0; i < q; i++) { 
        string s;
        getline(cin, s);
        // cout << s;
        if (s[0] == 'a'){
            string new_s = s.substr(3);
            // cout << new_s;
            for (char c : new_s) {
                if (c <= 'z' && c >= 'a') {
                    alpha[c - 'a' + 26]++;
                }else if (c <= 'Z' && c >= 'A') {
                    alpha[c - 'A']++;
                }
            }
        } else {
            int max = -1;
            for (int i = 0; i < 52; i++) {
                if (alpha[i] > max) max = alpha[i];
            }
            if (max == 0) continue;
            for (int i = 0; i < 52; i++) {
                if (alpha[i] == max) {
                    if (i <= 51 && i >= 26) {
                        cout << static_cast<char>(i + 'a' - 26);
                    }else if (i <= 25 && i >= 0) {
                        cout << static_cast<char>(i + 'A');
                    }
                }
            }
        }
    }
    
}