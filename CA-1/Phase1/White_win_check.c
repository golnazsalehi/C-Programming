#include "White_win_check.h"
int White_win_check(char GB[6][6])
{
	int temp = 0;
	//horizontal
	for (int a = 0; a < 6; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			if (GB[a][b] == 'w' && GB[a][b + 1] == 'w' && GB[a][b + 2] == 'w'
				&& GB[a][b + 3] == 'w')
			{
				if (a == 0)
				{
					if (GB[1][b] == 'w' || GB[1][b + 3] == 'w')
					{
						temp = 1;
					}
				}
				else if (a == 5)
				{
					if (GB[4][b] == 'w' || GB[4][b + 3] == 'w')
					{
						temp = 1;
					}
				}
				else
				{
					if (GB[a - 1][b] == 'w' || GB[a + 1][b] == 'w'
						|| GB[a - 1][b + 3] == 'w' || GB[a + 1][b - 3] == 'w')
					{
						temp = 1;
					}
				}
			}
		}
	}
	//vertical
	for (int c = 0; c < 6; c++)
	{
		for (int d = 0; d < 3; d++)
		{
			if (GB[d][c] == 'w' && GB[d + 1][c] == 'w' && GB[d + 2][c] == 'w'
				&& GB[d + 3][c] == 'w')
			{
				if (c == 0)
				{
					if (GB[d][1] == 'w' || GB[d + 3][1] == 'w')
					{
						temp = 1;
					}
				}
				if (c == 5)
				{
					if (GB[d][4] == 'w' || GB[d + 3][4] == 'w')
					{
						temp = 1;
					}
				}
				else
				{
					if (GB[d][c - 1] == 'w' || GB[d + 3][c - 1] == 'w'
						|| GB[d][c + 1] == 'w' || GB[d + 3][c + 1] == 'w')
					{
						temp = 1;
					}
				}
			}
		}
	}
	//Diagonal(sub diameter)
	for (int e = 3; e < 6; e++)
	{
		for (int f = 0; f < 3; f++)
		{
			if (GB[e][f] == 'w' && GB[e - 1][f + 1] == 'w'
				&& GB[e - 2][f + 2] == 'w' && GB[e - 3][f + 3] == 'w')
			{
				if (e == 3 && f == 0)
				{
					if (GB[4][1] == 'w' || GB[1][4] == 'w')
					{
						temp = 1;
					}
				}
				else if (e == 3 && f == 1)
				{
					if (GB[1][5] == 'w' || GB[4][2] == 'w' || GB[2][0] == 'w')
					{
						temp = 1;
					}
				}
				else if (e == 3 && f == 2)
				{
					if (GB[4][3] == 'w' || GB[2][1] == 'w')
					{
						temp = 1;
					}
				}
				else if (e == 4 && f == 0)
				{
					if (GB[5][1] == 'w' || GB[0][2] == 'w' || GB[2][4] == 'w')
					{
						temp = 1;
					}
				}
				else if (e == 4 && f == 1)
				{
					if (GB[0][3] == 'w' || GB[2][5] == 'w' || GB[3][0] == 'w'
						|| GB[5][2] == 'w')
					{
						temp = 1;
					}
				}
				else if (e == 4 && f == 2)
				{
					if (GB[0][4] == 'w' || GB[5][3] == 'w' || GB[3][1] == 'w')
					{
						temp = 1;
					}
				}
				else if (e == 5 && f == 0)
				{
					if (GB[1][2] == 'w' || GB[3][4] == 'w')
					{
						temp = 1;
					}
				}
				else if (e == 5 && f == 1)
				{
					if (GB[4][0] == 'w' || GB[1][3] == 'w' || GB[3][5] == 'w')
					{
						temp = 1;
					}
				}
				else
				{
					if (GB[4][1] == 'w' || GB[1][4] == 'w')
					{
						temp = 1;
					}
				}
			}
		}
	}
	//Diagonal(main diameter)
	for (int s = 3; s < 6; s++)
	{
		for (int u = 5; u > 2; u--)
		{
			if (GB[s][u] == 'w' && GB[s - 1][u - 1] == 'w'
				&& GB[s - 2][u - 2] == 'w' && GB[s - 3][u - 3] == 'w')
			{
				if (s == 3 && u == 5)
				{
					if (GB[4][4] == 'w' || GB[1][1] == 'w')
					{
						temp = 1;
					}
				}
				else if (s == 3 && u == 4)
				{
					if (GB[2][5] == 'w' || GB[4][3] == 'w' || GB[1][0] == 'w')
					{
						temp = 1;
					}
				}
				else if (s == 3 && u == 3)
				{
					if (GB[2][4] == 'w' || GB[4][2] == 'w')
					{
						temp = 1;
					}
				}
				else if (s == 4 && u == 5)
				{
					if (GB[5][4] == 'w' || GB[0][3] == 'w' || GB[2][1] == 'w')
					{
						temp = 1;
					}
				}
				else if (s == 4 && u == 4)
				{
					if (GB[5][3] == 'w' || GB[3][5] == 'w' || GB[0][2] == 'w'
						|| GB[2][0] == 'w')
					{
						temp = 1;
					}
				}
				else if (s == 4 && u == 3)
				{
					if (GB[3][4] == 'w' || GB[5][2] == 'w' || GB[0][1] == 'w')
					{
						temp = 1;
					}
				}
				else if (s == 5 && u == 5)
				{
					if (GB[3][1] == 'w' || GB[1][3] == 'w')
					{
						temp = 1;
					}
				}
				else if (s == 5 && u == 4)
				{
					if (GB[4][5] == 'w' || GB[3][0] == 'w' || GB[1][2] == 'w')
					{
						temp = 1;
					}
				}
				else
				{
					if (GB[4][4] == 'w' || GB[1][1] == 'w')
					{
						temp = 1;
					}
				}
			}
		}
	}
	return temp;
}