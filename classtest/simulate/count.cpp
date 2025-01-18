#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(){
    string str;
    int row = 0;
    int word = 0;
    int chara = 0;
    int sign = 0;
    while(getline(cin, str)){
        str += "\n";
        for(char c : str){
            if(c == '\n'){
                row++;
                chara++;
                if(sign){
                    sign = 0;
                    word++;
                }
            }else if(c == ' '){
                chara++;
                if(sign){
                    sign = 0;
                    word++;
                }
            }else{
                sign = 1;
                chara++;
            }
        }
    }
    cout << chara << ' ' << word << ' ' << row << endl;
}