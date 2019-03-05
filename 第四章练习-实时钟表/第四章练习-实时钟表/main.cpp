#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <tchar.h>

#define Height 480     //������Ϸ����ߴ�
#define Width 640
#define PI 3.14159

int main()
{
	initgraph(Width, Height);       //��ʼ��640*480�Ļ���
	int center_x, center_y;         //���ĵ����꣬Ҳ���ӱ����ĵ�����
	center_x = Width / 2;
	center_y = Height / 2;
	int secondLength = Width / 5;          //����ĳ���
	int minuteLength = Width / 6;          //����ĳ���
	int hourLength = Width / 7;            //ʱ��ĳ���

	int secondEnd_x, secondEnd_y;   //����������յ�
	int minuteEnd_x, minuteEnd_y;   //���������յ�
	int hourEnd_x, hourEnd_y;     //����ʱ����յ�

	float secondAngle = 0;          //�����Ӧ�ĽǶ�
	float minuteAngle = 0;          //�����Ӧ�ĽǶ�
	float hourAngle = 0;            //ʱ���Ӧ�ĽǶ�

	SYSTEMTIME ti;                  //����������浱ǰʱ��   

	BeginBatchDraw();
	while (1)
	{
		//����һ������
		setlinestyle(PS_SOLID, 1);  //ʵ�ߣ�����Ϊ1
		setcolor(WHITE);            //������ɫΪ��ɫ
		circle(center_x, center_y, Width / 4);

		//���̶�
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

		outtextxy(center_x - 25, center_y + Width / 6, _T("�ҵ�ʱ��"));

		GetLocalTime(&ti);          //��ȡϵͳʱ��

		secondAngle = ti.wSecond * 2 * PI / 60;     //����Ƕȵı仯
		minuteAngle = ti.wMinute * 2 * PI / 60;     //����Ƕȵı仯
		if (ti.wHour > 12)
		{
			hourAngle = (ti.wHour - 12) * 2 * PI / 12;         //ʱ��Ƕȵı仯
		}
		else
		{
			hourAngle = ti.wHour  * 2 * PI / 12;         //ʱ��Ƕȵı仯
		}

		//�����յ������
		secondEnd_x = center_x + secondLength * sin(secondAngle);
		secondEnd_y = center_y - secondLength * cos(secondAngle);

		//�����յ������
	    minuteEnd_x = center_x + minuteLength * sin(minuteAngle);
		minuteEnd_y = center_y - minuteLength * cos(minuteAngle);

		//ʱ���յ������
		hourEnd_x = center_x + hourLength * sin(hourAngle);
        hourEnd_y = center_y - hourLength * cos(hourAngle);

		//������
		setlinestyle(PS_SOLID, 2);      //��ʵ�ߣ�����Ϊ2
		setcolor(WHITE);                //�������ɫΪ��ɫ
		line(center_x, center_y, secondEnd_x, secondEnd_y);

		//������
		setlinestyle(PS_SOLID, 4);      //��ʵ�ߣ�����Ϊ4
		setcolor(BLUE);                 //������ɫΪ��ɫ
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);

		//��ʱ��
		setlinestyle(PS_SOLID, 6);      //��ʵ�ߣ�����Ϊ6
		setcolor(RED);                  //ʱ����ɫΪ��ɫ
		line(center_x, center_y, hourEnd_x, hourEnd_y);

		FlushBatchDraw();
		Sleep(10);

		setcolor(BLACK);
		setlinestyle(PS_SOLID, 2);
		line(center_x, center_y, secondEnd_x, secondEnd_y);   //����ǰһ֡������
		setlinestyle(PS_SOLID, 4);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);   //����ǰһ֡�ķ���
		setlinestyle(PS_SOLID, 6);
		line(center_x, center_y, hourEnd_x, hourEnd_y);       //����ǰһ֡��ʱ��

	}
	EndBatchDraw();
	getch();                        //�����������
	closegraph();                   //�رջ�ͼ����
	return 0;
}