#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define Height 25       //游戏画面尺寸
#define Width 50

//全局变量
int cells[Height][Width];     //所有细胞的位置生1死0

void gotoxy(int x, int y)     //将光标移动到（x,y）位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCurcor()     //隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};     //第二个值为0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()       //数据初始化
{
	HideCurcor();    //隐藏光标
	int i, j;
	for (i = 0;i < Height;i++)    //随机初始化
	{
		for (j = 0;j < Width;j++)
		{
			cells[i][j] = rand() % 2;
		/*	cells[i][j] = 1;*/
		}
	}
}

void show()      //显示画面
{
	gotoxy(0, 0);       //将光标移动到原点位置，以下重画清屏
	int i, j;
	for (i = 1;i <= Height - 1;i++)
	{
		for (j = 1;j <= Width - 1;j++)
		{
			if (cells[i][j] == 1)
			{
				printf("*");     //输出活的细胞
			} 
			else
			{
				printf(" ");     //输出空格
			}
		}
		printf("\n");
	}
	Sleep(50);
}

void UpdataWithoutInput()        //与用户无关的更新
{
	int NewCells[Height][Width];   //下一帧的细胞情况
	int NeibourNumber;             //统计邻居的个数
	int i, j;
	for (i = 1;i <= Height - 1;i++)
	{
		for (j = 1;j <= Width - 1;j++)
		{
			NeibourNumber = cells[i-1][j-1] + cells[i-1][j] + cells[i-1][j+1] + cells[i][j-1] + cells[i][j+1]
			+ cells[i+1][j-1] + cells[i+1][j] + cells[i+1][j+1];
			if (NeibourNumber == 3)
			{
				NewCells[i][j] = 1;
			}
			else if (NeibourNumber == 2)
			{
				NewCells[i][j] = cells[i][j];
			}
			else
			{
				NewCells[i][j] = 0;
			}
		}
	}
	for (i = 1;i <= Height - 1;i++)
	{
		for (j = 1;j <= Width - 1;j++)
		{
			cells[i][j] = NewCells[i][j];
		}
	}
}

void UpdataWithInput()           //与用户有关的更新
{

}

int main()
{
	startup();                   //初始化
	while(1)
	{
		show();                  //显示画面
		UpdataWithoutInput();    //与用户输出无关的更新
		UpdataWithInput();       //与用户有关的更新
	}
	return 0;
}

