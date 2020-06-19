struct Shur
{
    vector < vector < int > > A;
    string lambda, mu;
    int n;
    vector < pair < int, int > > pts;
    Polynomial res;

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


Polynomial s(string lambda, string mu, int n)
{
    Shur str;
    return str.sol(lambda, mu, n);
}
