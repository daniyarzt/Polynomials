
Polynomial denomenator(int n)
{
    Polynomial res(1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            Polynomial cur(-1);
            cur *= Xpower(j, 1);
            cur += Xpower(i, 1);
            res *= cur;
        }
    }
    return res;
}

Polynomial numerator(string lambda, int n)
{
    vector < vector < Polynomial > > A(n, vector < Polynomial > (n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = Xpower(j + 1, (lambda[i] - '0') + n - (i + 1));
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
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cerr << "A[" << i + 1 << "][" << j + 1 << "] = ";
            A[i][j].print();
        }
    }
    return det(A);
}

