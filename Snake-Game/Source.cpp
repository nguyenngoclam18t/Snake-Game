#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<ctime>

enum SNAKE
{
	MENU,
	SETTING,
	GAMEOVER,
	INFOR,
	INGAME,
	NONE = 10
}GAME;
int Snake[1000];
int Score = 0;
int Fruit = 12010;
int length;
void InitSnake();
int GetX(int a);
int GetY(int a);
int vx = 0, vy = -1, ct = 0;
void gotoxy(int x, int y);
void Creat_Fruit();
void Menu();
void Setting();
void Ingame();
void Gameover();
void Infor();
void Box_Game();
void Print_Score();
int main() {
	GAME = INGAME;
	while (true)
	{
		switch (GAME)
		{
		case MENU: {
			Menu();
			break; }
		case SETTING:
			Setting();
			break;
		case GAMEOVER:
			Gameover();
			break;
		case INFOR:
			Infor();
			break;
		case INGAME: {
			int key;
			Ingame();
			InitSnake();
			gotoxy(GetX(Snake[0]), GetY(Snake[0]));
			printf("#");
			for (int i = 1; i < length - 1; i++)
			{
				gotoxy(GetX(Snake[i]), GetY(Snake[i]));
				printf("o");
			}
			while (GAME == INGAME) {
				if (_kbhit()) {
					key = _getch();
					switch (key)
					{
					case 80://dow
						if (vx != 0) {
							vy = 1;
							vx = 0;
						}
						break;
					case 72://up
						if (vx != 0) {
							vy = -1;
							vx = 0;
						}
						break;
					case 75://left
						if (vy != 0) {
							vy = 0;
							vx = -1;
						}
						break;
					case 77://right
						if (vy != 0) {
							vy = 0;
							vx = 1;
						}
						break;
					default:
						break;
					}
				}

				if (ct % 5000 == 0) {
					gotoxy(GetX(Snake[length - 1]), GetY(Snake[length - 1]));
					printf(" ");
					for (int i = length - 1; i > 0; i--)
					{
						Snake[i] = Snake[i - 1];
					}
					Snake[0] += vy;
					Snake[0] += vx * 100;
					if (GetY(Snake[0]) == 0)Snake[0] += 19;
					if (GetY(Snake[0]) == 20)Snake[0] -= 19;
					if (GetX(Snake[0]) == 0) Snake[0] += 10000;
					if (GetX(Snake[0]) == 100)Snake[0] -= 10000;
					gotoxy(GetX(Snake[0]), GetY(Snake[0]));
					printf("#");
					gotoxy(GetX(Snake[1]), GetY(Snake[1]));
					printf("o");

					gotoxy(GetX(Fruit), GetY(Fruit));
					printf("$");
					if (Snake[0] == Fruit) {
						length++;
						Creat_Fruit();
						Score += 5;
					}
					Print_Score();
					for (int i = length - 1; i > 0; i--)
					{
						if (Snake[0] == Snake[i]) {
							GAME = GAMEOVER;
						}
					}
				}
				ct++;

			}
			break;
		}
		default:
			break;
		}
	}

}
void Menu() {

}
void Setting() {

}
void Ingame()
{
	Box_Game();
}

void Gameover() {
	system("cls");
	printf("BAN THUA ROI");
}
void Infor() {

}
void Box_Game() {
	for (int i = 0; i <= 20; i++)
	{
		for (int j = 0; j <= 100; j++)
		{
			if (i == 0 || i == 20) {
				printf("#");
			}

			else if (j == 100) {
				printf("#");
			}
			else printf(" ");

		}
		printf("\n");
	}

}
void gotoxy(int x, int y) {
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x,y };
	SetConsoleCursorPosition(h, c);
}
void Creat_Fruit() {
	srand(time(NULL));
	int Flag = 0;
	while (true)
	{
		Fruit = 10000 + ((1 + rand() % 20 - 1)) + (rand() % 99 * 100);
		for (int i = 0; i < length; i++)
		{
			if (Snake[i] == Fruit)
			{
				Flag++;
				break;
			}
		}
		if (Flag == false) break;
	}

}
void InitSnake() {
	length = 3;
	Snake[0] = 11010;
	Snake[1] = 11011;
	Snake[2] = 11012;


}
void Print_Score() {
	gotoxy(101, 10);
	printf("SCORE: %d", Score);
}
int GetY(int a) {
	return a % 100;
}
int GetX(int a) {
	return (a - 10000) / 100;
}