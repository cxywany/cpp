#include <bits/stdc++.h>
using namespace std;
/*
    给定输入字符串s1, s2，保证输入长度s1 > s2, 找到s1中第一次出现s2的位置并输出（s1中第一个字符的位置认为是1），如果未找到，那么输出0
    保证输入长度s1,s2 < 1e5,且保证字符串中均为小写字母
    输入格式:
        s1
        s2
    输出格式：
        一个数字
*/

const int N = 1e5;
int m[26];
bool vis[26] = {0};
bool vis2[26] = {0};
int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    // 初始化m
    for (int i = 0; i < s1.size(); i++)
    {
        char temp = s1[i];
        if (!vis[temp - 'a'])
        {
            vis[temp - 'a'] = 1;
            m[temp - 'a'] = s2.size() + 1;
        }
    }
    // 把s2中的字符更新m
    for (int i = s2.size() - 1; i >= 0; i--) // 注意这里要反着来，因为如果子串中重复出现某一字符，那么算前面的会移动太大，导致答案偏大
    {
        char temp = s2[i];
        if (!vis2[temp - 'a'])
        {
            vis2[temp - 'a'] = 1;
            m[temp - 'a'] = s2.size() - i;
        }
    }
    int st = 0, end = 0, check = 0; // st记录字符串开始匹配的位置，end记录匹配成功的最后一位
    while (st <= s1.size() - s2.size())
    {
        end = 0;
        while (end <= s2.size() - 1)
        {
            if (s1[st + end] == s2[end])
                end++;
            else
                break;
        }
        if (end == s2.size())
        {
            check = 1;
            break;
        }
        else
            st += m[s1[st + s2.size()] - 'a'];
    }
    if (check)
        printf("%d", st + 1);
    else
        printf("0");
    system("pause");
}