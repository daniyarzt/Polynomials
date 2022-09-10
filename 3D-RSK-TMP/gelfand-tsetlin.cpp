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
	
bool isColumnDecreasing(mat3d A)
{
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();
	for (int i = 0; i < x_len - 1; i++)
	{
		for (int j = 0; j < y_len; j++)
		{
			for (int k = 0; k < z_len; k++)
			{
				if (A[i][j][k] > 0 && A[i][j][k] == A[i + 1][j][k])
					return false;
			}
		}
	}
	return true;

}

vector < vector < int > > getShape(mat3d A)
{
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();
	
	vector < vector < int > > res;
	for (int i = 0; i < x_len; i++)
	{
		if (A[i][0][0] == 0)
			break;
		res.emplace_back();	
		for (int j = 0; j < y_len; j++)
		{
			if (A[i][j][0] == 0)
				break;
			res.back().emplace_back();	
			int & k = res.back().back();
			while(k < z_len && A[i][j][k])
				k++;
		}
	}
	return res;
}

void experiment19082022() // Check the sum{s_pi(q)^2} = sum_{q^|sigma|}
{
	int n = 5;
	vector < mat3d > sp;
	
	for (int i = 1; i <= n; i++)
	{
		auto G = SolidPartitionGenerator(n, n, n, i);
		
		auto cur = G.getNext();
		do
		{
			sp.pb(cur);
			cur = G.getNext();
		}	
		while(!cur.empty());
		cerr << cur.size() << endl;

	}

	vector < pair < vector < vector < int > >, mat3d > > ssyt;
	for (auto p : sp)	
		if (isColumnDecreasing(p))
			ssyt.pb({getShape(p), p});
	sort(all(ssyt));	
	cerr << sp.size() << endl;
		
}

int main() 
{
	experiment19082022();
}