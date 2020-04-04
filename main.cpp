#include <bits/stdc++.h>
#include "all.h"

using namespace std;

int main()
{
    string lambda;
    int n;
    cin >> lambda;
    cin >> n;
    while((int)lambda.size() < n)
        lambda += '0';
    Polynomial G = grassman(lambda, n);
    G.print();
    Polynomial D = denomenator(n);
    D.print();
    Polynomial N = numerator(lambda, n);
    N.normalize();
    N.print();
    G *= D;
    G.normalize();
    G.print();
    if (G == N)
        cout << "Same!!!" << endl;
    else
        cout << "Not really" << endl;
    /*TreeDimLGV Lattice;
     Lattice.addSource(0, 0, -4);
    Lattice.addSource(1, 0, -4);
    Lattice.addSource(2, 0, -4);
    Lattice.addSource(4, 0, -4);
    Lattice.addSink(4, 4, -2);
    Lattice.addSink(5, 4, -1);
    Lattice.addSink(6, 4, -1);
    Lattice.addSink(7, 4, 0);
    Lattice.addEdge(0, 0, 1, FLOOR, true, 1);
    Lattice.addEdge(-1, 0, 1, FLOOR, true, 10);
    Lattice.addEdge(0, 1, 0, WALL, true, 20);
    Lattice.addEdge(1, 1, 0, WALL, true, 30);
    Lattice.addEdge(2, 1, 0, WALL, true, 40);
    Lattice.LGV();
    return 0;*/
    /*srand(time(NULL));
    bool pos;
    do
    {
        pos = false;
        TreeDimLGV Lattice;
        Lattice.randomInit(3);
   Lattice.addEdge(0, 0, 1, FLOOR, true, 1);
    Lattice.addEdge(1, 0, 1, FLOOR, true, 10);
    Lattice.addEdge(-1, 1, 0, WALL, true, 20);
    Lattice.addEdge(0, 1, 0, WALL, true, 30);
        Polynomial res = Lattice.LGV();
        //res.print();
        if (pos = res.isPositive())
            cout << "Positive!" << endl;
        else
            cout << "Negative!" << endl;
    }
    while(pos);*/
    return 0;
}
