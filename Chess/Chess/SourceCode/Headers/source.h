#pragma once
#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

bool flag = true;
bool CPU = true;

int DOSKA[8][8] = {0};

int wP = 2659; //white pawn
int wB = 2657; //white bishop
int wN = 2658; //white knight
int wR = 2656; //white rock
int wQ = 2655; //white queen
int wK = 2654; //white king
int bP = 2653; //black pawn
int bB = 2652; //black bishop
int bN = 2651; //black knight
int bR = 2650; //black rock
int bQ = 2649; //black queen
int bK = 2648; //black king

RenderWindow window(sf::VideoMode(870, 580), "Chess");

int setPosition_X;
int setPosition_Y;


int whites[6] = { wP, wN, wB, wR, wQ, wK };
int blacks[6] = { bP, bN, bB, bR, bQ, bK };

int pawn(int x1, int y1, int x2, int y2);
int pawn(int x1, int y1);
int bishop(int x1, int y1, int x2, int y2);
int knight(int x1, int y1, int x2, int y2);
int knight(int x1, int y1);
int rock(int x1, int y1, int x2, int y2);
int queen(int x1, int y1, int x2, int y2);
int king(int x1, int y1, int x2, int y2);
int cpu(void);
void cpu_thinking(void);
void matrix_show(void);
void matrix_fill(void);
void wrong_enter(void);
void wrong_move(void);
void win(void);
int move(int x1, int y1, int x2, int y2);
void not_your_turn(void);
void introdaction(void);

void mate(int x1, int y1, int x2, int y2);
void step(int x1, int y1, int x2, int y2);

