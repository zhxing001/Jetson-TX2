#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

#define WINDOW_NAME "���򴰿�"

int g_nThresholdValue=100;        //��ֵ
int g_nThresholdType = 3;          //��ֵ������
Mat g_srcImage, g_dstImage, g_grayImage;    //ͼƬ׼��


//void on_Threshold(int, void*);    //�ص�����

int main()
{
	g_srcImage = imread("xy.jpg");
	imshow("ԭͼ", g_srcImage);
	//cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);  //ת��Ϊ�Ҷ�ͼ
	//imshow("�Ҷ�ͼ", g_grayImage);
	Mat img;
	img = g_srcImage;
	//namedWindow(WINDOW_NAME,4);
	//createTrackbar("ģʽ", WINDOW_NAME, &g_nThresholdType, 4, on_Threshold);
	//createTrackbar("��ֵ", WINDOW_NAME, &g_nThresholdValue, 255, on_Threshold);
	//on_Threshold(0, 0);     //��ʼ����ֵ�ص�����

	//resize(g_srcImage, g_srcImage, Size(0,0), 0.4, 0.4,INTER_AREA);  
	//resize�����÷�ʵ��
	/*imshow("��С", g_srcImage);
	imwrite("xy1.jpg", g_srcImage);*/
	
	pyrUp(g_srcImage, g_dstImage, Size(g_srcImage.cols * 2, g_srcImage.rows * 2));
	imshow("up", g_dstImage);
	
	pyrDown(img, g_grayImage, Size(img.cols / 2, img.rows / 2));
	imshow("dowm", g_grayImage);
	waitKey();
	return 0;

}


//void on_Threshold(int, void*)
//{
//	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
//	//��ֵ������ʾ
//	imshow(WINDOW_NAME, g_dstImage);
//}
//
