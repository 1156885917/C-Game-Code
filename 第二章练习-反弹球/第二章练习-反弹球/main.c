#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//全局变量
int height, width;           //游戏画面大小
int ball_x, ball_y;          //小球的坐标
int ball_vx, ball_vy;        //小球的速度
int position_x, position_y;  //挡板中心的位置
int ridus;                   //挡板的半径
int left, right;             //挡板的左右位置
int ball_number;             //反弹小球的次数
int block_x, block_y;        //消掉砖块的位置
int score;                   //消掉砖块的个数

void gotoxy(int x, int y)     //将光标移动到（x,y）处
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void startup()          //数据的初始化
{
	height = 13;
	width = 17;
	ball_x = 0;
	ball_y = width / 2;
	ball_vx = 1;
	ball_vy = 1;
	ridus = 6;
	position_x = height;
	position_y = width / 2;
	left = position_y - ridus;
	right = position_y + ridus;
	ball_number = 0;
	block_x = 0;
	block_y = width / 2 + 1;
	score = 0;
}

void show()             //显示画面
{
	int i, j;
    gotoxy(0, 0);     //光标移动到原点位置，以下重新画屏
	
	for (i = 0;i <= height + 1;i++)
	{
		for (j = 0;j <= width;j++)
		{
			if ((i == ball_x) && (j == ball_y))
			{
				printf("0");      //输出小球
			}
			else if (j == width)
			{
				printf("|");      //输出右边框
			}
			else if (i == height + 1)
			{
				printf("-");      //输出下边框
			}
			else if ((i == height) && (j > left) && (j < right))
			{
				printf("*");      //输出挡板；
			}
			else if ((i == block_x) && (j == block_y))
			{
				printf("B");      //输出砖块
			}
			else
			{
				printf(" ");      //输出空格
			}
		}
		printf("\n");
	}
	printf("反弹小球数：%d\n", ball_number);
	printf("反弹的砖块数：%d\n", score);
}

void UpdataWithoutInput()         //与用户输入无关的更新
{
	if (ball_x == height - 1)
	{
		if ((ball_y >= left) && (ball_y <= right))   //被挡板挡住
		{
			ball_number++;
			printf("\a");         //响铃
		}
		else                                         //没被挡板挡住
		{
			printf("游戏失败\n");
			system("pause");
			exit(0);
		}
	}

	if ((ball_x == block_x) && (ball_y == block_y))  //小球击中砖块
	{
		score++;                        //分数加一
		block_y = rand() % width;       //产生新的砖块
	}

	ball_x = ball_x + ball_vx;
	ball_y = ball_y + ball_vy;

	if ((ball_x == 0) || (ball_x == height - 1))
	{
		ball_vx = -ball_vx;
	}
	if ((ball_y == 0) || (ball_y == width - 1))
	{
		ball_vy = -ball_vy;
	}
	Sleep(80);
}

void UpdataWithInput()        //与用户输入有关的更新
{
	if (kbhit())              //判断用户是否有输入
	{
		char input;
		input = getch();      //根据用户不同的输入来控制移动
		if (input == 'a')
		{
			position_y--;     //位置左移
			left = position_y - ridus;
			right = position_y + ridus;
		}
		if (input == 'd')
		{
			position_y++;     //位置右移
			left = position_y - ridus;
			right = position_y + ridus;
		}
	}

}

int main()
{
	startup();                //初始化
	while (1)
	{
		show();               //显示画面
		UpdataWithInput();    //与用户输入有关的更新
		UpdataWithoutInput(); //与用户输入无关的更新
	}
	return 0;
}