

//By Don4ick 
//#define _GLIBCXX_DEBUG

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
	
	set < vector < int > > del;
	pair < long long, Polynomial > get(int i, int j, int k)
	{
		if (i < 0 || j < 0 || k < 0)
			return {0, Polynomial()};
		if (i >= x_len() || j >= y_len() || k >= z_len() || del.count({i, j, k}))
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

	void setEmpty()
	{
		for (int i = 0; i < x_len(); i++)
			for (int j = 0; j < y_len(); j++)
				for (int k = 0; k < z_len(); k++)
					del.insert({i, j, k});
	}

	void insert(int i, int j, int k)
	{	
		pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
		par[i][j][k].first = mx.first + par[i][j][k].first;
		par[i][j][k].second = mx.second + par[i][j][k].second;

		del.erase({i, j, k});
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

	void inverseInsert(int i, int j, int k)
	{	
		pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
		par[i][j][k].first -= mx.first;
		par[i][j][k].second -= mx.second;

		del.erase({i, j, k});
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

	void insert2d(int i, int j, int k)
	{
		pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
		par[i][j][k].first = mx.first + par[i][j][k].first;
		par[i][j][k].second = mx.second + par[i][j][k].second;

		del.erase({i, j, k});
		assert(par[i][j][k].first >= 0);
		while(i > 0 && j > 0)
		{     
			i--, j--;
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
	}
	
	void inverseInsert2d(int i, int j, int k)
	{	
		pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
		par[i][j][k].first -= mx.first;
		par[i][j][k].second -= mx.second;

		del.insert({i, j, k});
		assert(par[i][j][k].first >= 0);
		while(i > 0 && j > 0)
		{
			i--, j--;      
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
	}

	void insertThreeWay(int i, int j, int k)
	{
		int x = i, y = j, z = k;
		pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
		par[i][j][k].first = mx.first + par[i][j][k].first;
		par[i][j][k].second = mx.second + par[i][j][k].second;

		del.erase({i, j, k});
		assert(par[i][j][k].first >= 0);
		while(i > 0 && j > 0)
		{     
			i--, j--;
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
		i = x, j = y;
		while(i > 0 && k > 0)
		{     
			i--, k--;
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
		i = x, k = z;
		while(j > 0 && k > 0)
		{     
			j--, k--;
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));

			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
				
	}
	
	void inverseInsertThreeWay(int i, int j, int k)
	{	
		if (TEST)
		{
			cerr << "inverse insert three way at (" << i << " ," << j << " ," << k << ")" << endl;
		}

		int x = i, y = j, z = k;
		pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
		par[i][j][k].first -= mx.first;
		par[i][j][k].second -= mx.second;

		del.insert({i, j, k});
		assert(par[i][j][k].first >= 0);
		while(i > 0 && j > 0)
		{
			i--, j--;      
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
		i = x, j = y;
		while(i > 0 && k > 0)
		{
			i--, k--;      
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
		i = x, k = z;
		while(j > 0 && k > 0)
		{
			j--, k--;      
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;
	
	        if (TEST == true && x == 3 && y == 4 && z == 4)
	        {
	        	print();
	        	cerr << i << ' ' << j << ' ' << k << ' ' << par[i][j][k].first << ' ' << mx.first << ' ' << mn.first << endl;
	        }
	        assert(par[i][j][k].first >= 0);			
		}
		if (TEST)
		{
			cerr << "After inverser insert: " << endl;
			print();
		}
	}
	
	void insertStar(int i, int j, int k)
	{
		int x = i, y = j, z = k;
		pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
		par[i][j][k].first = mx.first + par[i][j][k].first;
		par[i][j][k].second = mx.second + par[i][j][k].second;

		del.erase({i, j, k});
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
		i = x, j = y, k = z;
		while(i > 0 && j > 0)
		{     
			i--, j--;
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
		i = x, j = y;
		while(i > 0 && k > 0)
		{     
			i--, k--;
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
		i = x, k = z;
		while(j > 0 && k > 0)
		{     
			j--, k--;
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
	}
	
	void inverseInsertStar(int i, int j, int k)
	{	
		if (TEST)
		{
			cerr << "inverse insert three way at (" << i << " ," << j << " ," << k << ")" << endl;
		}

		int x = i, y = j, z = k;
		pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
		par[i][j][k].first -= mx.first;
		par[i][j][k].second -= mx.second;

		del.insert({i, j, k});
		assert(par[i][j][k].first >= 0);
		
		while(i > 0 && j > 0)
		{
			i--, j--;      
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
		i = x, j = y;
		while(i > 0 && k > 0)
		{
			i--, k--;      
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
		i = x, k = z;
		while(j > 0 && k > 0)
		{
			j--, k--;      
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;
	
	        if (TEST == true && x == 3 && y == 4 && z == 4)
	        {
	        	print();
	        	cerr << i << ' ' << j << ' ' << k << ' ' << par[i][j][k].first << ' ' << mx.first << ' ' << mn.first << endl;
	        }
	        assert(par[i][j][k].first >= 0);			
		}
		i = x, j = y, k = z;
		while(i > 0 && j > 0 && k > 0)
		{
			i--, j--, k--;      
			pair < long long, Polynomial > mx = getMax(get(i - 1, j, k), get(i, j - 1, k), get(i, j, k - 1)); 
			pair < long long, Polynomial > mn = getMin(get(i + 1, j, k), get(i, j + 1, k), get(i, j, k + 1));
			par[i][j][k].first = mx.first + mn.first - par[i][j][k].first;
			par[i][j][k].second = mx.second + mn.second - par[i][j][k].second;


			assert(par[i][j][k].first >= 0);			
		}
		
		if (TEST)
		{
			cerr << "After inverser insert: " << endl;
			print();
		}
	}


	void rsk()
	{
		setEmpty();
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

	void rsk2d()
	{
		setEmpty();
		for (int i = 0; i < x_len(); i++)
		{
			for (int j = 0; j < y_len(); j++)
			{
				for (int k = 0; k < z_len(); k++)
				{	
					insert2d(i, j, k);
				}
			}
		}
	}

	void inverseRSK2d()
	{
		for (int i = x_len() - 1; i >= 0; i--)
		{
			for (int j = y_len() - 1; j >= 0; j--)
			{
				for (int k = z_len() - 1; k >= 0; k--)
				{
					inverseInsert2d(i, j, k);
				}
			}
		}
	}

	void rskThreeWay()
	{
		setEmpty();
		for (int i = 0; i < x_len(); i++)
		{
			for (int j = 0; j < y_len(); j++)
			{
				for (int k = 0; k < z_len(); k++)
				{	
					insertThreeWay(i, j, k);
				}
			}
		}
	}

	void inverseRSKStar()
	{
		for (int i = x_len() - 1; i >= 0; i--)
		{
			for (int j = y_len() - 1; j >= 0; j--)
			{
				for (int k = z_len() - 1; k >= 0; k--)
				{
					inverseInsertStar(i, j, k);
				}
			}
		}
	}

	void rskStar()
	{
		setEmpty();
		for (int i = 0; i < x_len(); i++)
		{
			for (int j = 0; j < y_len(); j++)
			{
				for (int k = 0; k < z_len(); k++)
				{	
					insertStar(i, j, k);
				}
			}
		}
	}

	void inverseRSKThreeWay()
	{
		for (int i = x_len() - 1; i >= 0; i--)
		{
			for (int j = y_len() - 1; j >= 0; j--)
			{
				for (int k = z_len() - 1; k >= 0; k--)
				{
					inverseInsertThreeWay(i, j, k);
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

	long long volume()
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
	
	ll corner_hook_volume()
	{
		ll vol = 0;
		for (int i = 0; i < x_len(); i++)
		{
			for (int j = 0; j < y_len(); j++)
			{
				for (int k = 0; k < z_len(); k++)
				{
					ll mx = 0;
					mx = max(get(i - 1, j, k).first, mx);
					mx = max(get(i, j - 1, k).first, mx);
					mx = max(get(i, j, k - 1).first, mx);
					int hook_len = x_len() - i + y_len() - j + z_len() - k - 2;
					vol += (par[i][j][k].first - mx) * hook_len;
				}
			}
		}
		return vol;
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

void mat3dprint(mat3d A)
{
	cout << "-----------------------mat3dprint--------------------" << endl;
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();
	cout << "dimensions: " << x_len << ' ' << y_len << ' ' << z_len << endl;
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{	
			for (int k = 0; k < z_len; k++)
			{
				cout << A[i][j][k] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}	
	cout << "-----------------------------------------------------" << endl;
}

mat3d flip(mat3d A)
{
	if (A.empty())
		return A;
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();

	auto B = A;
	for (int i = 0; i < x_len; i++)
		for (int j = 0; j < y_len; j++)
			for (int k = 0; k < z_len; k++)
				B[i][j][k] = A[x_len - i - 1][y_len - j - 1][z_len - k - 1];
	return B;	
}

mat3d transfer_map(const mat3d & A)
{
	mat3d p = A;
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();
	int volume = 0;
	for (int i = x_len - 1; i >= 0; i--)
	{
		for (int j = y_len - 1; j >= 0; j--)
		{
			for (int k = z_len - 1; k >= 0; k--)
			{
				if (i < x_len - 1)
					p[i][j][k] = max(p[i][j][k], p[i + 1][j][k] + A[i][j][k]);
				if (j < y_len - 1)
					p[i][j][k] = max(p[i][j][k], p[i][j + 1][k] + A[i][j][k]);
				if (k < z_len - 1)
					p[i][j][k] = max(p[i][j][k], p[i][j][k + 1] + A[i][j][k]);	
				volume += p[i][j][k];
			}
		}
	}
	//print(p);
	//cerr << volume << endl;
	return p;
}

ll volume(const mat3d & P)
{
	int x_len = P.size();
	int y_len = P[0].size();
	int z_len = P[0][0].size();
	
	ll vol = 0; 
	for (int i = 0; i < x_len; i++)
		for (int j = 0; j < y_len; j++)
			for (int k = 0; k < z_len; k++)
				vol += P[i][j][k];
	return vol;
}

ll corner_hook_volume(mat3d A)
{
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();

	ll vol = 0;
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{
			for (int k = 0; k < z_len; k++)
			{
				ll mx = 0;
				if (i < x_len - 1)
					mx = max(A[i + 1][j][k], mx);
				if (j < y_len - 1)	
					mx = max(A[i][j + 1][k], mx);
				if (k < z_len - 1)
					mx = max(A[i][j][k + 1], mx);
				vol += (A[i][j][k] - mx) * (i + j + k + 1);
			}
		}
	}
	return vol;
}


void experiment060822() 
{
	ofstream myfile;
	for (int n = 1; n <= 20; n++)
	{	
		// I could exchange volumes by ch volumes
		myfile.open("solid-partition-inverse-rsk-transfer-volume-distribution/n=" + to_string(n) + "ch-volumes.csv");
		SolidPartitionGenerator gen(n, n, n, n);
	    int counter = 0;
		auto A = flip(gen.getNext());
		map < int, int > cnt;
		while(!A.empty())
		{
			counter++;
			// do something 
			auto P = SolidPartition(A);
			//mat3dprint(A);
			P.inverseRSK();
			auto T = transfer_map(flip(P.getPartition()));
			//P.print();
			P.rsk();
			cnt[corner_hook_volume(T)]++;   
			assert(P.getPartition() == A);
			    
		
		    A = gen.getNext();
		    A = flip(A);
		}
		for (auto it : cnt)
			myfile << it.first << "," << it.second << "\n";
		myfile.close();
		cerr << "n=" << n << ' ' << "counter=" << counter << endl;
	}	
}

void experiment080822() 
{
	cerr << "Starting experiment 08.08.22" << endl;
	ofstream myfile1, myfile2;
	for (int n = 9; n <= 15; n++)
	{	
		// I could exchange volumes by ch volumes
		myfile1.open("solid-partition-inverse-rsk2d-transfer-volume-distribution/n=" + to_string(n) + "volumes.csv");
	    myfile2.open("solid-partition-inverse-rsk2d-transfer-volume-distribution/n=" + to_string(n) + "ch-volumes.csv");
		SolidPartitionGenerator gen(n, n, n, n);
	    
	    int counter = 0;
		map < int, int > cnt1, cnt2;
		
		auto A = flip(gen.getNext());
		while(!A.empty())
		{
			counter++;
			auto P = SolidPartition(A);
			
			//mat3dprint(A);
			
			P.inverseRSK2d();
			auto T = transfer_map(flip(P.getPartition()));
			//P.print();
			
			P.rsk2d();
			
			cnt1[volume(T)]++;
			cnt2[corner_hook_volume(T)]++;   
			assert(P.getPartition() == A);			    
		
		    A = gen.getNext();
		    A = flip(A);
		}
		for (auto it : cnt1)
			myfile1 << it.first << "," << it.second << "\n";
		for (auto it : cnt2)
			myfile2 << it.first << "," << it.second << "\n";
		
		myfile1.close(), myfile2.close();
		cerr << "n=" << n << ' ' << "counter=" << counter << endl;
	}	
}

void experiment080822ThreeWay() 
{
	cerr << "Starting experiment 08.08.22" << endl;
	ofstream myfile1, myfile2;

	for (int n = 1; n <= 15; n++)
	{	
		// I could exchange volumes by ch volumes
		myfile1.open("solid-partition-inverse-rskThreeWay-transfer-volume-distribution/n=" + to_string(n) + "volumes.csv");
	    myfile2.open("solid-partition-inverse-rskThreeWay-transfer-volume-distribution/n=" + to_string(n) + "ch-volumes.csv");
		SolidPartitionGenerator gen(n, n, n, n);
	    
	    int counter = 0;
		map < int, int > cnt1, cnt2;
		
		auto A = flip(gen.getNext());
		while(!A.empty())
		{
			counter++;
			
			auto P = SolidPartition(A);
			
			//mat3dprint(A);
			
			P.inverseRSKThreeWay();
			auto T = transfer_map(flip(P.getPartition()));
			//P.print();
			
			P.rskThreeWay();
			
			cnt1[volume(T)]++;
			cnt2[corner_hook_volume(T)]++;   
			

			assert(P.getPartition() == A);			    
		
		    A = gen.getNext();
		    A = flip(A);
		}
		for (auto it : cnt1)
			myfile1 << it.first << "," << it.second << "\n";
		for (auto it : cnt2)
			myfile2 << it.first << "," << it.second << "\n";
		
		myfile1.close(), myfile2.close();
		cerr << "n=" << n << ' ' << "counter=" << counter << endl;
	}	
}

void experiment080822Star() 
{
	cerr << "Starting experiment 08.08.22" << endl;
	ofstream myfile1, myfile2;

	for (int n = 1; n <= 15; n++)
	{	
		// I could exchange volumes by ch volumes
		myfile1.open("solid-partition-inverse-rskStar-transfer-volume-distribution/n=" + to_string(n) + "volumes.csv");
	    myfile2.open("solid-partition-inverse-rskStar-transfer-volume-distribution/n=" + to_string(n) + "ch-volumes.csv");
		SolidPartitionGenerator gen(n, n, n, n);
	    
	    int counter = 0;
		map < int, int > cnt1, cnt2;
		
		auto A = flip(gen.getNext());
		while(!A.empty())
		{
			counter++;
			
			auto P = SolidPartition(A);
			
			//mat3dprint(A);
			
			P.inverseRSKThreeWay();
			auto T = transfer_map(flip(P.getPartition()));
			//P.print();
			
			P.rskThreeWay();
			
			cnt1[volume(T)]++;
			cnt2[corner_hook_volume(T)]++;   
			

			assert(P.getPartition() == A);			    
		
		    A = gen.getNext();
		    A = flip(A);
		}
		for (auto it : cnt1)
			myfile1 << it.first << "," << it.second << "\n";
		for (auto it : cnt2)
			myfile2 << it.first << "," << it.second << "\n";
		
		myfile1.close(), myfile2.close();
		cerr << "n=" << n << ' ' << "counter=" << counter << endl;
	}	
}


void experiment160822()
{
	srand(time(NULL));
	int n = 3;
	while(true)
	{
	mat3d A = vector < vector < vector < ll > > > (n, vector < vector < ll > > (n, vector < ll > (n)));
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				A[i][j][k] = rand() % 10;
	
	auto P1 = SolidPartition(A);
	auto P2 = SolidPartition(A);
	auto P3 = SolidPartition(A);
	auto P4 = SolidPartition(A);

	P1.rsk();
	P2.rsk2d();
	P3.rskThreeWay();
	P4.rskStar();

	cout << P1.volume() << ' ' << P1.corner_hook_volume() << ' ' << 1.0 * P1.corner_hook_volume() / P1.volume() << endl;
	cout << P2.volume() << ' ' << P2.corner_hook_volume() << ' ' << 1.0 * P2.corner_hook_volume() / P2.volume() << endl;
	cout << P3.volume() << ' ' << P3.corner_hook_volume() << ' ' << 1.0 * P3.corner_hook_volume() / P3.volume() << endl;
	cout << P4.volume() << ' ' << P4.corner_hook_volume() << ' ' << 1.0 * P4.corner_hook_volume() / P4.volume() << endl;;
	//P4.getPVolume().print();
	cerr << "------------------------------------------------------------------------------------------------------------" << endl;
	}
}

int main()
{
	//ios_base::sync_with_stdio(false);
	//cin.tie();
	//cout.tie();		

	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
		

	//for (int n = 1; n <= 10; n++)
	//	cerr << 3 * n * n - 3 * n + 1 << ' ';

	experiment160822();


	//srand(time(NULL));
	//for (int n = 1; n <= 10; n++)
	//{
	//	int a, b, c;
	//	a = b = c = n;
	//	//cin >> a >> b >> c;
	//	mat3d A = vector < vector < vector < ll > > > (a, vector < vector < ll > > (b, vector < ll > (c)));
	//	
	//	/*vector < bigint > vals;
	//	bigint cur = 1;
	//	for (int i = 1; i <= a * b * c; i++)
	//	{
	//		vals.pb(cur);
	//		cur *= BASE;
	//		assert(cur > 0);
	//	}
	//	random_shuffle(all(vals)); */
	//	
	//	for (int i = 0; i < a; i++)
	//	{
	//		for (int j = 0; j < b; j++)
	//		{
	//			for (int k = 0; k < c; k++)
	//			{
	//				A[i][j][k] = rand() % 100;
	//				//A[i][j][k] = vals.back();
	//				//vals.pop_back();
	//			}
	//		}
	//    }
	//    //A[0][0][0] = 1;
	//	
	//	SolidPartition p(A);
	// 
	//    //p.printPVolumes();
	//    
	//	p.rsk();
	//	p.inverseRSK();
	//
		//p.printPVolumes();
	   	//return 0;
		//p.print();
		
	//	cout << "n = " << n << endl;
	//	cout << "volume = " << p.getVolume() << endl;
	//	cout << bool(p.getPartition() == A) << endl;

	//	Polynomial pvolume = p.getPVolume();
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
	//}
	
	//return 0;

}


