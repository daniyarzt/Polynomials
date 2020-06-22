struct CompleteHomogenousSymmetricFunction
{
    vector < int > ids, powers;
    Polynomial res;

    CompleteHomogenousSymmetricFunction () {}

    CompleteHomogenousSymmetricFunction (vector < int > _ids): ids(_ids), powers((int)_ids.size()) {}

    void rec(int id, int k)
    {
        if (id == (int)ids.size())
        {
            if (k)
                return;
            Polynomial cur(1);
            for (int i = 0; i < (int)ids.size(); i++)
            {
                if (powers[i])
                    cur *= Xpower(ids[i], powers[i]);
            }
            res += cur;
            return;
        }
        for (int i = 0; i <= k; i++)
        {
            powers[id] = i;
            rec(id + 1, k - i);
        }
    }

    Polynomial sol(int k)
    {
        rec(0, k);
        return res;
    }
};

Polynomial h(vector < int > arg, int k)
{
    if (k < 0)
        return Polynomial();
    CompleteHomogenousSymmetricFunction h(arg);
    return h.sol(k);
}
