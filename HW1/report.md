# 41141119

作業一

## Problem 1: Ackermann Function

### 問題描述

Ackermann函數 A(m,n) 定義如下：

$$
A(m,n) = \begin{cases}
n + 1 & \text{if } m = 0 \\
A(m-1, 1) & \text{if } n = 0 \\
A(m-1, A(m, n-1)) & \text{otherwise}
\end{cases}
$$

此函數因為對於較小的 m 和 n 值會快速增長而被研究。要求實現遞迴版本和非遞迴版本的演算法。

### 解題策略

**遞迴版本：**
1. 直接根據數學定義實現三個條件分支
2. 當 m = 0 時，返回 n + 1
3. 當 n = 0 時，遞迴呼叫 A(m-1, 1)
4. 其他情況下，遞迴呼叫 A(m-1, A(m, n-1))

**非遞迴版本：**
1. 使用堆疊模擬遞迴過程
2. 將函數呼叫的參數存放在堆疊中
3. 透過迴圈處理堆疊中的任務，避免遞迴深度限制

### 程式實作

**遞迴版本：**

```cpp
#include <iostream>
using namespace std;

int Ackermann(int m, int n)
{
    if (m == 0) {
        return n + 1;
    }
    else if (n == 0) {
        return Ackermann(m - 1, 1);
    }
    else {
        return Ackermann(m - 1, Ackermann(m, n - 1));
    }
}

int main()
{
    int t = 0;
    int a, b;
    
    cout << "please input (a,b): ";
    cin >> a >> b;
    
    t = Ackermann(a, b);
    
    cout << "Ackermann: " << t << endl;
    
    return 0;
}
```

**非遞迴版本：**

```cpp
#include <iostream>

using namespace std;

int Ackermann(int m, int n)
{
    const int MAX_SIZE = 100000;
    int stack_m[MAX_SIZE];
    int stack_n[MAX_SIZE];
    int top = 0;
    
    stack_m[top] = m;
    stack_n[top] = n;
    top++;
    
    while (top > 0) {
        top--;
        int curr_m = stack_m[top];
        int curr_n = stack_n[top];
        
        if (curr_m == 0) {
            int result = curr_n + 1;
            if (top > 0) {
                stack_n[top - 1] = result;
            } else {
                return result;
            }
        }
        else if (curr_n == 0) {
            stack_m[top] = curr_m - 1;
            stack_n[top] = 1;
            top++;
        }
        else {
            stack_m[top] = curr_m - 1;
            stack_n[top] = -1; 
            top++;
            
            stack_m[top] = curr_m;
            stack_n[top] = curr_n - 1;
            top++;
        }
    }
    
    return -1;
}

int main()
{
    int a, b;
    
    cout << "請輸入 (a,b): ";
    cin >> a >> b;
    
    int result = Ackermann(a, b);
    cout << "Ackermann(" << a << "," << b << ") = " << result << endl;
    
    return 0;
}
```

### 效能分析

**遞迴版本：**
- 時間複雜度：O(A(m,n))，隨著參數值呈指數級增長
- 空間複雜度：O(A(m,n))，受限於遞迴深度

**非遞迴版本：**
- 時間複雜度：O(A(m,n))，與遞迴版本相同
- 空間複雜度：O(A(m,n))，但不受系統堆疊大小限制

### 測試與驗證

| 測試案例 | 輸入 (m,n) | 預期輸出 | 實際輸出 |
|----------|------------|----------|----------|
| 測試一   | (0,0)      | 1        | 1        |
| 測試二   | (0,1)      | 2        | 2        |
| 測試三   | (1,0)      | 2        | 2        |
| 測試四   | (1,1)      | 3        | 3        |
| 測試五   | (3,3)      | 61       | 61       |
| 測試六   | (3,4)      | 125      | 125      |

## Problem 2: Powerset Generation

### 問題描述

如果 S 是一個有 n 個元素的集合，S 的冪集（powerset）是 S 所有可能子集的集合。例如，如果 S = {a,b,c}，則 powerset(S) = {{}, {a}, {b}, {c}, {a,b}, {a,c}, {b,c}, {a,b,c}}。要求撰寫遞迴函數來計算冪集。

### 解題策略

1. 使用遞迴的核心思想：對於集合中的每個元素，都有「包含」和「不包含」兩種選擇
2. 遞迴函數處理當前元素的選擇，並遞迴處理剩餘元素
3. 當處理完所有元素時，輸出當前形成的子集

### 程式實作

```cpp
#include <iostream>
using namespace std;

void powerset(char S[], int n, char subset[], int index, int subsetSize) {
    if (index == n) {
        cout << "{";
        for (int i = 0; i < subsetSize; i++) {
            cout << subset[i];
            if (i < subsetSize - 1) cout << ",";
        }
        cout << "}";
        return;
    }
    
    powerset(S, n, subset, index + 1, subsetSize);
    cout << ", ";
    
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
```

### 效能分析

- 時間複雜度：O(2^n)，因為需要生成所有 2^n 個子集
- 空間複雜度：O(n)，遞迴深度最多為 n

### 測試與驗證

**測試案例：S = {a, b, c}**

預期輸出：`{{}, {c}, {b}, {b,c}, {a}, {a,c}, {a,b}, {a,b,c}}`

實際輸出：`{{}, {c}, {b}, {b,c}, {a}, {a,c}, {a,b}, {a,b,c}}`

### 編譯與執行指令

```shell
$ ./HW1_1_recursive.cpp
please input (a,b): 1 1
Ackermann: 3

$ ./HW1_1_nonrecursive
please input (a,b): 1 1
Ackermann: 3

$ ./HW1_2
powerset(S) = {{}, {c}, {b}, {b,c}, {a}, {a,c}, {a,b}, {a,b,c}}
```

## 申論及開發報告

### Ackermann 函數的特性與挑戰

Ackermann 函數是一個快速增長的函數，具有以下特性：

1. **雙重遞迴結構**：函數定義中包含嵌套的遞迴呼叫，使得計算複雜度極高
2. **快速增長**：即使對於很小的輸入值，函數值也會快速增長
3. **堆疊深度問題**：遞迴版本容易因深度過深而導致堆疊溢出

### 非遞迴實作的優勢

非遞迴版本使用手動管理的堆疊來模擬遞迴過程，具有以下優勢：

1. **避免堆疊溢出**：不受系統遞迴深度限制
2. **可控的記憶體使用**：可以調整堆疊大小以適應不同需求
3. **更好的除錯能力**：可以追蹤堆疊狀態，便於理解執行過程

### 冪集生成的遞迴思想

冪集生成完美展現了遞迴的「分治」思想：

1. **問題分解**：將生成 n 元素集合的冪集分解為處理單個元素的選擇
2. **選擇策略**：對每個元素都有「包含」和「不包含」兩種選擇
3. **結果組合**：透過遞迴的回溯過程，組合出所有可能的子集

### 遞迴與迭代的選擇

在實際開發中，選擇遞迴或迭代需要考慮：

1. **程式碼可讀性**：遞迴通常更接近問題的數學定義
2. **效能考量**：迭代版本通常有更好的時間和空間效率
3. **問題特性**：某些問題（如樹遍歷、分治演算法）天然適合遞迴

通過這次作業，深入理解了遞迴的核心概念，以及如何在必要時將遞迴轉換為迭代實作，這對於處理複雜的演算法問題具有重要意義。