#include <bits/stdc++.h>

using namespace std;
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

struct Polynomial
{
    map < map < int, int >, ll > p;

    Polynomial() {};

    Polynomial (int _val) // init as a number
    {
        p[map < int, int > ()] = _val;
    };

    map < int, int > normalize(map < int, int > ch)
    {
        map < int, int > character;
        for (auto tmp : ch)
        {
            if (tmp.second == 0)
                continue;
            character[tmp.first] += tmp.second;
        }
        return character;
    }
    void normalize()
    {
        map < map < int, int >, ll > q;
        for (auto it : p)
        {
            if (it.second == 0)
                continue;
            q[normalize(it.first)] += it.second;
        }
        p = q;
    }

    void add(map < int, int > character, ll val)
    {
        p[normalize(character)] += val;
    }

    bool isPositive()
    {
        for (auto it : p)
        {
            if (it.second < 0)
                return false;
        }
        return true;
    }

    map < int, int > mult(map < int, int > a, map < int, int > b)
    {
        for (auto it : b)
        {
            a[it.first] += it.second;
        }
        return a;
    }

    ll getCoef(map < int, int > character)
    {
    	return p[character];
    }

    ll getCoef(Polynomial monome) 
    {
    	normalize();
    	monome.normalize();
    	
    	if ((int)monome.p.size() != 1)
    	{
    		cerr << "getCoef: argument must be a monome!" << endl;
			assert(false);
    	}
    	map < int, int > character = (*monome.p.begin()).first;
    	
    	return p[character];	
    }

    void print()
    {
        for (auto it : p)
        {
            cout << "\t";
            cout << it.second;
            cout << " * (";
            int cnt = 0;
            for (auto q : it.first)
            {
                cnt++;
                cout << q.first;
                if (cnt < (int)it.first.size())
                    cout << ",";
            }
            cout << ")^(";
            cnt = 0;
            for (auto q : it.first)
            {
                cnt++;
                cout << q.second;
                if (cnt < (int)it.first.size())
                    cout << ",";
            }
            cout << ")" << endl;
        }
    }

    void latexPrint(int M = INT_MAX) // prints polynomial in LaTEX, if you have xs and ts then ti = x[i + M]
    {
        normalize();
        if (p.empty())
        {
            cout << 0;
            return;
        }

        bool tmp = false;
        for (auto it : p)
        {
            if (it.first.empty())
            {
                cout << it.second << ' ';
                continue;
            }
            if (it.second < 0)
            {
                if (it.second == -1)
                    cout << " - ";
                else
                    cout << it.second;
            }
            else
            {
                if (tmp)
                    cout << " + ";
                if (it.second > 1)
                    cout << it.second;
            }
            tmp = true;
            for (auto x : it.first)
            {
                if (!x.second)
                    continue;
                if (x.first <= M)
                    cout << "x_{" << x.first << "}^{" << x.second << "}";
                else
                    cout << "t_{" << x.first - M << "}^{" << x.second << "}";
            }
        }
    }

    bool isSymmetric(int i, int j)
    {
        normalize();
        for (auto mp : p)
        {
            map < int, int > np = mp.first;
            assert(mp.second != 0);
            swap(np[i], np[j]);
            np = normalize(np);
            if (!p.count(np))
                return false;

            if (p[np] != mp.second) {
                return false;
            }
        }
        return true;
    }

    Polynomial spec_minus(int l, int r) {
        map < map < int, int >, ll > q;
        for (auto it : p)
        {
            if (it.second == 0)
                continue;
            map<int,int> term;
            int cnt = 0;
            for (auto [letter, pw] : it.first)
                if (l <= letter && letter <= r)
                    cnt += pw;

            q[normalize(it.first)] += it.second * (cnt & 1 ? -1 : 1);
        }
        Polynomial np;
        np.p = q;
        return np;
    }

    bool LRSymmetric(int l, int r)
    {
        for (int i = l; i < r; i++)
            if (!isSymmetric(i, i + 1))
                return false;
        return true;
    }

    void operator += (Polynomial q)
    {
        for (auto it : q.p)
        {
            p[it.first] += it.second;
        }
    };

    void operator -= (Polynomial q)
    {
        for (auto it : q.p)
        {
            p[it.first] -= it.second;
        }
    };

    void operator *= (Polynomial q)
    {
        map < map < int, int >, ll > res;
        for (auto a : p)
        {
            for (auto b : q.p)
            {
                res[mult(a.first, b.first)] += a.second * b.second;
            }
        }
        p = res;
    }

    void operator *= (ll k)
    {
        for (auto & it : p)
            it.second *= k;
    }

    bool operator == (Polynomial q)
    {
        normalize();
        q.normalize();
        return p == q.p;
    }

    void cut(int n)
    {
        cerr << n << endl;
        map < map < int, int >, ll > np;
        for (auto it : p)
        {
            map < int, int > ch;
            for (auto q : it.first)
            {
                if (q.first <= n)
                    ch.insert(q);
            }
            np[ch] += it.second;
        }
        p = np; // :)
        normalize();
    }

};

Polynomial Xpower(int id, int pwr)
{
    Polynomial res;
    map < int, int > c;
    c[id] = pwr;
    res.p[c] = 1;
    return res;
}



