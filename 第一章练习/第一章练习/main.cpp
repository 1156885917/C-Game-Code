#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>


int main()
{
	int i, j;    
	int x = 5;
	int y = 10;
	char input;
	int isFire = 0;

	int ny = 5;         //将靶子放在第一排的第n列上
	int isKilled = 0;

	while(1)
	{
		system("cls");  //清屏函数

		if(!isKilled)   //输出靶子
		{
			for(j = 0;j < ny;j++)
			{
				printf(" ");
			}
			printf("+");
		}

		if(isFire == 0)   //输出飞机上面的空行
		{
			for(i = 0;i < x;i++)
			{
				printf("\n");
			}
		}
		else             //输出激光竖线
		{
			for(i = 0;i < x;i++)
			{
				for(j = 0;j < y;j++)
				{
					printf(" ");
				}
				printf("  |\n");
			}
			if(y + 2 == ny)   //判断是否击中靶子
			{
				isKilled = 1;
			}
			isFire = 0;
		}

		//显示飞机
		for(j = 0;j < y;j++)
		{
			printf(" ");
		}
		printf("  *\n");
		for(j = 0;j < y;j++)
		{
			printf(" ");
		}
		printf("*****\n");
		for(j = 0;j < y;j++)
		{
			printf(" ");
		}
		printf(" * * \n");

		printf("\n");
		Sleep(10);  //停顿10ms

		if(kbhit())
		{
			input = getch();  //根据用户不同的输入来移动，不用输入回车
			if(input == 'a')
				y--;          //左移
			if(input == 'd')
				y++;          //右移
			if(input == 'w')
				x--;          //上移
			if(input == 's')
				x++;          //下移
			if(input == ' ')  
				isFire = 1;   //发射
		}
	}
	return 0;
}

