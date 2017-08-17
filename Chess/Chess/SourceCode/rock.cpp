#include "Headers/else.h"

int rock(int x1, int y1, int x2, int y2)
{
	//whites == false
	//blacks == true

	if (x1 != x2 && y1 != y2){
		if (CPU && flag);
		else wrong_move();
		return 0;
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

	if (y2 > y1){
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
	if (DOSKA[y2][x2] == wK && flag){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = bR;
		win();
	}
	else if (DOSKA[y2][x2] == bK && !flag){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = wR;
		win();
	}



	if (flag){
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = bR;
	}
	else{
		DOSKA[y1][x1] = 0;
		DOSKA[y2][x2] = wR;
	}

	return 1;
}