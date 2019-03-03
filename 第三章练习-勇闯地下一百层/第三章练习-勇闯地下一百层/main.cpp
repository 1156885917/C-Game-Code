#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define Height 25     //定义画面尺寸
#define Width 40

//全局变量
int canvas[Height][Width];    //用数组来存储游戏画面中的元素
//1为小球，2为板，3为边界，4为上边界的锯齿
int i, j;
int radius;                         //板子的半径
int board_1, board_2, board_3;      //三块板子的中心
int interval_1, interval_2;         //小球下落的频率、板子上升的频率和板子出现的频率不相同就可以营造出小球随重力下落的感觉
int interval_static;      
int ball;                           //小球的位置
char input;
int judge;
int turn_1, turn_2;
int score;                          //记录分数
char ch;

void gotoxy(int x, int y)           //将光标移动到（x,y）处
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()                   //隐藏光标
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO console_info = {1, 0};       //第二个值为0表示隐藏光标
	SetConsoleCursorInfo(handle, &console_info);
}

void startup()                      //数据初始化
{
	HideCursor();                   //隐藏光标
	srand(time(NULL));
	radius = 2;
	turn_1 = 1;
	turn_2 = 4;
	interval_1 = 0;
	interval_2 = 0;
	interval_static = 64;
	ball = Width / 2;
	score = 0;

	for (i = 0;i < Height;i++)
	{
		for (j = 0;j < Width;j++)
		{
			if (j == 0)
			{
				canvas[i][j] = 3;     //输出左边界
			}
			if (j == Width - 1)
			{
				canvas[i][j] = 3;     //输出右边界
			}
			if (i == 0 && j != 0 && j != Width - 1)
			{
				canvas[i][j] = 4;     //输出上边界的锯齿
			}
			if (i == Height - 1 && j > (Width / 2 - 3) && j < (Width / 2 + 3))
			{
				canvas[i][j] = 2;     //输出挡板
			}
			if (i == Height - 2 && j == ball)     //小球坐标赋值
			{
				canvas[i][j] = 1;    //输出小球
			}
		}
	}
}

void show()         //显示画面
{
	gotoxy(0, 0);     //将光标移到原点，以下重新画屏
	for (i = 0;i < Height + 1;i++)
	{
		for (j = 0;j < Width;j++)
		{
			if (i == Height)
			{
				printf("score:%d",score);    //输出分数
				break;
			}
			if (canvas[i][j] == 1)
			{
				printf("O");      //输出小球
			}
			else if (canvas[i][j] == 2)
			{
				printf("_");      //输出挡板
			}
			else if (canvas[i][j] == 3)
			{
				printf("|");      //输出左右边界
			}
			else if (canvas[i][j] == 4)
			{
				printf("T");      //输出上面的锯齿
			}
			else if (canvas[i][j] == 0)
			{
				printf(" ");      //输出空格   
			}
		}
		printf("\n");
	}
}

void UpdataWithoutInput()         //与用户输入无关的更新
{
	judge = 0;
	srand(time(NULL));
	if (score >= 10 && turn_1 == 1 && turn_2 == 4)
	{
		interval_1 = 0;
		interval_2 = 0;
		turn_1 = 2;
		turn_2 = 8;
	}
	if (score >=25 && turn_1 == 2 && turn_2 == 8)
	{
		interval_1 = 0;
		interval_2 = 0;
		turn_1 = 4;
		turn_2 = 16;
	}
	for (i = 0;i < Height;i++)
	{
		for (j = 0;j < Width;j++)
		{
			if (canvas[i][j] == 1 && ((i == 1) || (i == Height - 1)))
			{
				system("cls");
				printf("game over!\n");
				exit(0);
			}
		}
	}
	if (interval_2 == interval_static)
	{
		interval_2 = 0;      //计时器清零
		for (i = 0;i < Height;i++)
		{
			for (j = 0;j < Width;j++)
			{
				if (canvas[i][j] == 1 && canvas[i + 1][j] == 2)    //小球随板子上升
				{
					canvas[i][j] = 0;
					canvas[i - 1][j] = 1;
				}
				else if (canvas[i][j] == 2 && i > 1)     //板子上升
				{
					canvas[i - 1][j] = 2;
					canvas[i][j] = 0;
				}
				else if (canvas[i][j] == 2 && i == 1)
				{
					canvas[i][j] = 0;
				}
			}
		}
	}
	else
	{
		interval_2 += turn_2;
	}
	for (i = 0;i < Height;i++)
	{
		for (j = 0;j < Width;j++)
		{
			if (canvas[i][j] == 1 && canvas[i + 1][j] == 0)    //如果小球下面是空格，则小球下落
			{
				score++;       //小球每下落一个空格，分数加1
				canvas[i][j] = 0;
				canvas[i + 1][j] = 1;
				judge = 1;
			}
		}
		if (judge)
		{
			break;
		}
	}

	if (interval_1 == interval_static)      //每隔一段时间，重新出现三块板子
	{
		interval_1 = 0;
		board_1 = rand() % 13;
		board_2 = rand() % 13 + 13;
		board_3 = rand() % 13 + 24;

		for (i = 0;i < Height;i++)
		{
			for (j = 0;j < Width;j++)
			{
				if (i == Height - 1 && ((j >= (board_1 - radius) && (j <= (board_1 + radius)) || j >= (board_2 - radius) && (j <= (board_2 + radius)) || j >= (board_3 - radius) && (j <= (board_3 + radius)))))
				{
					canvas[i][j] = 2;
				}
			}
		}
	}
	else
	{
		interval_1 += turn_1;
	}
}

void UpdataWithInput()       //与用户输入有关的更新
{
	if (kbhit())             //判断用户是否输入
	{
		input = getch();     //根据用户的输入来控制小球的移动
		if (input == 'a')
		{
			for (i = 0;i < Height;i++)
			{
				for (j = 0;j < Width;j++)
				{
					if (canvas[i][j] == 1)   
					{
						canvas[i][j] = 0;    //小球左移
						canvas[i][j - 1] = 1;
						break;              //如果不加break，那么循环会将1以后的都变为0
					}
				}
			}
		}
		if (input == 'd')
		{
			for (i = 0;i < Height;i++)
			{
				for (j = 0;j < Width;j++)
				{
					if (canvas[i][j] == 1)   
					{
						canvas[i][j] = 0;    //小球右移
						canvas[i][j + 1] = 1;
						break;
					}
				}
			}
		}
	}

}


int main()
{
	startup();          //初始化
	printf("温馨提示：\na：向左\nd：向右\n游戏难度会随着分数的增加而增加\n按回车键继续\n");
	scanf("%c",&ch);
	while (1)
	{
		show();         //显示画面
		UpdataWithoutInput();    //与用户输入无关的更新
		UpdataWithInput();       //与用户有关的更新
	}
}