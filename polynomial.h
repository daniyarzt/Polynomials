#include <bits/stdc++.h>

#define pb push_back
typedef long long ll;

using namespace std;

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

    void print()
    {
        cout << endl;
        for (auto it : p)
        {
            cout << it.second;
            cout << "\t";
            cout << "(";
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
        /*
        bool tmp = false;
        for (auto it : p)
        {
            if (tmp)
                cout << " + ";
            cout << it.second << "(";
            bool kek = false;
            for (auto a : it.first)
            {
                if (kek)
                    cout << " * ";
                cout << a.first << "^" << a.second;
                kek = true;
            }
            cout << ")";
            tmp = true;
        }
        cout << endl;*/
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



