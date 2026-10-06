#include <iostream>
using namespace std;
int ackermann(int m, int n){
    if (m == 0)
        return n + 1;
    if (n == 0)
        return ackermann(m - 1, 1);
    int temp = ackermann(m, n - 1);
    return ackermann(m - 1, temp);
}
void push_stack(int*& s, int& top, int& capacity, int value){
    if (top + 1 == capacity){
        int new_capacity = capacity * 2;
        int* bigger = new int[new_capacity];
        for (int i = 0; i <= top; i++)
            bigger[i] = s[i];
        delete[] s;
        s = bigger;
        capacity = new_capacity;
    }
    top++;
    s[top] = value;
}
int pop_stack(int* s, int& top){
    int value = s[top];
    top--;
    return value;
}
int ackermann2(int m, int n){
    int capacity = 16;
    int top = -1;
    int* s = new int[capacity];
    push_stack(s, top, capacity, m);
    while (top >= 0){
        m = pop_stack(s, top);
        if (m == 0)
            n++;
        else if (n == 0){
            n = 1;
            push_stack(s, top, capacity, m - 1);
        }
        else{
            n--;
            push_stack(s, top, capacity, m - 1);
            push_stack(s, top, capacity, m);
        }
    }
    delete[] s;
    return n;
}
int main(){
    int m, n;
    cout << "Enter m and n: ";
    if (!(cin >> m >> n) || m < 0 || n < 0){
        cout << "Please enter non-negative integers.\n";
        return 1;
    }
    cout << "Recursive: " << ackermann(m, n) << '\n';
    cout << "Nonrecursive: " << ackermann2(m, n) << '\n';
    return 0;
}
