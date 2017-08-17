#include "Headers/cpu.h"

int cpu(void)
{
	int x1, y1;
	static int flag1 = 0;
	bool found = false;
	srand(time(NULL));
	int a = blacks[rand() % 6];
	
	while (true){
		
		if (flag1 == 0){
			a = blacks[rand() % 6];
			flag1++;
			for (int i = 0; i < 8; i++){
				for (int j = 0; j < 8; j++)
				if (DOSKA[i][j] == a){
					y1 = i;
					x1 = j;
					found = true;
					goto end;
				}
			}
		}
		else if (flag1 == 1){
			flag1++;
			for (int i = 0; i < 8; i++){
				for (int j = 7; j >= 0; j--)
				if (DOSKA[i][j] == a){
					y1 = i;
					x1 = j;
					found = true;
					goto end;
				}
			}
		}
		else if (flag1 == 2){
			flag1++;
			for (int i = 7; i >= 0; i--){
				for (int j = 7; j >= 0; j--)
				if (DOSKA[i][j] == a){
					y1 = i;
					x1 = j;
					found = true;
					goto end;
				}
			}
		}
		else if (flag1 == 3){
			flag1++;
			for (int i = 7; i >= 0; i--){
				for (int j = 0; j < 8; j++)
				if (DOSKA[i][j] == a){
					y1 = i;
					x1 = j;
					found = true;
					goto end;
				}
			}
		}
		if (flag1 == 4){
			flag1++;
			for (int i = 0; i < 8; i++){
				for (int j = 0; j < 8; j++)
				if (DOSKA[j][i] == a){
					y1 = i;
					x1 = j;
					found = true;
					goto end;
				}
			}
		}
		else if (flag1 == 5){
			flag1++;
			for (int i = 7; i >= 0; i--){
				for (int j = 7; j >= 0; j--)
				if (DOSKA[j][i] == a){
					y1 = i;
					x1 = j;
					found = true;
					goto end;
				}
			}
		}
		else if (flag1 == 6){
			flag1++;
			for (int i = 0; i < 8; i++){
				for (int j = 7; j >= 0; j--)
				if (DOSKA[j][i] == a){
					y1 = i;
					x1 = j;
					found = true;
					goto end;
				}
			}
		}
		else if (flag1 == 7){
			flag1 = 0;
			for (int i = 7; i >= 0; i--){
				for (int j = 0; j < 8; j++)
				if (DOSKA[j][i] == a){
					y1 = i;
					x1 = j;
					found = true;
					goto end;
				}
			}
		}
	end:
		if (found) break;
	}
		
	
	switch (DOSKA[y1][x1])
	{
	case 2653:    if (!pawn(x1, y1)) {
					  return 0;
	}
				  else break;
	case 2652:	if (!bishop(x1, y1)) {
					return 0;
	}
				else break;
	case 2651:	if (!knight(x1, y1)) {
					return 0;
	}
				else break;
	case 2650:	if (!rock(x1, y1)) {
					return 0;
	}
				else break;
	case 2649:	if (!queen(x1, y1)) {
					return 0;
	}
				else break;
	case 2648:	if (!king(x1, y1)) {
					return 0;
	}
				else break;
	default:        return 0;
	}

	return 1;
}
