#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <tchar.h>

#define Height 480     //定义游戏画面尺寸
#define Width 640
#define PI 3.14159

int main()
{
	initgraph(Width, Height);       //初始化640*480的画布
	int center_x, center_y;         //中心的坐标，也是钟表中心的坐标
	center_x = Width / 2;
	center_y = Height / 2;
	int secondLength = Width / 5;          //秒针的长度
	int minuteLength = Width / 6;          //分针的长度
	int hourLength = Width / 7;            //时针的长度

	int secondEnd_x, secondEnd_y;   //定义秒针的终点
	int minuteEnd_x, minuteEnd_y;   //定义分针的终点
	int hourEnd_x, hourEnd_y;     //定义时针的终点

	float secondAngle = 0;          //秒针对应的角度
	float minuteAngle = 0;          //分针对应的角度
	float hourAngle = 0;            //时针对应的角度

	SYSTEMTIME ti;                  //定义变量保存当前时间   

	BeginBatchDraw();
	while (1)
	{
		//绘制一个表盘
		setlinestyle(PS_SOLID, 1);  //实线，像素为1
		setcolor(WHITE);            //表盘颜色为白色
		circle(center_x, center_y, Width / 4);

		//画刻度
		int x, y, i;
		for (i = 0;i < 60;i++)
		{
			x = center_x + int(Width / 4.3 * sin(2 * PI * i / 60));
			y = center_y + int(Width / 4.3 * cos(2 * PI * i / 60));

			if (i % 15 == 0)
			{
				bar(x - 5, y - 5, x + 5, y + 5);
			}
			else if (i % 5 == 0)
			{
				circle(x, y, 3);
			}
			else
			{
				putpixel(x, y, WHITE);
			}
		}

		outtextxy(center_x - 25, center_y + Width / 6, _T("我的时钟"));

		GetLocalTime(&ti);          //获取系统时间

		secondAngle = ti.wSecond * 2 * PI / 60;     //秒针角度的变化
		minuteAngle = ti.wMinute * 2 * PI / 60;     //分针角度的变化
		if (ti.wHour > 12)
		{
			hourAngle = (ti.wHour - 12) * 2 * PI / 12;         //时针角度的变化
		}
		else
		{
			hourAngle = ti.wHour  * 2 * PI / 12;         //时针角度的变化
		}

		//秒针终点的坐标
		secondEnd_x = center_x + secondLength * sin(secondAngle);
		secondEnd_y = center_y - secondLength * cos(secondAngle);

		//分针终点的坐标
	    minuteEnd_x = center_x + minuteLength * sin(minuteAngle);
		minuteEnd_y = center_y - minuteLength * cos(minuteAngle);

		//时针终点的坐标
		hourEnd_x = center_x + hourLength * sin(hourAngle);
        hourEnd_y = center_y - hourLength * cos(hourAngle);

		//画秒针
		setlinestyle(PS_SOLID, 2);      //画实线，像素为2
		setcolor(WHITE);                //秒针的颜色为白色
		line(center_x, center_y, secondEnd_x, secondEnd_y);

		//画分针
		setlinestyle(PS_SOLID, 4);      //画实线，像素为4
		setcolor(BLUE);                 //分针颜色为绿色
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);

		//画时针
		setlinestyle(PS_SOLID, 6);      //画实线，像素为6
		setcolor(RED);                  //时针颜色为红色
		line(center_x, center_y, hourEnd_x, hourEnd_y);

		FlushBatchDraw();
		Sleep(10);

		setcolor(BLACK);
		setlinestyle(PS_SOLID, 2);
		line(center_x, center_y, secondEnd_x, secondEnd_y);   //隐藏前一帧的秒针
		setlinestyle(PS_SOLID, 4);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);   //隐藏前一帧的分针
		setlinestyle(PS_SOLID, 6);
		line(center_x, center_y, hourEnd_x, hourEnd_y);       //隐藏前一帧的时针

	}
	EndBatchDraw();
	getch();                        //按任意键继续
	closegraph();                   //关闭绘图窗口
	return 0;
}