#include <bits/stdc++.h>
#include "all.h"

using namespace std;
void jdt(int x, int y, vector < vector < int > > & a)
{
	int down = -1;
	int right = -1;
	if (x + 1 < (int)a.size() && y < (int)a[x + 1].size())
		down = a[x + 1][y];
	if (y + 1 < (int)a[x].size())
		right = a[x][y + 1];
	if (down == -1 && right == -1)
		return;
	if (down == -1)
	{
		swap(a[x][y], a[x][y + 1]);
		jdt(x, y + 1, a);
		return;
	}
	if (right == -1)
	{
		swap(a[x][y], a[x + 1][y]);
		jdt(x + 1, y, a);
		return;
	}
	if (down <= right)
	{
		swap(a[x][y], a[x + 1][y]);
		jdt(x + 1, y, a);
	}
	else
	{	
		swap(a[x][y], a[x][y + 1]);
		jdt(x, y + 1, a);	
	}
}

void shrink(vector < vector < int > > & a, string mu)
{
	//cerr << "shrink " << mu << endl;
	for (int i = (int)mu.size() - 1; i >= 0; i--)
	{
		for (int j = mu[i] - '0' - 1; j >= 0; j--)
		{	
			jdt(i, j, a);
		}
	}
}


struct uSchur
{
    vector < vector < int > > A;
    string lambda, mu;
    int n;
    vector < pair < int, int > > pts;
    Polynomial res, trans;
    vector < pair < vector < vector < int > >, Polynomial > > uni;

    Polynomial w()
    {
        Polynomial cur = Polynomial(1);
        for (int i = 1; i <= n; i++)
        {
            int degree = 0;
            for (int y = 0; y < lambda[0] - '0'; y++)
            {
                bool found = false;
                for (int x = 0; x < (int)lambda.size() && lambda[x] - '0' > y; x++)
                {
                    if (A[x][y] == i)
                    {
                        found = true;
                        break;
                    }
                }
                degree += found;
            }
            cur *= Xpower(i, degree);
        }
        return cur;
    }

    void rec(int id)
    {
        if (id == (int)pts.size())
        {
        	Polynomial monome = w();
        	monome.normalize();
        	res += monome;
        	//if (trans.getCoef(monome) == 1)
        		uni.pb({A, monome});
            return;
        }
        int x = pts[id].first;
        int y = pts[id].second;
        int min_val = 1;
        if (x > 0 && A[x - 1][y] != -1)
            min_val = A[x - 1][y] + 1;
        if (y > 0 && A[x][y - 1] != -1)
            min_val = max(min_val, A[x][y - 1]);
        for (int i = min_val; i <= n; i++)
        {
            A[x][y] = i;
            rec(id + 1);
        }
    }

    Polynomial sol(string _lambda, string _mu, int _n)
    {
        lambda = _lambda, mu = _mu;
        n = _n;
        while((int)mu.size() < (int)lambda.size())
            mu += '0';
        A = vector < vector < int > > ((int)lambda.size());
        for (int i = 0; i < (int)lambda.size(); i++)
        {
            A[i] = vector < int > (lambda[i] - '0');
            for (int j = 0; j < mu[i] - '0'; j++)
                    A[i][j] = -1;
            for (int j = mu[i] - '0'; j < lambda[i] - '0'; j++)
                pts.pb({i, j});
        }
        rec(0);
        return res;
    }
};

void print(const vector < vector < int > > & a)
{
	for (int i = 0; i < (int)a.size(); i++)
	{
		for (int j = 0; j < (int)a[i].size(); j++)
		{
			if (a[i][j] == -1)
				cout << ' ';
			else
				cout << a[i][j];
		}
		cout << endl;
	} 
}

void normalize(vector < vector < int > > & a)
{
	for (int i = 0; i < (int)a.size(); i++)
	{	
		while(!a[i].empty() && a[i].back() == -1)
			a[i].pop_back();
	}
}


int main()
{
	string lambda, mu;
	int n;
	
	cin >> lambda >> mu >> n;
	
	int l = (int)lambda.size();
	while((int)mu.size() < l)
		mu += '0';

	/* uSchur s;
	s.sol(lambda, mu, n);
	vector < pair < vector < vector < int > >, Polynomial > >  v = s.uni;
	for (auto it : v)
	{
		vector < vector < int > > a = it.first;
		print(a);
		shrink(a, mu);
		normalize(a);
		cout << "|" << endl << "|" << endl << "|" << endl << "V" << endl;;
		print(a);		
		cout << "===========================================" << endl;
	}  */
		
	string mu_;
	for (int i = 0; i < l; i++)
	{
		int cnt = 0;
		for (int j = 0; j < l; j++)
			if (mu[j] - '0' >= i + 1)
				cnt++;
		mu_ += char(cnt + '0');
	}		

	uSchur s;
	s.trans = Schur().sol(lambda, mu_, n);
	s.sol(lambda, mu, n);
	vector < pair < vector < vector < int > >, Polynomial > > v1 = s.uni;

	uSchur s_;
	s_.trans = Schur().sol(lambda, mu, n);
	s_.sol(lambda, mu_, n);
	vector < pair < vector < vector < int > >, Polynomial > > v2 = s_.uni;
	
	vector < pair < vector < vector < int > >, Polynomial > > wow;
	for (auto it1 : v1)
	{
		int cnt = 0;
		for (auto it2 : v2)
		{
			if (it1.second == it2.second)
			{
				vector < vector < int > > a = it1.first, b = it2.first;
				vector < vector < int > > a_ = a, b_ = b;
				shrink(a_, mu);
				shrink(b_, mu_);
				normalize(a_);
				normalize(b_);
				if (a_ == b_)
				{
					cnt++;
					
					print(a);
					cout << "^" << endl;
					cout << "|" << endl;
					cout << "v" << endl;
					print(b);
					cout << endl << "jdt" << endl << endl;
					print(a_);
					cout << "^" << endl;
					cout << "|" << endl;
					cout << "v" << endl;
					print(b_);
					cout << "------------------------------------------------" << endl;				
				}
			}
		}
		//assert(cnt == 1);
		if (cnt != 1)
			wow.pb(it1);
	} 
	
	for (auto it1 : wow)
	{
		int cnt = 0;
		for (auto it2 : v2)
		{
			if (it1.second == it2.second)
			{
				vector < vector < int > > a = it1.first, b = it2.first;
				vector < vector < int > > a_ = a, b_ = b;
				shrink(a_, mu);
				shrink(b_, mu_);
				normalize(a_);
				normalize(b_);
				if (a_ == b_)
				{
					cnt++;
					print(a);
					cout << "^" << endl;
					cout << "|" << endl;
					cout << "v" << endl;
					print(b);
					cout << endl << "jdt" << endl << endl;
					print(a_);
					cout << "^" << endl;
					cout << "|" << endl;
					cout << "v" << endl;
					print(b_);
					cout << "------------------------------------------------" << endl;				
				}
			}
		}
		//assert(cnt == 1);
		//if (cnt != 1)
		//	wow.pb(it1);
	}
}

