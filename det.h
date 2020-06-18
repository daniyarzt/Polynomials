#define all(x) x.begin(), x.end()

static ll sign(const vector < int > & p)
{
    ll res = 1;
    for (int i = 0; i < (int)p.size(); i++)
    {
        for (int j = 0; j < i; j++)
            if (p[j] > p[i])
                res *= -1;
    }
    return res;
}

Polynomial det(vector < vector < Polynomial > > A)
{
    int n = (int)A.size();
    vector < int > p;
    for (int i = 0; i < n; i++)
        p.pb(i);
    Polynomial res;
    int cnt = 0;
    bool hasNeg = false;
    do
    {
        Polynomial cur(1);
        for (int i = 0; i < n; i++)
            cur *= A[i][p[i]];
        cur *= sign(p);
        res += cur;
        cur.normalize();
        cnt += !cur.p.empty();
        if (sign(p) < 0 && !cur.p.empty())
            hasNeg = true;
    }
    while(next_permutation(p.begin(), p.end()));
    res.normalize();
    return res;
}
