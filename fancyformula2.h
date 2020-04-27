
Polynomial Adet(string lambda, int n)
{
    vector < vector < Polynomial > > A(n, vector < Polynomial > (n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = Xpower(j + 1, (lambda[i] - '0'));//?
            for (int k = 1; k <= i; k++)
            {
                Polynomial B = Xpower(n + k, 1);
                B *= Xpower(j + 1, 1);
                B *= Polynomial(-1);
                Polynomial C(1);
                C += B;
                A[i][j] *= C;
            }
        }
    }
    /*for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cerr << "A[" << i + 1 << "][" << j + 1 << "] = ";
            A[i][j].print();
        }
    }*/
    return det(A);
}

struct FancyFormula2
{
    string theta, lambda;
    int n;
    vector < pair < int, int > > cells;
    Polynomial ans;
    vector < vector < int > > A;

    FancyFormula2 (){}

    FancyFormula2 (string _theta, string _lambda, int _n) : theta(_theta), lambda(_lambda), n(_n) {}

    int firstElement(int mask)
    {
        for (int i = 0; i < n; i++)
            if (mask & (1 << i))
                return i + 1;
        //cerr << "firstElement " << mask << endl;
        assert(false);
    }
    int lastElement(int mask)
    {
        for (int i = n - 1; i >= 0; i--)
            if (mask & (1 << i))
                return i + 1;
        //cerr << "lastElement " << mask << endl;
        assert(false);
    }
    void print()
    {
        printf("Print!\n");
        for (int i = 0; i < (int)theta.size(); i++)
        {
            for (int j = 0; j < theta[i] - '0'; j++)
            {
                if (j > 0)
                    printf("\t");
                printf("(");
                for (int k = 0; k < n; k++)
                    if (A[i][j] & (1 << k))
                        cout << k + 1;
                printf(") ");
            }
            printf("\n");
        }
        printf("\n");
    }

    Polynomial W()
    {
        Polynomial res(1);
        int coef = 1;
        for (int i = 0; i < (int)theta.size(); i++)
        {
            int cur = 0, mask = 0;
            for (int j = 0; j < theta[i] - '0'; j++)
            {
                cur += __builtin_popcount(A[i][j]) - 1;
            }
            if (cur & 1)
                coef *= -1;
            if (cur)
                res *= Xpower(n + i + 1, cur);
        }
        res *= Polynomial(coef);
        return res;
    }

    int sz(string s)
    {
        int res = 0;
        for (int i = 0; i < (int)s.size(); i++)
            res += s[i] - '0';
        return res;
    }

    bool check()
    {
        vector < int > cnt(n);
        for (int j = theta[0] - '0' - 1; j >= 0; j--)
        {
            for (int i = 0; i < (int)theta.size(); i++)
            {
                if (theta[i] - '0' <= j)
                    break;
                for (int k = n - 1; k >= 0; k--)
                {
                    if (A[i][j] & (1 << k))
                    {
                        cnt[k]++;
                        for (int id = 1; id < n; id++)
                        {
                            if (lambda[id] - '0' + cnt[id] > lambda[id - 1] - '0' + cnt[id - 1])
                                return false;
                        }
                    }
                }
            }
        }
        return true;
    }


    void update()
    {
        //if (!check())
        //    return;
        vector < int > cnt(n);
        for (int i = 0; i < (int)theta.size(); i++)
        {
            for (int j = 0; j < theta[i] - '0'; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    cnt[k] += bool(A[i][j] & (1 << k));
                }
            }
        }
        string v = lambda;
        for (int i = 0; i < n; i++)
        {
            v[i] += cnt[i] + n - i - 1;
        }
        //int sign = 1;
        //if (abs(sz(v) - sz(lambda) - sz(theta)) & 1)
        //    sign = -1;
        Polynomial cur(1);
        cur *= W();
        cur *= Adet(v, n);
        ans += cur;
    }

    void rec(int id)
    {
        if (id == (int)cells.size())
        {
            update();
            return;
        }
        int x = cells[id].first;
        int y = cells[id].second;
        for (int mask = 1; mask < (1 << n); mask++)
        {
            if (x > 0 && firstElement(mask) <= lastElement(A[x - 1][y]))
                continue;
            if (y > 0 && firstElement(mask) < lastElement(A[x][y - 1]))
                continue;
            A[x][y] = mask;
            rec(id + 1);
        }
    }

    Polynomial calc()
    {
        A = vector < vector < int > > ((int)theta.size(), vector < int > (theta[0] - '0'));
        for (int i = 0; i < (int)theta.size(); i++)
            for (int j = 0; j < theta[i] - '0'; j++)
                cells.pb({i, j});
        rec(0);
        return ans;
    }
};

Polynomial fancyformula2(string lambda, string theta, int n)
{
    FancyFormula2 F(theta, lambda, n);
    return F.calc();
}
