#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define Height 25    //游戏画面尺寸
#define Width 50
#define enemyNum 5    //敌机的个数

//全局变量
int position_x, position_y;    //飞机的位置
int enemy_x[enemyNum], enemy_y[enemyNum];          //敌机的位置
int canvas[Height][Width] = {0};   //二维数组存储飞机游戏画布中对应的元素
                                   //0为空格，1为飞机*，2为子弹，3为敌机@
int score;                         //得分
int BulletWidth;                   //子弹的宽度
int EnemyMoveSpeed;                //敌机移动速度

void gotoxy(int x, int y)     //将光标移动到原点
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void startup()     //初始化
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

void show()        //显示画面
{
	gotoxy(0, 0);     //将光标移动到原点,以下重新画屏

	int i, j;
	for (i = 0;i < Height;i++)
	{
		for (j = 0;j < Width;j++)
		{
			if (canvas[i][j] == 0)
			{
				printf(" ");     //输出空格
			}
			else if (canvas[i][j] == 1)
			{
				printf("*");     //输出飞机*
			}
			else if (canvas[i][j] == 2)
			{
				printf("|");     //输出子弹|
			}
			else if (canvas[i][j] == 3)
			{
				printf("@");     //输出敌机@
			}
		}
		printf("\n");
	}
	printf("得分：%3d", score);
	Sleep(20);
}

void UpdataWithoutInput()     //与用户输入无关的更新
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
					if ((i == enemy_x[k]) && (j == enemy_y[k]))     //判断子弹是否击中敌机
					{
						score++;        //分数加一
						if (score % 5 == 0 && EnemyMoveSpeed > 3)   //达到一定积分后敌机变快
						{
							EnemyMoveSpeed--;
						}
						if (score % 5 == 0)         //达到一定积分后子弹变厉害
						{
							BulletWidth++;
						}
						canvas[enemy_x[k]][enemy_y[k]] = 0;
						enemy_x[k] = rand() % 2;    //产生新的敌机
						enemy_y[k] = rand() % Width;
						canvas[enemy_x[k]][enemy_y[k]] = 3;
						canvas[i][j] = 0;  //子弹消失
					}
				}
				canvas[i][j] = 0;
				if (i > 0)    //子弹向上移动
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
		if ((position_x == enemy_x[k]) && (position_y == enemy_y[k]))    //敌机是否撞到我机
		{
			printf("游戏结束\n");
			Sleep(1000);
			system("pause");
			exit(0);
		}

		if (enemy_x[k] > Height)   //敌机跑出飞机屏幕
		{
			canvas[enemy_x[k]][enemy_y[k]] = 0;
			enemy_x[k] = rand() % 2;   //产生新的敌机
			enemy_y[k] = rand() % Width;
			canvas[enemy_x[k]][enemy_y[k]] = 3;
			score--;       //减分
		}

		if (speed == EnemyMoveSpeed)
		{
			//敌机下落
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

void UpdataWithInput()        //与用户输入有关的更新
{
	char input;
	if (kbhit())       //判断用户是否输入
	{
		input = getch();    //根据用户的输入来控制飞机的移动，不必输入回车
		if (input == 'a')
		{
			canvas[position_x][position_y] = 0;
			position_y--;       //位置左移
			canvas[position_x][position_y] = 1;
		}
		if (input == 'd')
		{
			canvas[position_x][position_y] = 0;
			position_y++;       //位置右移
			canvas[position_x][position_y] = 1;
		}
		if (input == 'w')
		{
			canvas[position_x][position_y] = 0;
			position_x--;       //位置上移
			canvas[position_x][position_y] = 1;
		}
		if (input == 's')
		{
			canvas[position_x][position_y] = 0;
			position_x++;       //位置下移
			canvas[position_x][position_y] = 1;
		}
		if (input == ' ')       //发射子弹
		{
			int left = position_y - BulletWidth;    //子弹左边界
			int right = position_y + BulletWidth;   //子弹右边界
			if (left < 0)
			{
				left = 0;
			}
			if (right > Width - 1)
			{
				right = Width - 1;
			}
			int k;
			for (k = left;k <= right;k++)   //发射子弹
			{
				canvas[position_x - 1][k] = 2;   //子弹的初始位置在飞机的正上方
			}
		}
	}
}

int main()
{
	startup();     //初始化
	while (1)
	{
		show();    //显示画面
		UpdataWithoutInput();    //与用户输入无关的更新
		UpdataWithInput();       //与用户输入有关的更新
	}
}
