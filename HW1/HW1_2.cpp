#include <iostream>
using namespace std;

// 遞歸函數來計算冪集並直接打印
// S: 原始集合陣列
// n: 集合大小
// subset: 當前子集陣列
// index: 當前處理到第幾個元素
// subsetSize: 當前子集的大小
void powerset(char S[], int n, char subset[], int index, int subsetSize) {
    // 基本情況：已經處理完所有元素，打印當前子集
    if (index == n) {
        cout << "{";
        for (int i = 0; i < subsetSize; i++) {
            cout << subset[i];
            if (i < subsetSize - 1) cout << ",";
        }
        cout << "}";
        return;
    }
    
    // 選擇1：不包含當前元素 S[index]
    powerset(S, n, subset, index + 1, subsetSize);
    cout << ", ";
    
    // 選擇2：包含當前元素 S[index]
    subset[subsetSize] = S[index];  // 將當前元素加入子集
    powerset(S, n, subset, index + 1, subsetSize + 1);
}

// 包裝函數，方便呼叫
void printPowerset(char S[], int n) {
    char subset[n];  // 用來存儲當前子集的陣列
    cout << "{";
    powerset(S, n, subset, 0, 0);
    cout << "}" << endl;
}

int main() {
    // 測試例子：S = {a, b, c}
    char S[] = {'a', 'b', 'c'};
    int n = 3;
   
    cout << "powerset(S) = ";
    printPowerset(S, n);
    
    return 0;
}