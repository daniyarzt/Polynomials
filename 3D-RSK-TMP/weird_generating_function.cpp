#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n = 10;
	map < int, int > cnt;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= n; k++)
				cnt[i * j + j * k + i * k - i - j - k + 1]++;
	for (auto it : cnt)
		cout << it.first << ' ' << it.second << endl;
	

	return 0;
}