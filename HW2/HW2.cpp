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