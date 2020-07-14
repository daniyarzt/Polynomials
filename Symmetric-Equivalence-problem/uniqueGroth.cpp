
#include <bits/stdc++.h>
#include "all.h"


using namespace std;

void jdt(int x, int y, vector < vector < int > > & a)
{
	int down = 0;
	int right = 0;
	if (x + 1 < (int)a.size() && y < (int)a[x + 1].size())
		down = a[x + 1][y];
	if (y + 1 < (int)a[x].size())
		right = a[x][y + 1];
	if (down == 0 && right == 0)
		return;
	if (down == 0)
	{
		swap(a[x][y], a[x][y + 1]);
		jdt(x, y + 1, a);
		return;
	}
	if (right == 0)
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

void shrink(vector < vector < int > > & a)
{
	for (int i = (int)a.size() - 1; i >= 0; i--)
	{
		for (int j = a[i].size(); j >= 0; j--)
		{
			if (!a[i][j])
				jdt(i, j, a);
		}
	}
}



struct uGrothendieck_refined
{
    Polynomial ans;
    string lambda, mu;
    int M, n;
    vector < vector < int > > a;
    vector < pair < int, int > > cells;
	vector < vector < vector < int > > > rpps;
	Polynomial trans;

    uGrothendieck_refined () {}

    uGrothendieck_refined (string _lambda, string _mu, int _m): lambda(_lambda), mu(_mu), M(_m) {}

    void print(map < int, int > character)
    {
        cout << "-----------------------------------" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < (int)a[i].size(); j++)
            {
                if (!a[i][j])
                    cout << ' ';
                else
                    cout << a[i][j];
            }
            cout << endl;
        }
        cout << endl;
        cout << "x^c * t^d = ";
        bool tmp = false;
        for(auto it : character)
        {
            if (tmp)
                cout << " * ";
            tmp = true;
            if (it.first <= M)
            {
                cout << "x_" << it.first << "^" << it.second;
            }
            else
                cout << "t_" << it.first - M << "^" << it.second;
        }
        cout << endl;

        cout << "-----------------------------------" << endl;
    }

    map < int, int > getCharacter()
    {
        vector < int > c(M + 1);
        vector < int > d(n);
        vector < vector < bool > > used(M + 1, vector < bool > (lambda[0] - '0'));
        for (int i = 0; i < (int)cells.size(); i++)
        {
            int x = cells[i].first;
            int y = cells[i].second;
            used[a[x][y]][y] = true;
            if (x < n - 1 && a[x][y] == a[x + 1][y])
                d[x]++;
        }
        forn(i, M)
        {
            for (int j = 0; j < lambda[0] - '0'; j++)
                c[i] += used[i][j];
        }
        map < int, int > character;
        forn(i, M)
        {
            if (c[i])
                character[i] = c[i];
        }
        return character;
    }

    void rec(int id)
    {
        if (id == (int)cells.size())
        {
            map < int, int > character = getCharacter();
            Polynomial monome;
            monome.add(character, 1);
            ans += monome;

        	rpps.pb(a);
			           	
            return;
        }
        int x = cells[id].first;
        int y = cells[id].second;
        forn(i, M)
        {
            if (x > 0 && a[x - 1][y] > i)
                continue;
            if (y > 0 && a[x][y - 1] > i)
                continue;
            a[x][y] = i;
            rec(id + 1);
        }
    }

    Polynomial solve()
    {
        n = (int)lambda.size();
        while((int)mu.size() < n)
            mu += '0';
        a = vector < vector < int > > (n, vector < int > (lambda[0] - '0'));
        for (int i = 0; i < n; i++)
        {
            for (int j = mu[i] - '0'; j < lambda[i] - '0'; j++)
                cells.pb({i, j});
        }
        rec(0);
        ans.normalize();
        return ans;
    }
};

void print(const vector < vector < int > > & a)
{
	for (int i = 0; i < (int)a.size(); i++)
	{
		for (int j = 0; j < (int)a[i].size(); j++)
		{
			if (a[i][j] == 0)
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
		while(!a[i].empty() && a[i].back() == 0)
			a[i].pop_back();
	}
	while(!a.empty() && a.back().empty())
		a.pop_back();
}

void semistandartization(vector < vector < int > > & a)
{
	for (int i = 0; i < (int)a.size() - 1; i++)
		for (int j = 0; j < (int)a[i + 1].size(); j++)
			if (a[i][j] == a[i + 1][j])
				a[i][j] = 0;
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
	
	uGrothendieck_refined g(lambda, mu, n);
	g.trans = grothendieck_refined(lambda, mu_, n);
	g.trans.cut(n);
	g.solve();
	vector < vector < vector < int > > > v1 = g.rpps;

	uGrothendieck_refined g_(lambda, mu_, n);
	g_.trans = grothendieck_refined(lambda, mu, n);
	g_.trans.cut(n);
	g_.solve();
	vector < vector < vector < int > > > v2 = g_.rpps;

	cerr << endl;
	for (int i = 0; i < (int)v1.size(); i++)
	{
		//print(v1[i]);
		semistandartization(v1[i]);
		shrink(v1[i]);
		normalize(v1[i]);
		//print(v1[i]);
		//cerr << endl;
	}
	cerr << "--" << endl;
	for (int i = 0; i < (int)v2.size(); i++)
	{
		//print(v2[i]);
		semistandartization(v2[i]);
		shrink(v2[i]);
		normalize(v2[i]);	
		//print(v2[i]);
		//cerr << endl;
	}

	sort(all(v1));
	sort(all(v2));
	
	if (v1 == v2)
		cout << "Equivalent!" << endl;
	else
		cout << "not equivalent" << endl;
}