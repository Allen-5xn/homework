# 41141119

作業二

## Problem: Polynomial Class Implementation

### 問題描述

實現一個多項式類別 `Polynomial`，用於表示和操作數學多項式。多項式以有序對 `<ei, ai>` 的形式存儲，其中 `ai` 是非零浮點係數，`ei` 是非負整數指數。

要求實現以下功能：
1. 多項式的加法運算
2. 多項式的乘法運算
3. 多項式在給定值處的求值

### 解題策略

**程式設計方法：**
1. 用 `Term` 類別來存放每一項的係數和指數
2. `Polynomial` 類別用陣列來存放所有的項
3. 項目按照指數大到小排列，方便顯示

**主要功能做法：**
1. **加法**：把兩個多項式的項一個一個處理，相同次方的合併
2. **乘法**：第一個多項式的每一項都要跟第二個的每一項相乘
3. **求值**：把 x 代入每一項計算，然後全部加起來
4. **記憶體處理**：當陣列不夠大時自動擴大

### 程式實作

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Polynomial;

class Term {
    friend Polynomial;
private:
    float coef;
    int exp;
public:
    Term(float c = 0, int e = 0) : coef(c), exp(e) {}
};

class Polynomial {
private:
    Term *termArray;
    int capacity;
    int terms;

public:
    Polynomial() {
        capacity = 1;
        terms = 0;
        termArray = new Term[capacity];
    }
    
    Polynomial(int cap) {
        capacity = cap;
        terms = 0;
        termArray = new Term[capacity];
    }
    
    Polynomial(const Polynomial& other) {
        capacity = other.capacity;
        terms = other.terms;
        termArray = new Term[capacity];
        for (int i = 0; i < terms; i++) {
            termArray[i] = other.termArray[i];
        }
    }
    
    ~Polynomial() {
        delete[] termArray;
    }
    
    Polynomial& operator=(const Polynomial& other) {
        if (this != &other) {
            delete[] termArray;
            capacity = other.capacity;
            terms = other.terms;
            termArray = new Term[capacity];
            for (int i = 0; i < terms; i++) {
                termArray[i] = other.termArray[i];
            }
        }
        return *this;
    }
    
    void addTerm(float coef, int exp) {
        if (coef == 0) return;
        
        for (int i = 0; i < terms; i++) {
            if (termArray[i].exp == exp) {
                termArray[i].coef += coef;
                if (termArray[i].coef == 0) {
                    for (int j = i; j < terms - 1; j++) {
                        termArray[j] = termArray[j + 1];
                    }
                    terms--;
                }
                return;
            }
        }
        
        if (terms >= capacity) {
            capacity *= 2;
            Term* newArray = new Term[capacity];
            for (int i = 0; i < terms; i++) {
                newArray[i] = termArray[i];
            }
            delete[] termArray;
            termArray = newArray;
        }
        
        int pos = terms;
        for (int i = 0; i < terms; i++) {
            if (exp > termArray[i].exp) {
                pos = i;
                break;
            }
        }
        
        for (int i = terms; i > pos; i--) {
            termArray[i] = termArray[i - 1];
        }
        
        termArray[pos].coef = coef;
        termArray[pos].exp = exp;
        terms++;
    }
    
    Polynomial Add(Polynomial poly) {
        Polynomial result;
        
        for (int i = 0; i < terms; i++) {
            result.addTerm(termArray[i].coef, termArray[i].exp);
        }
        
        for (int i = 0; i < poly.terms; i++) {
            result.addTerm(poly.termArray[i].coef, poly.termArray[i].exp);
        }
        
        return result;
    }
    
    Polynomial Mult(Polynomial poly) {
        Polynomial result;
        
        for (int i = 0; i < terms; i++) {
            for (int j = 0; j < poly.terms; j++) {
                float newCoef = termArray[i].coef * poly.termArray[j].coef;
                int newExp = termArray[i].exp + poly.termArray[j].exp;
                result.addTerm(newCoef, newExp);
            }
        }
        
        return result;
    }
    
    float Eval(float f) {
        float result = 0;
        for (int i = 0; i < terms; i++) {
            result += termArray[i].coef * pow(f, termArray[i].exp);
        }
        return result;
    }
    
    friend ostream& operator<<(ostream& os, const Polynomial& poly) {
        if (poly.terms == 0) {
            os << "0";
            return os;
        }
        
        bool first = true;
        for (int i = 0; i < poly.terms; i++) {
            float coef = poly.termArray[i].coef;
            int exp = poly.termArray[i].exp;
            
            if (!first && coef > 0) {
                os << " + ";
            } else if (coef < 0) {
                if (first) {
                    os << "-";
                } else {
                    os << " - ";
                }
                coef = -coef;
            }
            
            if (exp == 0) {
                os << coef;
            } else if (exp == 1) {
                if (coef == 1) {
                    os << "x";
                } else {
                    os << coef << "x";
                }
            } else {
                if (coef == 1) {
                    os << "x^" << exp;
                } else {
                    os << coef << "x^" << exp;
                }
            }
            
            first = false;
        }
        return os;
    }
    
    friend istream& operator>>(istream& is, Polynomial& poly) {
        int numTerms;
        cout << "Terms: ";
        is >> numTerms;
        
        poly.terms = 0;
        
        for (int i = 0; i < numTerms; i++) {
            float coef;
            int exp;
            is >> coef >> exp;
            poly.addTerm(coef, exp);
        }
        
        return is;
    }
};

int main() {
    Polynomial p1, p2, p3, p4;
    
    cin >> p1;
    cout << "P1 = " << p1 << endl;
    
    cin >> p2;
    cout << "P2 = " << p2 << endl;
    
    p3 = p1.Add(p2);
    cout << "Add = " << p3 << endl;
    
    p4 = p1.Mult(p2);
    cout << "Mult = " << p4 << endl;
    
    float x;
    cout << "x = ";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.Eval(x) << endl;
    cout << "P2(" << x << ") = " << p2.Eval(x) << endl;
    cout << "P1+P2(" << x << ") = " << p3.Eval(x) << endl;
    cout << "P1*P2(" << x << ") = " << p4.Eval(x) << endl;
    
    return 0;
}
```

### 效能分析

**執行時間：**
- 加法：要處理兩個多項式的所有項目
- 乘法：第一個多項式的每項都要跟第二個的每項相乘，所以比較慢
- 求值：要算每一項的值，項目越多越慢

**記憶體使用：**
- 需要的記憶體跟多項式有多少項成正比
- 當空間不夠時會自動變成兩倍大

### 測試與驗證

| 測試案例 | 輸入 P1 | 輸入 P2 | 加法結果 | 乘法結果 |
|----------|---------|---------|----------|----------|
| 測試一   | 2x+1    | x+3     | 3x+4     | 2x²+7x+3 |
| 測試二   | x²+1    | x²-1    | 2x²      | x⁴-1     |


### 主要功能說明

**1. 自動調整記憶體大小**
- 當陣列滿了會自動變大，不用擔心空間不夠
- 程式會自動複製資料和清理舊記憶體

**2. 項目管理**
- 自動把相同次方的項目合併（如 2x + 3x = 5x）
- 按照次方大小排序（x² 在 x 前面）
- 係數變成 0 的項目會自動刪除

**3. 好看的輸出格式**
- 正確顯示正負號
- 係數是 1 時會省略不顯示（顯示 x 而不是 1x）
- 處理常數項和一次項的特殊情況

### 編譯與執行指令

```shell
$ g++ -o polynomial polynomial.cpp
$ ./polynomial
Terms: 2
2 1
1 0
P1 = 2x + 1
Terms: 2  
1 1
3 0
P2 = x + 3
Add = 3x + 4
Mult = 2x^2 + 7x + 3
x = 2
P1(2) = 5
P2(2) = 5
P1+P2(2) = 10
P1*P2(2) = 25
```

## 申論與開發報告

### 物件導向程式設計的好處

這次寫程式用到了物件導向的基本概念：

1. **資料保護**：把多項式內部的資料藏起來，只能透過特定方法使用
2. **類別合作**：Term 和 Polynomial 兩個類別可以互相存取資料
3. **運算子重新定義**：讓 `<<` 和 `>>` 可以直接輸入輸出多項式

### 記憶體管理的學習

在 C++ 中管理記憶體很重要：

1. **建立時分配，結束時釋放**：程式開始時要記憶體，結束時要還回去
2. **正確複製**：複製多項式時要把每個資料都複製，不能只複製地址
3. **避免記憶體洩漏**：確保每次申請的記憶體都有正確釋放

### 程式效率的考慮

寫程式時要考慮快慢和功能的平衡：

1. **插入新項目**：雖然要移動其他項目比較慢，但可以保持順序
2. **陣列擴大**：用加倍的方式擴大，平均來說很有效率
3. **處理零項**：自動刪掉係數為零的項，讓多項式保持簡潔

