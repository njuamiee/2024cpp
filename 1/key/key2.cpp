#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
using namespace std;

int main(){
    string s, string_k;
    getline(cin, s);
    getline(cin, string_k);

    long long k = stoi(string_k);

    string new_s;
    for (char c : s) {
        if (c != '-') {
            if (isalpha(c)) {
                new_s += toupper(c);
            } else if (isdigit(c)) {
                new_s += c;
            }
        }
    }

    long long group_count =  new_s.length() / k;
    long long remaind = (new_s.length() % k);
    // cout << remaind << endl;
    long long new_group = (remaind > 0) ? 1 : 0;
    new_group += group_count;

    string result;
    long long address = 0;
    for (long long i = 1; i <= new_group; i++) {
        if (i != k) {
            string check = new_s.substr(address, k);
            int has_letter = 0;
            int has_digit = 0;
            for (char c : check) {
                if (isalpha(c)) {
                    has_letter = 1;
                } else if (isdigit(c)) {
                    has_digit = 1;
                }
            }
            cout << check << '\n';
            if (has_digit != 1 || has_letter != 1) {
                cout << "INVALID" << endl;
                return 0;
            }
            result += check;
            address += k;
        } else {
            long long count = (remaind == 0) ? k : remaind;
            cout << address + count << '\n';
            result += new_s.substr(address, count);
            address += count;
        }
        if (i != new_group) {
            result += '-';
        }
        cout << result << '\n';
    }

    cout << result << endl;
    return 0;
}