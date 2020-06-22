

struct Grassman
{
    string lambda;
    int n;
    vector < pair < int, int > > cells;
    Polynomial ans;
    vector < vector < int > > A;

    Grassman (){}

    Grassman(string _lambda, int _n) : lambda(_lambda), n(_n) {}

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
        for (int i = 0; i < (int)lambda.size(); i++)
        {
            for (int j = 0; j < lambda[i] - '0'; j++)
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
        vector < int > cnt(n);
        for (int i = 0; i < (int)lambda.size(); i++)
        {
            for (int j = 0; j < lambda[i] - '0'; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    cnt[k] += bool(A[i][j] & (1 << k));
                }
            }
        }
        Polynomial res(1);
        for (int i = 0; i < n; i++)
        {
            if (cnt[i])
                res *= Xpower(i + 1, cnt[i]);
        }
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

    void rec(int id)
    {
        if (id == (int)cells.size())
        {
            ans += W();
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
        A = vector < vector < int > > ((int)lambda.size(), vector < int > (lambda[0] - '0'));
        for (int i = 0; i < (int)lambda.size(); i++)
            for (int j = 0; j < lambda[i] - '0'; j++)
                cells.pb({i, j});
        rec(0);
        return ans;
    }
};

Polynomial grassman(string lambda, int n)
{
    Grassman G(lambda, n);
    return G.calc();
}
