void experiment()
{
    TreeDimLGV Lattice;
    Lattice.addEdge(0, 0, 1, FLOOR, true, 1);
    Lattice.addEdge(1, 0, 1, FLOOR, true, 10);
    Lattice.addEdge(1, 1, 0, WALL, true, 20);
    Lattice.addEdge(0, 1, 0, WALL, true, 30);
    vector < int > Ax = {1, 2, 2, 3, 5};
    vector < int > Az = {1, 1, 3, 4, 4};
    straightCheck(Ax, 3, Az, Lattice);
}

