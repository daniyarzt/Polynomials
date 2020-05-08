#define MULTIFLOORS
#define sz(x) ((int)x.size())

void test_sym(Polynomial &P, int l, int r) {
    cout << "[" << l << " " << r << "] is ";
    cout << (P.LRSymmetric(l, r) ? "sym" : "non-sym") << "\n";
}


ll c[30][30];
ll C(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    return c[n][k];
}
void experiment()
{
    c[0][0] = 1;
    for (int i = 1; i < 30; i++)
        for (int j = 0; j <= i; j++)
            c[i][j] = (j == 0 ? 1 : c[i-1][j-1] + c[i-1][j]);


    TreeDimLGV Lattice;
    int m = 4;
    vector < int > lam = {3, 2, 2};
    vector < int > mu = {2, 1, 0};

    const int xID = 1;
    const int tID = m + lam[0];

    int n = lam.size();
    while(sz(mu) < n) mu.pb(0);

    Lattice.addEdge(0, 0, 1, FLOOR, true, tID);
    Lattice.addEdge(-1, 0, 1, FLOOR, false, 0);
    Lattice.addEdge(1, 1, 0, WALL, true, xID);
    Lattice.addEdge(0, 1, 0, WALL, false, 0);

    for (int i = 0; i < n; i++) {
    	Lattice.addSource(i-1, 0, -lam[i]+1);
    	Lattice.addSink(i, m, -mu[i]);
    }

    Polynomial P = Lattice.LGV();
    ll g = 0;
    for (auto &[ch, coef] : P.p) {
        g = __gcd(g, abs(coef));
    }
    for (auto &[ch, coef] : P.p) {
        coef /= g;
    }
    P.print();
    cout << "coef = " << g << "\n";
    if (P.isPositive())
    	cout << "isPositive\n";
    else
    	cout << "naaah\n";
    test_sym(P, xID, xID + m - 1);
    test_sym(P, tID - lam[0] + 1, tID - 1);

    cout << "coef = " << g << "\n";
    ll prod = 1;
    for (int i = 0; i < n; i++)
        prod *= C(m + lam[i] - mu[i] - 1, m);
    cout << "my = " << prod << "\n";
    assert(prod == g);


    // P.symmetricPrint({ mp(300, 300 + m - 1) });
}

