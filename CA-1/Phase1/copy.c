#include "copy.h"
void copy(char GB[6][6], char gb[6][6])
{

	for (int cop = 0; cop < 6; cop++)
	{
		for (int cop2 = 0; cop2 < 6; cop2++)
		{
			gb[cop][cop2] = GB[cop][cop2];
		}
	}
}