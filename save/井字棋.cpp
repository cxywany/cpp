#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;

int main()
{
	int n;
	cin >> n;
	char first[n];
	for (int i = 0; i < n; i++)
	{
		cin >> first[i];
	}
	int a[3][3] = {};
	cin.ignore();

	for (int i = 0; i < n; i++)
	{
		for (int i = 0; i < 3; i++)
		{
			string line;
			getline(cin, line);
			for (int j = 0; j < 3; j++)
			{
				a[i][j] = line[j] - '0';
			}
		}
		char judge = first[i];
		bool flag = 0;
		int n;
		for (int j = 0; j < 3; j++)
		{
			if (a[j][0] == a[j][1] && a[j][1] == a[j][0])
			{
				n = a[j][0];
				flag = 1;
				break;
			}
		}
		if ((a[0][0] == a[2][2] && a[2][2] == a[3][3]) || (a[1][3] == a[2][2] && a[2][2] == a[3][1]))
		{
			n = a[2][2];
			flag = 1;
			break;
		}
		if (flag)
		{
			if (n == 1)
			{
				cout << judge << endl;
			}
			else
			{
				if (judge == 'A')
				{
					cout << 'B' << endl;
				}
				else
				{
					cout << 'A' << endl;
				}
			}
		}
	}
	system("pause");
}