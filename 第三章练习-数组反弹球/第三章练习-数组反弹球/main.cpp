#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Height 15   //游戏画面尺寸
#define Width 20

//全局变量
int ball_x, ball_y;     //小球的位置
int ball_vx, ball_vy;  //小球的速度
int position_x, position_y;   //挡板的中心坐标
int ridus;                    //挡板的半径大小
int left, right;              //挡板的左右位置
int canvas[Height][Width] = {0};    //二位数组用来存放游戏画布中对应的元素，0为空格，1为小球，2为挡板*,3为砖块#

void gotoxy(int x, int y)     //将光标移动到原点
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()      //隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};     //第二个为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()     //初始化
{
	HideCursor();    //隐藏光标
	ridus = 5;
	position_x = Height - 1;
	position_y = Width / 2;
	left = position_y - ridus;
	right = position_y + ridus;

	ball_x = position_x - 1;
	ball_y = position_y;
	ball_vx = -1;
	ball_vy = 1;
	canvas[ball_x][ball_y] = 1;

	int k, i;
	for (k = left;k <= right;k++)
	{
		canvas[position_x][k] = 2;
	}

	for (i = 0;i < Height / 4;i++)    //显示几排砖块
	{
		for (k = 0;k < Width;k++)
		{
			canvas[i][k] = 3;
		}
	}
}

void show()        //显示画面
{
	int i, j;
	gotoxy(0, 0);      //将光标移动到原点，以下重新画屏
	for (i = 0;i < Height;i++)
	{
		for (j = 0;j < Width;j++)
		{
			if (canvas[i][j] == 0)
			{
				printf(" ");     //输出空格
			} 
			else if(canvas[i][j] == 1)
			{
				printf("0");     //输出小球
			}
			else if (canvas[i][j] == 2)
			{
				printf("*");     //输出挡板
			}
			else if (canvas[i][j] = 3)
			{
				printf("#");     //输出砖块
			}
		}
		printf("|\n");           //输出右边界
	}
	for (j=0;j<Width;j++)
	{
		printf("-");             //输出下边界
	}
}

void UpdataWithoutInput()        //与用户输入无关的更新
{
	if (ball_x == Height - 2)
	{
		if ((ball_y >= left) && (ball_y <= right))   //被挡板挡住
		{
			printf("\a");        //响铃
		}
		else                                         //没有被挡板挡住
		{
			printf("游戏失败\n");
			system("pause");
			exit(0);
		}
	}

	static int speed = 0;
	if (speed < 7)
	{
		speed++;
	}
	if (speed == 7)
	{
		speed = 0;

		canvas[ball_x][ball_y] = 0;
		//更新小球的坐标
		ball_x = ball_x + ball_vx;
		ball_y = ball_y + ball_vy;
		canvas[ball_x][ball_y] = 1;

		//碰到边界后反弹
		if ((ball_x == 0) || (ball_x == Height - 2))
		{
			ball_vx = -ball_vx;
		}
		if ((ball_y == 0) || (ball_y == Width - 1))
		{
			ball_vy = -ball_vy;
		}

		//碰到砖块后反弹
		if (canvas[ball_x - 1][ball_y] == 3)  
		{
			ball_vx = -ball_vx;
			canvas[ball_x - 1][ball_y] = 0;
			printf("\a");
		}

	}
}

void UpdataWithInput()       //与用户输入有关的更新
{
	char input;
	if (kbhit())             //判断用户有没有输入
	{
		input = getch();     //根据用户的输入来控制挡板的移动
		if (input == 'a' && left > 0)
		{
			canvas[position_x][right] = 0;
			position_y--;    //挡板左移
			left = position_y - ridus;
			right = position_y + ridus;
			canvas[position_x][left] = 2;
		}
		if (input == 'd' && right <Width - 1)
		{
			canvas[position_x][left] = 0;
			position_y++;    //挡板右移
			left = position_y - ridus;
			right = position_y + ridus;
			canvas[position_x][right] = 2;
		}
	}
}


int main()
{
	startup();      //初始化
	while(1)
	{
		show();                 //显示画面
		UpdataWithoutInput();   //与用户输入无关地更新
		UpdataWithInput();      //与用户有关的更新
	}
	return 0;
}