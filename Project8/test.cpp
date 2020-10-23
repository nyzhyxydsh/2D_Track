#include<easyx.h>
#include <conio.h>
#include<mysql.h>
#include<thread>
#include <iostream>
#include <graphics.h>
#pragma comment(lib, "libmysql.lib")
#define IDC_STATIC_POINT    1000
#define POINT_COUNT 20000

double weidu[POINT_COUNT], jingdu[POINT_COUNT];
double weidu1[POINT_COUNT], jingdu1[POINT_COUNT];
double pxx[POINT_COUNT], pyy[POINT_COUNT];
double pxx1[POINT_COUNT], pyy1[POINT_COUNT];


using namespace std;
void connectMysql()
{
	MYSQL mysql;
	mysql_init(&mysql);
	int index = 0, p;
	//const char * i_query = "select * from inspectgps"; //��ѯ��䣬���Ǹ����в�ѯ,�������û��;
	const char * i_query = "select name,lat,lon,alt from track";
	//const char * i_query = "select name,x,y,z from orbit";
	MYSQL_RES * result = NULL; //����������
	MYSQL_ROW row = NULL; //������ǽ�����е�һ��
	//915��������һ��satellite���ݿ⣬��һ�����ݴ洢��ʽ���Լ������������
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "root", "track", 3306, NULL, 0))
	{
		//AfxMessageBox(_T("���ݿ�����ʧ��!"));
		return;
	}
	else//���ӳɹ�������������ݿ⣬֮�����ز�����������Ƿ����������
	{
		if (mysql_query(&mysql, i_query) != 0) //������ӳɹ�����ʼ��ѯ .�ɹ�����0
		{
			//AfxMessageBox(_T("��ѯʧ��!"));
		}
		else
		{
			if ((result = mysql_store_result(&mysql)) == NULL) //�����ѯ�Ľ�� 
			{
				//AfxMessageBox(_T("����ʧ��!"));
			}
			else
			{
				while ((row = mysql_fetch_row(result)) != NULL) //��ȡ������е����ݣ����ص�����һ�С���Ϊ��������ʱ����ǰ���α��ڵ�һ�С�֮ǰ�� 
				{
					p = index++;
					weidu[p] = (atof(row[1]));
					jingdu[p] = (atof(row[2]));
					//vertices->push_back(osg::Vec3d(atof(row[1]), atof(row[2]), atof(row[3])));
					//vaTemp->push_back(osg::Vec4f(atof(row[1]), atof(row[2]), atof(row[3]), 1000000));
				}
			}
		}
		mysql_free_result(result); //�ͷŽ����  
		mysql_close(&mysql); //�ر����� 
	}
}
void draw_track1()
{
	BeginBatchDraw();

	for (int i = 1; i < 362; i++)
	{
		IMAGE test;//����һ��ͼƬ��.
		loadimage(&test, "world1.jpg", 1000, 500);//��ͼƬ�ļ���ȡͼ��
		putimage(0, 0, &test);//����ͼ����Ļ��ͼƬ���Ͻ�����Ϊ(0,0)
		
		moveto(pxx[0], pyy[0]);
		setlinecolor(RED);
		for (int j = 0; j < 361; j++)
		{
			if (jingdu[j - 1]< 0.0&& jingdu[j] > 0.0)
			{
				moveto(pxx[j], pyy[j]);
			}
			setlinestyle(PS_SOLID, 5);
			lineto(pxx[j], pyy[j]);
		}

		circle(pxx[i], pyy[i], 15);
		//floodfill(i, 100, WHITE);
		FlushBatchDraw();   //ִ��δ��ɵĻ�������
		//Sleep(5);
		//cleardevice();
	}


}

void draw_track2()
{
	BeginBatchDraw();

	for (int i = 361*1; i < 361*2; i++) 
	{
		IMAGE test;//����һ��ͼƬ��.
		loadimage(&test, "world1.jpg", 1000, 500);//��ͼƬ�ļ���ȡͼ��
		putimage(0, 0, &test);//����ͼ����Ļ��ͼƬ���Ͻ�����Ϊ(0,0)

		moveto(pxx1[361], pyy1[361]);
		setlinecolor(WHITE);
		for (int j = 361; j < 361*2; j++)
		{
			if (jingdu1[j - 1]< 0.0&& jingdu1[j] > 0.0)
			{
				moveto(pxx1[j], pyy1[j]);
				//setlinecolor(RED);
			}
			setlinestyle(PS_SOLID, 5);
			lineto(pxx1[j], pyy1[j]);
		}

		circle(pxx1[i], pyy1[i], 15);
		//floodfill(i, 100, WHITE);
		FlushBatchDraw();   //ִ��δ��ɵĻ�������
		Sleep(1);
		//cleardevice();  
	}
	
}

void myprint() {
	cout << "123";
}
int main() {
	initgraph(1000, 500);//����һ������
	connectMysql();
	for (int i = 0; i < 360 * 4; i++)
	{
		pyy[i] = (-25.0 / 9)* weidu[i] + 250;
		pxx[i] = (25.0 / 9.0)*jingdu[i] + 500;
	}

	for (size_t i = 0; i < 360*4; i++)
	{
		pxx1[i] = pxx[i];
		pyy1[i] = pyy[i];
		jingdu1[i] = jingdu[i];
		weidu1[i] = weidu[i];

	}


	thread drawthraed1(draw_track1);
	thread drawthraed2(draw_track2);
	drawthraed1.join();
	drawthraed2.join();

	EndBatchDraw();
	_getch();//��ֹ����ر�
	closegraph();//�رմ���
	
	return 0;
}

