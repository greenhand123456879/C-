#pragma once
#include<iostream>
#include<stdio.h>
#include<graphics.h>
#include<string.h>
#include<string>
#include<math.h>
#include<time.h>

#define CIRCLE 40
#define BEGIN 1
#define END 0
#define GRAPH_EDGE 900
#define CHESS_EDGE_ROW 700.0 //heng
#define CHESS_EDGE_COL 800.0 //shu
#define GAME_ROW 10
#define GAME_COL 9
#define INTERVAL_ROW (CHESS_EDGE_COL / (GAME_ROW - 1.0))
#define INTERVAL_COL (CHESS_EDGE_ROW / (GAME_COL - 1.0))
#define WAIFRAME_TOP_X (((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) - 5)
#define WAIFRAME_TOP_Y (((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) - 5)
#define WAIFRAME_BOTTOM_X (CHESS_EDGE_ROW + ((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + 5)
#define WAIFRAME_BOTTOM_Y (CHESS_EDGE_COL + ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + 5)
#define MIZI_TOP_X (((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + (3 * INTERVAL_COL))
#define MIZI_TOP_Y ((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0)
#define MIZI_BOTTOM_X (((GRAPH_EDGE - CHESS_EDGE_ROW) / 2.0) + (5 * INTERVAL_COL))
#define MIZI_BOTTOM_Y (((GRAPH_EDGE - CHESS_EDGE_COL) / 2.0) + (2 * INTERVAL_ROW))
using namespace std;

typedef enum Pieces
{
	NONE = -1,
	車, 馬, 相, 士, 帅, 炮, 兵,//红方
	车, 马, 象, 仕, 将, 砲, 卒//黑方
}Pieces;

struct MyPoint
{
	int x = -1;
	int y = -1;
};

struct MouseEventState
{
	MyPoint pBegin;
	MyPoint pEnd;
	int pointState;
};

struct Chess
{
	int x = 0;
	int y = 0;
	Pieces chessName = NONE;
	bool flag_choosing = false;
	bool flag_die = false;
	bool flag_through_river = false;
	char color = ' ';
};

Pieces redChess[7] = { 車, 馬, 相, 士, 帅, 炮, 兵 };
Pieces blackChess[7] = { 车, 马, 象, 仕, 将, 砲, 卒 };
const string chessName[] = { "車", "馬", "相", "士", "帅", "炮", "兵", "车", "马", "象", "仕", "将", "砲", "卒"};
																		//7 ....
void MyDelay(int sec);
void GameInit();
void ShowGameConsole();
void MouseEvent();
void ChessMove();
void DrawChess();
void GameDrawBoard();