#include <iostream>
#include <algorithm>
using namespace std;
int m;
bool is_first_subset = true;
void powerset(int index, bool* chosen, char* p){
    if (index == m){
        if (!is_first_subset)
            cout << ", ";
        is_first_subset = false;
        cout << "(";
        bool first_element = true;
        for (int i = 0; i < m; i++){
            if (chosen[i]){
                if (!first_element)
                    cout << ", ";
                cout << p[i];
                first_element = false;
            }
        }
        cout << ")";
        return;
    }
    chosen[index] = false;
    powerset(index + 1, chosen, p);
    chosen[index] = true;
    powerset(index + 1, chosen, p);
}
int main(){
    int n;
    cout << "Enter the number of characters: ";
    if (!(cin >> n) || n < 0){
        cout << "Please enter a non-negative integer.\n";
        return 1;
    }
    char* p = new char[n];
    cout << "Enter the characters (for example: a b c): ";
    for (int i = 0; i < n; i++){
        if (!(cin >> p[i])){
            delete[] p;
            cout << "Invalid input.\n";
            return 1;
        }
    }
    sort(p, p + n);
    m = 0;
    for (int i = 0; i < n; i++){
        if (m == 0 || p[i] != p[m - 1]){
            p[m] = p[i];
            m++;
        }
    }
    bool* chosen = new bool[m];
    for (int i = 0; i < m; i++)
        chosen[i] = false;
    is_first_subset = true;
    cout << "powerset(S) = {";
    powerset(0, chosen, p);
    cout << "}\n";
    delete[] chosen;
    delete[] p;
    return 0;
}
