#include "Headers/cpu.h"

int rock(int x1, int y1)
{
	int x2, y2;
	const int options = 7;
	static int flag_local = 0;

	COORD steps[options];
	if (flag_local == 0){
		steps[0] = { 0, 1 }; steps[1] = { 0, 2 }; steps[2] = { 0, 3 }; steps[3] = { 0, 4 }; steps[4] = { 0, 5 }; steps[5] = { 0, 6 }; steps[6] = { 0, 7 };
		flag_local++;
	}
	else if (flag_local == 1){
		steps[0] = { 1, 0 }; steps[1] = { 2, 0 }; steps[2] = { 3, 0 }; steps[3] = { 4, 0 }; steps[4] = { 5, 0 }; steps[5] = { 6, 0 }; steps[6] = { 7, 0 };
		flag_local++;
	}
	else if (flag_local == 2){
		steps[0] = { 0, -1 }; steps[1] = { 0, -2 }; steps[2] = { 0, -3 }; steps[3] = { 0, -4 }; steps[4] = { 0, -5 }; steps[5] = { 0, -6 }; steps[6] = { 0, -7 };
		flag_local++;
	}
	else{
		steps[0] = { -1, 0 }; steps[1] = { -2, 0 }; steps[2] = { -3, 0 }; steps[3] = { -4, 0 }; steps[4] = { -5, 0 }; steps[5] = { -6, 0 }; steps[6] = { -7, 0 };
		flag_local = 0;
	}
	
	
	while (true){
		for (int i = options - 1; i >= 0; i--){
			
			if (DOSKA[y1 + steps[i].Y][x1 + steps[i].X] != 0 && y1 + steps[i].Y >= 0 && x1 + steps[i].X >= 0 && y1 + steps[i].Y <= 7 && x1 + steps[i].X <= 7){
				
				for (int j = 0; j < 6; j++){
					if (DOSKA[y1 + steps[i].Y][x1 + steps[i].X] == whites[j]){
						bool buzy = true;
						for (int a = i - 1; a >= 0; a--){
							if (DOSKA[y1 + steps[a].Y][x1 + steps[a].X] != 0) buzy = false;
						}
						if (buzy){
							y2 = y1 + steps[i].Y;
							x2 = x1 + steps[i].X;
							mate(x1, y1, x2, y2);
							step(x1, y1, x2, y2);
							return 1;
						}
						
					}
				}
			}
			
			if (DOSKA[y1 + steps[i].Y][x1 + steps[i].X] != 0 && y1 + steps[i].Y >= 0 && x1 + steps[i].X >= 0 && y1 + steps[i].Y <= 7 && x1 + steps[i].X <= 7);
			else if (DOSKA[y1 + steps[i].Y][x1 + steps[i].X] == 0 && y1 + steps[i].Y >= 0 && x1 + steps[i].X >= 0 && y1 + steps[i].Y <= 7 && x1 + steps[i].X <= 7){
				bool buzy = true;
				for (int a = i - 1; a >= 0; a--){
					if (DOSKA[y1 + steps[a].Y][x1 + steps[a].X] != 0)
						buzy = false;
				}
				if (buzy){
					y2 = y1 + steps[i].Y;
					x2 = x1 + steps[i].X;
					mate(x1, y1, x2, y2);
					step(x1, y1, x2, y2);
					return 1;
				}
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
		DOSKA[y2][x2] = bR;
		win();
	}

}

void step(int x1, int y1, int x2, int y2)
{
	DOSKA[y1][x1] = 0;
	DOSKA[y2][x2] = bR;
	setPosition_X = x2;
	setPosition_Y = y2;
}