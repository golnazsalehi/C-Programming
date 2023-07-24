#include "Turn.h"
void Turn(char GB[6][6], char gb[6][6])
{
	int Area;
	char direction;
	while (1)
	{
		printf("please inter an area\n");
		if (scanf("%d", &Area))
		{
			if (Area == 1 || Area == 2 || Area == 3 || Area == 4)
			{
				printf("please inter a direction\n");
				if (scanf(" %c", &direction))
				{
					if ((direction == '+' || direction == '-'))
					{
						if (Area == 1 && direction == '+')
						{
							GB[0][5] = gb[0][3];
							GB[1][5] = gb[0][4];
							GB[2][5] = gb[0][5];
							GB[0][4] = gb[1][3];
							GB[1][4] = gb[1][4];
							GB[2][4] = gb[1][5];
							GB[0][3] = gb[2][3];
							GB[1][3] = gb[2][4];
							GB[2][3] = gb[2][5];

						}
						else if (Area == 1 && direction == '-')
						{
							GB[2][3] = gb[0][3];
							GB[1][3] = gb[0][4];
							GB[0][3] = gb[0][5];
							GB[2][4] = gb[1][3];
							GB[1][4] = gb[1][4];
							GB[0][4] = gb[1][5];
							GB[2][5] = gb[2][3];
							GB[1][5] = gb[2][4];
							GB[0][5] = gb[2][5];
						}
						else if (Area == 2 && direction == '+')
						{
							GB[0][2] = gb[0][0];
							GB[1][2] = gb[0][1];
							GB[2][2] = gb[0][2];
							GB[0][1] = gb[1][0];
							GB[1][1] = gb[1][1];
							GB[2][1] = gb[1][2];
							GB[0][0] = gb[2][0];
							GB[1][0] = gb[2][1];
							GB[2][0] = gb[2][2];

						}
						else if (Area == 2 && direction == '-')
						{
							GB[0][0] = gb[0][2];
							GB[0][1] = gb[1][2];
							GB[0][2] = gb[2][2];
							GB[1][0] = gb[0][1];
							GB[1][1] = gb[1][1];
							GB[1][2] = gb[2][1];
							GB[2][0] = gb[0][0];
							GB[2][1] = gb[1][0];
							GB[2][2] = gb[2][0];
						}
						else if (Area == 3 && direction == '+')
						{
							GB[3][0] = gb[5][0];
							GB[3][1] = gb[4][0];
							GB[3][2] = gb[3][0];
							GB[4][0] = gb[5][1];
							GB[4][1] = gb[4][1];
							GB[4][2] = gb[3][1];
							GB[5][0] = gb[5][2];
							GB[5][1] = gb[4][2];
							GB[5][2] = gb[3][2];
						}
						else if (Area == 3 && direction == '-')
						{
							GB[3][0] = gb[3][2];
							GB[3][1] = gb[4][2];
							GB[3][2] = gb[5][2];
							GB[4][0] = gb[3][1];
							GB[4][1] = gb[4][1];
							GB[4][2] = gb[5][1];
							GB[5][0] = gb[3][0];
							GB[5][1] = gb[4][0];
							GB[5][2] = gb[5][0];
						}
						else if (Area == 4 && direction == '+')
						{
							GB[3][5] = gb[3][3];
							GB[4][5] = gb[3][4];
							GB[5][5] = gb[3][5];
							GB[3][4] = gb[4][3];
							GB[4][4] = gb[4][4];
							GB[5][4] = gb[4][5];
							GB[3][3] = gb[5][3];
							GB[4][3] = gb[5][4];
							GB[5][3] = gb[5][5];
						}
						else if (Area == 4 && direction == '-')
						{
							GB[3][5] = gb[5][5];
							GB[4][5] = gb[5][4];
							GB[5][5] = gb[5][3];
							GB[3][4] = gb[4][5];
							GB[4][4] = gb[4][4];
							GB[5][4] = gb[4][3];
							GB[3][3] = gb[3][5];
							GB[4][3] = gb[3][4];
							GB[5][3] = gb[3][3];
						}
						break;
					}
					else {
						printf("invalid input,please try again\n");
						getchar();
						continue;
					}
				}
				else {
					printf("invalid input,please try again\n");
					getchar();
					continue;
				}
			}

			else {
				printf("invalid input,please try again\n");
				getchar();
				continue;
			}

		}

		else
		{
			printf("invalid input,please try again\n");
			getchar();
			continue;
		}


	}
}