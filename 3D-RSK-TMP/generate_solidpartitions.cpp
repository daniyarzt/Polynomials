#include <bits/stdc++.h>
#include "spartition_generator.h"


using namespace std;


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

ll semi_corner_hook_volume(mat3d A)
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

bool isColumnDecreasing(mat3d A)
{
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len - 1; j++)
		{
			for (int k = 0; k < z_len; k++)
			{
				if (A[i][j][k] > 0 && A[i][j][k] == A[i][j + 1][k])
					return false;
			}
		}
	}
	return true;

}

bool isRowDecreasing(mat3d A)
{
	int x_len = A.size();
	int y_len = A[0].size();
	int z_len = A[0][0].size();
	for (int i = 0; i < x_len; i++)
	{
		for (int j = 0; j < y_len; j++)
		{
			for (int k = 0; k < z_len - 1; k++)
			{
				if (A[i][j][k] > 0 && A[i][j][k] == A[i][j][k + 1])
					return false;
			}
		}
	}
	return true;

}



int main() 
{
	/*for (int n = 1; n <= 25; n++)
	{
		SolidPartitionGenerator gen(1, n, n, n);
		auto A = gen.getNext();
		
		int cntColumnDecreasing = 0;
		while(!A.empty())
		{
			cntColumnDecreasing += (isColumnDecreasing(A) & isRowDecreasing(A));
			A = gen.getNext();	
		}
		cout << cntColumnDecreasing << endl;
	}*/
	/*mat3d A = vector < vector < vector < ll > > > (4, vector < vector < ll > > (1, vector < ll > (1)));
	A[0][0][0] = 4;
	A[1][0][0] = 3;
	A[2][0][0] = 2;
	A[3][0][0] = 1;
	mat3dprint(A);
	cout << semi_corner_hook_volume(A) << endl;

	return 0;*/

	ofstream myfile;
	for (int n = 1; n <= 25; n++)
	{
		myfile.open("fixed-volume-plane-partition-semi-corner-hook-volume/n=" + to_string(n) + "ch-volumes.csv");		

		SolidPartitionGenerator	gen(1, n, n, n);
		auto A = gen.getNext();
		int cnt = 0;
		
		vector < int > cnt_ch(3 * n + 1);

		while(!A.empty())
		{	
			//mat3dprint(A);
			//myfile << corner_hook_volume(A) << "\n";
			//if (isColumnDecreasing(A))
			//{
				if (semi_corner_hook_volume(A) == n)	
				{
					cnt++;
					//mat3dprint(A);
				}
				cnt_ch[semi_corner_hook_volume(A)]++;
			//}
			A = gen.getNext();

		}                   
		for (int i = 1; i < (int)cnt_ch.size(); i++)
			myfile << i << "," << cnt_ch[i] << "\n";	
		cout << cnt <<endl;
		myfile.close();
	}  
	return 0;
}                                                               	