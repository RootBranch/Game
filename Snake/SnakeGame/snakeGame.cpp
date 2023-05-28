#include "snakeGame.h"


SnakeGame::SnakeGame()
{
	InitSnake();
	PrintMap();
	PrintSnake();
	CreateFood();
	MoveSnake();
}

void SnakeGame::gotoxy(short x, short y)
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	pos = { x, y };
	SetConsoleCursorPosition(hOut, pos);
}

void SnakeGame::HideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &CursorInfo);
}


void SnakeGame::InitSnake()
{
	gotoxy(WIDTH / 2, HEIGHT / 2);
	cout << '@';
	snake.push_front({ WIDTH / 2, HEIGHT / 2 });
	for (int i = 0; i < 2; i++)
	{
		snake.push_back({ WIDTH / 2,HEIGHT / 2 + i + 1 });
	}
}


void SnakeGame::PrintMap()
{
	gotoxy(0, 0);
	for (int i = 0; i < WIDTH; i += 2)cout << "■";
	gotoxy(0, 1);
	for (int i = 1; i < HEIGHT; i++)cout << "■" << endl;
	gotoxy(2, HEIGHT - 1);
	for (int i = 2; i < WIDTH; i += 2)cout << "■";
	for (int i = 1; i < HEIGHT - 1; i++)
	{
		gotoxy(WIDTH - 2, i);
		cout << "■";
	}

	gotoxy(1, HEIGHT);
	cout << "w,s,a,d控制方向，n加速，m减速" << endl;
	cout << endl;
}

void SnakeGame::PrintSnake()
{
	for (deque<Snake>::iterator it = snake.begin() + 1; it != snake.end(); it++)
	{
		gotoxy(it->x, it->y);
		cout << "+";
	}
}

void SnakeGame::GetUserKey()
{
	char ch;
	switch (ch = _getch())
	{
	case 'w':if (dir != 's') dir = ch; break;
	case 's':if (dir != 'w') dir = ch; break;
	case 'a':if (dir != 'd') dir = ch; break;
	case 'd':if (dir != 'a') dir = ch; break;
	case 'm':if (speed <= 600) speed *= 1.3;
	case 'n':if (speed >= 50) speed /= 1.3;
	default:
		break;
	}
}

void SnakeGame::MoveSnake()
{
	while (true)
	{
		if (_kbhit())GetUserKey();

		Snake temp1, temp2, temp3;
		temp1 = snake.back();
		temp2 = snake.front();
		temp3 = temp2;

		if (dir == 'w') temp2.y--;
		else if (dir == 's') temp2.y++;
		else if (dir == 'a') temp2.x--;
		else if (dir == 'd') temp2.x++;

		if (temp2.x == mFoodX && temp2.y == mFoodY)
		{
			FoodEaten();
		}

		if (eatFood)
		{
			gotoxy(temp1.x, temp1.y);
			cout << '+';
			snake.push_back(temp1);
			eatFood = false;
		}

		snake.pop_back();
		snake.push_front(temp2);

		JudgeIsCrash();

		gotoxy(temp1.x, temp1.y);
		cout << " ";
		gotoxy(temp2.x, temp2.y);
		if (dir == 'w') cout << "$"; 
		else if (dir == 's') cout << "$";
		else if (dir == 'a') cout << "<";
		else if (dir == 'd') cout << ">";

		gotoxy(temp3.x, temp3.y);
		cout << "+";

		Sleep(speed + 30);

	}
}

void SnakeGame::CreateFood()
{
	while (true)
	{
		this->mFoodX = rand() % (WIDTH - 4) + 2;
		this->mFoodY = rand() % (HEIGHT - 2) + 1;
		if (JudgeIsRight()) break;
	}
	gotoxy(mFoodX, mFoodY);
	cout << "*";
}

bool SnakeGame::JudgeIsRight()
{
	for (deque<Snake>::iterator it = snake.begin(); it != snake.end(); it++)
	{
		if (it->x == mFoodX && it->y == mFoodY) return 0;
	}
	return 1;
}

void SnakeGame::FoodEaten()
{
	CreateFood();
	eatFood = true;
	score++;
}


void SnakeGame::JudgeIsCrash()
{
	int flag = 0;
	if (snake.size() >= 5)
	{
		deque<Snake>::iterator it = snake.begin();
		int x = it->x;
		int y = it->y;
		it++;
		for (; it != snake.end(); it++)
		{
			if (x == it->x && y == it->y)
			{
				flag = 1;
				break;
			}
		}
	}
	if (flag || snake.front().x == 1 || snake.front().y == 0 || snake.front().x == WIDTH - 2 || snake.front().y == HEIGHT - 1)
	{
		gotoxy(1, HEIGHT + 1);
		cout << "Game over!" << endl << "Score:" << this->score << endl;
		system("pause");
		exit(0);
	}
}

