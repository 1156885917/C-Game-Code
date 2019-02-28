#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int height, width;     //��Ϸ�����С
int bird_x, bird_y;    //С���λ��
int bar1_y, bar1_xDown, bar1_xTop;   //�ϰ���
int score = 0;             //�÷֣������ϰ���ĸ���

void gotoxy(int x, int y)    //������ƶ�����x,y��λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void startup()      //��ʼ��
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
	gotoxy(0, 0);         //������Ƶ�ԭ��
	for (i = 0;i < height;i++)
	{
		for (j = 0;j < width;j++)
		{
			if ((i == bird_x) && (j == bird_y))
			{
				printf("@");     //��ʾС��
			}
			else if (((i < bar1_xTop) || (i > bar1_xDown)) && (j == bar1_y))
			{
				printf("*");
			}
			else
			{
				printf(" ");     //����ո�
			}
		}
		printf("\n");
	}
	printf("�÷֣�%d\n", score);
}

void UpdataWithInput()      //���û������йصĸ���
{
	char input;
	if (kbhit())     //�ж��û��Ƿ�������
	{
		input = getch();   //ͨ���ж��û�������������С����ƶ�,��������س�
		if (input == ' ')
		{
			bird_x = bird_x - 2;
		}
	}
}

void UpdataWithoutInput()     //���û������޹صĸ���
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
			printf("��Ϸʧ��\n");
			system("pause");
			exit(0);
		}
	}
	if (bar1_y <= 0)    //��������һ���ϰ���
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
	startup();                //���ݳ�ʼ��
	while(1)
	{
		show();               //��ʾ����
		UpdataWithInput();    //���û������йصĸ���
		UpdataWithoutInput(); //���û��޹صĸ���
	}
	return 0;
}