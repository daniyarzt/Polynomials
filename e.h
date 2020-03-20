
static map < int, int > character;
static vector < int > argv;
static Polynomial ans;

static void rec(int i, int k)
{
    if (k > (int)argv.size() - i)
        return;
    if (i == (int)argv.size())
    {
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

Polynomial e(vector < int > _argv, int k)
{
    argv = _argv;
    rec(0, k);
    return ans;
}
