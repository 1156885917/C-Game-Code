#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//全局变量
int plane_x, plane_y;            //飞机位置
int bullet_x, bullet_y;          //子弹位置
int enemy_x, enemy_y;            //敌机位置
int height, width;               //游戏画面尺度
int score;                       //得分

void gotoxy(int x, int y)        //将光标移动到（x，y）处
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};    //第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()                   //数据的初始化
{
	height = 20;
	width = 30;
	plane_x = height / 2;
	plane_y = width / 2;
	bullet_x = -2;
	bullet_y = plane_y;
	enemy_x = 0;
	enemy_y = plane_y;
	score = 0;

	HideCursor();                //隐藏光标
}

void show()                      //显示画面
{
	//system("cls");               //清屏函数
	gotoxy(0, 0);                  //光标移动到原点
	int i, j, k;

	for(i = 0;i < height;i++)
	{
		for (j = 0;j < width;j++)
		{
			if ((i == plane_x)&&(j == plane_y))
			{
				printf("*");     //输出飞机
			}
			else if ((i == plane_x + 1) && (j == plane_y - 2))
			{
				printf("*****");
				j+=5;
			}
			else if ((i == plane_x + 2) && (j == plane_y - 2))
			{
				printf(" * * ");
				j+=5;
			}
			else if ((i == bullet_x) && (j == bullet_y))
			{
				printf("|");     //输出子弹
			}
			else if ((i == enemy_x) && (j == enemy_y))
			{
				printf("@");     //输出敌机
			}
			else
			{
				printf(" ");     //输出空格
			}
		}
		printf("\n");
	}
	printf("得分：%d\n",score);  //输出得分
}

void UpdataWithoutInput()        //与用户输入无关的更新
{
	if (bullet_x > -1)           //子弹上移
	{
		bullet_x--;
	}
	if ((bullet_x == enemy_x) && (bullet_y == enemy_y))   //子弹击中敌机
	{
		score++;            //分数加一
		enemy_x = -1;       //产生新的敌机
		enemy_y = rand() % width;
		bullet_x = -2;      //子弹无效
	}
	if (enemy_x > height)   //敌机跑出屏幕显示
	{
		enemy_x = -1;       //产生新的敌机
		enemy_y = rand() % width;
	}

	//用来控制敌机向下移动的速度，每隔几次循环才移动一次敌机
	//这样修改，虽然用户按键的交互速度还是很快，但NPC的移动显示可以降速
	static int speed = 0;
	if (speed < 10)
	{
		speed++;
	}
	if (speed == 10)
	{
		enemy_x++;
		speed = 0;
	}

}

void UpdataWithInput()        //与用户输入有关的更新
{
	char input;   
	if (kbhit())              //判断是否有输入
	{
		input = getch();      //根据用户输入的不同来移动，不用回车
		if (input == 'a')
		{
			plane_y--;     //位置左移
		}
		if (input == 'd')
		{
			plane_y++;     //位置右移
		}
		if (input == 's')
		{
			plane_x++;     //位置下移
		}
		if (input == 'w')
		{
			plane_x--;     //位置上移
		}
		if (input == ' ')     //发射子弹
		{
			bullet_x = plane_x - 1;  //发射子弹的初试位置在飞机的正上方
			bullet_y = plane_y;
		}
	}

}

int main()
{
	startup();                   //游戏初始化
	while(1)
	{
		show();                  //显示画面
		UpdataWithoutInput();    //与用户输入无关的更新
		UpdataWithInput();       //与用户输入有关的更新
	}
	return 0;
}
