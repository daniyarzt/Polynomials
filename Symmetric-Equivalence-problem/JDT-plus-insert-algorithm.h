/* 	
	It might be a solution for problem s_{rho/lambda} = s_{rho/lambda'}
	
	Idea of algorithm: We will fill SSYT T' of shape (rho/lambda') from SSYT T of shape (rho/lambda).
	Proceed inward(?) adding diagonals. Then there will be new cells to fill. First of all do JDT on them. 
	Then do an insert operation. 
*/

struct SymSchur
{
    vector < vector < int > > A, B;
    string lambda, mu;
    int n;
    vector < pair < int, int > > pts;
    Polynomial res, symres;

    Polynomial w()
    {
        Polynomial cur = Polynomial(1);
        for (int i = 1; i <= n; i++)
        {
            int degree = 0;
            for (int y = 0; y < lambda[0] - '0'; y++)
            {
                bool found = false;
                for (int x = 0; x < (int)lambda.size() && lambda[x] - '0' > y; x++)
                {
                    if (A[x][y] == i)
                    {
                        found = true;
                        break;
                    }
                }
                degree += found;
            }
            cur *= Xpower(i, degree);
        }
        return cur;
    }

	void jdt(int x, int y)
	{
		if (x + y == (int)A.size() - 1)
			return;
		if (B[x + 1][y] <= B[x][y + 1])
		{
			swap(B[x][y], B[x + 1][y]);
			jdt(x + 1, y);
		}
		else
		{
			swap(B[x][y], B[x][y + 1]);
			jdt(x, y + 1);
		}
	}

  	void insert(int r, int val)
  	{
  		//cerr << r << ' ' << val << endl;
  		for (int c = 0; c < (int)B[r].size(); c++)
  		{
  			if (r + c > (int)A.size() - 1)
  				break;
			if (B[r][c] == -1 && r + c == (int)A.size() - 1 && A[c][r] != -1)
			{
				B[r][c] = val;
				return;
			}
			if (B[r][c] > val)
			{
				swap(val, B[r][c]);
				insert(r + 1, val);
				return;
			}
  		}
  		insert(r + 1, val);
  	}

    void filling()
    {
    	for (int i = 0; i < (int)A.size(); i++)
    	{
    		for (int j = 0; j < (int)A[i].size(); j++)
    		{	
    			if (A[i][j] == -1)
    				cout << ' ';
				else
					cout << A[i][j];
    		}
    		cout << endl;
    	}
    	for (int i = 0; i < (int)B.size(); i++)
    		for (int j = 0; j < (int)B[i].size(); j++)
    			B[i][j] = -1;
    	int minDiag = 0, maxDiag = (int)A.size() - 1;
		for (int d = maxDiag; d >= minDiag; d--)
		{
			vector < int > vals;
			for (int x = d; x >= 0; x--)
			{
				int y = d - x;
				if (A[x][y] != -1)
					vals.pb(A[x][y]);			
			}
			//reverse(all(vals));
			for (int x = d; x >= 0; x--)
			{
				int y = d - x;
				if (A[y][x] == -1)
					continue;
				jdt(x, y);
				insert(0, vals.back()); // ?????? so what to insert
				vals.pop_back();
			}
		}
		for (int x = 0; x < (int)B.size(); x++)
		{
			for (int y = 0; y < (int)B[x].size(); y++)
			{
				if (B[x][y] == -1)
					cout << ' ';
				else
					cout << B[x][y];	
			}
			cout << endl;
		}
		cerr << "END" << endl;	
    }

    void rec(int id)
    {
        if (id == (int)pts.size())
        {
            res += w();
            filling();
            return;
        }
        int x = pts[id].first;
        int y = pts[id].second;
        int min_val = 1;
        if (x > 0 && A[x - 1][y] != -1)
            min_val = A[x - 1][y] + 1;
        if (y > 0 && A[x][y - 1] != -1)
            min_val = max(min_val, A[x][y - 1]);
        for (int i = min_val; i <= n; i++)
        {
            A[x][y] = i;
            rec(id + 1);
        }
    }

    Polynomial sol(string _lambda, string _mu, int _n)
    {
        lambda = _lambda, mu = _mu;
        n = _n;
        while((int)mu.size() < (int)lambda.size())
            mu += '0';
        A = vector < vector < int > > ((int)lambda.size());
        for (int i = 0; i < (int)lambda.size(); i++)
        {
            A[i] = vector < int > (lambda[i] - '0');
            for (int j = 0; j < mu[i] - '0'; j++)
                    A[i][j] = -1;            
            for (int j = mu[i] - '0'; j < lambda[i] - '0'; j++)
                pts.pb({i, j});
        }
        B = A;
        rec(0);
        return res;
    }
};


Polynomial symS(string lambda, string mu, int n)
{
    SymSchur str;
    return str.sol(lambda, mu, n);
}
