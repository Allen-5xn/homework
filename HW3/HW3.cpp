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