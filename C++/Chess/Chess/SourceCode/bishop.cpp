#include "Headers/cpu.h"
#include "Headers/else.h"


int bishop(int x1, int y1, int x2, int y2)
{
start:
	if (DOSKA[y2][x2] != 0){
		for (int a = 0; a < 6; a++) {
			if (DOSKA[y2][x2] == blacks[a] && flag){
				if (CPU && flag);
				else wrong_move();
				return 0;
			}
			else if (DOSKA[y2][x2] == whites[a] && !flag){
				if (CPU && flag);
				else wrong_move();
				return 0;
			}
		}
	}

	if (y2 < y1 && x1 != x2){
		if (x2 < x1){
			int y, x;
			for (y = y1, x = x1; y2 < (y - 1); y--, x--){
				if (DOSKA[y - 1][x - 1] != 0){
					if (CPU && flag);
					else wrong_move();
					return 0;
				}
			}
			if (x2 == x - 1 && y2 == y - 1){
				mate(x1, y1, x - 1, y - 1);
				step(x1, y1, x - 1, y - 1);
				return 1;
			}
			else {
				if (CPU && flag);
				else wrong_move();
				return 0;
			}

		}
		else if (x2 > x1){
			int y, x;
			for (y = y1, x = x1; y2 < (y - 1); y--, x++){
				if (DOSKA[y - 1][x + 1] != 0){
					if (CPU && flag);
					else wrong_move();
					return 0;
				}
			}
			if (x2 == x + 1 && y2 == y - 1){
				mate(x1, y1, x + 1, y - 1);
				step(x1, y1, x + 1, y - 1);
				return 1;
			}
			else {
				if (CPU && flag);
				else wrong_move();
				return 0;
			}
		}
	}

	else if (y2 > y1 && x1 != x2){
		if (x2 < x1){
			int y, x;
			for (y = y1, x = x1; y2 >(y + 1); y++, x--){
				if (DOSKA[y + 1][x - 1] != 0){
					if (CPU && flag);
					else wrong_move();
					return 0;
				}
			}
			if (x2 == x - 1 && y2 == y + 1){
				mate(x1, y1, x - 1, y + 1);
				step(x1, y1, x - 1, y + 1);
				return 1;
			}
			else {
				if (CPU && flag);
				else wrong_move();
				return 0;
			}
		}
		else if (x2 > x1){
			int y, x;
			for (y = y1, x = x1; y2 > (y + 1); y++, x++){
				if (DOSKA[y + 1][x + 1] != 0){
					if (CPU && flag);
					else wrong_move();
					return 0;
				}
			}
			if (x2 == x + 1 && y2 == y + 1){
				mate(x1, y1, x + 1, y + 1);
				step(x1, y1, x + 1, y + 1);
				return 1;
			}
			else {
				if (CPU && flag);
				else wrong_move();
				return 0;
			}
		}
	}
	if (CPU && flag);
	else wrong_move();
	return 0;
}

void mate(int x1, int y1, int x2, int y2)
{
	if (DOSKA[y2][x2] == wK && flag){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = bB;
		win();
	}
	else if (DOSKA[y2][x2] == bK && !flag){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = wB;
		win();
	}

}

void step(int x1, int y1, int x2, int y2)
{
	if (flag){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = bB;
	}
	else{
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = wB;
	}
}