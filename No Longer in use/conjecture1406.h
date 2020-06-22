


void conjecture1406()
{
    int n;
    cout << "n = ";
    cin >> n;
    string lambda, mu;
    cout << "lambda, mu = ";
    cin >> lambda >> mu;
    while((int)mu.size() < (int)lambda.size())
        mu += '0';
    int L = (int)lambda.size();
    vector < vector < Polynomial > > A(L, vector < Polynomial > (L));
    for (int i = 1; i <= L; i++)
    {
        for (int j = 1; j <= L; j++)
        {
            int k = (lambda[i - 1] - '0') - i - (mu[j - 1] - '0') + j;
            cout << "h_{" << k << "}";
            vector < int > arg;
            for (int x = 1; x <= n; x++)
                arg.pb(x);
            for (int x = 1; x <= i; x++)
                arg.pb(x + n);
            cout << "(";
            for (int x = 0; x < (int)arg.size(); x++)
            {
                if (x > 0)
                    cout << ", ";
                if (arg[x] <= n)
                    cout << "x_" << arg[x] ;
                else
                    cout << "t_" << arg[x] - n;
            }
            cout << ") ";
            A[i-1][j-1] = h(arg, k);
        }
        cout << endl;
    }

    Polynomial g = grothendieck_refined(lambda, mu, n);
    Polynomial d = det(A);

    cerr << "A:" << endl;
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < L; j++)
        {
            if (j > 0)
                cout << " & ";
            A[i][j].latexPrint(n);
        }
        cout << "\\\\" << endl;
    }

    //g.cut(n);
    //d.cut(n);
    g.latexPrint(n);
    //hello

    cout << endl;
    d.latexPrint(n);
    cout << endl;
    if (g == d)
        cout << "Equivalent!" << endl;
    else
        cout << "Not Equivalent!" << endl;
}
