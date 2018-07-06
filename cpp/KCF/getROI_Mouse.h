#ifndef GETROI_MOUSE_H
#define GETROI_MOUSE_H
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;


//---------------------�������������֡�---------------------------------

bool g_bDrawingBox = false;   //�Ƿ���л��Ƶı�־
Rect g_rectange = Rect(-1, -1, 0, 0);

void DrawRectagle(cv::Mat &img, cv::Rect box);
Rect& GetRoi(cv::String &WINDOWNAME, cv::Mat srcImage);
void on_MouseHandle(int event, int x, int y, int flags, void *param);


	//׼������
	//cv::String TEST = "TEST";
	//Mat Image = imread("zx.jpg");
	//namedWindow(TEST);
	//imshow(TEST, Image);
	//GetRoi(TEST, Image);

Rect& GetRoi(cv::String &WINDOWNAME, cv::Mat srcImage)
{


	setMouseCallback(WINDOWNAME, on_MouseHandle, (void*)&srcImage);
	cv::Mat tempImage;
	//������ѭ��
	while (1)            //��ѭ��
	{
		srcImage.copyTo(tempImage);     //����ԭͼ����ʱ����
		if (g_bDrawingBox)
			DrawRectagle(srcImage, g_rectange);
		//�����л��Ʊ�ʶ��Ϊ��ʱ�����л���
		imshow(WINDOWNAME, tempImage);

		if (waitKey(20) == 27)
			break;             //����ESCʱ�˳�
	}
	return g_rectange;
}

void on_MouseHandle(int event, int x, int y, int flags, void *param)
{
	Mat &image = *(cv::Mat*) param;
	switch (event)
	{
	case EVENT_MOUSEMOVE:    //����ƶ�
	{
		if (g_bDrawingBox)      //����Ƿ�Ҫ���л��Ƶı�ʶ��Ϊ�棬���¼�³��Ϳ�RECT�͵ı�����
		{
			g_rectange.width = x - g_rectange.x;
			g_rectange.height = y - g_rectange.y;
		}

	}break;

	case EVENT_LBUTTONDOWN:      //�������ʱ
	{ g_bDrawingBox = true;
	g_rectange = Rect(x, y, 0, 0);  //��¼���
	}
	break;
	case EVENT_LBUTTONUP:        //���̧��ʱ
	{
		g_bDrawingBox = false;
		//��λ��ʶ��ΪFALSE
		//�ԸߺͿ�С����Ĵ���

		if (g_rectange.width < 0)
		{
			g_rectange.x += g_rectange.width;
			g_rectange.width *= -1;
		}
		if (g_rectange.height < 0)
		{
			g_rectange.y += g_rectange.height;
			g_rectange.height *= -1;
		}
		DrawRectagle(image, g_rectange);
	}
	break;
	}
}



//���ܣ��Զ���ľ��λ��ƺ��������ÿ⺯��reetangle

void DrawRectagle(cv::Mat &img, cv::Rect box)
{
	rectangle(img, box.tl(), box.br(), Scalar(0, 255, 255));
	//��ɫ
}

#endif