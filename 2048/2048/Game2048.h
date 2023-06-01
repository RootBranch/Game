#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
#define WIDTH 4
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Game2048
{
public:
	Game2048();
	void InitChessboard();
	void PrintChessboard();
	void RandomNumber();
	void GetInput();
	void MoveDirection();
	void rotateMatrix(int);
	void Move();
	void Gather(int);
	void JudgeEnd();
	bool judgeGo();
private:
	HANDLE hOut;
	COORD pos;
	int Chessboard[WIDTH][WIDTH];
	int dir;
};