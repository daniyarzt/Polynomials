//By Don4ick 
//#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
typedef unsigned int ui;

#define forn(i, n) for (int i = 1; i <= n; i++)
#define pb push_back
#define all(x) x.begin(), x.end()
#define y1 qewr1234

const double PI = acos(-1.0);
const int DIR = 4;
const int X[] = {1, 0, -1, 0};
const int Y[] = {0, 1, 0, -1};

using namespace std;

int a[100][100][100];

int main()
{
	//ios_base::sync_with_stdio(false);
	//cin.tie();
	//cout.tie();		

	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);

	a[1][1][1] = 1;
	a[1][2][1] = 10;
	a[2][1][1] = 100;
	a[1][1][2] = 1000;
	a[1][2][2] = 10000;
	a[2][1][2] = 100000;
	a[2][2][1] = 1000000;
	a[2][2][2] = 10000000;

 	a[2][1][1] = a[1][1][1] + a[2][1][1];
 	a[1][2][1] = a[1][1][1] + a[1][2][1];
 	a[1][1][2] = a[1][1][1] + a[1][1][2];

	a[2][2][1] = max(a[1][2][1], a[2][1][1]) + a[2][2][1];
	a[1][1][1] = min({a[1][2][1], a[2][1][1]}) - a[1][1][1] + min({a[1][1][2], a[1][2][1], a[2][1][1]});

	a[2][1][2] = max(a[2][1][1], a[1][1][2]) + a[2][1][2];
	a[1][1][1] = min({a[1][1][2], a[2][1][1]}) - a[1][1][1] + min({a[1][1][2], a[1][2][1], a[2][1][1]});

	a[1][2][2] = max(a[1][2][1], a[1][1][2]) + a[1][2][2];
	a[1][1][1] = min({a[1][1][2], a[1][2][1]}) - a[1][1][1] + min({a[1][1][2], a[1][2][1], a[2][1][1]});

	//a[1][1][1] = min({a[1][1][2], a[1][2][1], a[2][1][1]}) - a[1][1][1];

	int sum = 0;
	for (int i = 1; i <= 2; i++)
		for (int j = 1; j <= 2; j++)	
			for (int k = 1; k <= 2; k++)	
				sum += a[i][j][k];
	cout << sum - a[2][2][2] << endl;


	a[2][2][2] = max({a[2][2][1], a[2][1][2], a[1][2][2]}) + a[2][2][2];
	a[2][1][1] = min(a[2][2][1], a[2][1][2]) + a[1][1][1] - a[2][1][1];
	a[1][2][1] = min(a[2][2][1], a[1][2][2]) + a[1][1][1] - a[1][2][1];
	a[1][1][2] = min(a[1][2][2], a[2][1][2]) + a[1][1][1] - a[1][1][2];
	a[1][1][1] = min({a[1][1][2], a[1][2][1], a[2][1][1]}) - a[1][1][1];
	 

	sum = 0;
	for (int i = 1; i <= 2; i++)
		for (int j = 1; j <= 2; j++)	
			for (int k = 1; k <= 2; k++)	
				sum += a[i][j][k];
	cout << sum << endl;

	return 0;
}

