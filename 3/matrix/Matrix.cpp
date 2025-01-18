#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

// 定义矩阵类型
typedef vector<vector<int>> Matrix;

// 矩阵乘法，返回两个矩阵的乘积
Matrix matrixMultiply(const Matrix& A, const Matrix& B, int n) {
    Matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] = (C[i][j] + (long long)A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    return C;
}

// 矩阵快速幂
Matrix matrixPower(Matrix A, int p, int n) {
    // 初始化为单位矩阵
    Matrix result(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        result[i][i] = 1;
    }

    while (p) {
        if (p & 1) {
            result = matrixMultiply(result, A, n);
        }
        A = matrixMultiply(A, A, n);
        p >>= 1;
    }

    return result;
}

int main() {
    int n, p;
    cin >> n >> p;
    
    // 输入矩阵
    Matrix A(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> A[i][j];
        }
    }

    // 计算 A^p
    Matrix result = matrixPower(A, p, n);

    // 输出结果
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
