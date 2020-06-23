#include "bits/stdc++.h"
#include "all.h"

using namespace std;

void test1()
{
	int n = 2;
	PathMatrix D(n, PathRow(n));
	
	// A: (0, 0, 0), (0, 0, 1)
	// B: (0, 1, 0), (0, 1, 1)

	// 0 -> 0
	Path curPath(0, 0, 0);
	curPath.addEdge({0, 1, 0}, 1);
	D[0][0].pb(curPath);

	// 0 -> 1
	curPath = Path(0, 0, 0);
	curPath.addEdge({0, 1, 1}, 2);
	D[0][1].pb(curPath);

	// 1 -> 0
	curPath = Path(0, 0, 1);
	curPath.addEdge({0, 1, -1}, 3);
	D[1][0].pb(curPath);

	// 1 -> 1
	curPath = Path(0, 0, 1);
	curPath.addEdge({0, 1, 0}, 4);
	D[1][1].pb(curPath);

	for (int i = 0; i < n; i++, cerr << endl)
		for (int j = 0; j < n; j++)
			D[i][j][0].getWeight().print();
	vector < NPath > res = PathSavingLGV().det(D);
  
    cerr << "I was here" << endl;
    for (auto it : res)
    {
    	it.print();
    	it.weight.print();
    	cout << endl;
    }
}

void test2()
{
	TreeDimLGV T;
	T.addSource(0, 0, 0);
	T.addSource(0, 1, 0);

	T.addSink(1, 0, 0);
	T.addSink(1, 1, 0);

	T.addEdge(1, 0, 0, WALL, true, 1);
	T.addEdge(1, 1, 0, WALL, true, 10);
	T.addEdge(1, -1, 0, WALL, true, 20);

	T.LGV();

	vector < NPath > res = PathSavingLGV().det(T.D);

	for (auto it : res)
    {
    	it.print();
    	it.weight.print();
    	cout << endl;
    }
}
     
int main() 
{
	test2();
	 
	
	return 0;
}
