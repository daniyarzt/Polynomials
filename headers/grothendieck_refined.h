
#define forn(i, n) for (int i = 1; i <= n; i++)

static const bool WONNAPRINT = false;
using namespace std;

struct Grothendieck_refined
{
    Polynomial ans;
    string lambda, mu;
    int M, n;
    vector < vector < int > > a;
    vector < pair < int, int > > cells;

    Grothendieck_refined () {}

    Grothendieck_refined (string _lambda, string _mu, int _m): lambda(_lambda), mu(_mu), M(_m) {}

    void print(map < int, int > character)
    {
        cout << "-----------------------------------" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < (int)a[i].size(); j++)
            {
                if (!a[i][j])
                    cout << ' ';
                else
                    cout << a[i][j];
            }
            cout << endl;
        }
        cout << endl;
        cout << "x^c * t^d = ";
        bool tmp = false;
        for(auto it : character)
        {
            if (tmp)
                cout << " * ";
            tmp = true;
            if (it.first <= M)
            {
                cout << "x_" << it.first << "^" << it.second;
            }
            else
                cout << "t_" << it.first - M << "^" << it.second;
        }
        cout << endl;

        cout << "-----------------------------------" << endl;
    }

    map < int, int > getCharacter()
    {
        vector < int > c(M + 1);
        vector < int > d(n);
        vector < vector < bool > > used(M + 1, vector < bool > (lambda[0] - '0'));
        for (int i = 0; i < (int)cells.size(); i++)
        {
            int x = cells[i].first;
            int y = cells[i].second;
            used[a[x][y]][y] = true;
            if (x < n - 1 && a[x][y] == a[x + 1][y])
                d[x]++;
        }
        forn(i, M)
        {
            for (int j = 0; j < lambda[0] - '0'; j++)
                c[i] += used[i][j];
        }
        map < int, int > character;
        forn(i, M)
        {
            if (c[i])
                character[i] = c[i];
        }
        for (int i = 0; i < n; i++)
        {
            if (d[i])
                character[M + i + 1] = d[i];
        }
        return character;
    }

    void rec(int id)
    {
        if (id == (int)cells.size())
        {
            map < int, int > character = getCharacter();
            ans.add(character, 1);
            if (WONNAPRINT)
                print(character);
            return;
        }
        int x = cells[id].first;
        int y = cells[id].second;
        forn(i, M)
        {
            if (x > 0 && a[x - 1][y] > i)
                continue;
            if (y > 0 && a[x][y - 1] > i)
                continue;
            a[x][y] = i;
            rec(id + 1);
        }
    }

    Polynomial solve()
    {
        n = (int)lambda.size();
        while((int)mu.size() < n)
            mu += '0';
        a = vector < vector < int > > (n, vector < int > (lambda[0] - '0'));
        for (int i = 0; i < n; i++)
        {
            for (int j = mu[i] - '0'; j < lambda[i] - '0'; j++)
                cells.pb({i, j});
        }
        rec(0);
        ans.normalize();
        return ans;
    }
};

Polynomial grothendieck_refined(string lambda, string mu, int m)
{
    Grothendieck_refined G(lambda, mu, m);
    return G.solve();
}
