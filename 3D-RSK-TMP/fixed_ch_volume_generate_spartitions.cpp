#include <bits/stdc++.h>
using namespace std;

#define ll long long
typedef vector<vector< vector < int > > > mat3d;


mat3d box(int n, int m, int k)
{
	return vector < vector < vector < int > > > (n, vector < vector < int > > (m, vector < int > (k)));
}

void print(const mat3d & p)
{
	cout << "* --------------------------------- *" << endl;
	int x_len = p.size();
	int y_len = p[0].size();
	int z_len = p[0][0].size();
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{
			for (int k = 0; k < z_len; k++)
			{
				cout << p[i][j][k] << ' ';
			}
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;
	cout << "* --------------------------------- *" << endl;
}

vector < int > cnt;
mat3d transfer_map(const mat3d & A)
{
	mat3d p = A;
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();
	int volume = 0;
	for (int i = x_len - 1; i >= 0; i--)
	{
		for (int j = y_len - 1; j >= 0; j--)
		{
			for (int k = z_len - 1; k >= 0; k--)
			{
				if (i < x_len - 1)
					p[i][j][k] = max(p[i][j][k], p[i + 1][j][k] + A[i][j][k]);
				if (j < y_len - 1)
					p[i][j][k] = max(p[i][j][k], p[i][j + 1][k] + A[i][j][k]);
				if (k < z_len - 1)
					p[i][j][k] = max(p[i][j][k], p[i][j][k + 1] + A[i][j][k]);	
				volume += p[i][j][k];
			}
		}
	}
	//print(p);
	//cerr << volume << endl;
	cnt[volume]++;
	return p;
}

int total;
void rec(int id, int n, const vector < vector < int > > & ord, mat3d & A)
{
	if (id == (int)ord.size() - 1)
	{
		A[0][0][0] = n;
		transfer_map(A);
		total++;
		return;
	}
	int i = ord[id][0];
	int j = ord[id][1];
	int k = ord[id][2];
	for (int val = 0; val * (i + j + k + 1) <= n; val++)
	{
		A[i][j][k] = val;
		rec(id + 1, n - val * (i + j + k + 1), ord, A);
		A[i][j][k] = 0;
	}
}

void gen(int n)
{
	mat3d A = box(n, n, n);
	vector < vector < int > > ord;
	for (int l = n; l >= 1; l--)
	{	
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; i + j + 1 <= l; j++)
			{				
				int k = l - i - j - 1;
				ord.push_back({i, j, k});
			} 
		}
	}
	rec(0, n, ord, A);	
}

int main() 
{
	ofstream myfile;
	for (int n = 20; n <= 23; n++)
	{
		total = 0;
		myfile.open("fixed-CH-volume-Solid-Partitions/ch-volume=" + to_string(n) + "volumes.csv");
		cnt = vector < int > (10000);
		gen(n);
		while(!cnt.empty() && cnt.back() == 0)
			cnt.pop_back();
		for (int i = 0; i < (int)cnt.size(); i++)
			myfile << i << "," << cnt[i] << "\n";
		myfile.close();
		cerr << total << endl;
	}
	return 0;

}            