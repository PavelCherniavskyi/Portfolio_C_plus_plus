#include "Headers/else.h"


int knight(int x1, int y1, int x2, int y2)
{
	//whites == false
	//blacks == true

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
	if (y2 == (y1 - 2)){
		if (x2 == x1 + 1){
			mate(x1, y1, x2, y2);
			step(x1, y1, x2, y2);
			return 1;
		}
		else if (x2 == x1 - 1){
			mate(x1, y1, x2, y2);
			step(x1, y1, x2, y2);
			return 1;
		}
	}
	else if (y2 == (y1 + 2)){
		if (x2 == x1 + 1){
			mate(x1, y1, x2, y2);
			step(x1, y1, x2, y2);
			return 1;
		}
		else if (x2 == x1 - 1){
			mate(x1, y1, x2, y2);
			step(x1, y1, x2, y2);
			return 1;
		}
	}
	else if (x2 == (x1 + 2)){
		if (y2 == y1 + 1){
			mate(x1, y1, x2, y2);
			step(x1, y1, x2, y2);
			return 1;
		}
		else if (y2 == y1 - 1){
			mate(x1, y1, x2, y2);
			step(x1, y1, x2, y2);
			return 1;
		}
	}
	else if (x2 == (x1 - 2)){
		if (y2 == y1 + 1){
			mate(x1, y1, x2, y2);
			step(x1, y1, x2, y2);
			return 1;
		}
		else if (y2 == y1 - 1){
			mate(x1, y1, x2, y2);
			step(x1, y1, x2, y2);
			return 1;
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
		DOSKA[y2][x2] = bN;
		win();
	}
	else if (DOSKA[y2][x2] == bK && !flag){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = wN;
		win();
	}

}

void step(int x1, int y1, int x2, int y2)
{
	if (flag){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = bN;
	}
	else{
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = wN;
	}
}