#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define Height 25       //��Ϸ����ߴ�
#define Width 50

//ȫ�ֱ���
int cells[Height][Width];     //����ϸ����λ����1��0

void gotoxy(int x, int y)     //������ƶ�����x,y��λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCurcor()     //���ع��
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};     //�ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()       //���ݳ�ʼ��
{
	HideCurcor();    //���ع��
	int i, j;
	for (i = 0;i < Height;i++)    //�����ʼ��
	{
		for (j = 0;j < Width;j++)
		{
			cells[i][j] = rand() % 2;
		/*	cells[i][j] = 1;*/
		}
	}
}

void show()      //��ʾ����
{
	gotoxy(0, 0);       //������ƶ���ԭ��λ�ã������ػ�����
	int i, j;
	for (i = 1;i <= Height - 1;i++)
	{
		for (j = 1;j <= Width - 1;j++)
		{
			if (cells[i][j] == 1)
			{
				printf("*");     //������ϸ��
			} 
			else
			{
				printf(" ");     //����ո�
			}
		}
		printf("\n");
	}
	Sleep(50);
}

void UpdataWithoutInput()        //���û��޹صĸ���
{
	int NewCells[Height][Width];   //��һ֡��ϸ�����
	int NeibourNumber;             //ͳ���ھӵĸ���
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

void UpdataWithInput()           //���û��йصĸ���
{

}

int main()
{
	startup();                   //��ʼ��
	while(1)
	{
		show();                  //��ʾ����
		UpdataWithoutInput();    //���û�����޹صĸ���
		UpdataWithInput();       //���û��йصĸ���
	}
	return 0;
}

