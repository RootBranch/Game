#include "Game2048.h"

Game2048::Game2048()
{
	InitChessboard();
	PrintChessboard();
	MoveDirection();
}

void Game2048::InitChessboard()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			Chessboard[i][j] = 0;
		}
	}
	RandomNumber();
}


void Game2048::PrintChessboard()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			cout << Chessboard[i][j] << "     ";
		}
		cout << endl;
	}
}


void Game2048::RandomNumber()
{
	srand((unsigned)time(NULL));
	int Random;
	Random = rand() % 10 + 1;
	int x, y;
	while (true)
	{
		x = rand() % WIDTH;
		y = rand() % WIDTH;
		if (Chessboard[x][y] == 0)
			break;
	}
	Chessboard[x][y] = Random <= 8 ? 2 : 4;
}
void Game2048::rotateMatrix(int times)
{
	int temp1[10][10];
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			temp1[i][j] = Chessboard[i][j];
		}
	}
	for (int i = WIDTH - 1, k = 0; i >= 0; i--, k++)
	{
		for (int j = 0; j < WIDTH; j++) {
			Chessboard[j][i] = temp1[k][j];
		}
	}	if (times > 1)
	{
		rotateMatrix(times - 1);
	}
}


void Game2048::GetInput()
{
	char temp;
	temp = _getch();
	switch (temp)
	{
	case 'w':dir = UP; break;
	case's':dir = DOWN; break;
	case'a':dir = LEFT; break;
	case 'd':dir = RIGHT; break;
	}
}


void Game2048::MoveDirection()
{
	while (true)
	{
		loop:
		GetInput();
		if (dir == UP)
		{
			if (judgeGo() == false)
			{
				goto loop;
			}
			Move();
		}
		else if (dir == DOWN)
		{
			rotateMatrix(2);
			if (judgeGo() == false)
			{
				goto loop;
			}
			Move();
			rotateMatrix(2);
		}
		else if (dir == LEFT)
		{
			rotateMatrix(1);
			if (judgeGo() == false)
			{
				goto loop;
			}
			Move();
			rotateMatrix(3);
		}
		else if (dir == RIGHT)
		{
			rotateMatrix(3);
			if (judgeGo() == false)
			{
				goto loop;
			}
			Move();
			rotateMatrix(1);
		}
		system("cls");
		RandomNumber();
		PrintChessboard();
		JudgeEnd();
	}
}


void Game2048::Move()
{
	for (int j = WIDTH - 1; j >= 0; j--)
	{
		Gather(j);
		for (int i = WIDTH - 1; i > 0; i--)
		{
			int n = 1;
			if (Chessboard[i][j] == Chessboard[i - n][j] && Chessboard[i][j] != 0)
			{
				Chessboard[i - n][j] *= 2;
				Chessboard[i][j] = 0;
				Gather(j);
			}
		}
	}
}


void Game2048::Gather(int y)
{
	int j = 0;
	for (int i = 0; i < WIDTH; i++)
	{
		if (Chessboard[i][y] != 0)
		{
			Chessboard[j][y] = Chessboard[i][y];
			j++;
		}
	}
	for (; j < WIDTH; j++) Chessboard[j][y] = 0;
}


void Game2048::JudgeEnd()
{
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };
	bool flag = false;
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				if (dx[k] + i < 0 || dx[k] + i >= WIDTH || dy[k] + j < 0 || dy[k] + j >= WIDTH) continue;
				if (Chessboard[dx[k] + i][dy[k] + j] == Chessboard[i][j]||Chessboard[i][j]==0)
				{
					flag = true;
				}
			}
			if (flag == true) break;
		}
		if (flag == true) break;
	}
	if (flag == false)
	{
		
		cout << "Game over" << endl;
		exit(0);
	}

}


bool Game2048::judgeGo()
{
	for (int j = 0; j < WIDTH; j++)
	{
		for (int i = 0; i < WIDTH - 1; i++)
		{
			if (Chessboard[i][j] == Chessboard[i + 1][j]||Chessboard[i][j]==0||Chessboard[i+1][j]==0)
				return true;
		}
	}
	return false;
}


