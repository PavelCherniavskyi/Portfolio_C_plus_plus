#pragma once
#include <ctime>
#include <Windows.h>

using namespace std;

extern int DOSKA[8][8];


extern int wP; //white pawn
extern int wB; //white bishop
extern int wN; //white knight
extern int wR; //white rock
extern int wQ; //white queen
extern int wK; //white king
extern int bP; //black pawn
extern int bB; //black bishop
extern int bN; //black knight
extern int bR;  //black rock
extern int bQ; //black queen
extern int bK; //black king

extern int blacks[6];
extern int whites[6];

extern int setPosition_X;
extern int setPosition_Y;


extern int pawn(int x1, int y1);
extern int bishop(int x1, int y1);
extern int knight(int x1, int y1);
extern int rock(int x1, int y1);
extern int queen(int x1, int y1);
extern int king(int x1, int y1);

extern void matrix_fill(void);
extern void wrong_enter(void);
extern void win(void);
extern int move(void);
extern void not_your_turn(void);
extern void wrong_move(void);
static void mate(int x1, int y1, int x2, int y2);
static void step(int x1, int y1, int x2, int y2);