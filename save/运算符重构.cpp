#include <bits/stdc++.h>
using namespace std;

class p
{
public:
    int a = 5;
    int b = 10;
};
p operator+(p &p1, p &p2)
{
    p temp;
    temp.a = p1.a + p2.a;
    return temp;
}

ostream &operator<<(ostream &os, p &p1)
{
    os << p1.a;
    return os;
}

int main()
{
    p p1;
    p p2;
    p p3;
    p3 = p1 + p2;
    cout << p3 << endl;
    system("pause");
}
