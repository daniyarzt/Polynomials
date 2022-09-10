
using namespace std;

typedef long long ll;
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
