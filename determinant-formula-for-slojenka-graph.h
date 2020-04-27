// The task is to calculate theorem 2 from https://arxiv.org/pdf/1604.06276.pdf, and check the expression for positivity
// in a special case G1 = G2 = G3 = G4 = ..., G - acyclic,

vector < pair < int, int > > generate_edge_set(int n, int m)
{
    // we will build acyclic graph in a way that for each e: i -> j, i < j
    vector < pair < int, int > > e;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            e.pb({i, j});
        }
    }
    random_shuffle(all(e));
    assert(m <= (int)e.size());
    while((int)e.size() > m)
        e.pop_back();
    return e;
}

vector < vector < pair < int, int > > > generate_slojenka_graph(int n, int L, int m, vector < pair < int, int > > e)
{
    vector < vector < pair < int, int > > > g(n * L);
    for (int i = 0; i < m; i++)
    {
        int v = e[i].first;
        int u = e[i].second;
        for (int layer = 0; layer < L; layer++)
        {
            g[layer * n + v].pb({layer * n + u, i + 1});
        }
    }
    for (int layer = 0; layer < L - 1; layer++)
    {
        for (int v = 0; v < n; v++)
        {
            g[layer * n + v].pb({layer * n + v + n, 0}); // between layer edges
        }
    }
    return g;
}

vector < int > generate_set(int n, int k)
{
    vector < int > p(n);
    for (int i = 0; i < n; i++)
        p[i] = i;
    random_shuffle(all(p));
    vector < int > res(k);
    for (int i = 0; i < k; i++)
            res[i] = p[i];
    return res;
}

bool positivity_of_determinant_formula_of_slojenka_graph(int n, int k, int L, int m, int seed)
{
    // N = number of vertices, L = number of layers, m = number of edges, k = number of sources and sinks
    srand(seed);
    vector < pair < int, int > > e = generate_edge_set(n, m);
    vector < vector < pair < int, int > > > g = generate_slojenka_graph(n, L, m, e);
    vector < int > A = generate_set(n, k);
    vector < int > B = generate_set(n, k);
    for (int i = 0; i < k; i++)
        B[i] = (L - 1) * n + B[i];
    // Matrix P, where P[i][j] = sum_{path: A[i] -> B[j]}(w(path))
    vector < vector < Polynomial > > P(k, vector < Polynomial > (k));
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            Graph G(g);
            P[i][j] = G.calc_w(A[i], B[j]);
        }
    }
    Polynomial res = det(P); // graph is acyclic, thus what is left in the function is the classical LGV
    if (res.p.empty())
        cout << "Empty!" << endl;
    else if (res.isPositive())
    {
        cout << "Positive!" << endl;
        return true;
    }
    else
    {
        cout << "Negative!" << endl;
        for (auto it : e)
            cout << it.first << ' ' << it.second << endl;
        cout << "A: ";
        for (auto it : A)
            cout << it << ' ';
        cout << endl << "B: ";
        for (auto it : B)
            cout << it << ' ';
        cout << endl;
        cout << "res = " << endl;
        res.print();
        return false;
    }
}
