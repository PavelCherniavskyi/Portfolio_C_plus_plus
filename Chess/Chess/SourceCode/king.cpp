#include "Headers/else.h"


int king(int x1, int y1, int x2, int y2)
{
	if (!flag && y1 == 7 && DOSKA[y2][x2] == wR && DOSKA[y2][x2 - 1] == 0 && DOSKA[y2][x2 - 2] == 0){
		DOSKA[y1][x1 + 1] = wR;
		DOSKA[y2][x2 - 1] = wK;
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = 0;
		return 1;
	}
	else if (!flag && y1 == 7 && DOSKA[y2][x2] == wR && DOSKA[y2][x2 + 1] == 0 && DOSKA[y2][x2 + 2] == 0 && DOSKA[y2][x2 + 3] == 0){
		DOSKA[y1][x1 - 1] = wR;
		DOSKA[y2][x2 + 2] = wK;
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = 0;
		return 1;
	}
	else if (flag && y1 == 0 && DOSKA[y2][x2] == wR && DOSKA[y2][x2 - 1] == 0 && DOSKA[y2][x2 - 2] == 0){
		DOSKA[y1][x1 + 1] = bR;
		DOSKA[y2][x2 - 1] = bK;
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = 0;
		return 1;
	}
	else if (flag && y1 == 0 && DOSKA[y2][x2] == wR && DOSKA[y2][x2 + 1] == 0 && DOSKA[y2][x2 + 2] == 0 && DOSKA[y2][x2 + 3] == 0){
		DOSKA[y1][x1 - 1] = bR;
		DOSKA[y2][x2 + 2] = bK;
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = 0;
		return 1;
	}

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
	if (y2 == y1 + 1){
		if (x1 == x2){
			mate(x1, y1, x2, y2);
			step(x1, y1, x2, y2);
			return 1;
		}
		else if (x2 == x1 + 1){
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
	else if (y2 == y1 - 1){
		if (x1 == x2){
			mate(x1, y1, x2, y2);
			step(x1, y1, x2, y2);
			return 1;
		}
		else if (x2 == x1 + 1){
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
	else if (x2 == x1 - 1){
		if (y1 == y2){
			mate(x1, y1, x2, y2);
			step(x1, y1, x2, y2);
			return 1;
		}
		else if (y2 == y1 + 1){
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
	else if (x2 == x1 + 1){
		if (y1 == y2){
			mate(x1, y1, x2, y2);
			step(x1, y1, x2, y2);
			return 1;
		}
		else if (y2 == y1 + 1){
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
		DOSKA[y2][x2] = bK;
		win();
	}
	else if (DOSKA[y2][x2] == bK && !flag){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = wK;
		win();
	}

}

void step(int x1, int y1, int x2, int y2)
{
	if (flag){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = bK;
	}
	else{
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = wK;
	}
}