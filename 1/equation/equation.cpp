#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main(){
    double a;
    double b;
    cin >> a >> b;
    
    double left = 0;
    double right = 10;
    while (right - left > 1e-6){
        double mid = (left + right) / 2;
        if ((exp(mid) - a * mid - b) * (exp(right) - a * right - b) < 0){
            left = mid;
        }else {
            right = mid;
        }
    }
    cout << fixed << setprecision(6);
    cout << right << endl;
}