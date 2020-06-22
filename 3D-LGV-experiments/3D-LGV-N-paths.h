// struct Path: {source, weigh, {list of Edges}}
// generator: Path(x, y, z) - creates Path with source - (x, y, z)
// functions:
// addEdge(Edge e, Polynomial weight) - adds an edge to the current path
// addEdge(Edge e, int id) - same as prev. but weight = x_{id}
// print() - prints source, and seq. of edges

struct Path
{
    int source_x, source_y, source_z;
    Polynomial weight;
    vector < Edge > edges;

    Path () {}

    Path (int x, int y, int z): source_x(x), source_y(y), source_z(z), weight(1) {}

    void addEdge(Edge e, Polynomial w)
    {
        edges.pb(e);
        weight *= w;
    }

    void addEdge(Edge e, int id)
    {
        edges.pb(e);
        weight *= Xpower(id, 1);
    }

    void print()
    {
        cout << "--path print--" << endl;
        cout << "Source: " << source_x << ' ' << source_y << ' ' << source_z << endl;
        cout << "Edges: ";
        for (auto e : edges)
            cout << '(' << e.dx << ',' << e.dy << ',' << e.dz << ") ";
        cout << endl << "--------------" << endl;
    }
};




