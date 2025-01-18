#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

int main(){
    string str;
    cin >> str;
    int sign = 0;
    while(str[0] == '-'){
        sign = 1;
        str = str.substr(1);
    }
    reverse(str.begin(), str.end());
    long num = stoll(str);
    if(num > numeric_limits<int>::max()){
        cout << -1 << endl;
    }else{
        if(sign){
            cout << "-" << str << endl;
        }else{
            cout << str << endl;
        }
    }
}