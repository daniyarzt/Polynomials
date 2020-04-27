#include <bits/stdc++.h>
#include "all.h"

using namespace std;

int main()
{
    TreeDimLGV Lattice;
    Lattice.randomInit(3);
    Lattice.addEdge(0, 0, 1, FLOOR, true, 1);
    Lattice.addEdge(1, 0, 1, FLOOR, true, 10);
    Lattice.addEdge(1, 1, 0, WALL, true, 20)
    //expansion_conjecture();
    /*bool good;
    do
    {
        TreeDimLGV lattice;
        lattice.addEdge(0, 0, 1, WALL, false, -1);
        lattice.addEdge(0, 1, 0, WALL, true, 1);
        lattice.addEdge(1, 1, 0, WALL, true, 20);

        generate_layer_lattice_xy_weakly_increasing(lattice, 3);
        Polynomial res = lattice.LGV();
        good = res.isPositive();
        res.print();
        if (good)
            cout << "Positive!" << endl;
        else
        {
            cout << "Negative!" << endl;
            lattice.print();
        }
    }
    while(good);*/

    return 0;
}
