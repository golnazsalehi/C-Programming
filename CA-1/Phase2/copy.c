#include "copy.h"
void copy(char GB[600][600], char gb[600][600])
{
	for (int cop = 50; cop < 600; cop += 100)
	{
		for (int cop2 = 50; cop2 < 600; cop2 += 100)
		{
			gb[cop][cop2] = GB[cop][cop2];
		}
	}
}