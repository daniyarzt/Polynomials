#include <bits/stdc++.h>
#include "all.h"

#define forn(i, n) for (int i = 1; i <= n; i++)

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


struct _Grothendieck_refined
{
    Polynomial ans;
    string lambda, mu;
    int M, n;
    vector < vector < int > > a;
    vector < pair < int, int > > cells;
    vector < vector < vector < int > > > shrinks;

    _Grothendieck_refined () {}

    _Grothendieck_refined (string _lambda, string _mu, int _m): lambda(_lambda), mu(_mu), M(_m) {}

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
        for (int i = 0; i < n; i++)
        {
            if (d[i])
                character[M + i + 1] = d[i];
        }
        return character;
    }

    void rec(int id)
    {
        if (id == (int)cells.size())
        {
            map < int, int > character = getCharacter();
            ans.add(character, 1);
            if (WONNAPRINT)
                print(character);
			vector < vector < int > > b = a;
			shrink(b, mu);
			normalize(b);
			shrinks.pb(b);
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
        a = vector < vector < int > > (n, vector < int > (lambda[0] - '0', -1));
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
	int m;
	cin >> lambda >> mu >> m;

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

	_Grothendieck_refined G(lambda, mu, m);
    G.solve();
	vector < vector < vector < int > > > s1 = G.shrinks;

	_Grothendieck_refined G_(lambda, mu_, m);
    G_.solve();
	vector < vector < vector < int > > > s2 = G_.shrinks;

	sort(all(s1));
	sort(all(s2));

	G.ans.cut(m);
	G_.ans.cut(m);
	assert(G.ans == G_.ans);
	if (s1 == s2)
		cout << "Equivalent!" << endl;
	else
		cout << "Not equivalent!" << endl;	
	
	
}
