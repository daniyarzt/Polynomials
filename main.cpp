#include <bits/stdc++.h>
#include "all.h"

using namespace std;

int main()
{
    TreeDimLGV Lattice;
    Lattice.addSource(0, 0, -4);
    Lattice.addSource(1, 0, -3);
    Lattice.addSink(1, 4, -2);
    Lattice.addSink(3, 4, -1);
    Lattice.addEdge(0, 0, 1, FLOOR, true, 1);
    Lattice.addEdge(-1, 0, 1, FLOOR, true, 10);
    Lattice.addEdge(0, 1, 0, WALL, true, 20);
    Lattice.addEdge(1, 1, 0, WALL, true, 30);
    Lattice.addEdge(1, 0, 0, WALL, true, 40);
    Polynomial res = Lattice.LGV();
    if (res.isPositive())
        cout << "Positive!" << endl;
    else
        cout << "Negative!" << endl;
}
