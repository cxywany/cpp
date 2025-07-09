#include <iostream>
#include <string>

using namespace std;

// 算法4-13: 求解模式串t的next数组
void GetNext(const string &t, int *next)
{
    int m = t.length();
    next[0] = -1;

    for (int i = 1; i < m; i++)
    { // 求出next[1]~next[m-1]
        int j = next[i - 1];
        while (j >= 0 && t[i] != t[j + 1])
            j = next[j];

        if (t[i] == t[j + 1])
            next[i] = j + 1;
        else
            next[i] = -1;
    }
}

// 算法4-14: 字符串匹配的KMP算法
int PatternMatchKMP(const string &s, const string &t)
{
    int n = s.length();
    int m = t.length();
    int p = -1; // NIL用-1表示

    if (n >= m)
    {
        int *next = new int[m];
        GetNext(t, next);

        int i = 0;
        int j = 0;

        while (j < n && i < m)
        {
            if (s[j] == t[i])
            {
                i++;
                j++;
            }
            else if (i > 0)
                i = next[i - 1] + 1;
            else
                j++;
        }

        if (i == m)
            p = j - m;

        delete[] next;
    }
    return p;
}

// 打印next数组
void PrintNextArray(const string &t)
{
    int m = t.length();
    int *next = new int[m];

    GetNext(t, next);

    cout << "字符串 \"" << t << "\" 的next数组: ";
    for (int i = 0; i < m; i++)
    {
        cout << next[i] << " ";
    }
    cout << endl;

    delete[] next;
}

int main()
{
    system("chcp 65001");

    string s, t;
    cout << "请输入目标串: ";
    getline(cin, s);

    cout << "请输入模式串: ";
    getline(cin, t);

    // 打印next数组
    PrintNextArray(t);

    // 查找第一个匹配位置
    int position = PatternMatchKMP(s, t);
    if (position != -1)
    {
        cout << "起始位置: " << position << endl;
    }
    else
    {
        cout << "未找到匹配" << endl;
    }

    system("pause");
    return 0;
}