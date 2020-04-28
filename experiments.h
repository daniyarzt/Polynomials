void experiment()
{
    TreeDimLGV Lattice;
    Lattice.addEdge(0, 0, 1, FLOOR, true, 100);
    Lattice.addEdge(-1, 0, 1, FLOOR, true, 200);
    Lattice.addEdge(1, 1, 0, WALL, true, 300);
    Lattice.addEdge(0, 1, 0, WALL, true, 400);
    int m = 2;
    vector < int > L = {2, 2};
    // vector < int > X = {3, 2};
    // vector < int > Z = {2, 2};
    int n = L.size();
    for (int i = 0; i < n; i++) {
    	Lattice.addSource(i - 1, 0, -L[i]);
    	Lattice.addSink(i, m, 0);
    }
    Polynomial P = Lattice.LGV();
    ll g = 0;
    for (auto &[ch, coef] : P.p) {
        g = __gcd(g, coef);
    }
    for (auto &[ch, coef] : P.p) {
        coef /= g;
    }
    cout << g << "\n";
    P.print();
    if (P.isPositive())
    	cout << "isPositive\n";
    else
    	cout << "naaah\n";
    cout << g << "\n";
}

