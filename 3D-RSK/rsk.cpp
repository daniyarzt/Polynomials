

//By Don4ick 
//#define _GLIBCXX_DEBUG

#include <bits/stdc++.h>
#include "../all.h"

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


//#define ll bigint


using namespace std;

//#include "BigInt.h"

const ll INF = (ll)1e18 + 228;

typedef vector<vector< vector < ll > > > mat3d;
	

#define spartition 
struct SolidPartition 
{
	// initial matrix 
	mat3d vals;

	// Solid partition that is created by rks() method, unlike par, 
	// values are stored as polynomials with variables corresponding the inial matrix entries
	vector < vector < vector < pair < ll, Polynomial > > > > par;   

	SolidPartition () {}

	// Generator that simply assings the given matrix values for a partition
	// There is no check if solid partition is valid!
	// Polynomial matrix is set x_{i * ylen * zlen + j * zlen + k}
	SolidPartition (mat3d A) 
	{
		vals = A;		

		assert(!A.empty() && !A[0].empty() && !A[0][0].empty());
	    int xlen = A.size();
	    int ylen = A[0].size();
	    int zlen = A[0][0].size();

	    for (int i = 0; i < xlen; i++)
	    {
	    	par.emplace_back();
	    	for (int j = 0; j < ylen; j++)
	    	{
	    		par[i].emplace_back();
	    		for (int k = 0; k < zlen; k++)
	    		{
	    			par[i][j].push_back({A[i][j][k], Xpower(i * ylen * zlen + j * zlen + k, 1)});
	    		}
	    	}
	    }
	}

	int x_len()
	{
		return par.size();
	}
	
	int y_len()
	{
		return par[0].size();
	}
	
	int z_len()
	{
		return par[0][0].size();
	}
	
	pair < long long, Polynomial > get(int i, int j, int k)
	{
		if (i < 0 || j < 0 || k < 0)
			return {0, Polynomial()};
		if (i >= x_len() || j >= y_len() || k >= z_len())
			return {INF, Polynomial()};
		return par[i][j][k];	
	}

	pair < long long, Polynomial > getMax(pair < long long, Polynomial > a, pair < long long, Polynomial > b, pair < long long, Polynomial > c)
	{
		if (a.first >= b.first && a.first >= c.first)
			return a;
		if (b.first >= a.first && b.first >= c.first)
			return b;
		return c;
	}
	
	pair < long long, Polynomial > getMin(pair < long long, Polynomial > a, pair < long long, Polynomial > b, pair < long long, Polynomial > c)
	{
		if (a.first <= b.first && a.first <= c.first)
			return a;
		if (b.first <= a.first && b.first <= c.first)
			return b;
		return c;
	}

	void insert(int i, int j, int k)
	{	
		pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
		par[i][j][k].first = mx.first + par[i][j][k].first;
		par[i][j][k].second = mx.second + par[i][j][k].second;

		assert(par[i][j][k].first >= 0);
		while(i > 0 && j > 0 && k > 0)
		{
			i--, j--, k--;      
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
	}

	void rsk()
	{
		for (int i = 0; i < x_len(); i++)
		{
			for (int j = 0; j < y_len(); j++)
			{
				for (int k = 0; k < z_len(); k++)
				{	
					insert(i, j, k);
				}
			}
		}
	}

	void inverseInsert(int i, int j, int k)
	{	
		pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
		par[i][j][k].first -= mx.first;
		par[i][j][k].second -= mx.second;

		assert(par[i][j][k].first >= 0);
		while(i > 0 && j > 0 && k > 0)
		{
			i--, j--, k--;      
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
	}

	void inverseRSK()
	{
		for (int i = x_len() - 1; i >= 0; i--)
		{
			for (int j = y_len() - 1; j >= 0; j--)
			{
				for (int k = z_len() - 1; k >= 0; k--)
				{
					inverseInsert(i, j, k);
				}
			}
		}
	}

	mat3d getPartition()
	{
		mat3d res;
		for (int i = 0; i < x_len(); i++)
		{
			res.emplace_back();
			for (int j = 0; j < y_len(); j++)
			{
				res[i].emplace_back();
				for (int k = 0; k < z_len(); k++)
				{
					res[i][j].push_back(par[i][j][k].first);
				}
			}
		}
		return res;
	}

	long long getVolume()
	{
		long long volume = 0;
		for (int i = 0; i < x_len(); i++)
		{
			for (int j = 0; j < y_len(); j++)
			{
				for (int k = 0; k < z_len(); k++)
				{
					volume += par[i][j][k].first;
				}
			}
		}
		return volume;
	}

	Polynomial getPVolume() 
	{
		Polynomial volume;
		for (int i = 0; i < x_len(); i++)
		{
			for (int j = 0; j < y_len(); j++)
			{
				for (int k = 0; k < z_len(); k++)
				{
					volume += par[i][j][k].second;
				}
			}
		}
		return volume;
	}

	Polynomial getMonome(int i, int j, int k)
	{
		return Xpower(i * y_len() * z_len() + j * z_len() + k, 1);	
	}

	bool checkValid()
	{
		for (int i = 0; i < x_len(); i++)
		{
			for (int j = 0; j < y_len(); j++)
			{
				for (int k = 0; k < z_len(); k++)
				{
					if (i < x_len() - 1 && par[i][j][k].first > par[i + 1][j][k].first)
						return false;
					if (j < y_len() - 1 && par[i][j][k].first > par[i][j + 1][k].first)
						return false;
					if (k < z_len() - 1 && par[i][j][k].first > par[i][j][k + 1].first)
						return false;		
				}
			}
		}
		return true;
	}

	void print()
	{
		cout << "*-----------Printing partition-------------*" << endl;
		cout << "" << endl;
		for (int i = 0; i < x_len(); i++)
		{
			for (int j = 0; j < y_len(); j++)
			{	
				for (int k = 0; k < z_len(); k++)
				{
					cout << par[i][j][k].first << ' ';
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << "*------------------------------------------*" << endl;
	}

	void printPVolumes() 
	{
		cout << "*--------Printing partition pvolumes ----------*" << endl;
		cout << "" << endl;
		for (int i = 0; i < x_len(); i++)
		{
			for (int j = 0; j < y_len(); j++)
			{	
				for (int k = 0; k < z_len(); k++)
				{
					cout << "(" << i << "," << j << "," << k << "):\n";
					par[i][j][k].second.print();
					cout << endl;
					 
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << "*----------------------------------------------*" << endl;
		
	}
};

int main()
{
	//ios_base::sync_with_stdio(false);
	//cin.tie();
	//cout.tie();		

	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
		


	srand(time(NULL));
	for (int n = 1; n <= 10; n++)
	{
		int a, b, c;
		a = b = c = n;
		//cin >> a >> b >> c;
		mat3d A = vector < vector < vector < ll > > > (a, vector < vector < ll > > (b, vector < ll > (c)));
		
		/*vector < bigint > vals;
		bigint cur = 1;
		for (int i = 1; i <= a * b * c; i++)
		{
			vals.pb(cur);
			cur *= BASE;
			assert(cur > 0);
		}
		random_shuffle(all(vals)); */
		
		for (int i = 0; i < a; i++)
		{
			for (int j = 0; j < b; j++)
			{
				for (int k = 0; k < c; k++)
				{
					A[i][j][k] = rand() % 100;
					//A[i][j][k] = vals.back();
					//vals.pop_back();
				}
			}
	    }
	    //A[0][0][0] = 1;
		
		SolidPartition p(A);
	
	    //p.printPVolumes();
	    
		p.rsk();
		p.inverseRSK();

		//p.printPVolumes();
	   	//return 0;
		//p.print();
		
		cout << "n = " << n << endl;
		cout << "volume = " << p.getVolume() << endl;
		cout << bool(p.getPartition() == A) << endl;

		Polynomial pvolume = p.getPVolume();
		//pvolume.print();
		
		
		
		
		
		//ll layer_coef = 0;
		//int layer = 5;
		//for (int i = 0; i < a; i++)
		//{
		//	for (int j = 0; j < b; j++)
		//	{
		//		for (int k = 0; k < c; k++)
		//		{
		//			if (i + j + k == layer)
		//				layer_coef += pvolume.getCoef(p.getMonome(i, j, k));
		//		}
		//	}
		//}
	    //cout << "coeficient of layer " << layer << " = " << layer_coef << endl;
		
		//Printing the P matrix
		//cout << "------------------------------------------------------------------------" << endl;
		//cout << "A: " << endl;
		//for (int i = 0; i < a; i++)
		//{
		//	for (int j = 0; j < b; j++)
		//	{
		//		for (int k = 0; k < c; k++)
		//		{
		//			cout << p[i][j][k] << ' ';
		//		}
		//		cout << endl;
		//	}
		//	cout << endl;
		//}        

		//Printing the coeifcient of A[0][0][0] for every cell  
		//bigint cnt = 0;
		//for (int i = 0; i < a; i++)
		//{
		//	for (int j = 0; j < b; j++)
		//	{
		//		for (int k = 0; k < c; k++)
		//		{
		//			bigint coef1 = getcoef(p[i][j][k], A[0][0][1]); 
		//			bigint coef2 = getcoef(p[i][j][k], A[0][1][0]);
		//			bigint coef3 = getcoef(p[i][j][k], A[0][1][0]);
		//			bigint coef = coef1 + coef2 + coef3;
		//			cnt += coef;
		//			cout << '(' << coef1 << ',' << coef2 << ',' << coef3 << ')' << ' ';
		//		}	
		//		cout << endl;
		//	}
		//	cout << endl;
		//}	
		//cout << "cnt = " << cnt << endl;
	}
	
	return 0;

}


