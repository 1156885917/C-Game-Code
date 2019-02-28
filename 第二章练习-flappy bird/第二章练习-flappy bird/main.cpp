#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int height, width;     //游戏画面大小
int bird_x, bird_y;    //小鸟的位置
int bar1_y, bar1_xDown, bar1_xTop;   //障碍物
int score = 0;             //得分，经过障碍物的个数

void gotoxy(int x, int y)    //将光标移动到（x,y）位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void startup()      //初始化
{
	height = 20;
	width = 50;
	bird_x = 0;
	bird_y = width / 3;
	bar1_y = width / 2;
	bar1_xTop = height / 3;
	bar1_xDown = height / 2;
}

void show()
{
	int i, j;
	gotoxy(0, 0);         //将光标移到原点
	for (i = 0;i < height;i++)
	{
		for (j = 0;j < width;j++)
		{
			if ((i == bird_x) && (j == bird_y))
			{
				printf("@");     //显示小鸟
			}
			else if (((i < bar1_xTop) || (i > bar1_xDown)) && (j == bar1_y))
			{
				printf("*");
			}
			else
			{
				printf(" ");     //输出空格
			}
		}
		printf("\n");
	}
	printf("得分：%d\n", score);
}

void UpdataWithInput()      //与用户输入有关的更新
{
	char input;
	if (kbhit())     //判断用户是否有输入
	{
		input = getch();   //通过判断用户的输入来控制小鸟的移动,不用输入回车
		if (input == ' ')
		{
			bird_x = bird_x - 2;
		}
	}
}

void UpdataWithoutInput()     //与用户输入无关的更新
{
	bird_x++;
	bar1_y--;

	if (bird_y == bar1_y)
	{
		if ((bird_x > bar1_xTop) && (bird_x < bar1_xDown))
		{
			score++;
		}
		else
		{
			printf("游戏失败\n");
			system("pause");
			exit(0);
		}
	}
	if (bar1_y <= 0)    //重新生成一个障碍物
	{
		bar1_y = width;
		int temp = rand() % (int)(height * 0.8);
		bar1_xTop = temp - height / 10;
		bar1_xDown = temp + height / 10;
	}
	Sleep(150);
}

int main()
{
	startup();                //数据初始化
	while(1)
	{
		show();               //显示画面
		UpdataWithInput();    //与用户输入有关的更新
		UpdataWithoutInput(); //与用户无关的更新
	}
	return 0;
}