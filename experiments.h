
int MAXP = 3; // max lam part
int MAX_X = 3; // number of x-vars (height)
int MAX_Z = 2; // number of z-vars (width)
int n = 2; // size of det

#include "all.h"
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
void experiment() {
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

void experiment2() {
    c[0][0] = 1;
    for (int i = 1; i < 30; i++)
        for (int j = 0; j <= i; j++)
            c[i][j] = (j == 0 ? 1 : c[i-1][j-1] + c[i-1][j]);


    TreeDimLGV Lattice;
    int xID = 100;
    int yID = 200;
    int zID = 300;
    int m = 2;
    int k = 2;
    // int n = 2;
    vector < int > lam = {4, 3, 2};
    vector < int > mu = {2, 1, 0};
    int n = lam.size();
    // while(sz(mu) < n) mu.pb(0);

    Lattice.addEdge(1, 0, 0, DOOR, true, xID);
    Lattice.addEdge(0, 1, 0, WALL, true, yID);
    Lattice.addEdge(0, 0, 1, FLOOR, true, zID);

    Check({0, 1, 2, 3, 4}, 4, {0, 1, 2, 3, 4}, Lattice);
}

int get_rand(int n) {
    if (n == 0) return 0;
    int N = n * (n + 1) / 2;
    int x = rand() % (N + 1);
    int y = 0;
    while (x > y * (y + 1) / 2) y++;
    return y;
}


void gen_rand_par(vector<int> &a, vector<int> bound = vector<int>()) {
    int n = sz(a);
    if (sz(bound) == 0) {
        bound.resize(n);
        for (int i = 0; i < n; i++) {
            bound[i] = MAXP+1;
        }
    }
    for (int i = 0; i < n; i++) {
        int up = min(max(0, bound[i]-1), i == 0 ? 100 : a[i-1]);
        a[i] = get_rand(up);
        // a[i] = rand() % (min(bound[i], (i == 0 ? 100 : a[i-1])) + 1);
    }
}

void gen_rand_seq(vector<int> &a, vector<int> b = vector<int>()) {
    int n = sz(a);
    if (sz(b) < n) {
        b.resize(n);
        for (int i = 0; i < n; i++) b[i] = MAXP;
    }
    for (int i = 0; i < n; i++) {
        a[i] = 1 + rand() % b[i];
    }
}

/* x-floor + z-walls */
void experiment3() {
    c[0][0] = 1;
    for (int i = 1; i < 30; i++)
        for (int j = 0; j <= i; j++)
            c[i][j] = (j == 0 ? 1 : c[i-1][j-1] + c[i-1][j]);


    
    int xID = 100;
    int yID = 200;
    int zID = 300;

    int n = 4;
    vector < int > lam = {4, 3, 2};
    vector < int > mu = {2, 1, 0};
    vector < int > a = {2, 3, 4, 5};
    vector < int > b = {4, 4, 4, 4};
    lam.resize(n);
    mu.resize(n);
    a.resize(n);
    b.resize(n);

    srand(time(NULL));
    while(true) {
        gen_rand_par(lam);
        gen_rand_par(mu, lam);
        gen_rand_par(a);
        // reverse(all(a));
        gen_rand_par(b);
        // reverse(all(b));

        // int cur = W;
        // for (int i = 0; i < n; i++) {
        //     lam[i] = rand() % ((i == 0 ? W : lam[i-1]) + 1);
        //     mu[i] = rand() % (min(lam[i], (i == 0 ? W : mu[i-1])) + 1);

        //     // a[] <= lam[]
        //     a[i] = rand() % (min(lam[i], (i == 0 ? W : a[i-1])) + 1);
        //     a[i] = rand() % (min(lam[i], (i == 0 ? W : a[i-1])) + 1);

        //     // 
        //     b[i] = rand();
        //     // b[i] = i == 0
        //     //     ? 1 + rand() % H
        //     //     : b[i-1] + rand() % (H - b[i-1] + 1);
        //     // b[i] = 1 + rand() % H;
        // }

        TreeDimLGV Lattice;
        Lattice.addEdge(0, -1, 0, WALL, false, zID);
        // Lattice.addEdge(1, 1, 0, WALL, true, zID);
        Lattice.addEdge(-1, 0, 0, WALL, true, zID);
        Lattice.addEdge(-1, 0, -1, FLOOR, true, xID);
        Lattice.addEdge(0, 0, -1, FLOOR, false, xID);

        for (int i = 0; i < n; i++) {
            // Lattice.addSource(i - lam[i], 0, 0);
            // Lattice.addSink(i - mu[i], b[i], a[i]);
            Lattice.addSink(i - lam[i], 0, 0);
            Lattice.addSource(i - mu[i], b[i], a[i]);
        }
        cout << "\n==================\n";
        Polynomial P = Lattice.LGV();
        if (P.p.size() <= 1) continue;

        P.print();
        cout << "lambda = "; for (int i = 0; i < n; i++) cout << lam[i]; cout << " ";
        cout << "mu = "; for (int i = 0; i < n; i++) cout << mu[i]; cout << "\n";
        cout << "a = "; for (int i = 0; i < n; i++) cout << a[i]; cout << "\n";
        cout << "b = "; for (int i = 0; i < n; i++) cout << b[i]; cout << "\n";
        Lattice.print();
        if (P.isPositive())
            cout << "isPositive\n";
        else {
            cout << "naaah\n";
            break;
        }
    }

    /*
        1) lambda = 1110 mu = 0000
        a = 4556
        b = 2455
        104 weight involves neg


    */
}

/* x-wall[H] + z-floors[H] */
void experiment4() {
    int xID = 100;
    int yID = 200;
    int zID = 300;

    vector<int> boundX(n, MAX_X);
    vector<int> boundZ(n, MAX_Z);

    vector < int > lam = {2,2};//{4,4,3,2};
    vector < int > mu = {0,0};
    // vector < int > a = {3,2,2,1};
    // vector < int > b = {1,1,2,4};
    vector < int > a = {2,3};
    vector < int > b = {1,2};
    lam.resize(n);
    mu.resize(n, 0);
    a.resize(n);
    b.resize(n);

    srand(time(NULL));
    int T = 20;
    // while(T--) {
    while(true) {
        // gen_rand_seq(lam); sort(all(lam)); reverse(all(lam));
        // gen_rand_par(lam);
        // gen_rand_par(mu, lam);
        // gen_rand_par(a, boundX); reverse(all(a)); // 0 <= a[i] <= MAX_X - 1
        // gen_rand_par(b, boundZ); reverse(all(b)); // 0 <= b[i] <= MAX_Z - 1
        // for (int i = 0; i < n; i++) a[i]++, b[i]++;

        TreeDimLGV Lattice;
        Lattice.addEdge(0, 1, 0, WALL, false, xID);
        Lattice.addEdge(1, 0, 0, WALL, true, xID);
        Lattice.addEdge(1, 0, 0, FLOOR, true, zID);
        Lattice.addEdge(0, 0, 1, FLOOR, false, zID);

        for (int i = 0; i < n; i++) {
            assert(MAX_X + 1 - a[i] > 0);
            Lattice.addSource(i - lam[i], MAX_X + 1 - a[i], -b[i]);
            Lattice.addSink(i - mu[i], MAX_X, 0);
        }
        Lattice.calcLGV();
        
        cout << "~~~~~~~~~~~~~~~~~\n";
        // Lattice.print();
        // cout << "lambda = "; for (int i = 0; i < n; i++) cout << lam[i]; cout << " ";
        // cout << "mu = "; for (int i = 0; i < n; i++) cout << mu[i]; cout << "\n";
        // cout << "a = "; for (int i = 0; i < n; i++) cout << a[i]; cout << "\n";
        // cout << "b = "; for (int i = 0; i < n; i++) cout << b[i]; cout << "\n";

        if (!Lattice.isInteresting())
            continue;
        cout << "Interesting...\n";
        Polynomial P = Lattice.getLGV();
        cout << "P = ";
        P.print();
        cout << "lambda = "; for (int i = 0; i < n; i++) cout << lam[i]; cout << " ";
        cout << "mu = "; for (int i = 0; i < n; i++) cout << mu[i]; cout << "\n";
        cout << "a = "; for (int i = 0; i < n; i++) cout << a[i]; cout << "\n";
        cout << "b = "; for (int i = 0; i < n; i++) cout << b[i]; cout << "\n";
        // Polynomial Q = P.spec_minus(zID-10, zID + 10);
        if (P.isPositive()) {
            Lattice.print();
            cout << "P-positive\n";
            Polynomial I = Lattice.getTrace();
            I -= P;
            assert(I.isPositive());
            cout << "Only indentity:\n";
            cout << "Tr-P =";
            I.print();

        }
        else {
            Lattice.print(true);
            cout << "naaah\n";
            exit(0);
        }

        if (sz(P.p) <= 10) exit(0);
        exit(0);
    }
}


/* x-wall[H] + z-floors[E] */
void experiment5() {
    int xID = 100;
    int yID = 200;
    int zID = 300;

    int n = 4;
    vector<int> boundX(n, MAX_X);
    vector<int> boundZ(n, MAX_Z);

    vector < int > lam = {4,4,3,2};
    vector < int > mu = {3,1};
    vector < int > a = {3,2,1,1};
    vector < int > b = {1,2,2,3};
    lam.resize(n);
    mu.resize(n, 0);
    a.resize(n);
    b.resize(n);

    srand(time(NULL));
    int T = 20;
    // while(T--) {
    while(true) {
        gen_rand_par(lam);
        gen_rand_par(mu, lam);
        // gen_rand_par(a, boundX); // 0 <= a[i] <= MAX_X - 1
        // gen_rand_par(b, boundZ); reverse(all(b)); // 0 <= b[i] <= MAX_Z - 1


        TreeDimLGV Lattice;
        Lattice.addEdge(0, 1, 0, WALL, false, xID);
        Lattice.addEdge(1, 0, 0, WALL, true, xID);
        Lattice.addEdge(1, 0, 1, FLOOR, true, zID);
        Lattice.addEdge(0, 0, 1, FLOOR, false, zID);

        for (int i = 0; i < n; i++) {
            Lattice.addSource(i - lam[i], a[i], -b[i]);
            Lattice.addSink(i - mu[i], n, 0);
        }
        Lattice.calcLGV();
        
        cout << "~~~~~~~~~~~~~~~~~\n";
        // Lattice.print();
        // cout << "lambda = "; for (int i = 0; i < n; i++) cout << lam[i]; cout << " ";
        // cout << "mu = "; for (int i = 0; i < n; i++) cout << mu[i]; cout << "\n";
        // cout << "a = "; for (int i = 0; i < n; i++) cout << a[i]; cout << "\n";
        // cout << "b = "; for (int i = 0; i < n; i++) cout << b[i]; cout << "\n";

        if (!Lattice.isInteresting())
            continue;
        cout << "Interesting...\n";
        Polynomial P = Lattice.getLGV();
        P.print();
        cout << "lambda = "; for (int i = 0; i < n; i++) cout << lam[i]; cout << " ";
        cout << "mu = "; for (int i = 0; i < n; i++) cout << mu[i]; cout << "\n";
        cout << "a = "; for (int i = 0; i < n; i++) cout << a[i]; cout << "\n";
        cout << "b = "; for (int i = 0; i < n; i++) cout << b[i]; cout << "\n";
        
        // Polynomial Q = P.spec_minus(zID-10, zID + 10);
        if (P.isPositive()) {
            Lattice.print();
            cout << "P-positive\n";
            Polynomial I = Lattice.getTrace();
            I -= P;
            assert(I.isPositive());
            cout << "Only indentity\n";

        }
        else {
            Lattice.print(true);
            cout << "naaah\n";
            break;
        }
        // break;
    }

    /*
        1) lambda = 1110 mu = 0000
        a = 4556
        b = 2455
        104 weight involves neg


    */
}
