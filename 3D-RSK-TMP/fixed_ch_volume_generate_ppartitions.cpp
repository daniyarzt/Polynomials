#include <bits/stdc++.h>

using namespace std;

#define ll lonng long 
#define f first
#define s second

pair < int, int > next_pos(int x, int y)
{
	if (y > 0)
		return {x + 1, y - 1};
	return {0, x - 1};
		
}


ofstream myfile;
vector < int > cnt;
int total = 0;
void transfer(vector < vector < int > > a)
{
	vector < vector < int > > p = a;
	for (int i = (int)a.size() - 1; i >= 0; i--)
	{
		for (int j = (int)a[i].size() - 1; j >= 0; j--)
		{
        	if (i < (int)a.size() - 1)
        	{
        		p[i][j] = max(p[i][j], a[i][j] + p[i + 1][j]);
			}
			if (j < (int)a[i].size() - 1)
			{
				p[i][j] = max(p[i][j], a[i][j] + p[i][j + 1]);
			}
		}
	}
	int sum = 0;
	for (int i = 0; i < (int)p.size(); i++)
	{
		for (int j = 0; j < (int)p[i].size(); j++)
		{
		//	cerr << p[i][j] << ' ';
			sum += p[i][j];
		}
		//cerr << endl;
	}
	//cerr << endl;
	
	cnt[sum]++;
}

vector < vector < int > > cur;
void rec(int x, int y, int s)
{	
	if (x == 0 && y == 0)
	{
		cur[x][y] = s;
		transfer(cur);
		total++;
		return;
	}
	for (int i = 0; i * (x + y + 1) <= s; i++)
	{
		cur[x][y] = i;
		rec(next_pos(x, y).f, next_pos(x, y).s, s - i * (x + y + 1));
		cur[x][y] = 0;
	}
}


int main()
{
	for (int n = 25; n <= 27; n++)
	{
		total = 0;
		myfile.open("fixed-CH-volume-Plane-Partitions/ch-volume=" + to_string(n) + "volumes.csv");
		cur = vector < vector < int > > (n, vector < int > (n));
		cnt = vector < int > (10000);
		rec(0, n - 1, n);
		while(!cnt.empty() && cnt.back() == 0)
			cnt.pop_back();
		for (int i = 0; i < (int)cnt.size(); i++)
			myfile << i << "," << cnt[i] << "\n";
		myfile.close();
		cerr << total << endl;
	}
	return 0;
}