#include "Headers/cpu.h"

int pawn(int x1, int y1)
{
	int x2, y2;
	const int options = 4;
	static int flag_local = 0;
	COORD steps[options] = { { -1, 1 }, { 1, 1 }, { 0, 1 }, {0, 2} };
	
	while (true){
		for (int i = 0; i < options - 2; i++){
			if (DOSKA[y1 + steps[i].Y][x1 + steps[i].X] != 0 && y1 + steps[i].Y >= 0 && x1 + steps[i].X >= 0 && y1 + steps[i].Y <= 7 && x1 + steps[i].X <= 7){
				for (int j = 0; j < 6; j++){
					if (DOSKA[y1 + steps[i].Y][x1 + steps[i].X] == whites[j]){
						if (y1 == 6){
							y2 = y1 + steps[i].Y;
							x2 = x1 + steps[i].X;
							DOSKA[y1][x1] = 0;
							DOSKA[y2][x2] = bQ;
							return 1;
						}
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

	if (y1 == 1){
		if (DOSKA[y1 + steps[2].Y][x1 + steps[2].X] == 0 && flag_local == 0){
			y2 = y1 + steps[2].Y;
			x2 = x1 + steps[2].X;
			mate(x1, y1, x2, y2);
			step(x1, y1, x2, y2);
			flag_local++;
			return 1;
		}
		if (DOSKA[y1 + steps[3].Y][x1 + steps[3].X] == 0 && flag_local == 1 && DOSKA[y1 + steps[2].Y][x1 + steps[2].X] == 0){
			y2 = y1 + steps[3].Y;
			x2 = x1 + steps[3].X;
			mate(x1, y1, x2, y2);
			step(x1, y1, x2, y2);
			flag_local = 0;
			return 1;
		}
	}

	if (DOSKA[y1 + steps[2].Y][x1 + steps[2].X] == 0){
		if (y1 == 6){
			y2 = y1 + steps[2].Y;
			x2 = x1 + steps[2].X;
			DOSKA[y1][x1] = 0;
			DOSKA[y2][x2] = bQ;
			return 1;
		}
		y2 = y1 + steps[2].Y;
		x2 = x1 + steps[2].X;
		mate(x1, y1, x2, y2);
		step(x1, y1, x2, y2);
		return 1;
	}
	
	
	return 0;
}

void mate(int x1, int y1, int x2, int y2)
{
	if (DOSKA[y2][x2] == wK){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = bP;
		win();
	}

}

void step(int x1, int y1, int x2, int y2)
{
	DOSKA[y1][x1] = 0;
	DOSKA[y2][x2] = bP;
	setPosition_X = x2;
	setPosition_Y = y2;
}