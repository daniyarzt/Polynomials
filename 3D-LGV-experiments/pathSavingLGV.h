#define PathRow vector < vector < Path > > 
#define PathMatrix vector < vector < vector < Path > > > 


/* *** INSTRUCTIONS *** 
	1. set WONNASAVEPATH = true in 3D-LGV.h
	2. TreeDimLGV has two-dimensional matrix D of vector < Path >  (vector < vector < vector < Path > > >).
	3. Calculate TreeDimLGV().LGV() as before, and D will be automatically filled
	4. Then you can use PathSavingLGV().det(D) to calculate the needed vector < NPath > 

	see examples in "checkPathSavingLGV.cpp"
	
	no need to include anything, everything is already included in "3D-LGV.h"
*/

/*  *** struct PathSavingLGV *** 
	Is Used to calculate Lindstrom-Gessel-Vienot Lemma with saving each path in the lattice

	mult(vector < NPath > a, vector < Path > b, int start, int finish) - does the same thing as polynomial multiplication, 
									but now with saving paths (a * b)
	
	add (vector < NPath > a, vector < NPath > b) - same as polynomial addition 

	det(D) - does the same thing as the polynomial det, but also saves paths
	
*/


struct PathSavingLGV
{
	// mult(,,,) - does the same thing as polynomial multiplication, but now with saving paths
	vector < NPath > mult(vector < NPath > vec, vector < Path > vpath, int start, int finish) 
	{
		vector < NPath > newvec;
		for (auto p : vpath)
		{
			for (auto it : vec)
			{
				it.addPath(start, finish, p);
				newvec.pb(it);
			}
		}
		return newvec;
	}

	// same as polynomial addition 
	vector < NPath > add(vector < NPath > a, vector < NPath > b)
	{
		for (auto it : b)
			a.pb(it);
		return a;
	}

	// det(D) - does the same thing as the polynomial det, but saves paths
	vector < NPath > det(vector < vector < vector < Path > > > D) 
	{
		int n = (int)D.size();
		
		vector < int > p(n);
		for (int i = 0; i < n; i++)
			p[i] = i;	

		vector < NPath > res;
			
		do
		{
			vector < NPath > cur(1, p);
			for (int i = 0; i < n; i++)
			{
				//D[i][p[i]]: i -> p[i]
				cur = mult(cur, D[i][p[i]], i, p[i]);		
			}	
			res = add(res, cur);			
		}
		while(next_permutation(all(p)));

		return res;
	}

};

