#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>


int main()
{
	int i, j;    
	int x = 5;
	int y = 10;
	char input;
	int isFire = 0;

	int ny = 5;         //�����ӷ��ڵ�һ�ŵĵ�n����
	int isKilled = 0;

	while(1)
	{
		system("cls");  //��������

		if(!isKilled)   //�������
		{
			for(j = 0;j < ny;j++)
			{
				printf(" ");
			}
			printf("+");
		}

		if(isFire == 0)   //����ɻ�����Ŀ���
		{
			for(i = 0;i < x;i++)
			{
				printf("\n");
			}
		}
		else             //�����������
		{
			for(i = 0;i < x;i++)
			{
				for(j = 0;j < y;j++)
				{
					printf(" ");
				}
				printf("  |\n");
			}
			if(y + 2 == ny)   //�ж��Ƿ���а���
			{
				isKilled = 1;
			}
			isFire = 0;
		}

		//��ʾ�ɻ�
		for(j = 0;j < y;j++)
		{
			printf(" ");
		}
		printf("  *\n");
		for(j = 0;j < y;j++)
		{
			printf(" ");
		}
		printf("*****\n");
		for(j = 0;j < y;j++)
		{
			printf(" ");
		}
		printf(" * * \n");

		printf("\n");
		Sleep(10);  //ͣ��10ms

		if(kbhit())
		{
			input = getch();  //�����û���ͬ���������ƶ�����������س�
			if(input == 'a')
				y--;          //����
			if(input == 'd')
				y++;          //����
			if(input == 'w')
				x--;          //����
			if(input == 's')
				x++;          //����
			if(input == ' ')  
				isFire = 1;   //����
		}
	}
	return 0;
}

