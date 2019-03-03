#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define Height 25     //���廭��ߴ�
#define Width 40

//ȫ�ֱ���
int canvas[Height][Width];    //���������洢��Ϸ�����е�Ԫ��
//1ΪС��2Ϊ�壬3Ϊ�߽磬4Ϊ�ϱ߽�ľ��
int i, j;
int radius;                         //���ӵİ뾶
int board_1, board_2, board_3;      //������ӵ�����
int interval_1, interval_2;         //С�������Ƶ�ʡ�����������Ƶ�ʺͰ��ӳ��ֵ�Ƶ�ʲ���ͬ�Ϳ���Ӫ���С������������ĸо�
int interval_static;      
int ball;                           //С���λ��
char input;
int judge;
int turn_1, turn_2;
int score;                          //��¼����
char ch;

void gotoxy(int x, int y)           //������ƶ�����x,y����
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()                   //���ع��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO console_info = {1, 0};       //�ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(handle, &console_info);
}

void startup()                      //���ݳ�ʼ��
{
	HideCursor();                   //���ع��
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
				canvas[i][j] = 3;     //�����߽�
			}
			if (j == Width - 1)
			{
				canvas[i][j] = 3;     //����ұ߽�
			}
			if (i == 0 && j != 0 && j != Width - 1)
			{
				canvas[i][j] = 4;     //����ϱ߽�ľ��
			}
			if (i == Height - 1 && j > (Width / 2 - 3) && j < (Width / 2 + 3))
			{
				canvas[i][j] = 2;     //�������
			}
			if (i == Height - 2 && j == ball)     //С�����긳ֵ
			{
				canvas[i][j] = 1;    //���С��
			}
		}
	}
}

void show()         //��ʾ����
{
	gotoxy(0, 0);     //������Ƶ�ԭ�㣬�������»���
	for (i = 0;i < Height + 1;i++)
	{
		for (j = 0;j < Width;j++)
		{
			if (i == Height)
			{
				printf("score:%d",score);    //�������
				break;
			}
			if (canvas[i][j] == 1)
			{
				printf("O");      //���С��
			}
			else if (canvas[i][j] == 2)
			{
				printf("_");      //�������
			}
			else if (canvas[i][j] == 3)
			{
				printf("|");      //������ұ߽�
			}
			else if (canvas[i][j] == 4)
			{
				printf("T");      //�������ľ��
			}
			else if (canvas[i][j] == 0)
			{
				printf(" ");      //����ո�   
			}
		}
		printf("\n");
	}
}

void UpdataWithoutInput()         //���û������޹صĸ���
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
		interval_2 = 0;      //��ʱ������
		for (i = 0;i < Height;i++)
		{
			for (j = 0;j < Width;j++)
			{
				if (canvas[i][j] == 1 && canvas[i + 1][j] == 2)    //С�����������
				{
					canvas[i][j] = 0;
					canvas[i - 1][j] = 1;
				}
				else if (canvas[i][j] == 2 && i > 1)     //��������
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
			if (canvas[i][j] == 1 && canvas[i + 1][j] == 0)    //���С�������ǿո���С������
			{
				score++;       //С��ÿ����һ���ո񣬷�����1
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

	if (interval_1 == interval_static)      //ÿ��һ��ʱ�䣬���³����������
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

void UpdataWithInput()       //���û������йصĸ���
{
	if (kbhit())             //�ж��û��Ƿ�����
	{
		input = getch();     //�����û�������������С����ƶ�
		if (input == 'a')
		{
			for (i = 0;i < Height;i++)
			{
				for (j = 0;j < Width;j++)
				{
					if (canvas[i][j] == 1)   
					{
						canvas[i][j] = 0;    //С������
						canvas[i][j - 1] = 1;
						break;              //�������break����ôѭ���Ὣ1�Ժ�Ķ���Ϊ0
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
						canvas[i][j] = 0;    //С������
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
	startup();          //��ʼ��
	printf("��ܰ��ʾ��\na������\nd������\n��Ϸ�ѶȻ����ŷ��������Ӷ�����\n���س�������\n");
	scanf("%c",&ch);
	while (1)
	{
		show();         //��ʾ����
		UpdataWithoutInput();    //���û������޹صĸ���
		UpdataWithInput();       //���û��йصĸ���
	}
}