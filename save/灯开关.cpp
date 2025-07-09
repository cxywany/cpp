#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    int a[n][m];
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        for (int j = 0; j < m; j++)
        {
            a[i][j] = str[j] - '0';
        }
    }
    int yesno[n];
    for (int i = 0; i < n; i++)
        yesno[i] = 1;
    for (int i = 0; i < n; i++)
    {
        int judge[m] = {0};
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            else
            {
                for (int k = 0; k < m; k++)
                {
                    judge[k] = judge[k] + a[j][k];
                }
            }
        }
        for (int j = 0; j < m; j++)
        {
            if (judge[j] == 0)
                yesno[i] = 0;
        }
    }
    bool flag = 0;
    for (int i = 0; i < n; i++)
    {
        if (yesno[i] == 1)
        {
            flag = 1;
            break;
        }
    }
    if (flag)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    int a[n][m];
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        for (int j = 0; j < m; j++)
        {
            a[i][j] = str[j] - '0';
        }
    }
    int yesno[n];
    for (int i = 0; i < n; i++)
        yesno[i] = 1;
    for (int i = 0; i < n; i++)
    {
        int judge[m] = {0};
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            else
            {
                for (int k = 0; k < m; k++)
                {
                    judge[k] = judge[k] + a[j][k];
                }
            }
        }
        for (int j = 0; j < m; j++)
        {
            if (judge[j] == 0)
                yesno[i] = 0;
        }
    }
    bool flag = 0;
    for (int i = 0; i < n; i++)
    {
        if (yesno[i] == 1)
        {
            flag = 1;
            break;
        }
    }
    if (flag)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}
