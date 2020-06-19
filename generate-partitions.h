
struct GenPartitions
{
    vector < string > res;

    void rec(int n, string cur)
    {
        if (n == 0)
        {
            res.pb(cur);
            return;
        }
        int last = n;
        if (!cur.empty())
            last = cur[(int)cur.size() - 1] - '0';
        for (int i = 1; i <= min(n, last); i++)
        {
            rec(n - i, cur + char(i + '0'));
        }
    }

    vector < string > gen(int n)
    {
        rec(n, "");
        return res;
    }
};

vector < string > generate_partitions(int n)
{
    GenPartitions G;
    return G.gen(n);
}
