//#include<easyx.h>
//#include <conio.h>
//#include<mysql.h>
//#include <graphics.h>
//#pragma comment(lib, "libmysql.lib")
//#define POINT_COUNT 20000
//double weidu[POINT_COUNT], jingdu[POINT_COUNT];
//void connectMysql()
//{
//	MYSQL mysql;
//	mysql_init(&mysql);
//	int index = 0, p;
//	//const char * i_query = "select * from inspectgps"; //��ѯ��䣬���Ǹ����в�ѯ,�������û��;
//	const char * i_query = "select name,lat,lon,alt from track";
//	//const char * i_query = "select name,x,y,z from orbit";
//	MYSQL_RES * result = NULL; //����������
//	MYSQL_ROW row = NULL; //������ǽ�����е�һ��
//	//915��������һ��satellite���ݿ⣬��һ�����ݴ洢��ʽ���Լ������������
//	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "root", "track", 3306, NULL, 0))
//	{
//		//AfxMessageBox(_T("���ݿ�����ʧ��!"));
//		return;
//	}
//	else//���ӳɹ�������������ݿ⣬֮�����ز�����������Ƿ����������
//	{
//		if (mysql_query(&mysql, i_query) != 0) //������ӳɹ�����ʼ��ѯ .�ɹ�����0
//		{
//			//AfxMessageBox(_T("��ѯʧ��!"));
//		}
//		else
//		{
//			if ((result = mysql_store_result(&mysql)) == NULL) //�����ѯ�Ľ�� 
//			{
//				//AfxMessageBox(_T("����ʧ��!"));
//			}
//			else
//			{
//				while ((row = mysql_fetch_row(result)) != NULL) //��ȡ������е����ݣ����ص�����һ�С���Ϊ��������ʱ����ǰ���α��ڵ�һ�С�֮ǰ�� 
//				{
//					p = index++;
//					weidu[p] = (atof(row[1]));
//					jingdu[p] = (atof(row[2]));
//					//vertices->push_back(osg::Vec3d(atof(row[1]), atof(row[2]), atof(row[3])));
//					//vaTemp->push_back(osg::Vec4f(atof(row[1]), atof(row[2]), atof(row[3]), 1000000));
//				}
//			}
//		}
//		mysql_free_result(result); //�ͷŽ����  
//		mysql_close(&mysql); //�ر����� 
//	}
//}
//
//int main() {
//
//	initgraph(1000, 500);//����һ������
//	connectMysql();
//
//	double pxx[POINT_COUNT], pyy[POINT_COUNT];
//	pyy[0] = (-25.0 / 9)* weidu[0] + 250;
//	pxx[0] = (25.0 / 9.0)*jingdu[0] + 500;
//
//
//	//���ߺ���
//	for (int i = 1; i <1444 ; i++)
//	{
//		pyy[i] = (-25.0 / 9)* weidu[i] + 250;
//		pxx[i] = (25.0 / 9.0)*jingdu[i] + 500;
//	}
//
//	BeginBatchDraw();
//	setlinecolor(WHITE);
//	for (int i = 1; i < 361; i++)
//	{
//		IMAGE test;//����һ��ͼƬ��.
//		loadimage(&test, "world1.jpg", 1000, 500);//��ͼƬ�ļ���ȡͼ��
//		putimage(0, 0, &test);//����ͼ����Ļ��ͼƬ���Ͻ�����Ϊ(0,0)
//		setlinecolor(WHITE);
//		circle(pxx[i], pyy[i], 15);
//		setlinecolor(RED);
//		circle(pxx[i + 361 ], pyy[i + 361], 15);
//		setlinecolor(LIGHTRED);
//		circle(pxx[i+361*2], pyy[i+361*2], 15);
//		setlinecolor(YELLOW);
//		circle(pxx[i + 361 * 3], pyy[i + 361 * 3], 15);
//		
//		//floodfill(i, 100, WHITE);
//		FlushBatchDraw();   //ִ��δ��ɵĻ�������
//		Sleep(5);
//		cleardevice();
//	}  
//	EndBatchDraw();
//	_getch();//��ֹ����ر�
//	closegraph();//�رմ���
//	return 0;
//}
