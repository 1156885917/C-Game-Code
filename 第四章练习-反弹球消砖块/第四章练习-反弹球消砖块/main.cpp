#include <graphics.h>
#include <conio.h>

#define Height 480       //定义游戏尺寸
#define Width 640
#define Brick_num 10     //定义砖块的个数

//全局变量
int ball_x, ball_y;      //小球的坐标
int ball_vx, ball_vy;    //小球的速度
int radius;              //小球的半径
int bar_x, bar_y;        //挡板中心的位置
int bar_height, bar_width;  //挡板的高与宽
int bar_left, bar_right, bar_top, bar_bottom;    //挡板的上下左右

int isBrickExisted[Brick_num];     //每个砖块是否存在，1为存在，0为没有了
int brick_height, brick_width;     //每个砖块的高度和宽度 

void startup()           //游戏初始化
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

	initgraph(Width, Height);     //初始化640*480的绘图窗口
	BeginBatchDraw();
}

void clean()         //清空绘图窗口
{
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillcircle(ball_x, ball_y,radius);    //绘制黑线、黑色填充的圆
	bar(bar_left, bar_top, bar_right, bar_bottom);   //绘制黑线、黑色填充的矩形

	int i, brick_left, brick_right, brick_top, brick_bottom;
	for (i = 0;i < Brick_num;i++)
	{
		brick_left = i * brick_width;
		brick_right = brick_left + brick_width;
		brick_top = 0;
		brick_bottom = brick_height;
		if (!isBrickExisted[i])      //如果砖块没有了，则绘成黑色
		{
			fillrectangle(brick_left, brick_top, brick_right, brick_bottom);
		}
	}
}

void show()           //显示画面
{
	setcolor(YELLOW);
	setfillcolor(GREEN);
	fillcircle(ball_x, ball_y, radius);     //绘制黄线、绿色填充的圆
	bar(bar_left, bar_top, bar_right, bar_bottom);   //绘制黄线、绿色填充的矩形

	int i, brick_left, brick_right, brick_top, brick_bottom;
	for (i = 0;i < Brick_num;i++)
	{
		brick_left = i * brick_width;
		brick_right = brick_left + brick_width;
		brick_top = 0;
		brick_bottom = brick_height;
		if (isBrickExisted[i])      //如果砖块没有了，则绘成黑色
		{
			setcolor(WHITE);
			setfillcolor(RED);
			fillrectangle(brick_left, brick_top, brick_right, brick_bottom);   //绘制砖块
		}
	}

	FlushBatchDraw();
	//延时
	Sleep(3);
}

void UpdataWithoutInput()      //与用户输入无关的更新
{
	//判断挡板是否与小球相撞
	if (((ball_y + radius >= bar_top) && (ball_y + radius < bar_bottom - bar_height / 3)) || ((ball_y - radius <= bar_bottom) && (ball_y - radius > bar_top + bar_height / 3)))
	{
		if ((ball_x >= bar_left) && (ball_x <= bar_right))
		{
			ball_vy = -ball_vy;
		}
	}

	//更新小球的坐标
	ball_x = ball_x + ball_vx;
	ball_y = ball_y + ball_vy;

	//小球1和边界触碰
	if ((ball_x <= radius) || (ball_x >= Width - radius))
	{
		ball_vx = -ball_vx;
	}
	if ((ball_y <= radius) || (ball_y >= Height - radius))
	{
		ball_vy = -ball_vy;
	}

	//小球和砖块触碰
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

void UpdataWithInput()    //与用户输入有关的更新
{
	char input;
	if (kbhit())          //判断用户是否有输入
	{
		input = getch();  //根据用户的输入来控制挡板的移动,不必输入回车
		if (input == 'a' && bar_left >0)
		{
			bar_x -= 15;      //向左移动
			bar_left = bar_x - bar_width / 2;
			bar_right = bar_x + bar_width / 2;
		}
		if (input == 'd' && bar_right < Width)
		{
			bar_x += 15;      //向右移动
			bar_left = bar_x - bar_width / 2;
			bar_right = bar_x + bar_width / 2;
		}
		if (input == 'w' && bar_top > 0)
		{
			bar_y -= 15;      //向上移动
			bar_top = bar_y - bar_height / 2;
			bar_bottom = bar_y + bar_height / 2;
		}
		if (input == 's' && bar_bottom < Height)
		{
			bar_y += 15;      //向下移动
			bar_top = bar_y - bar_height / 2;
			bar_bottom = bar_y + bar_height / 2;
		}
	}
    
}

void gameover()      //游戏结束后的后续处理
{
	EndBatchDraw();
	closegraph();         //关闭绘图窗口
}

int main()
{
	startup();       //数据初始化
	while (1)
	{
		clean();     //清除画面
		UpdataWithoutInput();   //与用户输入无关的更新
		UpdataWithInput();      //与用户输入有关的更新
		show();      //显示画面
	}
	gameover();      //游戏结束。进行后续处理
	return 0;
}