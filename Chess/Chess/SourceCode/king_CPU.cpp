#include "Headers/cpu.h"


int king(int x1, int y1)
{
	int x2, y2;
	const int options = 8;
	static int flag_local = 0;
	COORD steps[options] = { { 0, -1 }, { 1, -1 }, { -1, -1 }, { 1, 0 }, { -1, 0 }, { 1, 1 }, { -1, 1 }, { 0, 1 } };

	while (true){
		for (int i = 0; i < options; i++){
			if (DOSKA[y1 + steps[i].Y][x1 + steps[i].X] != 0 && y1 + steps[i].Y >= 0 && x1 + steps[i].X >= 0 && y1 + steps[i].Y <= 7 && x1 + steps[i].X <= 7){
				for (int j = 0; j < 6; j++){
					if (DOSKA[y1 + steps[i].Y][x1 + steps[i].X] == whites[j]){
						y2 = y1 + steps[i].Y;
						x2 = x1 + steps[i].X;
						mate(x1, y1, x2, y2);
						step(x1, y1, x2, y2);
						return 1;
					}
				}
			}
		}
		break;
	}
	while (true){
		for (int i = 0; i < options; i++){
			if (DOSKA[y1 + steps[i].Y][x1 + steps[i].X] != 0 && y1 + steps[i].Y >= 0 && x1 + steps[i].X >= 0 && y1 + steps[i].Y <= 7 && x1 + steps[i].X <= 7);
			else if (DOSKA[y1 + steps[i].Y][x1 + steps[i].X] == 0 && y1 + steps[i].Y >= 0 && x1 + steps[i].X >= 0 && y1 + steps[i].Y <= 7 && x1 + steps[i].X <= 7){
				y2 = y1 + steps[i].Y;
				x2 = x1 + steps[i].X;
				mate(x1, y1, x2, y2);
				step(x1, y1, x2, y2);
				return 1;
			}
		}
		break;
	}

	return 0;
}

void mate(int x1, int y1, int x2, int y2)
{
	if (DOSKA[y2][x2] == wK){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = bK;
		win();
	}

}

void step(int x1, int y1, int x2, int y2)
{
	DOSKA[y1][x1] = 0;
	DOSKA[y2][x2] = bK;
	setPosition_X = x2;
	setPosition_Y = y2;
}