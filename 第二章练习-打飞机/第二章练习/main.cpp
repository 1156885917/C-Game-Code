#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//ȫ�ֱ���
int plane_x, plane_y;            //�ɻ�λ��
int bullet_x, bullet_y;          //�ӵ�λ��
int enemy_x, enemy_y;            //�л�λ��
int height, width;               //��Ϸ����߶�
int score;                       //�÷�

void gotoxy(int x, int y)        //������ƶ�����x��y����
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};    //�ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()                   //���ݵĳ�ʼ��
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

	HideCursor();                //���ع��
}

void show()                      //��ʾ����
{
	//system("cls");               //��������
	gotoxy(0, 0);                  //����ƶ���ԭ��
	int i, j, k;

	for(i = 0;i < height;i++)
	{
		for (j = 0;j < width;j++)
		{
			if ((i == plane_x)&&(j == plane_y))
			{
				printf("*");     //����ɻ�
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
				printf("|");     //����ӵ�
			}
			else if ((i == enemy_x) && (j == enemy_y))
			{
				printf("@");     //����л�
			}
			else
			{
				printf(" ");     //����ո�
			}
		}
		printf("\n");
	}
	printf("�÷֣�%d\n",score);  //����÷�
}

void UpdataWithoutInput()        //���û������޹صĸ���
{
	if (bullet_x > -1)           //�ӵ�����
	{
		bullet_x--;
	}
	if ((bullet_x == enemy_x) && (bullet_y == enemy_y))   //�ӵ����ел�
	{
		score++;            //������һ
		enemy_x = -1;       //�����µĵл�
		enemy_y = rand() % width;
		bullet_x = -2;      //�ӵ���Ч
	}
	if (enemy_x > height)   //�л��ܳ���Ļ��ʾ
	{
		enemy_x = -1;       //�����µĵл�
		enemy_y = rand() % width;
	}

	//�������Ƶл������ƶ����ٶȣ�ÿ������ѭ�����ƶ�һ�εл�
	//�����޸ģ���Ȼ�û������Ľ����ٶȻ��Ǻܿ죬��NPC���ƶ���ʾ���Խ���
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

void UpdataWithInput()        //���û������йصĸ���
{
	char input;   
	if (kbhit())              //�ж��Ƿ�������
	{
		input = getch();      //�����û�����Ĳ�ͬ���ƶ������ûس�
		if (input == 'a')
		{
			plane_y--;     //λ������
		}
		if (input == 'd')
		{
			plane_y++;     //λ������
		}
		if (input == 's')
		{
			plane_x++;     //λ������
		}
		if (input == 'w')
		{
			plane_x--;     //λ������
		}
		if (input == ' ')     //�����ӵ�
		{
			bullet_x = plane_x - 1;  //�����ӵ��ĳ���λ���ڷɻ������Ϸ�
			bullet_y = plane_y;
		}
	}

}

int main()
{
	startup();                   //��Ϸ��ʼ��
	while(1)
	{
		show();                  //��ʾ����
		UpdataWithoutInput();    //���û������޹صĸ���
		UpdataWithInput();       //���û������йصĸ���
	}
	return 0;
}
