void jdt(int x, int y, vector < vector < int > > & a, vector < vector < int > > & b)
{
	int down = -1;
	int right = -1;
	if (x + 1 < (int)a.size() && y < (int)a[x + 1].size())
		down = a[x + 1][y];
	if (y + 1 < (int)a[x].size())
		right = a[x][y + 1];
	if (down == -1 && right == -1)
	{	
		b[x][y] = 1;
		return;
	}
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

pair < vector < vector < int > >, vector < vector < int > > > shrink_transformation(vector < vector < int > > a)
{
	vector < vector < int > > b = a;
	for (int i = 0; i < (int)b.size(); i++)
	{
		for (int j = 0; j < (int)b[i].size(); j++)
			b[i][j] = -1;
	}
	for (int i = (int)a.size() - 1; i >= 0; i--)
	{
		for (int j = (int)a[i].size() - 1; j >= 0; j--)
		{	
			if (a[i][j] == -1)
			{
				for (int i = 0; i < (int)b.size(); i++)
				{
					for (int j = 0; j < (int)b[i].size(); j++)
						if (b[i][j] != -1)
							b[i][j]++;
				}
				jdt(i, j, a, b);
			}
		}
	}
	return make_pair(a, b);
}

