#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Height 25    //��Ϸ����ߴ�
#define Width 50
#define enemyNum 5    //�л��ĸ���

//ȫ�ֱ���
int position_x, position_y;    //�ɻ���λ��
int enemy_x[enemyNum], enemy_y[enemyNum];          //�л���λ��
int canvas[Height][Width] = {0};   //��ά����洢�ɻ���Ϸ�����ж�Ӧ��Ԫ��
                                   //0Ϊ�ո�1Ϊ�ɻ�*��2Ϊ�ӵ���3Ϊ�л�@
int score;                         //�÷�
int BulletWidth;                   //�ӵ��Ŀ��
int EnemyMoveSpeed;                //�л��ƶ��ٶ�

void gotoxy(int x, int y)     //������ƶ���ԭ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void startup()     //��ʼ��
{
	position_x = Height / 2;
	position_y = Width / 2;
	canvas[position_x][position_y] = 1;
	
	int k;
	for (k = 0;k < enemyNum;k++)
	{
		enemy_x[k] = rand() % 2;
		enemy_y[k] = rand() % Width;
		canvas[enemy_x[k]][enemy_y[k]] = 3;
	}
	score = 0;
	BulletWidth = 0;
	EnemyMoveSpeed = 20;
}

void show()        //��ʾ����
{
	gotoxy(0, 0);     //������ƶ���ԭ��,�������»���

	int i, j;
	for (i = 0;i < Height;i++)
	{
		for (j = 0;j < Width;j++)
		{
			if (canvas[i][j] == 0)
			{
				printf(" ");     //����ո�
			}
			else if (canvas[i][j] == 1)
			{
				printf("*");     //����ɻ�*
			}
			else if (canvas[i][j] == 2)
			{
				printf("|");     //����ӵ�|
			}
			else if (canvas[i][j] == 3)
			{
				printf("@");     //����л�@
			}
		}
		printf("\n");
	}
	printf("�÷֣�%3d", score);
	Sleep(20);
}

void UpdataWithoutInput()     //���û������޹صĸ���
{
	int i, j, k;
	for (i = 0;i < Height;i++)
	{
		for (j = 0;j < Width;j++)
		{
			if (canvas[i][j] == 2)    
			{
				for (k = 0;k < enemyNum;k++)
				{
					if ((i == enemy_x[k]) && (j == enemy_y[k]))     //�ж��ӵ��Ƿ���ел�
					{
						score++;        //������һ
						if (score % 5 == 0 && EnemyMoveSpeed > 3)   //�ﵽһ�����ֺ�л����
						{
							EnemyMoveSpeed--;
						}
						if (score % 5 == 0)         //�ﵽһ�����ֺ��ӵ�������
						{
							BulletWidth++;
						}
						canvas[enemy_x[k]][enemy_y[k]] = 0;
						enemy_x[k] = rand() % 2;    //�����µĵл�
						enemy_y[k] = rand() % Width;
						canvas[enemy_x[k]][enemy_y[k]] = 3;
						canvas[i][j] = 0;  //�ӵ���ʧ
					}
				}
				canvas[i][j] = 0;
				if (i > 0)    //�ӵ������ƶ�
				{
					canvas[i - 1][j] = 2;
				}
 			}
		}
	}

	static int speed = 0;
	if (speed < EnemyMoveSpeed)
	{
		speed++;
	}

	for (k = 0;k < enemyNum;k++)
	{
		if ((position_x == enemy_x[k]) && (position_y == enemy_y[k]))    //�л��Ƿ�ײ���һ�
		{
			printf("��Ϸ����\n");
			Sleep(1000);
			system("pause");
			exit(0);
		}

		if (enemy_x[k] > Height)   //�л��ܳ��ɻ���Ļ
		{
			canvas[enemy_x[k]][enemy_y[k]] = 0;
			enemy_x[k] = rand() % 2;   //�����µĵл�
			enemy_y[k] = rand() % Width;
			canvas[enemy_x[k]][enemy_y[k]] = 3;
			score--;       //����
		}

		if (speed == EnemyMoveSpeed)
		{
			//�л�����
			for (k = 0;k < enemyNum;k++)
			{
				canvas[enemy_x[k]][enemy_y[k]] = 0;
				enemy_x[k]++;
				canvas[enemy_x[k]][enemy_y[k]] = 3;
				speed = 0;
			}
		}
	}
}

void UpdataWithInput()        //���û������йصĸ���
{
	char input;
	if (kbhit())       //�ж��û��Ƿ�����
	{
		input = getch();    //�����û������������Ʒɻ����ƶ�����������س�
		if (input == 'a')
		{
			canvas[position_x][position_y] = 0;
			position_y--;       //λ������
			canvas[position_x][position_y] = 1;
		}
		if (input == 'd')
		{
			canvas[position_x][position_y] = 0;
			position_y++;       //λ������
			canvas[position_x][position_y] = 1;
		}
		if (input == 'w')
		{
			canvas[position_x][position_y] = 0;
			position_x--;       //λ������
			canvas[position_x][position_y] = 1;
		}
		if (input == 's')
		{
			canvas[position_x][position_y] = 0;
			position_x++;       //λ������
			canvas[position_x][position_y] = 1;
		}
		if (input == ' ')       //�����ӵ�
		{
			int left = position_y - BulletWidth;    //�ӵ���߽�
			int right = position_y + BulletWidth;   //�ӵ��ұ߽�
			if (left < 0)
			{
				left = 0;
			}
			if (right > Width - 1)
			{
				right = Width - 1;
			}
			int k;
			for (k = left;k <= right;k++)   //�����ӵ�
			{
				canvas[position_x - 1][k] = 2;   //�ӵ��ĳ�ʼλ���ڷɻ������Ϸ�
			}
		}
	}
}

int main()
{
	startup();     //��ʼ��
	while (1)
	{
		show();    //��ʾ����
		UpdataWithoutInput();    //���û������޹صĸ���
		UpdataWithInput();       //���û������йصĸ���
	}
}
