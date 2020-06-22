struct FancyFormula
{
    string theta, lambda;
    int n;
    vector < pair < int, int > > cells;
    Polynomial ans;
    vector < vector < int > > A;

    FancyFormula (){}

    FancyFormula (string _theta, string _lambda, int _n) : theta(_theta), lambda(_lambda), n(_n) {}

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
        for (int i = 0; i < (int)lambda.size(); i++)
        {
            int cur = 0, mask = 0;
            for (int j = 0; j < lambda[i] - '0'; j++)
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
        if (!check())
            return;
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
            v[i] += cnt[i];
        }
        //int sign = 1;
        //if (abs(sz(v) - sz(lambda) - sz(theta)) & 1)
        //    sign = -1;
        Polynomial cur(1);
        cur *= W();
        cur *= grassman(v, n);
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

Polynomial fancyformula(string lambda, string theta, int n)
{
    FancyFormula F(theta, lambda, n);
    return F.calc();
}
