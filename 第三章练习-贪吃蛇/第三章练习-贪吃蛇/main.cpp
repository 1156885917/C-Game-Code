#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Height 20    //定义游戏画面尺寸
#define Width 30

//全局变量
int moveDirection;                   //小蛇移动的方向，上、下、左、右分别用1、2、3、4表示
int food_x, food_y;                  //食物的位置
int canvas[Height][Width] = {0};      //二维数组用来存储游戏中画布中对应的元素
                                      //0为空格，-1为边框#，-2为食物，1为舌头@，大于1的正数为蛇身*
void gotoxy(int x, int y)            //将光标移动到点（x,y）处
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()        //隐藏光标
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO console_info = {1, 0};    //第二个值为0表示隐藏光标
	SetConsoleCursorInfo(handle, &console_info);
}

//移动小蛇
//第一步扫描数组中的元素，找到其中的正数元素都加1
//找到最大元素（即蛇尾），把其变成0
//找到等于2的元素（即蛇头），根据输出的上下左右方向把对应的另一个像素值设置为1（新蛇头）
void moveSnackByDerection()
{
	int i, j;
	for (i = 1;i < Height - 1;i++)
	{
		for (j = 1;j < Width - 1;j++)
		{
			if (canvas[i][j] > 0)
			{
				canvas[i][j]++;
			}
		}
	}

	int oldTail_x, oldTail_y, oldHead_x, oldHead_y;
	int max = 0;
	for (i = 1;i < Height - 1;i++)
	{
		for (j = 1;j < Width - 1;j++)
		{
			if (canvas[i][j] > 0)
			{
				if (max < canvas[i][j])
				{
					max = canvas[i][j];
					oldTail_x = i;
					oldTail_y = j;
				}
				if (canvas[i][j] == 2)
				{
					oldHead_x = i;
					oldHead_y = j;
				}
			}
		}
	}

	int newHead_x, newHead_y;
	if (moveDirection == 1)    //向上移动
	{
		newHead_x = oldHead_x - 1;
		newHead_y = oldHead_y;
	}
	if (moveDirection == 2)    //向下移动
	{
		newHead_x = oldHead_x + 1;
		newHead_y = oldHead_y;
	}
	if (moveDirection == 3)    //向左移动
	{
		newHead_x = oldHead_x;
		newHead_y = oldHead_y - 1;
	}
	if (moveDirection == 4)    //向右移动
	{
		newHead_x = oldHead_x;
		newHead_y = oldHead_y + 1;
	}

	//如果小蛇吃到食物,原来的旧蛇尾留着，长度自动加1
	if (canvas[newHead_x][newHead_y] == -2)
	{
		canvas[food_x][food_y] = 0;
		//产生一个新食物
		food_x = rand() % (Height - 5) + 2;
		food_y = rand() % (Width - 5) + 2;
		canvas[food_x][food_y] = -2;
	}
	else    //否则原来的旧蛇尾减掉，保持长度不变
	{
		canvas[oldTail_x][oldTail_y] = 0;
	}


	//小蛇是否和自身或者边框撞，游戏失败
	if (canvas[newHead_x][newHead_y] > 0 || canvas[newHead_x][newHead_y] == -1)
	{
		printf("游戏失败！\n");
		Sleep(1000);
		system("pause");
		exit(0);
	} 
	else
	{
		canvas[newHead_x][newHead_y] = 1;
	}
}

void startup()         //数据的初始化
{
	HideCursor();      //隐藏光标
	int i, j;
	//初始化边框
	for (i = 0;i < Height;i++)
	{
		canvas[i][0] = -1;
		canvas[i][Width - 1] = -1;
	}
	for (j = 0;j < Width;j++)
	{
		canvas[0][j] = -1;
		canvas[Height - 1][j] = -1;
	}

	//初始化蛇头位置
	canvas[Height / 2][Width / 2] = 1;
	//初始化蛇身，画布中的元素值分别为2，3，4，5等
	for (i = 1;i <= 4;i++)
	{
		canvas[Height / 2][Width / 2 - i] = i + 1;
	}

	//初始小蛇向右移动
	moveDirection = 4;

	food_x = rand() % (Height - 5) + 2;
	food_y = rand() % (Width - 5) + 2;
	canvas[food_x][food_y] = -2;
}

void show()      //显示画面
{
	gotoxy(0, 0);        //将光标移动到原点，以下重新画屏
	int i, j;
	for (i = 0;i < Height;i++)
	{
		for (j = 0;j < Width;j++)
		{
			if (canvas[i][j] == -1)
			{
				printf("#");       //输出边框#
			}
			if (canvas[i][j] == 0)
			{
				printf(" ");       //输出空格
			}
			if (canvas[i][j] == 1)
			{
				printf("@");       //输出蛇头@
			}
			if (canvas[i][j] > 1)
			{
				printf("*");       //输出蛇身*
			}
			if (canvas[i][j] == -2)
			{
				printf("F");       //输出食物F
			}
		}
		printf("\n");
	}
	Sleep(100);
}

void UpdataWithoutInput()          //与用户输入无关的更新
{
	moveSnackByDerection();
}

void UpdataWithInput()             //与用户输入有关的更新
{
	char input;
	if (kbhit())                   //判断用户是否有输入
	{
		input = getch();           //根据用户的不同输入来控制小蛇的移动
		if (input == 'w')
		{
			moveDirection = 1;  //向上移动
			moveSnackByDerection();
		}
		if (input == 's')
		{
			moveDirection = 2;  //向下移动
			moveSnackByDerection();
		}
		if (input == 'a')
		{
			moveDirection = 3;  //向左移动
			moveSnackByDerection();
		}
		if (input == 'd')
		{
			moveDirection = 4;  //向右移动
			moveSnackByDerection();
		}
	}
}

int main()
{
	startup();          //初始化
	while (1)
	{
		show();         //显示画面
		UpdataWithoutInput();    //与用户输入有关的更新
		UpdataWithInput();       //与用户输入有关的更新
	}
	return 0;
}
