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

void normalize(vector < vector < int > > & a)
{
	for (int i = 0; i < (int)a.size(); i++)
	{	
		while(!a[i].empty() && a[i].back() == -1)
			a[i].pop_back();
	}
}

struct uSchur
{
    vector < vector < int > > A;
    string lambda, mu;
    int n;
    vector < pair < int, int > > pts;
    Polynomial res;
    vector < vector < vector < int > > > shrinks;

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
        	res += w();
        	vector < vector < int > > B = A;
        	shrink(B, mu);
        	normalize(B);
        	shrinks.pb(B);
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




int main()
{
	string lambda, mu;
	int n;
	
	cin >> lambda >> mu >> n;
	
	int l = (int)lambda.size();
	while((int)mu.size() < l)
		mu += '0';
	
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
	s.sol(lambda, mu, n);
	vector < vector < vector < int > > > s1 = s.shrinks;

	uSchur s_;
	s_.sol(lambda, mu_, n);
	vector < vector < vector < int > > > s2 = s_.shrinks;

	sort(all(s1));
	sort(all(s2));
	
	if (s1 == s2)
		cout << "Equivalent!" << endl;
	else
		cout << "Not equivalent" << endl;

}

