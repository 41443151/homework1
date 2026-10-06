# 41143263

## 作業一：Ackermann 函數

### 解題說明

本題使用遞迴與非遞迴兩種方式計算 Ackermann 函數。

1. 當 `m == 0`，回傳 `n + 1`。
2. 當 `m > 0` 且 `n == 0`，計算 `A(m - 1, 1)`。
3. 其他情況先計算 `A(m, n - 1)`，再計算 `A(m - 1, 內層結果)`。

遞迴版本由函式呼叫自己；非遞迴版本依照講義，用動態陣列保存還沒處理的資料，不使用 `<stack>`。

### 程式實作

檔案：`ackermann.cpp`

```cpp
#include <iostream>
using namespace std;

// 遞迴：直接依照題目的三個規則計算。
int ackermann(int m, int n)
{
    if (m == 0)
        return n + 1;
    if (n == 0)
        return ackermann(m - 1, 1);

    int temp = ackermann(m, n - 1);
    return ackermann(m - 1, temp);
}

// 自己用動態陣列加入資料，不使用 <stack>。
void push_stack(int*& s, int& top, int& capacity, int value)
{
    if (top + 1 == capacity)
    {
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

// 呼叫前，必須確定陣列中還有待處理的資料。
int pop_stack(int* s, int& top)
{
    int value = s[top];
    top--;
    return value;
}

int ackermann_nonrecursive(int m, int n)
{
    int capacity = 16;
    int top = -1;
    int* s = new int[capacity];

    push_stack(s, top, capacity, m);

    while (top >= 0)
    {
        m = pop_stack(s, top);

        if (m == 0)
            n++;
        else if (n == 0)
        {
            n = 1;
            push_stack(s, top, capacity, m - 1);
        }
        else
        {
            n--;
            // 外層先放，內層後放，所以內層先處理。
            push_stack(s, top, capacity, m - 1);
            push_stack(s, top, capacity, m);
        }
    }

    delete[] s;
    return n;
}

int main()
{
    int m, n;
    cout << "Enter m and n: ";
    if (!(cin >> m >> n) || m < 0 || n < 0)
    {
        cout << "Please enter non-negative integers.\n";
        return 1;
    }

    cout << "Recursive: " << ackermann(m, n) << '\n';
    cout << "Nonrecursive: " << ackermann_nonrecursive(m, n) << '\n';
    return 0;
}
```

### 效能分析

- 時間：兩個版本都需要反覆套用公式，輸入變大時，計算次數會快速增加。
- 空間：遞迴版本需要保存函式呼叫；非遞迴版本需要動態陣列保存待處理的資料。
- 程式使用 `int`，因此先用小數字測試，避免超出整數範圍或計算太久。

### 測試與驗證

以下為實際執行結果：

| 輸入 m、n | 預期結果 | 遞迴結果 | 非遞迴結果 |
|---|---|---|---|
| 0、0 | 1 | 1 | 1 |
| 1、1 | 3 | 3 | 3 |
| 2、2 | 7 | 7 | 7 |

兩種方法的結果相同，以上案例皆符合預期。

### 申論及開發報告

遞迴的寫法接近數學公式，較容易理解。非遞迴需要自己記住還沒完成的工作，並注意先處理內層，再處理外層。動態陣列使用完後，以 `delete[]` 釋放記憶體。

---

## 作業二：Power Set

### 解題說明

本題使用遞迴列出集合的所有子集合，也就是冪集合。

1. 在 `main()` 輸入字元，排序並去除重複。
2. 用 `chosen[]` 記錄每個元素是否被選取。
3. 每個元素分成「不選」與「選」兩條路。
4. 全部元素都決定完後，印出一個子集合。

例如 `{a,b}` 的所有子集合為 `()`、`(b)`、`(a)`、`(a,b)`，其中 `()` 表示空集合。

### 程式實作

檔案：`powerset.cpp`

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

// 依照投影片的介面，使用全域變數記錄集合大小與輸出狀態。
int m;
bool is_first_subset = true;

void powerset(int index, bool* chosen, char* p)
{
    if (index == m)
    {
        if (!is_first_subset)
            cout << ", ";
        is_first_subset = false;

        cout << "(";
        bool first_element = true;
        for (int i = 0; i < m; i++)
        {
            if (chosen[i])
            {
                if (!first_element)
                    cout << ", ";
                cout << p[i];
                first_element = false;
            }
        }
        cout << ")";
        return;
    }

    // 第一條路：不選目前的元素。
    chosen[index] = false;
    powerset(index + 1, chosen, p);

    // 第二條路：選目前的元素。
    chosen[index] = true;
    powerset(index + 1, chosen, p);
}

int main()
{
    int n;
    cout << "Enter the number of characters: ";
    if (!(cin >> n) || n < 0)
    {
        cout << "Please enter a non-negative integer.\n";
        return 1;
    }

    char* p = new char[n];
    cout << "Enter the characters (for example: a b c): ";
    for (int i = 0; i < n; i++)
    {
        if (!(cin >> p[i]))
        {
            delete[] p;
            cout << "Invalid input.\n";
            return 1;
        }
    }

    sort(p, p + n);

    // 排序後，相同字元會相鄰，只保留每組的第一個字元。
    m = 0;
    for (int i = 0; i < n; i++)
    {
        if (m == 0 || p[i] != p[m - 1])
        {
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
```

### 效能分析

假設輸入有 n 個字元，去除重複後有 m 個元素：

- 排序需要 O(n log n) 時間。
- 共有 2^m 個子集合，每次輸出都檢查 m 個位置，因此 m ≥ 1 時，列出全部子集合需要 O(m × 2^m) 時間。
- 陣列和遞迴需要 O(n + m) 空間；空集合只需固定空間。

### 測試與驗證

以下為實際執行結果，省略輸入提示文字：

| 輸入數量與字元 | 預期結果 | 實際結果 |
|---|---|---|
| `0` | `{()}` | `{()}` |
| `1`；`x` | `{(), (x)}` | `{(), (x)}` |
| `3`；`a b c` | 8 個不同子集合 | 8 個不同子集合 |
| `4`；`c a a b` | 去重後列出 8 個子集合 | 去重後列出 8 個子集合 |

輸入 `a b c` 時，完整結果為：

```text
powerset(S) = {(), (c), (b), (b, c), (a), (a, c), (a, b), (a, b, c)}
```

### 申論及開發報告

每個元素只有「選」或「不選」兩種情況，因此適合用遞迴處理。先去除重複元素，可以避免重複輸出相同的子集合。`main()` 負責整理輸入，`powerset()` 負責遞迴，讓程式分工清楚。

兩個程式各有自己的 `main()`，需要分別編譯執行。
