#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

long long int n;
long long int board[1000005];
long long int board_span[1000005];
long long int total_board;

void add_handle(long long int length){
    board[total_board] = length;
    long long int current_length = length;
    while(current_length > 0){
        board_span[total_board]++;
        current_length /= 256;
    }
    total_board++;
}

void del_handle(long long int length){
    for(long long int i = 0; i < total_board; i++){
        if(board[i] == length){
            board[i] = -1;
            board_span[i] = -1;
            break;
        }
    }
}

void print_handle(){
    long long int max_span = -1;
    for(long long int i = 0; i < total_board; i++){
        if(max_span < board_span[i]){
            max_span = board_span[i];
        }
    }
    long long int current_span = 0;
    cout << "0x";
    for(long long int i = 0; i < total_board; i++){
        if(board[i] == -1){
            continue;
        }
        if(current_span + board_span[i] > max_span){
            long long int temporary_span = max_span - current_span;
            for(int j = 0; j < temporary_span; j++){
                cout << "CC";
            }
            current_span = board_span[i];
            stringstream ss;
            ss << hex << board[i];
            cout << "\n0x" << ss.str();
        }else {
            current_span += board_span[i];
            stringstream ss;
            ss << hex << board[i];
            cout << ss.str();
        }
    }
    cout << "\n";
}

void address_print_handle(long long int address, long long int length){
    long long int max_span = -1;
    for(long long int i = 0; i < total_board; i++){
        if(max_span < board_span[i]){
            max_span = board_span[i];
        }
    }
    long long int current_span = 0;
    long long int current_address = 0;
    long long int current_length = 0;
    int signal = 0;
    for(long long int i = 0; i < total_board; i++){
        if(board[i] == -1){
            continue;
        }
        current_span += board_span[i];
        if(current_span > max_span){
            long long int temporary_span = max_span - (current_span - board_span[i]);
            current_address += temporary_span;
            if(current_address >= address && signal == 0){
                signal = 1;
                cout << "0x";
            }
            if(signal == 1){
                for(int j = address + current_length; j < min(current_address, address + length); j++){
                    current_length++;
                    cout << "CC";
                }
                if(current_length == length){
                    cout << endl;
                    break;
                }
            } 
            current_span = board_span[i];
        }
        current_address += board_span[i];
        if(current_address >= address && signal == 0){
            signal = 1;
            cout << "0x";
        }
        if(signal == 1){
            ostringstream ss;
            ss << hex << board[i];
            string board_str = ss.str();
            for(int j = address + current_length; j < min(current_address, address + length); j++){
                cout << board_str.substr(((j - (current_address - board_span[i])) * 2), 2);
                current_length++;
            }
            if(current_length == length){
                cout << endl;
                break;
            }
        }
    }
    if(current_length < length){
        if(signal == 0){
            cout << "0x";
        }
        for(int i = current_length; i < length; i++){
            cout << "CC";
        }
        cout << endl;
    }
}

int main(){
    cin >> n;
    string s;
    string addr;
    string length;
    cin.ignore();
    for(long long int i = 0; i < n; i++){
        getline(cin, s);
        istringstream iss(s);
        iss >> s;
        if(s == "add"){
            iss >> length;
            add_handle(stoll(length, nullptr, 16));
        }else if(s == "del"){
            iss >> length;
            del_handle(stoll(length, nullptr, 16));
        }else if(s == "print"){
            if(iss >> addr){
                iss >> length;
                address_print_handle(stoll(addr), stoll(length));
            }else {
                print_handle();
            }
        }else {
            continue;
        }
    }
    return 0;
}