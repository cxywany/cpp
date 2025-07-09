#include <iostream>
#include "add.h"
using namespace std;

int main()
{
    int b = 0, c = 0;
    cin >> b >> c;
    int a = add(b, c);
    cout << a << endl;
    system("pause");
}