#include <bits/stdc++.h>

using namespace std;

int blabla(int x)
{
	return x + 1;
}

int plus2(int x, int(*plus1)(int))
{
	return plus1(plus1(x));
}



int main() 
{
	int x;
	cin >> x;
	cout << plus2(x, blabla) << endl;
}