
void jdt(int x, int y, vector < vector < int > > & a)
{
	int down = -1;
	int right = -1;
	if (x + 1 < (int)a.size() && y < (int)a[x + 1].size())
		down = a[x + 1][y];
	if (y + 1 < (int)a[x].size())
		right = a[x][y + 1];
	if (down == -1 && right == -1)
		return;
	if (down == -1)
	{
		swap(a[x][y], a[x][y + 1]);
		jdt(x, y + 1, a);
		return;
	}
	if (right == -1)
	{
		swap(a[x][y], a[x + 1][y]);
		jdt(x + 1, y, a);
		return;
	}
	if (down <= right)
	{
		swap(a[x][y], a[x + 1][y]);
		jdt(x + 1, y, a);
	}
	else
	{	
		swap(a[x][y], a[x][y + 1]);
		jdt(x, y + 1, a);	
	}
}

void shrink(vector < vector < int > > & a)
{
	for (int i = (int)a.size() - 1; i >= 0; i--)
	{
		for (int j = (int)a[i].size() - 1; j >= 0; j--)
		{	
			if (a[i][j] == -1)
				jdt(i, j, a);
		}
	}
}

void print(const vector < vector < int > > & a)
{
	for (int i = 0; i < (int)a.size(); i++)
	{
		for (int j = 0; j < (int)a[i].size(); j++)
		{
			if (a[i][j] == -1)
				cout << ' ';
			else
				cout << a[i][j];
		}
		cout << endl;
	} 
}

void normalize(vector < vector < int > > & a)
{
	for (int i = 0; i < (int)a.size(); i++)
	{	
		while(!a[i].empty() && a[i].back() == -1)
			a[i].pop_back();
	}
}

void reduce(vector < vector < int > > & a)
{
	for (int i = 0; i < (int)a.size() - 1; i++)
		for (int j = 0; j < (int)a[i + 1].size(); j++)
			if (a[i][j] == a[i + 1][j])
				a[i][j] = -1;
}

