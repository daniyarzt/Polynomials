
struct SVT
{
    string T, lambda, mu;
    int n;
    vector < pair < int, int > > cells;
    vector < vector < int > > A;
    Polynomial res;

    bool cmp1(int mask1, int mask2)
    {
        int a = -1;
        for (int i = n - 1; i >= 0; i--)
        {
            if (mask1 & (1 << i))
            {
                a = i;
                break;
            }
        }
        int b = -1;
        for (int i = 0; i < n; i++)
        {
            if (mask2 & (1 << i))
            {
                b = i;
                break;
            }
        }
        assert(a != -1 && b != -1);
        return a < b;
    }

    bool cmp2(int mask1, int mask2)
    {
        int a = -1;
        for (int i = n - 1; i >= 0; i--)
        {
            if (mask1 & (1 << i))
            {
                a = i;
                break;
            }
        }
        int b = -1;
        for (int i = 0; i < n; i++)
        {
            if (mask2 & (1 << i))
            {
                b = i;
                break;
            }
        }
        assert(a != -1 && b != -1);
        return a <= b;
    }

    string lambda_good()
    {
        string s = lambda;
        for (int i = 0; i < (int)T.size(); i++)
        {
            for (int j = T[i] - '0' - 1; j >= 0; j--)
            {
                for (int k = n - 1; k >= 0; k--)
                {
                    if (A[i][j] & (1 << k))
                    {
                        s[k]++;
                        for (int id = 1; id < (int)s.size(); id++)
                        {
                            if (s[id] > s[id - 1])
                                return "-1";
                        }
                    }
                }
            }
        }
        return s;
    }

    void upd()
    {
        string shape = lambda_good();
        if (shape == "-1")
            return;
        cout << shape << endl;
        print();
        Polynomial coef(1);
        ll sgn = 1;
        for (int i = 0; i < (int)T.size(); i++)
        {
            int cnt = 0;
            for (int j = 0; j < T[i] - '0'; j++)
            {
                cnt += __builtin_popcount(A[i][j]) - 1;
            }
            if (cnt & 1)
                sgn *= -1;
            coef *= Xpower(n + 1, cnt);
        }
        coef.normalize();
        coef *= Polynomial(sgn);
        coef *= grassman(shape, n);
        res += coef;
    }

    void print()
    {
        for (int i = 0; i < (int)T.size(); i++)
        {
            for (int j = 0; j < T[i] - '0'; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    if (A[i][j] & (1 << k))
                        cout << k + 1;
                }
                cout << ' ';
            }
            cout << endl;
        }
    }

    bool check()
    {
        string cur = mu;
        for (int j = T[0] - '0' - 1; j >= 0; j--)
        {
            for (int i = 0; i < (int)T.size(); i++)
            {
                if (T[i] - '0' > j)
                {
                    for (int k = 0; k < n; k++)
                    {
                        if (A[i][j] & (1 << k))
                        {
                            cur[k]++;
                            for (int x = 1; x < (int)cur.size(); x++)
                            {
                                if (cur[x] > cur[x - 1])
                                    return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    void search_lambda()
    {
        string cur;
        while((int)cur.size() < n)
            cur += '0';
        for (int i = 0; i < (int)T.size(); i++)
        {
            for (int j = 0; j < T[i] - '0'; j++)
            {
                for (int k = 0; k < n; k++)
                    if (A[i][j] & (1 << k))
                        cur[k]++;
            }
        }
        for (int i = 1; i < (int)cur.size(); i++)
            if (cur[i] > cur[i - 1])
                return;
        if (cur == "311" || cur == "211")
            return;
        //if (!check())
        //    return;
        cout << cur << endl;
        print();
        if (cur == lambda)
        {
            if (check())
                cout << "CHECK = True!" << endl;
            print();
            cout << "found! " << endl;
        }
    }

    void rec(int id)
    {
        if (id == (int)cells.size())
        {
            search_lambda();
            return;
        }
        int x = cells[id].first;
        int y = cells[id].second;
        for (int mask = 1; mask < (1 << n); mask++)
        {
            //if (__builtin_popcount(mask) > 1)
            //    continue;
            A[x][y] = mask;
            if (x > 0 && !cmp1(A[x - 1][y], A[x][y]))
                continue;
            if (y > 0 && !cmp2(A[x][y - 1], A[x][y]))
                continue;
            rec(id + 1);
        }
    }

    Polynomial sol(string _T, int _n, string _lambda, string _mu)
    {
        lambda = _lambda;
        mu = _mu;
        T = _T;
        n = _n;

        while((int)mu.size() < n)
            mu += '0';
        while((int)T.size() < n)
            T += '0';
        while((int)lambda.size() < n)
            lambda += '0';
        for (int i = 0; i < (int)T.size(); i++)
            for (int j = 0; j < (int)T[i] - '0'; j++)
                cells.pb({i, j});
        A = vector < vector < int > > ((int)T.size(), vector < int > (T[0] - '0'));
        rec(0);
        return res;
    }
};





void expansion_conjecture()
{
    SVT s;
    s.sol("31", 3, "2011", "");

}
