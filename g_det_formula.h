

Polynomial g_det(string lambda, string mu, int M)
{
    int n = lambda[0] - '0';
    vector < vector < Polynomial > > A(n, vector < Polynomial > (n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int _l = 0;
            for (int x = 0; x < (int)lambda.size(); x++)
                _l += bool(lambda[x] - '0' >= i + 1);
            int _m = 0;
            for (int x = 0; x < (int)mu.size(); x++)
                _m += bool(mu[x] - '0' >= j + 1);
            int k = _l - (i + 1) - _m + (j + 1);
            vector < int > argv;
            for (int x = 1; x <= M; x++)
                argv.pb(x);
            for (int x = _m + 1; x <= _l - 1; x++)
                argv.pb(M + x);
            A[i][j] = e(argv, k);
        }
    }
    return det(A);
}
