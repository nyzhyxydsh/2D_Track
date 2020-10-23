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
	//const char * i_query = "select * from inspectgps"; //查询语句，从那个表中查询,这里后面没有;
	const char * i_query = "select name,lat,lon,alt from track";
	//const char * i_query = "select name,x,y,z from orbit";
	MYSQL_RES * result = NULL; //保存结果集的
	MYSQL_ROW row = NULL; //代表的是结果集中的一行
	//915工作：建一个satellite数据库，看一下数据存储格式，以及程序调用流程
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "root", "track", 3306, NULL, 0))
	{
		//AfxMessageBox(_T("数据库连接失败!"));
		return;
	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		if (mysql_query(&mysql, i_query) != 0) //如果连接成功，则开始查询 .成功返回0
		{
			//AfxMessageBox(_T("查询失败!"));
		}
		else
		{
			if ((result = mysql_store_result(&mysql)) == NULL) //保存查询的结果 
			{
				//AfxMessageBox(_T("保存失败!"));
			}
			else
			{
				while ((row = mysql_fetch_row(result)) != NULL) //读取结果集中的数据，返回的是下一行。因为保存结果集时，当前的游标在第一行【之前】 
				{
					p = index++;
					weidu[p] = (atof(row[1]));
					jingdu[p] = (atof(row[2]));
					//vertices->push_back(osg::Vec3d(atof(row[1]), atof(row[2]), atof(row[3])));
					//vaTemp->push_back(osg::Vec4f(atof(row[1]), atof(row[2]), atof(row[3]), 1000000));
				}
			}
		}
		mysql_free_result(result); //释放结果集  
		mysql_close(&mysql); //关闭连接 
	}
}
void draw_track1()
{
	BeginBatchDraw();

	for (int i = 1; i < 362; i++)
	{
		IMAGE test;//定义一个图片名.
		loadimage(&test, "world1.jpg", 1000, 500);//从图片文件获取图像
		putimage(0, 0, &test);//绘制图像到屏幕，图片左上角坐标为(0,0)
		
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
		FlushBatchDraw();   //执行未完成的绘制任务。
		//Sleep(5);
		//cleardevice();
	}


}

void draw_track2()
{
	BeginBatchDraw();

	for (int i = 361*1; i < 361*2; i++) 
	{
		IMAGE test;//定义一个图片名.
		loadimage(&test, "world1.jpg", 1000, 500);//从图片文件获取图像
		putimage(0, 0, &test);//绘制图像到屏幕，图片左上角坐标为(0,0)

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
		FlushBatchDraw();   //执行未完成的绘制任务。
		Sleep(1);
		//cleardevice();  
	}
	
}

void myprint() {
	cout << "123";
}
int main() {
	initgraph(1000, 500);//创建一个窗口
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
	_getch();//防止程序关闭
	closegraph();//关闭窗口
	
	return 0;
}

