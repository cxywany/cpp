#include <bits/stdc++.h>
using namespace std;

struct p
{
    double x, y;
};

double res(p A, p B, p C)
{
    return fabs(((B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y)) / 2.0);
}

int main()
{
    p a, b, c;
    while (1)
    {
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
        if (a.x == 0 && a.y == 0 && b.x == 0 && b.y == 0 && c.x == 0 && c.y == 0)
            break;
        cout << fixed << setprecision(6) << res(a, b, c) << endl;
    }
}
