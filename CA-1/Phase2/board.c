#include "graphics.h"
#include "board.h"
void board(char GB[600][600])
{
	setcolor(15);
	line(300, 0, 300, 600);
	line(0, 300, 600, 300);
	int row, column;
	for (row = 50; row < 600; row += 100) {
		for (column = 50; column < 600; column += 100) {
			if (GB[row][column] == '.') {
				setcolor(15);
				setfillstyle(1, 1);
				fillellipse(row, column, 20, 20);
			}
			else if (GB[row][column] == 'b') {
				setfillstyle(1, 0);
				fillellipse(row, column, 20, 20);
			}
			else {
				setfillstyle(1, 15);
				fillellipse(row, column, 20, 20);
			}
		}
	}
}