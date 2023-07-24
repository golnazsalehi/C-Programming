#include "Black_win_check.h"
int Black_win_check(char GB[6][6])
{
	int ans = 0;
	//horizontal
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (GB[i][j] == 'b' && GB[i][j + 1] == 'b' && GB[i][j + 2] == 'b'
				&& GB[i][j + 3] == 'b')
			{
				if (i == 0)
				{
					if (GB[1][j] == 'b' || GB[1][j + 3] == 'b')
					{
						ans = 1;
					}
				}
				else if (i == 5)
				{
					if (GB[4][j] == 'b' || GB[4][j + 3] == 'b')
					{
						ans = 1;
					}
				}
				else
				{
					if (GB[i - 1][j] == 'b' || GB[i + 1][j] == 'b'
						|| GB[i - 1][j + 3] == 'b' || GB[i + 1][j - 3] == 'b')
					{
						ans = 1;
					}
				}
			}
		}
	}
	//vertical
	for (int k = 0; k < 6; k++)
	{
		for (int t = 0; t < 3; t++)
		{
			if (GB[t][k] == 'b' && GB[t + 1][k] == 'b' && GB[t + 2][k] == 'b'
				&& GB[t + 3][k] == 'b')
			{
				if (k == 0)
				{
					if (GB[t][1] == 'b' || GB[t + 3][1] == 'b')
					{
						ans = 1;
					}
				}
				if (k == 5)
				{
					if (GB[t][4] == 'b' || GB[t + 3][4] == 'b')
					{
						ans = 1;
					}
				}
				else
				{
					if (GB[t][k - 1] == 'b' || GB[t + 3][k - 1] == 'b'
						|| GB[t][k + 1] == 'b' || GB[t + 3][k + 1] == 'b')
					{
						ans = 1;
					}
				}
			}
		}
	}
	//Diagonal(sub diameter)
	for (int z = 3; z < 6; z++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (GB[z][y] == 'b' && GB[z - 1][y + 1] == 'b'
				&& GB[z - 2][y + 2] == 'b' && GB[z - 3][y + 3] == 'b')
			{
				if (z == 3 && y == 0)
				{
					if (GB[4][1] == 'b' || GB[1][4] == 'b')
					{
						ans = 1;
					}
				}
				else if (z == 3 && y == 1)
				{
					if (GB[1][5] == 'b' || GB[4][2] == 'b' || GB[2][0] == 'b')
					{
						ans = 1;
					}
				}
				else if (z == 3 && y == 2)
				{
					if (GB[4][3] == 'b' || GB[2][1] == 'b')
					{
						ans = 1;
					}
				}
				else if (z == 4 && y == 0)
				{
					if (GB[5][1] == 'b' || GB[0][2] == 'b' || GB[2][4] == 'b')
					{
						ans = 1;
					}
				}
				else if (z == 4 && y == 1)
				{
					if (GB[0][3] == 'b' || GB[2][5] == 'b' || GB[3][0] == 'b'
						|| GB[5][2] == 'b')
					{
						ans = 1;
					}
				}
				else if (z == 4 && y == 2)
				{
					if (GB[0][4] == 'b' || GB[5][3] == 'b' || GB[3][1] == 'b')
					{
						ans = 1;
					}
				}
				else if (z == 5 && y == 0)
				{
					if (GB[1][2] == 'b' || GB[3][4] == 'b')
					{
						ans = 1;
					}
				}
				else if (z == 5 && y == 1)
				{
					if (GB[4][0] == 'b' || GB[1][3] == 'b' || GB[3][5] == 'b')
					{
						ans = 1;
					}
				}
				else
				{
					if (GB[4][1] == 'b' || GB[1][4] == 'b')
					{
						ans = 1;
					}
				}
			}
		}
	}
	//Diagonal(main diameter)
	for (int v = 3; v < 6; v++)
	{
		for (int p = 5; p > 2; p--)
		{
			if (GB[v][p] == 'b' && GB[v - 1][p - 1] == 'b'
				&& GB[v - 2][p - 2] == 'b' && GB[v - 3][p - 3] == 'b')
			{
				if (v == 3 && p == 5)
				{
					if (GB[4][4] == 'b' || GB[1][1] == 'b')
					{
						ans = 1;
					}
				}
				else if (v == 3 && p == 4)
				{
					if (GB[2][5] == 'b' || GB[4][3] == 'b' || GB[1][0] == 'b')
					{
						ans = 1;
					}
				}
				else if (v == 3 && p == 3)
				{
					if (GB[2][4] == 'b' || GB[4][2] == 'b')
					{
						ans = 1;
					}
				}
				else if (v == 4 && p == 5)
				{
					if (GB[5][4] == 'b' || GB[0][3] == 'b' || GB[2][1] == 'b')
					{
						ans = 1;
					}
				}
				else if (v == 4 && p == 4)
				{
					if (GB[5][3] == 'b' || GB[3][5] == 'b' || GB[0][2] == 'b'
						|| GB[2][0] == 'b')
					{
						ans = 1;
					}
				}
				else if (v == 4 && p == 3)
				{
					if (GB[3][4] == 'b' || GB[5][2] == 'b' || GB[0][1] == 'b')
					{
						ans = 1;
					}
				}
				else if (v == 5 && p == 5)
				{
					if (GB[3][1] == 'b' || GB[1][3] == 'b')
					{
						ans = 1;
					}
				}
				else if (v == 5 && p == 4)
				{
					if (GB[4][5] == 'b' || GB[3][0] == 'b' || GB[1][2] == 'b')
					{
						ans = 1;
					}
				}
				else
				{
					if (GB[4][4] == 'b' || GB[1][1] == 'b')
					{
						ans = 1;
					}
				}
			}
		}
	}
	return ans;
}