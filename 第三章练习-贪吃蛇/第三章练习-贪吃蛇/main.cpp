#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Height 20    //������Ϸ����ߴ�
#define Width 30

//ȫ�ֱ���
int moveDirection;                   //С���ƶ��ķ����ϡ��¡����ҷֱ���1��2��3��4��ʾ
int food_x, food_y;                  //ʳ���λ��
int canvas[Height][Width] = {0};      //��ά���������洢��Ϸ�л����ж�Ӧ��Ԫ��
                                      //0Ϊ�ո�-1Ϊ�߿�#��-2Ϊʳ�1Ϊ��ͷ@������1������Ϊ����*
void gotoxy(int x, int y)            //������ƶ����㣨x,y����
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor()        //���ع��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO console_info = {1, 0};    //�ڶ���ֵΪ0��ʾ���ع��
	SetConsoleCursorInfo(handle, &console_info);
}

//�ƶ�С��
//��һ��ɨ�������е�Ԫ�أ��ҵ����е�����Ԫ�ض���1
//�ҵ����Ԫ�أ�����β����������0
//�ҵ�����2��Ԫ�أ�����ͷ��������������������ҷ���Ѷ�Ӧ����һ������ֵ����Ϊ1������ͷ��
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
	if (moveDirection == 1)    //�����ƶ�
	{
		newHead_x = oldHead_x - 1;
		newHead_y = oldHead_y;
	}
	if (moveDirection == 2)    //�����ƶ�
	{
		newHead_x = oldHead_x + 1;
		newHead_y = oldHead_y;
	}
	if (moveDirection == 3)    //�����ƶ�
	{
		newHead_x = oldHead_x;
		newHead_y = oldHead_y - 1;
	}
	if (moveDirection == 4)    //�����ƶ�
	{
		newHead_x = oldHead_x;
		newHead_y = oldHead_y + 1;
	}

	//���С�߳Ե�ʳ��,ԭ���ľ���β���ţ������Զ���1
	if (canvas[newHead_x][newHead_y] == -2)
	{
		canvas[food_x][food_y] = 0;
		//����һ����ʳ��
		food_x = rand() % (Height - 5) + 2;
		food_y = rand() % (Width - 5) + 2;
		canvas[food_x][food_y] = -2;
	}
	else    //����ԭ���ľ���β���������ֳ��Ȳ���
	{
		canvas[oldTail_x][oldTail_y] = 0;
	}


	//С���Ƿ��������߱߿�ײ����Ϸʧ��
	if (canvas[newHead_x][newHead_y] > 0 || canvas[newHead_x][newHead_y] == -1)
	{
		printf("��Ϸʧ�ܣ�\n");
		Sleep(1000);
		system("pause");
		exit(0);
	} 
	else
	{
		canvas[newHead_x][newHead_y] = 1;
	}
}

void startup()         //���ݵĳ�ʼ��
{
	HideCursor();      //���ع��
	int i, j;
	//��ʼ���߿�
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

	//��ʼ����ͷλ��
	canvas[Height / 2][Width / 2] = 1;
	//��ʼ�����������е�Ԫ��ֵ�ֱ�Ϊ2��3��4��5��
	for (i = 1;i <= 4;i++)
	{
		canvas[Height / 2][Width / 2 - i] = i + 1;
	}

	//��ʼС�������ƶ�
	moveDirection = 4;

	food_x = rand() % (Height - 5) + 2;
	food_y = rand() % (Width - 5) + 2;
	canvas[food_x][food_y] = -2;
}

void show()      //��ʾ����
{
	gotoxy(0, 0);        //������ƶ���ԭ�㣬�������»���
	int i, j;
	for (i = 0;i < Height;i++)
	{
		for (j = 0;j < Width;j++)
		{
			if (canvas[i][j] == -1)
			{
				printf("#");       //����߿�#
			}
			if (canvas[i][j] == 0)
			{
				printf(" ");       //����ո�
			}
			if (canvas[i][j] == 1)
			{
				printf("@");       //�����ͷ@
			}
			if (canvas[i][j] > 1)
			{
				printf("*");       //�������*
			}
			if (canvas[i][j] == -2)
			{
				printf("F");       //���ʳ��F
			}
		}
		printf("\n");
	}
	Sleep(100);
}

void UpdataWithoutInput()          //���û������޹صĸ���
{
	moveSnackByDerection();
}

void UpdataWithInput()             //���û������йصĸ���
{
	char input;
	if (kbhit())                   //�ж��û��Ƿ�������
	{
		input = getch();           //�����û��Ĳ�ͬ����������С�ߵ��ƶ�
		if (input == 'w')
		{
			moveDirection = 1;  //�����ƶ�
			moveSnackByDerection();
		}
		if (input == 's')
		{
			moveDirection = 2;  //�����ƶ�
			moveSnackByDerection();
		}
		if (input == 'a')
		{
			moveDirection = 3;  //�����ƶ�
			moveSnackByDerection();
		}
		if (input == 'd')
		{
			moveDirection = 4;  //�����ƶ�
			moveSnackByDerection();
		}
	}
}

int main()
{
	startup();          //��ʼ��
	while (1)
	{
		show();         //��ʾ����
		UpdataWithoutInput();    //���û������йصĸ���
		UpdataWithInput();       //���û������йصĸ���
	}
	return 0;
}
