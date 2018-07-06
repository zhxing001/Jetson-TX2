/*******************************************************************************
* Created by Qiang Wang on 16/7.24
* Copyright 2016 Qiang Wang.  [wangqiang2015-at-ia.ac.cn]
* Licensed under the Simplified BSD License
*******************************************************************************/

#ifndef SRC_KCF_HPP_
#define SRC_KCF_HPP_

#define PI 3.141592653589793

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <string>
#include <cmath>
#include "fhog.hpp"

using namespace cv;
using namespace std;

class KCF
{
public:
  KCF(std::string kernel_type = "gaussian", std::string feature_type = "hog");   //���캯������Ĭ�ϲ���
  void Init(cv::Mat image, cv::Rect rect_init);    //��ʼ������
  cv::Rect Update(cv::Mat image);           //��Ҫ���ú���
  cv::Rect Update1(cv::Mat image);
  Point getPos()    //��posҲ����ȥ������һ�»������ĵ�
  {
	  return pos_;
  }
  cv::Rect getRec()
  {
	  return result_rect_;
  }
  int Num = 0;
  ofstream maxLoctxt;
protected:
  void Learn(cv::Mat &patch, float lr);         

  cv::Mat CreateGaussian1D(int n, float sigma);         //һά��˹

  cv::Mat CreateGaussian2D(cv::Size sz, float sigma);     //��ά��˹
   
  cv::Mat GaussianShapedLabels(float sigma, cv::Size sz);      //��˹��ǩ��y

  cv::Mat CalculateHann(cv::Size sz);           //������

  cv::Mat GetSubwindow(const cv::Mat &frame, cv::Point centraCoor, cv::Size sz);
                                                //�Ӵ���
  std::vector<cv::Mat> GetFeatures(cv::Mat patch);    //��ȡ��֤

  cv::Mat GaussianCorrelation(std::vector<cv::Mat> xf, std::vector<cv::Mat> yf);   //��˹��

  cv::Mat PolynomialCorrelation(std::vector<cv::Mat> xf, std::vector<cv::Mat> yf);   //����ʽ��

  cv::Mat LinearCorrelation(std::vector<cv::Mat> xf, std::vector<cv::Mat> yf);  //���Ժ�

  cv::Mat ComplexMul(const cv::Mat &x1, const cv::Mat &x2);    //�����˷���element_wise��

  cv::Mat ComplexDiv(const cv::Mat &x1, const cv::Mat &x2);    //��������(element_wise)
 

  inline cv::Size FloorSizeScale(cv::Size sz, double scale_factor) {
            if (scale_factor > 0.9999 && scale_factor < 1.0001)
              return sz;
           return cv::Size(cvFloor(sz.width * scale_factor), 
                           cvFloor(sz.height * scale_factor));
         }

  inline cv::Point FloorPointScale(cv::Point p, double scale_factor) {
           if (scale_factor > 0.9999 && scale_factor < 1.0001)
              return p; 
           return cv::Point(cvFloor(p.x * scale_factor), 
                            cvFloor(p.y * scale_factor));
	 }
 //���������������ڸ��³���

private:
  float padding_ = 2;    
  float lambda_ = 1e-4;
  float output_sigma_factor_ = 0.1;          
  bool features_hog_ = false;   
  int features_hog_orientations_ = 9;    //9������
  bool features_gray_ = false;          
  float kernel_sigma_ = 0.2;         //�˵�sigma
  int kernel_poly_a_ = 1;
  int kernel_poly_b_ = 7;             //����ʽϵ��
  std::string kernel_type_;           //������
  int cell_size_ = 1;                  
  float interp_factor_ = 0.075;       //��ֵϵ��
  cv::Rect result_rect_;              //����Ǵ���ο�İɣ����Ͻ�������ӳ��Ϳ����忴�ඨ�壬
									//update���صľ����������
  cv::Point pos_;
  cv::Size target_sz_;
  bool resize_image_ = false;
  cv::Size window_sz_;
  cv::Mat yf_;
  cv::Mat cos_window_;
  std::vector<cv::Mat> model_xf_;
  cv::Mat model_alphaf_;
  FHoG f_hog_;
};

#endif /* SRC_KCF_HPP_ */
