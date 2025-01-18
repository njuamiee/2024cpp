#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
using namespace std;

int ptr[1005];

unordered_map<int, int> match(string s){
    stack<int> st;
    unordered_map<int, int> matching;

    for(int i = 0; i < s.length(); i++){
        if (s[i] == '['){
            st.push(i);
        }else if(s[i] == ']'){
            matching[st.top()] = i;
            matching[i] = st.top();
            st.pop();
        }
    }
    return matching;
}
int main(){
    string cmd;
    getline(cin, cmd);
    int current_point = 0;
    unordered_map<int, int> matching = match(cmd);
    for(int i = 0; i < cmd.length(); i++){
        if(cmd[i] == '>'){
            current_point++;
        }else if(cmd[i] == '<'){
            current_point--;
        }else if(cmd[i] == '+'){
            ptr[current_point]++;
        }else if(cmd[i] == '-'){
            ptr[current_point]--;
        }else if(cmd[i] == ','){
            char ch = cin.get();
            if (ch == EOF){
                ptr[current_point] = 0;
            }else {
                ptr[current_point] = (int) ch;
            }
        }else if(cmd[i] == '.'){
            cout << (char)ptr[current_point];
        }else if(cmd[i] == '['){
            if(ptr[current_point] == 0){
                i = matching[i];
            }
        }else if(cmd[i] == ']'){
            if(ptr[current_point] != 0){
                i = matching[i];
            }
        }
    }
    // cout << endl;
}