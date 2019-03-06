#include <graphics.h>
#include <conio.h>

#define Height 480       //������Ϸ�ߴ�
#define Width 640
#define Brick_num 10     //����ש��ĸ���

//ȫ�ֱ���
int ball_x, ball_y;      //С�������
int ball_vx, ball_vy;    //С����ٶ�
int radius;              //С��İ뾶
int bar_x, bar_y;        //�������ĵ�λ��
int bar_height, bar_width;  //����ĸ����
int bar_left, bar_right, bar_top, bar_bottom;    //�������������

int isBrickExisted[Brick_num];     //ÿ��ש���Ƿ���ڣ�1Ϊ���ڣ�0Ϊû����
int brick_height, brick_width;     //ÿ��ש��ĸ߶ȺͿ�� 

void startup()           //��Ϸ��ʼ��
{
	ball_x = Width / 2;
	ball_y = Height / 2;
	ball_vx = 1;
	ball_vy = 1;
	radius = 20;

	bar_height = Height / 20;
	bar_width = Width / 5;
	bar_x = Width / 2;
	bar_y = Height - bar_height / 2;
	bar_left = bar_x - bar_width / 2;
	bar_right = bar_x + bar_width / 2;
	bar_top = bar_y - bar_height / 2;
	bar_bottom = bar_y + bar_height / 2;

	brick_height = Height / Brick_num;
	brick_width = Width / Brick_num;

	int i;
	for (i = 0;i < Brick_num;i++)
	{
		isBrickExisted[i] = 1;
	}

	initgraph(Width, Height);     //��ʼ��640*480�Ļ�ͼ����
	BeginBatchDraw();
}

void clean()         //��ջ�ͼ����
{
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(ball_x, ball_y,radius);    //���ƺ��ߡ���ɫ����Բ
	bar(bar_left, bar_top, bar_right, bar_bottom);   //���ƺ��ߡ���ɫ���ľ���

	int i, brick_left, brick_right, brick_top, brick_bottom;
	for (i = 0;i < Brick_num;i++)
	{
		brick_left = i * brick_width;
		brick_right = brick_left + brick_width;
		brick_top = 0;
		brick_bottom = brick_height;
		if (!isBrickExisted[i])      //���ש��û���ˣ����ɺ�ɫ
		{
			fillrectangle(brick_left, brick_top, brick_right, brick_bottom);
		}
	}
}

void show()           //��ʾ����
{
	setcolor(YELLOW);
	setfillcolor(GREEN);
	fillcircle(ball_x, ball_y, radius);     //���ƻ��ߡ���ɫ����Բ
	bar(bar_left, bar_top, bar_right, bar_bottom);   //���ƻ��ߡ���ɫ���ľ���

	int i, brick_left, brick_right, brick_top, brick_bottom;
	for (i = 0;i < Brick_num;i++)
	{
		brick_left = i * brick_width;
		brick_right = brick_left + brick_width;
		brick_top = 0;
		brick_bottom = brick_height;
		if (isBrickExisted[i])      //���ש��û���ˣ����ɺ�ɫ
		{
			setcolor(WHITE);
			setfillcolor(RED);
			fillrectangle(brick_left, brick_top, brick_right, brick_bottom);   //����ש��
		}
	}

	FlushBatchDraw();
	//��ʱ
	Sleep(3);
}

void UpdataWithoutInput()      //���û������޹صĸ���
{
	//�жϵ����Ƿ���С����ײ
	if (((ball_y + radius >= bar_top) && (ball_y + radius < bar_bottom - bar_height / 3)) || ((ball_y - radius <= bar_bottom) && (ball_y - radius > bar_top + bar_height / 3)))
	{
		if ((ball_x >= bar_left) && (ball_x <= bar_right))
		{
			ball_vy = -ball_vy;
		}
	}

	//����С�������
	ball_x = ball_x + ball_vx;
	ball_y = ball_y + ball_vy;

	//С��1�ͱ߽紥��
	if ((ball_x <= radius) || (ball_x >= Width - radius))
	{
		ball_vx = -ball_vx;
	}
	if ((ball_y <= radius) || (ball_y >= Height - radius))
	{
		ball_vy = -ball_vy;
	}

	//С���ש�鴥��
	int i, brick_left, brick_right, brick_top, brick_bottom;
	for (i = 0;i < Brick_num;i++)
	{
		if (isBrickExisted[i])
		{
			brick_left = i * brick_width;
			brick_right = brick_left + brick_width;
			brick_top = 0;
			brick_bottom = brick_height;
			if ((ball_y == brick_bottom + radius) && (ball_x >= brick_left) && (ball_x <= brick_right))
			{
				isBrickExisted[i] = 0;
				ball_vy = -ball_vy;
			}
		}
	}
}

void UpdataWithInput()    //���û������йصĸ���
{
	char input;
	if (kbhit())          //�ж��û��Ƿ�������
	{
		input = getch();  //�����û������������Ƶ�����ƶ�,��������س�
		if (input == 'a' && bar_left >0)
		{
			bar_x -= 15;      //�����ƶ�
			bar_left = bar_x - bar_width / 2;
			bar_right = bar_x + bar_width / 2;
		}
		if (input == 'd' && bar_right < Width)
		{
			bar_x += 15;      //�����ƶ�
			bar_left = bar_x - bar_width / 2;
			bar_right = bar_x + bar_width / 2;
		}
		if (input == 'w' && bar_top > 0)
		{
			bar_y -= 15;      //�����ƶ�
			bar_top = bar_y - bar_height / 2;
			bar_bottom = bar_y + bar_height / 2;
		}
		if (input == 's' && bar_bottom < Height)
		{
			bar_y += 15;      //�����ƶ�
			bar_top = bar_y - bar_height / 2;
			bar_bottom = bar_y + bar_height / 2;
		}
	}
    
}

void gameover()      //��Ϸ������ĺ�������
{
	EndBatchDraw();
	closegraph();         //�رջ�ͼ����
}

int main()
{
	startup();       //���ݳ�ʼ��
	while (1)
	{
		clean();     //�������
		UpdataWithoutInput();   //���û������޹صĸ���
		UpdataWithInput();      //���û������йصĸ���
		show();      //��ʾ����
	}
	gameover();      //��Ϸ���������к�������
	return 0;
}