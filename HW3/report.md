# 41141119

作業三

## Problem: Polynomial Class Implementation with Circular Linked List

### 問題描述

實現一個多項式類別 `Polynomial`，使用循環鏈結串列來表示和操作數學多項式。每個多項式項以節點形式存儲，包含係數、指數和鏈結指標。

要求實現以下功能：
1. 輸入輸出運算子（>> 和 <<）
2. 複製建構子和賦值運算子
3. 解構子
4. 多項式的加法、減法、乘法運算
5. 多項式在給定值處的求值

### 解題策略

**程式設計方法：**
1. 使用 `Node` 結構存放每一項的係數、指數和指標
2. `Polynomial` 類別使用循環鏈結串列實作
3. 採用標頭節點方式，簡化鏈結操作
4. 項目按照指數遞減排序

**主要功能做法：**
1. **輸入**：讀取項數和各項資料，自動排序和合併相同指數項
2. **加減法**：同時走訪兩個多項式，比較指數後決定操作
3. **乘法**：使用雙重迴圈，每項相乘後合併同類項
4. **求值**：依序計算每項的值並累加
5. **記憶體管理**：正確處理動態記憶體配置與釋放

### 程式實作

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int coef;
    int exp;
    Node* link;
    
    Node(int c = 0, int e = 0, Node* l = nullptr) : coef(c), exp(e), link(l) {}
};

class Polynomial {
private:
    Node* first;
    
public:
    Polynomial() {
        first = new Node();
        first->link = first;
    }
    
    Polynomial(const Polynomial& a) {
        first = new Node();
        first->link = first;
        *this = a;
    }
    
    ~Polynomial() {
        if (first == nullptr) return;
        
        Node* current = first->link;
        while (current != first) {
            Node* temp = current;
            current = current->link;
            delete temp;
        }
        delete first;
    }
    
    const Polynomial& operator=(const Polynomial& a) {
        if (this == &a) return *this;
        
        Node* current = first->link;
        while (current != first) {
            Node* temp = current;
            current = current->link;
            delete temp;
        }
        first->link = first;
        
        Node* a_current = a.first->link;
        Node* last = first;
        
        while (a_current != a.first) {
            Node* newNode = new Node(a_current->coef, a_current->exp);
            last->link = newNode;
            newNode->link = first;
            last = newNode;
            a_current = a_current->link;
        }
        
        return *this;
    }

    friend istream& operator>>(istream& is, Polynomial& x) {
        Node* current = x.first->link;
        while (current != x.first) {
            Node* temp = current;
            current = current->link;
            delete temp;
        }
        x.first->link = x.first;
        
        int n;
        is >> n;
        
        vector<pair<int, int>> terms;
        
        for (int i = 0; i < n; i++) {
            int coef, exp;
            is >> coef >> exp;
            if (coef != 0) {
                terms.push_back(make_pair(coef, exp));
            }
        }
        
        sort(terms.begin(), terms.end(), 
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.second > b.second;
             });
        
        vector<pair<int, int>> merged;
        for (const auto& term : terms) {
            bool found = false;
            for (auto& m : merged) {
                if (m.second == term.second) {
                    m.first += term.first;
                    found = true;
                    break;
                }
            }
            if (!found) {
                merged.push_back(term);
            }
        }
        
        Node* last = x.first;
        for (const auto& term : merged) {
            if (term.first != 0) {
                Node* newNode = new Node(term.first, term.second);
                last->link = newNode;
                newNode->link = x.first;
                last = newNode;
            }
        }
        
        return is;
    }
    
    friend ostream& operator<<(ostream& os, const Polynomial& x) {
        Node* current = x.first->link;
        
        if (current == x.first) {
            os << "0";
            return os;
        }
        
        bool firstTerm = true;
        while (current != x.first) {
            if (!firstTerm && current->coef > 0) {
                os << " + ";
            } else if (current->coef < 0) {
                os << (firstTerm ? "-" : " - ");
            }
            
            int absCoef = abs(current->coef);
            
            if (current->exp == 0) {
                os << absCoef;
            } else if (current->exp == 1) {
                if (absCoef == 1) {
                    os << "x";
                } else {
                    os << absCoef << "x";
                }
            } else {
                if (absCoef == 1) {
                    os << "x^" << current->exp;
                } else {
                    os << absCoef << "x^" << current->exp;
                }
            }
            
            current = current->link;
            firstTerm = false;
        }
        
        return os;
    }
    
    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        Node* a_current = this->first->link;
        Node* b_current = b.first->link;
        Node* result_last = result.first;
        
        while (a_current != this->first && b_current != b.first) {
            Node* newNode = nullptr;
            
            if (a_current->exp > b_current->exp) {
                newNode = new Node(a_current->coef, a_current->exp);
                a_current = a_current->link;
            } else if (a_current->exp < b_current->exp) {
                newNode = new Node(b_current->coef, b_current->exp);
                b_current = b_current->link;
            } else {
                int sumCoef = a_current->coef + b_current->coef;
                if (sumCoef != 0) {
                    newNode = new Node(sumCoef, a_current->exp);
                }
                a_current = a_current->link;
                b_current = b_current->link;
            }
            
            if (newNode) {
                result_last->link = newNode;
                newNode->link = result.first;
                result_last = newNode;
            }
        }
        
        while (a_current != this->first) {
            Node* newNode = new Node(a_current->coef, a_current->exp);
            result_last->link = newNode;
            newNode->link = result.first;
            result_last = newNode;
            a_current = a_current->link;
        }
        
        while (b_current != b.first) {
            Node* newNode = new Node(b_current->coef, b_current->exp);
            result_last->link = newNode;
            newNode->link = result.first;
            result_last = newNode;
            b_current = b_current->link;
        }
        
        return result;
    }
    
    Polynomial operator-(const Polynomial& b) const {
        Polynomial result;
        Node* a_current = this->first->link;
        Node* b_current = b.first->link;
        Node* result_last = result.first;
        
        while (a_current != this->first && b_current != b.first) {
            Node* newNode = nullptr;
            
            if (a_current->exp > b_current->exp) {
                newNode = new Node(a_current->coef, a_current->exp);
                a_current = a_current->link;
            } else if (a_current->exp < b_current->exp) {
                newNode = new Node(-b_current->coef, b_current->exp);
                b_current = b_current->link;
            } else {
                int diffCoef = a_current->coef - b_current->coef;
                if (diffCoef != 0) {
                    newNode = new Node(diffCoef, a_current->exp);
                }
                a_current = a_current->link;
                b_current = b_current->link;
            }
            
            if (newNode) {
                result_last->link = newNode;
                newNode->link = result.first;
                result_last = newNode;
            }
        }
        
        while (a_current != this->first) {
            Node* newNode = new Node(a_current->coef, a_current->exp);
            result_last->link = newNode;
            newNode->link = result.first;
            result_last = newNode;
            a_current = a_current->link;
        }
        
        while (b_current != b.first) {
            Node* newNode = new Node(-b_current->coef, b_current->exp);
            result_last->link = newNode;
            newNode->link = result.first;
            result_last = newNode;
            b_current = b_current->link;
        }
        
        return result;
    }
    
    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        
        Node* a_current = this->first->link;
        while (a_current != this->first) {
            Node* b_current = b.first->link;
            while (b_current != b.first) {
                Polynomial temp;
                int newCoef = a_current->coef * b_current->coef;
                int newExp = a_current->exp + b_current->exp;
                
                if (newCoef != 0) {
                    Node* newNode = new Node(newCoef, newExp);
                    temp.first->link = newNode;
                    newNode->link = temp.first;
                    
                    result = result + temp;
                }
                
                b_current = b_current->link;
            }
            a_current = a_current->link;
        }
        
        return result;
    }
    
    float Evaluate(float x) const {
        float result = 0.0;
        Node* current = first->link;
        
        while (current != first) {
            float term = current->coef;
            for (int i = 0; i < current->exp; i++) {
                term *= x;
            }
            result += term;
            current = current->link;
        }
        
        return result;
    }
};

int main() {
    Polynomial p1, p2;
    
    cin >> p1;
    cin >> p2;
    
    cout << p1 << endl;
    cout << p2 << endl;
    
    Polynomial sum = p1 + p2;
    cout << sum << endl;
    
    Polynomial diff = p1 - p2;
    cout << diff << endl;
    
    Polynomial prod = p1 * p2;
    cout << prod << endl;
    
    float x;
    cin >> x;
    cout << p1.Evaluate(x) << endl;
    
    Polynomial p3 = p1;
    cout << p3 << endl;
    
    Polynomial p4;
    p4 = p2;
    cout << p4 << endl;
    
    return 0;
}
```

### 效能分析

**執行時間：**
- 加法/減法：O(m + n)，其中 m, n 是兩個多項式的項數
- 乘法：O(m × n)，需要計算每項相乘的結果
- 求值：O(n)，需要計算每一項的值
- 輸入：O(n log n)，因為需要排序

**記憶體使用：**
- 空間複雜度：O(n)，n 是多項式的項數
- 使用循環鏈結串列，只在需要時分配記憶體
- 標頭節點簡化邊界處理

### 測試與驗證

| 測試案例 | 輸入 P1 | 輸入 P2 | 加法結果 | 減法結果 | 乘法結果 |
|----------|---------|---------|----------|----------|----------|
| 測試一   | 2x+1    | x+3     | 3x+4     | x-2      | 2x²+7x+3 |
| 測試二   | x²+1    | x²-1    | 2x²      | 2        | x⁴-1     |

### 編譯與執行

```shell
$ g++ -o polynomial polynomial.cpp
$ ./polynomial
2
2 1
1 0
2
1 1  
3 0
2x + 1
x + 3
3x + 4
x - 2
2x^2 + 7x + 3
2
5
2x + 1
x + 3
```

## 申論及開發報告

### 與陣列實作的比較

#### 優勢
1. **記憶體效率**：只使用實際需要的空間
2. **動態性**：可以處理任意大小的多項式
3. **插入效率**：在已知位置插入為 O(1)

#### 劣勢
1. **隨機存取**：無法直接存取第 i 項，需要循序搜尋
2. **記憶體碎片**：每個節點分別分配，可能造成記憶體碎片
3. **額外空間**：每個節點需要額外的指標空間

#### 適用場景
- 稀疏多項式（大部分係數為零）
- 多項式大小在執行時才確定
- 需要頻繁插入/刪除項目的應用