#include <iostream>
#include <string>
#include <iomanip> 
#include <ctime>
using namespace std;

int main(){
    struct tm time1 = {0};
    struct tm time2 = {0};
    for (int i = 0; i < 6; i++) {
        string s;
        cin >> s;
        switch (i) {
            case 0:
                time1.tm_year = stoi(s) - 1900;
                break;
            case 1:
                if (s == "January") {
                    time1.tm_mon = 0;  
                } else if (s == "February") {
                    time1.tm_mon = 1;
                } else if (s == "March") {
                    time1.tm_mon = 2;
                } else if (s == "April") {
                    time1.tm_mon = 3;
                } else if (s == "May") {
                    time1.tm_mon = 4;
                } else if (s == "June") {
                    time1.tm_mon = 5;
                } else if (s == "July") {
                    time1.tm_mon = 6;
                } else if (s == "August") {
                    time1.tm_mon = 7;
                } else if (s == "September") {
                    time1.tm_mon = 8;
                } else if (s == "October") {
                    time1.tm_mon = 9;
                } else if (s == "November") {
                    time1.tm_mon = 10;
                } else {
                    time1.tm_mon = 11;
                }
                break;
            case 2:
                time1.tm_mday = stoi(s);
                break;
            case 3:
                time1.tm_hour = stoi(s);
                break;
            case 4:
                time1.tm_min = stoi(s);
                break;
            case 5:
                time1.tm_sec = stoi(s);
                break;
            
        }
    }
    
    time2.tm_year = 2024 - 1900;
    time2.tm_mon = 9 - 1;
    time2.tm_mday = 1;
    time2.tm_hour = 22;
    time2.tm_min = 20;
    time2.tm_sec = 0;

    time_t t1 = mktime(&time1);
    time_t t2 = mktime(&time2);

    double seconds = difftime(t1, t2);
    
    seconds = seconds * 60 / 59;
    
    struct tm time3 = {0};
    time3.tm_year = 2024 - 1900;
    time3.tm_mon = 9 - 1;
    time3.tm_mday = 16;
    time3.tm_hour = 0;
    time3.tm_min = 0;
    time3.tm_sec = 0;
    
    time_t t3 = mktime(&time3);
    time_t newtime = t3 + seconds;
    
    struct tm* timeinfo = localtime(&newtime);

    cout << 1900 + timeinfo->tm_year << '-'
    << std::setfill('0') << std::setw(2) << 1 + timeinfo->tm_mon << '-'
    << std::setfill('0') << std::setw(2) << timeinfo->tm_mday << 'T'
    << std::setfill('0') << std::setw(2) << timeinfo->tm_hour << ':'
    << std::setfill('0') << std::setw(2) << timeinfo->tm_min << ':'
    << std::setfill('0') << std::setw(2) << timeinfo->tm_sec << '\n';

    return 0;
}