
static const int FLOOR = 0;
static const int WALL = 1;
static const int K = 20;

struct Edge
{
    int dx, dy, dz, type;
    bool isWeighted;
    int firstID;

    bool canUse(int x, int y, int z)
    {
        if (type == FLOOR && y > 0)
            return false;
        return true;
    }
};

struct Paths
{
    int fx, fy, fz;
    vector < Edge > e;
    map < int, map < int, map < int, bool > > > was;
    Polynomial res;
    map < int, int > character;

    Paths () {}

    Paths (int _fx, int _fy, int _fz, const vector < Edge > & _e): fx(_fx), fy(_fy), fz(_fz), e(_e) {}

    bool isInside(int x, int y, int z)
    {
        return abs(x) < K && abs(y) < K && abs(z) < K;
    }

    void dfs1(int x, int y, int z)
    {
        if (!isInside(x, y, z))
            return;
        if (was[x][y][z])
            return;
        was[x][y][z] = true;
        for (auto it : e)
        {
            int tx = x - it.dx;
            int ty = y - it.dy;
            int tz = z - it.dz;
            if (it.canUse(tx, ty, tz))
                dfs1(tx, ty, tz);
        }
    }

    void dfs2(int x, int y, int z)
    {
        if (!was[x][y][z])
            return;
        if (x == fx && y == fy && z == fz)
        {
            res.add(character, 1);
            return;
        }
        for (auto it : e)
        {
            if (!it.canUse(x, y, z))
                continue;
            if (it.isWeighted)
            {
                int id;
                if (it.type == FLOOR)
                    id = it.firstID + z - 1;
                else
                    id = it.firstID - y;
                character[id]++;
                dfs2(x + it.dx, y + it.dy, z + it.dz);
                character[id]--;
                if (character[id] == 0)
                    character.erase(id);
            }
            else
            {
                dfs2(x + it.dx, y + it.dy, z + it.dz);
            }
        }
    }
};

Polynomial W(int x1, int y1, int z1, int x2, int y2, int z2, const vector < Edge > & e)
{
    Paths P(x2, y2, z2, e);
    P.dfs1(x2, y2, z2);
    P.dfs2(x1, y1, z1);
    P.res.normalize();
    return P.res;
}

struct TreeDimLGV
{
    vector < Edge > e;
    vector < int > Ax, Ay, Az;
    vector < int > Bx, By, Bz;

    void addEdge(int dx, int dy, int dz, int type, bool isWeighted, int firstID)
    {
        e.pb({dx, dy, dz, type, isWeighted, firstID});
    }

    void addSource(int x, int y, int z)
    {
        Ax.pb(x);
        Ay.pb(y);
        Az.pb(z);
    }

    void addSink(int x, int y, int z)
    {
        Bx.pb(x);
        By.pb(y);
        Bz.pb(z);
    }

    Polynomial LGV()
    {
        int n = (int)Ax.size();
        vector < vector < Polynomial > > A(n, vector < Polynomial > (n));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                A[i][j] = W(Ax[i], Ay[i], Az[i], Bx[j], By[j], Bz[j], e);
            }
        }
        return det(A);
    }

    void GrothendieckInit(string lambda, string mu, int M)
    {
        int n = lambda[0] - '0';
        for (int i = 0; i < n; i++)
        {
            int _l = 0;
            for (int x = 0; x < (int)lambda.size(); x++)
                _l += bool(lambda[x] - '0' >= i + 1);
            addSource(i, 0, _l - 1);
        }
        for (int i = 0; i < n; i++)
        {
            int _m = 0;
            for (int x = 0; x < (int)mu.size(); x++)
                _m += bool(mu[x] - '0' >= i + 1);
            addSink(i + 1, M, _m);
        }
        addEdge(0, 1, 0, WALL, false, M);
        addEdge(1, 1, 0, WALL, true, M);
        addEdge(0, 0, -1, FLOOR, true, M + 1);
        addEdge(-1, 0, -1, FLOOR, false, M + 1);
    }
};
