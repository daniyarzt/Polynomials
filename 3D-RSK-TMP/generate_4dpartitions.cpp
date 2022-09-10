#include <bits/stdc++.h>


using namespace std;

#define ll long long
typedef vector < vector<vector< vector < ll > > > > mat4d;


struct PGeneratorState4D
{
	int i, j, k, h;
};

struct PartitionGenerator4D
{
	int N = 0, M = 0, K = 0, H = 0, n = 0, sum = 0;
	mat4d A;
	stack < PGeneratorState4D > st;

	PartitionGenerator4D() {}

	PartitionGenerator4D(int _N, int _M, int _K, int _H, int _n)
	{
    	N = _N;
		M = _M;
		K = _K;
	    H = _H;
		n = _n;
		A = vector < vector < vector < vector < ll > > > > (_N+1, vector < vector < vector < ll > > > (_M, vector < vector < ll > > (_K, vector < ll > (_H))));
		A[0][0][0][0] = 1;
		sum = 1;
		st.push({0, 0, 0, 0});
	}

	bool isTerminal(PGeneratorState4D state) 
	{
		return state.h == 0 && state.j == 0 && state.k == 0 && state.i == N;
	}

	PGeneratorState4D nextPos(PGeneratorState4D state)
	{
		if (state.j == M - 1 && state.k == K - 1 && state.h == H - 1)
			return {state.i + 1, 0, 0, 0};
		if (state.k == K - 1 && state.h == H - 1)
            return {state.i, state.j + 1, 0, 0};
        if (state.h  == H - 1)
			return {state.i, state.j, state.k + 1, 0};
		return {state.i, state.j, state.k, state.h + 1};
	}

	ll getVal(int i, int j, int k, int h)
	{
		if (i < 0 || j < 0 || k < 0 || h < 0)
			return INT_MAX;
		return A[i][j][k][h];	
	}	

	void retract() 
	{
		auto state = st.top();
		sum -= A[state.i][state.j][state.k][state.h];
		A[state.i][state.j][state.k][state.h] = 0;	

		st.pop();
		if (st.empty())	
			return;

		state = st.top();

		// we try to increment 
		ll mn = min({getVal(state.i - 1, state.j, state.k, state.h), getVal(state.i, state.j - 1, state.k, state.h), getVal(state.i, state.j, state.k - 1, state.h), getVal(state.i, state.j, state.k, state.h - 1)});
		if (A[state.i][state.j][state.k][state.h] < mn && sum < n)
		{
			A[state.i][state.j][state.k][state.h]++;
			sum++;
		}
		else
			retract();
		
	}


	void step()
	{
		//cerr << "step ";
		auto state = st.top();
		//cerr << state.i << ' ' << state.j << ' ' << state.k << endl;
		if (isTerminal(state))
		{
			retract();
			return;
		}
		auto nstate = nextPos(state);
		
		st.push(nstate);
	}

	mat4d getNext()
	{	
		if (st.empty())
			return mat4d();
		do
		{
			step();
		}
		while(!st.empty() && !(isTerminal(st.top()) && sum == n));
		if (st.empty())
			return mat4d();
		mat4d res = A;
		res.pop_back();
		return res;	
	}
};

void mat4dprint(mat4d A)
{
	cout << "-----------------------mat3dprint--------------------" << endl;
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();
    int h_len = A[0][0][0].size();
	cout << "dimensions: " << x_len << ' ' << y_len << ' ' << z_len << endl;
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{	
			for (int k = 0; k < z_len; k++)
			{   
                for (int h = 0; h < h_len; h++)
                {
			    	cout << A[i][j][k][h] << ' ';
			    }
            }
			cout << endl;
		}
		cout << endl;
	}	
	cout << "-----------------------------------------------------" << endl;
}

ll corner_hook_volume(mat4d A)
{
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();
    int h_len = A[0][0][0].size();

	ll vol = 0;
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{
			for (int k = 0; k < z_len; k++)
			{
                for (int h = 0; h < h_len; h++)
                {
				    ll mx = 0;
				    if (i < x_len - 1)
					    mx = max(A[i + 1][j][k][h], mx);
				    if (j < y_len - 1)	
					    mx = max(A[i][j + 1][k][h], mx);
				    if (k < z_len - 1)
					    mx = max(A[i][j][k + 1][h], mx);
                    if (h < h_len - 1)
                        mx = max(A[i][j][k][h + 1], mx);
				    vol += (A[i][j][k][h] - mx) * (i + j + k + h + 1);
                }
            }
		}
	}
	return vol;
}

int main() 
{
   
	ofstream myfile;
	for (int n = 1; n <= 15; n++)
	{
		myfile.open("4D-Partition-CH-volumes/n=" + to_string(n) + "ch-volumes.csv");		

		PartitionGenerator4D gen(n, n, n, n, n);
		auto A = gen.getNext();
		int cnt = 0;
		
		vector < int > cnt_ch(3 * n + 1);

		while(!A.empty())
		{	
			//mat3dprint(A);
			//myfile << corner_hook_volume(A) << "\n";
			cnt_ch[corner_hook_volume(A)]++;
			A = gen.getNext();
			cnt++;

		}                   
		for (int i = 1; i < (int)cnt_ch.size(); i++)
			myfile << i << "," << cnt_ch[i] << "\n";	
		cout << cnt <<endl;
		myfile.close();
	}
	return 0;
}