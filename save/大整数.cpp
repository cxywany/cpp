#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

string add(string a, string b)
{
    string c;
    int x[N] = {};
    int y[N] = {};
    int z[N] = {};
    for (int i = 0; i < a.size(); i++)
    {
        x[a.size() - 1 - i] = a[i] - '0';
    }
    for (int i = 0; i < b.size(); i++)
    {
        y[b.size() - 1 - i] = b[i] - '0';
    }
    int m = max(a.size(), b.size());
    for (int i = 0; i < m; i++)
    {
        z[i] += x[i] + y[i];
        z[i + 1] += z[i] / 10;
        z[i] = z[i] % 10;
    }
    if (z[m] != 0)
        c.push_back(z[m] + '0');
    for (int i = m - 1; i >= 0; i--)
    {
        c.push_back(z[i] + '0');
    }
    return c;
}

string mul(string a, string b)
{
    string c;
    int x[N] = {};
    int y[N] = {};
    int z[N] = {};
    for (int i = 0; i < a.size(); i++)
    {
        x[a.size() - 1 - i] = a[i] - '0';
    }
    for (int i = 0; i < b.size(); i++)
    {
        y[b.size() - 1 - i] = b[i] - '0';
    }

    int lc = a.size() + b.size();
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            z[i + j] += x[i] * y[j];
            z[i + j + 1] += z[i + j] / 10;
            z[i + j] = z[i + j] % 10;
        }
    }

    while (lc && z[lc] == 0)
        lc--;
    for (int i = lc; i >= 0; i--)
    {
        c.push_back(z[i] + '0');
    }
    return c;
}

int main()
{
    string a, b, c, d;
    cin >> a >> b;
    c = add(a, b);
    d = mul(a, b);
    cout << "和" << c << "积" << d;
    system("pause");
}
