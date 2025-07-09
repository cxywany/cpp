#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, tmp = 1;
    cin >> n;
    vector<vector<int>> v;
    v.emplace_back(1, 1); // 直接构造包含一个元素1的向量

    for (int i = 2; i <= n; ++i)
    {
        if (i % 2 == 0)
        {
            // 偶数行：先扩展现有行，再添加新行到末尾
            for (int j = 0; j < i - 1; ++j)
                v[j].push_back(++tmp);

            // 直接在末尾构造新行
            v.emplace_back();
            v.back().resize(i);
            for (int j = i - 1; j >= 0; --j)
                v.back()[j] = ++tmp;
        }
        else
        {
            // 奇数行：先扩展现有行，再添加新行到开头
            for (int j = i - 2; j >= 0; --j)
                v[j].insert(v[j].begin(), ++tmp);

            // 直接在开头构造新行
            v.emplace(v.begin());
            v[0].resize(i);
            for (int j = 0; j < i; ++j)
                v[0][j] = ++tmp;
        }
    }

    // 输出结果
    for (const auto &row : v)
    {
        for (const auto &num : row)
            cout << num << " ";
        cout << "\n";
    }

    return 0;
}