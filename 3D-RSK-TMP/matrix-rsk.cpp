#include <bits/stdc++.h>
#include "../all.h"
#include "spartition_generator.h"

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


bool TEST = false;

//#define ll bigint


using namespace std;

//#include "BigInt.h"

const ll INF = (ll)1e18 + 228;

typedef vector<vector< vector < ll > > > mat3d;



void mat3dprint(mat3d A)
{
	cout << "-----------------------mat3dprint--------------------" << endl;
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = 0;
	for (int i = 0; i < x_len; i++)
		for (int j = 0; j < y_len; j++)
			z_len = max(z_len, (int)A[i][j].size());
	cout << "dimensions: " << x_len << ' ' << y_len << ' ' << z_len << endl;
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{
			for (int k = 0; k < A[i][j].size(); k++)
			{
				cout << A[i][j][k] << ' ';
			}
			//for (int k = 0; k < z_len - (int)A[i][j].size(); k++)
			//	cout << 0 << ' ';	
			cout << endl;
		}
		cout << endl;
	}	
	cout << "-----------------------------------------------------" << endl;
}

vector < ll > mergesort(vector < ll > a, vector < ll > b)
{
	int ptr1 = (int)a.size() - 1;
	int ptr2 = (int)b.size() - 1;
	vector < ll > res;
	while(ptr1 >= 0 || ptr2 >= 0)
	{
		if (ptr1 < 0)
			res.pb(b[ptr2--]);
		else if (ptr2 < 0)
			res.pb(a[ptr1--]);
		else if (a[ptr1] < b[ptr2])
			res.pb(a[ptr1--]);
		else
			res.pb(b[ptr2--]);	
	}	
	reverse(all(res));
	while(!res.empty() && res.back() == 0)
		res.pop_back();
	return res;
}

vector < ll > unmerge(vector < ll > a, vector < ll > b)
{
	vector < ll > res;
	int ptr = 0;
	for (int i = 0; i < (int)a.size(); i++)
	{
		if (ptr < (int)b.size() && a[i] == b[ptr])
			ptr++;
		else
			res.pb(a[i]);	
	}
	if (ptr != b.size())
	{
		cerr << "a: ";
		for (auto it : a)
			cerr << it << ' ';
		cerr << endl;
		cerr << "b: ";
		for (auto it : b)
			cerr << it << ' ';
		cerr << endl;	
	}
	assert(ptr == (int)b.size());
	while(!res.empty() && res.back() == 0)	
		res.pop_back();	
	return res;
}

vector < ll > getmax(vector < ll > a, vector < ll > b)
{
	int n = max((int)a.size(), (int)b.size());
	while((int)a.size() < n)
		a.pb(0);
	while((int)b.size() < n)
		b.pb(0);
	vector < ll > c(n);
	for (int i = 0; i < n; i++)	
		c[i] = max(a[i], b[i]);	
	while(!c.empty() && c.back() == 0)
		c.pop_back();
	return c;	
}

vector < ll > getmin(vector < ll > a, vector < ll > b)
{
	int n = max((int)a.size(), (int)b.size());
	while((int)a.size() < n)
		a.pb(0);
	while((int)b.size() < n)
		b.pb(0);
	vector < ll > c(n);
	for (int i = 0; i < n; i++)	
		c[i] = min(a[i], b[i]);
	while(!c.empty() && c.back() == 0)
		c.pop_back();
	return c;	
}

vector < ll > add(vector < ll > a, vector < ll > b)
{
	int n = max((int)a.size(), (int)b.size());
	while((int)a.size() < n)
		a.pb(0);
	while((int)b.size() < n)
		b.pb(0);
	vector < ll > c(n);
	for (int i = 0; i < n; i++)	
		c[i] = a[i] + b[i];
	while(!c.empty() && c.back() == 0)
		c.pop_back();
	return c;	
}

vector < ll > substract(vector < ll > a, vector < ll > b)
{
	int n = max((int)a.size(), (int)b.size());
	while((int)a.size() < n)
		a.pb(0);
	while((int)b.size() < n)
		b.pb(0);
	vector < ll > c(n);
	for (int i = 0; i < n; i++)	
	{
		c[i] = a[i] - b[i];
		assert(c[i] >= 0);
	}
	while(!c.empty() && c.back() == 0)
		c.pop_back();
	return c;	
}

vector < ll > getentry(const mat3d & p, int i, int j)
{
	if (i < 0 || j < 0)
		return vector < ll > ();
	return p[i][j];
}

void insert(mat3d & p, const mat3d & A, int i, int j)
{
	p[i][j] = mergesort(getmax(getentry(p, i - 1, j), getentry(p, i, j - 1)), getentry(A, i, j));
	while(i > 0 && j > 0)
	{
		i--, j--;
		p[i][j] = substract(add(getmax(getentry(p, i - 1, j), getentry(p, i, j - 1)), getmin(getentry(p, i + 1, j), getentry(p, i, j + 1))), getentry(p, i, j));
	}		
}

mat3d rsk(const mat3d & A)
{
	int x_len = (int)A.size();
	int y_len = (int)A[0].size();
	auto p = A;
	
	for (int i = 0; i < x_len; i++)
		for (int j = 0; j < y_len; j++)
		{
			cout << "insert(" << i << ", " << j << ")" << endl;
			mat3dprint(p);
			insert(p, A, i, j);
		}
	return p;
}

void inverseInsert(mat3d & A, int i, int j)
{
	//cerr << "inverseInsert(" << i << ", " << j << ")" << endl;
	A[i][j] = unmerge(getentry(A, i, j), getmax(getentry(A, i - 1, j), getentry(A, i, j - 1)));
	while(i > 0 && j > 0)
	{
		i--, j--;
		A[i][j] = substract(add(getmax(getentry(A, i - 1, j), getentry(A, i, j - 1)), getmin(getentry(A, i + 1, j), getentry(A, i, j + 1))), getentry(A, i, j));
	}		
}

mat3d inversersk(const mat3d & p)
{
	mat3d A = p;
	int x_len = (int)A.size();
	int y_len = (int)A[0].size();
	
	for (int i = x_len - 1; i >= 0; i--)
		for (int j = y_len - 1; j >= 0; j--)
			inverseInsert(A, i, j);
	return A;
}

ll volume(const mat3d & A)
{
	int x_len = (int)A.size();
	int y_len = (int)A[0].size();
	ll vol = 0;
	for (int i = 0; i < x_len; i++)
		for (int j = 0; j < y_len; j++)
			for (int k = 0; k < (int)A[i][j].size(); k++)
				vol += A[i][j][k];
	return vol;
}

ll desired_volume(const mat3d & A)
{
	int x_len = (int)A.size(); 
	int y_len = (int)A[0].size();
	ll vol = 0;
	for (int i = 0; i < x_len; i++)
		for (int j = 0; j < y_len; j++)
			for (int k = 0; k < (int)A[i][j].size(); k++)
				vol += A[i][j][k] * (x_len - i + y_len - j - 1);
	return vol;	
}

int main()
{
	auto A = mat3d(3, vector < vector < ll > > (3));
	A[0][0] = {3, 1};
	A[0][1] = {2};
	A[0][2] = {2};
	A[1][0] = {4};
	A[1][1] = {2, 2};
	A[1][2] = {3, 1, 1};
	A[2][0] = {1};
	A[2][1] = {4};
	A[2][2] = {3, 3, 1};
	mat3d p = rsk(A);
	mat3dprint(p);
	mat3d B = inversersk(p);
	cerr << "here" << endl;
	mat3dprint(B);
	cerr << "result: " << bool(A == B) << endl;
	cerr << "vol = " << volume(p) << ' ' << "desired volume = " << desired_volume(A) << endl;
}