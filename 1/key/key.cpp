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
    cout << k << endl; 
    
    string letter_s, digit_s;
    for (char c : s) {
        if (c != '-') {
            if (isalpha(c)) {
                letter_s += toupper(c);
            } else if (isdigit(c)) {
                digit_s += c;
            }
        }
    }
    
    long long letter_count = letter_s.length();
    long long digit_count = digit_s.length();
    if (k == 0) {
        cout << "INVALID" << endl;
        return 0;
    }
    long long group_count = (letter_count + digit_count) / k;
    
    if (   ((letter_count < group_count) && (group_count < k)) 
        || ((digit_count < group_count) && (group_count < k))
        || ((letter_count < group_count - 1) && (group_count >= k) && ((letter_count + digit_count) % k == 0))
        || ((letter_count < group_count) && (group_count >= k) && ((letter_count + digit_count) % k != 0))
        || ((digit_count < group_count - 1) && (group_count >= k) && ((letter_count + digit_count) % k == 0))
        || ((digit_count < group_count) && (group_count >= k) && ((letter_count + digit_count) % k != 0))
        || ((group_count < (k - 1)) && ((letter_count + digit_count) % k != 0))
        || (k == 1)
        // || (group_count < (k - 1))
        ) {
        cout << "INVALID" << endl;
        return 0;
    }
    
    string result;
    
    long long remaind = (letter_count + digit_count) % k;
    // cout << remaind << endl;
    long long new_group = (remaind > 0) ? 1 : 0;
    new_group += group_count;
    
    long long equal = (letter_count - digit_count == 0) ? 1 : 0;
    // cout << letter_count << digit_count << endl;
    
    long long letter = 0;
    long long letter_address = 0;
    long long digit_address = 0;
    for (long long i = 1; i <= new_group; i++) {
        if (i != k) {
            for (long long j = 0; j < k; j++) {
                if (equal) {
                    if (letter) {
                        result += letter_s[letter_address];
                        letter_address++;
                        letter = 0;
                        continue;
                    } else {
                        result += digit_s[digit_address];
                        digit_address++;
                        letter = 1;
                        continue;
                    }
                } else {
                    if (j == 0) {
                        if (letter_count > digit_count) {
                            result += digit_s[digit_address];
                            digit_address++;
                            digit_count--;
                            continue;
                        } else {
                            result += letter_s[letter_address];
                            letter_address++;
                            letter_count--;
                            continue;
                        }
                    } else {
                        if (letter_count < digit_count) {
                            result += digit_s[digit_address];
                            digit_address++;
                            digit_count--;
                            if (letter_count - digit_count == 0) equal = 1;
                            continue;
                        } else {
                            result += letter_s[letter_address];
                            letter_address++;
                            letter_count--;
                            if (letter_count - digit_count == 0) equal = 1;
                            continue;
                        }
                    }
                }
            }
        } else {
            long long count = (remaind == 0) ? k : remaind;
            for (long long j = 0; j < count; j++) {
                if (equal) {
                    if (letter) {
                        result += letter_s[letter_address];
                        letter_address++;
                        letter = 0;
                        continue;
                    } else {
                        result += digit_s[digit_address];
                        digit_address++;
                        letter = 1;
                        continue;
                    }
                } else {
                    if (letter_count < digit_count) {
                        result += digit_s[digit_address];
                        digit_address++;
                        digit_count--;
                        if (letter_count - digit_count == 0) equal = 1;
                        continue;
                    } else {
                        result += letter_s[letter_address];
                        letter_address++;
                        letter_count--;
                        if (letter_count - digit_count == 0) equal = 1;
                        continue;
                    }
                }
            }
        }
        
        if (i != new_group) {
            result += '-';
        }
    }

    cout << result << endl;

    return 0;
}