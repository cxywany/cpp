#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

struct student
{
	int ti, si; // 时间，得分
	int id;
};

student a[N];

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i].ti >> a[i].si;
		a[i].id = i + 1;
	}
	int jili[n + 1] = {};
	vector<int> dalao;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				continue;
			if (a[i].ti >= a[j].ti && a[i].si <= a[j].si)
			{
				jili[a[i].id] = 1;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		if (jili[i] == 0)
			dalao.push_back(i);
	}
	sort(dalao.begin(), dalao.end());
	for (int i = 0; i < dalao.size(); i++)
	{
		cout << dalao[i] << endl;
		system("pause");
	}
}