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