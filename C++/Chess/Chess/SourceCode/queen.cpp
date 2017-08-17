#include "Headers/else.h"

int queen(int x1, int y1, int x2, int y2)
{
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

	if (x1 != x2 && y1 != y2){
		if (CPU && flag);
		else wrong_move();
		return 0;
	}

	else if (y2 > y1){
		for (int i = y1; y2 > (i + 1); i++){
			if (DOSKA[i + 1][x1] != 0){
				if (CPU && flag);
				else wrong_move();
				return 0;
			}
		}
	}
	else if (y2 < y1){
		for (int i = y1; y2 < (i - 1); i--){
			if (DOSKA[i - 1][x1] != 0){
				if (CPU && flag);
				else wrong_move();
				return 0;
			}
		}
	}
	else if (x2 < x1){
		for (int i = x1; x2 < (i - 1); i--){
			if (DOSKA[y1][i - 1] != 0){
				if (CPU && flag);
				else wrong_move();
				return 0;
			}
		}
	}
	else if (x2 > x1){
		for (int i = x1; x2 >(i + 1); i++){
			if (DOSKA[y1][i + 1] != 0){
				if (CPU && flag);
				else wrong_move();
				return 0;
			}
		}
	}

	mate(x1, y1, x2, y2);
	step(x1, y1, x2, y2);
	return 1;
}

void mate(int x1, int y1, int x2, int y2)
{
	if (DOSKA[y2][x2] == wK && flag){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = bQ;
		win();
	}
	else if (DOSKA[y2][x2] == bK && !flag){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = wQ;
		win();
	}

}

void step(int x1, int y1, int x2, int y2)
{
	if (flag){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = bQ;
	}
	else{
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = wQ;
	}
}