#pragma once
#include <iostream>
#include <Windows.h>
#include <queue>
#include<conio.h>
using namespace std;
#define HEIGHT 40
#define WIDTH 30

struct Snake
{
	int x, y;
};


class SnakeGame
{
public:
	SnakeGame();
	void InitSnake();
	void PrintMap();
	void PrintSnake();
	void gotoxy(short x, short y);
	void HideCursor();
	void GetUserKey();
	void MoveSnake();
	void CreateFood();
	bool JudgeIsRight();
	void FoodEaten();
	void JudgeIsCrash();


private:
	HANDLE hOut;
	COORD pos;
	deque<Snake> snake;
	int dir;
	int mFoodX;
	int mFoodY;
	bool eatFood = false;
	int score = 0;
	double speed = 200;
};