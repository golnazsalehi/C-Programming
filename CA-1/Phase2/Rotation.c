#include "graphics.h"
#include "Rotation.h"
int Rotation(char GB[600][600], char gb[600][600]) {
	int district1, district2;
	int c;
	district1 = 300;
	district2 = 0;
	setcolor(14);
	rectangle(300, 0, 600, 300);
	while (1)
	{
		int chari;
		chari = getch();
		if (chari == 83 || chari == 115) {
			//S
			if (district2 == 300) {
				setcolor(14);
				rectangle(district1, district2, district1 + 300, district2 + 300);

			}
			else {
				setcolor(1);
				rectangle(district1, district2, district1 + 300, district2 + 300);
				setcolor(14);
				district2 += 300;
				rectangle(district1, district2, district1 + 300, district2 + 300);

			}
		}
		else if (chari == 68 || chari == 100) {
			//D
			if (district1 == 300) {
				setcolor(14);
				rectangle(district1, district2, district1 + 300, district2 + 300);
			}
			else {
				setcolor(1);
				rectangle(district1, district2, district1 + 300, district2 + 300);
				setcolor(14);
				district1 += 300;
				rectangle(district1, district2, district1 + 300, district2 + 300);
			}
		}
		else if (chari == 87 || chari == 119) {
			//W
			if (district2 == 0) {
				setcolor(14);
				rectangle(district1, district2, district1 + 300, district2 + 300);
			}
			else {
				setcolor(1);
				rectangle(district1, district2, district1 + 300, district2 + 300);
				setcolor(14);
				district2 -= 300;
				rectangle(district1, district2, district1 + 300, district2 + 300);
			}
		}
		else if (chari == 65 || chari == 97) {
			//A
			if (district1 == 0) {
				setcolor(14);
				rectangle(district1, district2, district1 + 300, district2 + 300);
			}
			else {
				setcolor(1);
				rectangle(district1, district2, district1 + 300, district2 + 300);
				setcolor(14);
				district1 -= 300;
				rectangle(district1, district2, district1 + 300, district2 + 300);
			}
		}
		else if (chari == 70 || chari == 102) {
			//F
			while (1) {
				setcolor(0);
				outtextxy(0, 700, "your opponent has chosen this before\n");
				setcolor(14);
				outtextxy(0, 700, "choose a direction\n");
				char direction;
				direction = getch();
				if (direction == '+') {
					if (district1 == 0 && district2 == 0) {
						GB[250][50] = gb[50][50];
						GB[250][150] = gb[150][50];
						GB[250][250] = gb[250][50];
						GB[150][50] = gb[50][150];
						GB[150][150] = gb[150][150];
						GB[150][250] = gb[250][150];
						GB[50][50] = gb[50][250];
						GB[50][150] = gb[150][250];
						GB[50][250] = gb[250][250];
					}
					else if (district1 == 300 && district2 == 0) {
						GB[550][50] = gb[350][50];
						GB[550][150] = gb[450][50];
						GB[550][250] = gb[550][50];
						GB[450][50] = gb[350][150];
						GB[450][150] = gb[450][150];
						GB[450][250] = gb[550][150];
						GB[350][50] = gb[350][250];
						GB[350][150] = gb[450][250];
						GB[350][250] = gb[550][250];
					}
					else if (district1 == 0 && district2 == 300) {
						GB[50][350] = gb[50][550];
						GB[150][350] = gb[50][450];
						GB[250][350] = gb[50][350];
						GB[50][450] = gb[150][550];
						GB[150][450] = gb[150][450];
						GB[250][450] = gb[150][350];
						GB[50][550] = gb[250][550];
						GB[150][550] = gb[250][450];
						GB[250][550] = gb[250][350];
					}
					else {
						GB[550][350] = gb[350][350];
						GB[550][450] = gb[450][350];
						GB[550][550] = gb[550][350];
						GB[450][350] = gb[350][450];
						GB[450][550] = gb[550][450];
						GB[350][350] = gb[350][550];
						GB[350][450] = gb[450][550];
						GB[350][550] = gb[550][550];
					}
				}
				else if (direction == '-') {
					if (district1 == 0 && district2 == 0) {
						GB[50][50] = gb[250][50];
						GB[150][50] = gb[250][150];
						GB[250][50] = gb[250][250];
						GB[50][150] = gb[150][50];
						GB[250][150] = gb[150][250];
						GB[50][250] = gb[50][50];
						GB[150][250] = gb[50][150];
						GB[250][250] = gb[50][250];
					}
					else if (district1 == 300 && district2 == 0) {
						GB[350][250] = gb[350][50];
						GB[350][150] = gb[450][50];
						GB[350][50] = gb[550][50];
						GB[450][250] = gb[350][150];
						GB[450][50] = gb[550][150];
						GB[550][250] = gb[350][250];
						GB[550][150] = gb[450][250];
						GB[550][50] = gb[550][250];
					}
					else if (district1 == 0 && district2 == 300) {
						GB[50][350] = gb[250][350];
						GB[150][350] = gb[250][450];
						GB[250][350] = gb[250][550];
						GB[50][450] = gb[150][350];
						GB[250][450] = gb[150][550];
						GB[50][550] = gb[50][350];
						GB[150][550] = gb[50][450];
						GB[250][550] = gb[50][550];
					}
					else {
						GB[550][350] = gb[550][550];
						GB[550][450] = gb[450][550];
						GB[550][550] = gb[350][550];
						GB[450][350] = gb[550][450];
						GB[450][550] = gb[350][450];
						GB[350][350] = gb[550][350];
						GB[350][450] = gb[450][350];
						GB[350][550] = gb[350][350];
					}

				}
				else {
					outtextxy(0, 700, "invalide input\n");
					continue;
				}
				setcolor(0);
				outtextxy(0, 700, "your opponent has chosen this before");
				setcolor(1);
				rectangle(district1, district2, district1 + 300, district2 + 300);
				return 0;
			}
		}
	}
}
