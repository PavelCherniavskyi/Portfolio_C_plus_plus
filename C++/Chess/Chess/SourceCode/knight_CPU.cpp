#include "Headers/cpu.h"


int knight(int x1, int y1)
{
	int x2, y2;
	const int options = 8;
	COORD steps[options];
	static int flag_local = 0;
	

	if (flag_local == 0){
		steps[0] = { 1, 2 }; steps[1] = { -1, 2 }; steps[2] = { -2, 1 }; steps[3] = { -2, -1 }; steps[4] = { -1, -2 }; steps[5] = { 1, -2 }; steps[6] = { 2, -1 }; steps[7] = { 2, 1 };
		flag_local++;
	}
	else if (flag_local == 1){
		steps[0] = { -1, -2 }; steps[1] = { 1, -2 }; steps[2] = { 2, -1 }; steps[3] = { 2, 1 }; steps[4] = { 2, -1 }; steps[5] = { 2, 1 }; steps[6] = { -2, -1 }; steps[7] = { -2, 1 };
		flag_local++;
	}
	else if (flag_local == 2){
		steps[0] = { -2, 1 }; steps[1] = { -2, -1 }; steps[2] = { -1, -2 }; steps[3] = { 1, -2 }; steps[4] = { 2, -1 }; steps[5] = { 2, 1 }; steps[6] = { 2, 1 }; steps[7] = { 2, -1 };
		flag_local++;
	}
	else{
		steps[0] = { 2, -1 }; steps[1] = { 2, 1 }; steps[2] = { -1, 2 }; steps[3] = { 1, 2 }; steps[4] = { -2, 1 }; steps[5] = { -2, -1 }; steps[6] = { -1, -2 }; steps[7] = { 1, -2 };
		flag_local = 0;
	}
		


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
		DOSKA[y2][x2] = bN;
		win();
	}

}

void step(int x1, int y1, int x2, int y2)
{
	DOSKA[y1][x1] = 0;
	DOSKA[y2][x2] = bN;
	setPosition_X = x2;
	setPosition_Y = y2;
}