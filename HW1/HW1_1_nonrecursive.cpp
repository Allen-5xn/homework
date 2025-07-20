#include <iostream>
#include <stack>
using namespace std;

int Ackermann(int m, int n) {
    stack<int> stk;
    stk.push(m);
    while (!stk.empty()) {
        m = stk.top();
        stk.pop();
        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            stk.push(m - 1);
            n = 1;
        } else {
            stk.push(m - 1);
            stk.push(m);
            n = n - 1;
        }
    }
    return n;
}

int main() {
    int m = 1, n = 1;
    int result = Ackermann(m, n);
    cout << "Ackermann(" << m << "," << n << ") = " << result << endl;
    return 0;
}