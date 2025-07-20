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