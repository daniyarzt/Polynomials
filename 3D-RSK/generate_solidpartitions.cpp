#include <bits/stdc++.h>


using namespace std;

#define ll long long
typedef vector<vector< vector < ll > > > mat3d;


struct SPGeneratorState
{
	int i, j, k;
};

struct SolidPartitionGenerator
{
	int N = 0, M = 0, K = 0, n = 0, sum = 0;
	mat3d A;
	stack < SPGeneratorState > st;

	SolidPartitionGenerator() {}

	SolidPartitionGenerator(int _N, int _M, int _K, int _n)
	{
		N = _N;
		M = _M;
		K = _K;
		n = _n;
		A = vector < vector < vector < ll > > > (_N+1, vector < vector < ll > > (_M, vector < ll > (_K, 0)));
		A[0][0][0] = 1;
		sum = 1;
		st.push({0, 0, 0});
	}

	bool isTerminal(SPGeneratorState state) 
	{
		return state.j == 0 && state.k == 0 && state.i == N;
	}

	SPGeneratorState nextPos(SPGeneratorState state)
	{
		if (state.j == M - 1 && state.k == K - 1)
			return {state.i + 1, 0, 0};
		if (state.k  == K - 1)
			return {state.i, state.j + 1, 0};
		return {state.i, state.j, state.k + 1};
	}

	ll getVal(int i, int j, int k)
	{
		if (i < 0 || j < 0 || k < 0)
			return INT_MAX;
		return A[i][j][k];	
	}	

	void retract() 
	{
		SPGeneratorState state = st.top();
		sum -= A[state.i][state.j][state.k];
		A[state.i][state.j][state.k] = 0;	

		st.pop();
		if (st.empty())	
			return;

		state = st.top();

		// we try to increment 
		ll mn = min({getVal(state.i - 1, state.j, state.k), getVal(state.i, state.j - 1, state.k), getVal(state.i, state.j, state.k - 1)});
		if (A[state.i][state.j][state.k] < mn && sum < n)
		{
			A[state.i][state.j][state.k]++;
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

	mat3d getNext()
	{	
		if (st.empty())
			return mat3d();
		do
		{
			step();
		}
		while(!st.empty() && !(isTerminal(st.top()) && sum == n));
		if (st.empty())
			return mat3d();
		mat3d res = A;
		res.pop_back();
		return res;	
	}
};

void mat3dprint(mat3d A)
{
	cout << "-----------------------mat3dprint--------------------" << endl;
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();
	cout << "dimensions: " << x_len << ' ' << y_len << ' ' << z_len << endl;
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{	
			for (int k = 0; k < z_len; k++)
			{
				cout << A[i][j][k] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}	
	cout << "-----------------------------------------------------" << endl;
}

ll corner_hook_volume(mat3d A)
{
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();

	ll vol = 0;
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{
			for (int k = 0; k < z_len; k++)
			{
				ll mx = 0;
				if (i < x_len - 1)
					mx = max(A[i + 1][j][k], mx);
				if (j < y_len - 1)	
					mx = max(A[i][j + 1][k], mx);
				if (k < z_len - 1)
					mx = max(A[i][j][k + 1], mx);
				vol += (A[i][j][k] - mx) * (i + j + k + 1);
			}
		}
	}
	return vol;
}

ll ch1(mat3d A)
{
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();

	ll vol = 0;
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{
			for (int k = 0; k < z_len; k++)
			{
				ll mx = 0;
				if (i < x_len - 1)
					mx = max(A[i + 1][j][k], mx);
				if (j < y_len - 1)	
					mx = max(A[i][j + 1][k], mx);
				if (k < z_len - 1)
					mx = max(A[i][j][k + 1], mx);
				vol += (A[i][j][k] - mx) * (i + 1);
			}
		}
	}
	return vol;
}

ll ch2(mat3d A)
{
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();

	ll vol = 0;
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{
			for (int k = 0; k < z_len; k++)
			{
				ll mx = 0;
				if (i < x_len - 1)
					mx = max(A[i + 1][j][k], mx);
				if (j < y_len - 1)	
					mx = max(A[i][j + 1][k], mx);
				if (k < z_len - 1)
					mx = max(A[i][j][k + 1], mx);
				vol += (A[i][j][k] - mx) * (j + 1);
			}
		}
	}
	return vol;
}

ll ch3(mat3d A)
{
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();

	ll vol = 0;
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{
			for (int k = 0; k < z_len; k++)
			{
				ll mx = 0;
				if (i < x_len - 1)
					mx = max(A[i + 1][j][k], mx);
				if (j < y_len - 1)	
					mx = max(A[i][j + 1][k], mx);
				if (k < z_len - 1)
					mx = max(A[i][j][k + 1], mx);
				vol += (A[i][j][k] - mx) * (k + 1);
			}
		}
	}
	return vol;
}

ll ch_count(mat3d A)
{
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();

	ll vol = 0;
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{
			for (int k = 0; k < z_len; k++)
			{
				ll mx = 0;
				if (i < x_len - 1)
					mx = max(A[i + 1][j][k], mx);
				if (j < y_len - 1)	
					mx = max(A[i][j + 1][k], mx);
				if (k < z_len - 1)
					mx = max(A[i][j][k + 1], mx);
				vol += (A[i][j][k] - mx);
			}
		}
	}
	return vol;
}

int main() 
{
	ofstream myfile;
	for (int n = 1; n <= 24; n++)
	{
		myfile.open("fixed-volume-plane-partition-semi-corner-hook-volume/n=" + to_string(n) + "ch-volumes.csv");		

		SolidPartitionGenerator	gen(1, n, n, n);
		auto A = gen.getNext();
		int cnt = 0;
		vector < int > c(n + 1);
		while(!A.empty())
		{	
			//mat3dprint(A);
			//myfile << corner_hook_volume(A) << "\n";
			c[ch2(A)]++;
			assert(corner_hook_volume(A) == ch1(A) + ch2(A) + ch3(A) - 2 * ch_count(A));
			A = gen.getNext();
			cnt++;

		}
		for (int i = 0; i < (int)c.size(); i++)
			myfile << i << ' ' << c[i] << '\n';
		cout << cnt <<endl;
		myfile.close();
	}
	return 0;
}