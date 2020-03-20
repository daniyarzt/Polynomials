
struct E
{
    map < int, int > character;
    vector < int > argv;
    Polynomial ans;

    E() {}

    E(vector < int > _argv):argv(_argv) {}

    void rec(int i, int k)
    {
        if (k > (int)argv.size() - i)
            return;
        if (i == (int)argv.size())
        {
            assert(k == 0);
            ans.add(character, 1);
            return;
        }
        if (k > 0)
        {
            character[argv[i]]++;
            rec(i + 1, k - 1);
            character.erase(argv[i]);
        }
        rec(i + 1, k);
    }
};
Polynomial e(vector < int > _argv, int k)
{
    E res(_argv);
    if (k >= 0)
        res.rec(0, k);
    return res.ans;
}
