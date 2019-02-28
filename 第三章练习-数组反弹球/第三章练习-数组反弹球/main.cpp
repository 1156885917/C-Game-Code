#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Height 15   //��Ϸ����ߴ�
#define Width 20

//ȫ�ֱ���
int ball_x, ball_y;     //С���λ��
int ball_vx, ball_vy;  //С����ٶ�
int position_x, position_y;   //�������������
int ridus;                    //����İ뾶��С
int left, right;              //���������λ��
int canvas[Height][Width] = {0};    //��λ�������������Ϸ�����ж�Ӧ��Ԫ�أ�0Ϊ�ո�1ΪС��2Ϊ����*,3Ϊש��#

void gotoxy(int x, int y)     //������ƶ���ԭ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()      //���ع��
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};     //�ڶ���Ϊ0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup()     //��ʼ��
{
	HideCursor();    //���ع��
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

	for (i = 0;i < Height / 4;i++)    //��ʾ����ש��
	{
		for (k = 0;k < Width;k++)
		{
			canvas[i][k] = 3;
		}
	}
}

void show()        //��ʾ����
{
	int i, j;
	gotoxy(0, 0);      //������ƶ���ԭ�㣬�������»���
	for (i = 0;i < Height;i++)
	{
		for (j = 0;j < Width;j++)
		{
			if (canvas[i][j] == 0)
			{
				printf(" ");     //����ո�
			} 
			else if(canvas[i][j] == 1)
			{
				printf("0");     //���С��
			}
			else if (canvas[i][j] == 2)
			{
				printf("*");     //�������
			}
			else if (canvas[i][j] = 3)
			{
				printf("#");     //���ש��
			}
		}
		printf("|\n");           //����ұ߽�
	}
	for (j=0;j<Width;j++)
	{
		printf("-");             //����±߽�
	}
}

void UpdataWithoutInput()        //���û������޹صĸ���
{
	if (ball_x == Height - 2)
	{
		if ((ball_y >= left) && (ball_y <= right))   //�����嵲ס
		{
			printf("\a");        //����
		}
		else                                         //û�б����嵲ס
		{
			printf("��Ϸʧ��\n");
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
		//����С�������
		ball_x = ball_x + ball_vx;
		ball_y = ball_y + ball_vy;
		canvas[ball_x][ball_y] = 1;

		//�����߽�󷴵�
		if ((ball_x == 0) || (ball_x == Height - 2))
		{
			ball_vx = -ball_vx;
		}
		if ((ball_y == 0) || (ball_y == Width - 1))
		{
			ball_vy = -ball_vy;
		}

		//����ש��󷴵�
		if (canvas[ball_x - 1][ball_y] == 3)  
		{
			ball_vx = -ball_vx;
			canvas[ball_x - 1][ball_y] = 0;
			printf("\a");
		}

	}
}

void UpdataWithInput()       //���û������йصĸ���
{
	char input;
	if (kbhit())             //�ж��û���û������
	{
		input = getch();     //�����û������������Ƶ�����ƶ�
		if (input == 'a' && left > 0)
		{
			canvas[position_x][right] = 0;
			position_y--;    //��������
			left = position_y - ridus;
			right = position_y + ridus;
			canvas[position_x][left] = 2;
		}
		if (input == 'd' && right <Width - 1)
		{
			canvas[position_x][left] = 0;
			position_y++;    //��������
			left = position_y - ridus;
			right = position_y + ridus;
			canvas[position_x][right] = 2;
		}
	}
}


int main()
{
	startup();      //��ʼ��
	while(1)
	{
		show();                 //��ʾ����
		UpdataWithoutInput();   //���û������޹صظ���
		UpdataWithInput();      //���û��йصĸ���
	}
	return 0;
}