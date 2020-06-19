
// for each n, split partitions of n into families with same s_{\lambda}

void experiment1606()
{
    int n, m;
    cin >> n >> m;
    vector < string > pars = generate_partitions(n);
    map < map < map < int, int >, ll >, int > id;
    vector < vector < string > > fam;
    for (auto lambda : pars)
    {
        Polynomial func = grothendieck_refined(lambda, "", m);
        func.normalize();
        int curId = (int)fam.size();
        if (id.count(func.p))
            curId = id[func.p];
        else
        {
            id[func.p] = curId;
            fam.emplace_back();
        }
        fam[curId].pb(lambda);
    }
    for (auto v : fam)
    {
        cout << "{";
        bool tmp = false;
        for (auto lambda : v)
        {
            if (tmp)
                cout << ", ";
            cout << lambda;
            tmp = true;
        }
        cout << "}" << endl;
    }
}

void experiment1606withRho()
{
    int n, m;
    int k;
    cout << "n = ";
    cin >> n;
    cout << "k = ";
    cin >> k;
    cout << "m = ";
    cin >> m;

    string rho;
    for (int i = k; i >= 1; i--)
        rho += char(i + '0');

    vector < string > pars = generate_partitions(n);
    map < map < map < int, int >, ll >, int > id;
    vector < vector < string > > fam;

    vector < string > tmpPars;
    for (auto lambda : pars)
    {
        bool good = true;
        for (int i = 0; i < (int)lambda.size(); i++)
            if (lambda[i] > rho[i])
                good = false;
        if (good)
            tmpPars.pb(lambda);
    }
    pars = tmpPars;

    for (auto lambda : pars)
    {
        Polynomial func = s(rho, lambda, m);
        func.normalize();
        int curId = (int)fam.size();
        if (id.count(func.p))
            curId = id[func.p];
        else
        {
            id[func.p] = curId;
            fam.emplace_back();
        }
        fam[curId].pb(lambda);
    }
    for (auto v : fam)
    {
        cout << "{";
        bool tmp = false;
        for (auto lambda : v)
        {
            if (tmp)
                cout << ", ";
            cout << lambda;
            tmp = true;
        }
        cout << "}" << endl;
    }
}
