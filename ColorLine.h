#pragma once
#include "opencv2/imgproc/imgproc.hpp"    
#include "opencv2/highgui/highgui.hpp"   
#include "qdebug.h"
#include "GlobalClass.h"
#include "list"
#include "Patch.h"
#include "limits.h"
#define Img_w 400
#define Img_h 600
using namespace cv;
using namespace std;

class ColorLine
{
public:

	//static const int Img_w = 1024;
	//static const int Img_h = 731;
	double m[Img_h][Img_w][3];
	//double t[Img_h][Img_w];
	int countT[Img_h][Img_w];

public:
	ColorLine(String imgSource, double ar, double ag, double ab);
	void smooth();
	void findPatches(int dx, int dy, double m[Img_h][Img_w][3]);//寻找候选Patches
	int double2RGB(double color);
	//int double2RGB(double color[3]);
	//图像恢复
	void recover(double I[Img_h][Img_w][3], double t[Img_h][Img_w], double AR, double AG, double AB);
	//梯度下降
	void gradientDecent(double raw_t[Img_h][Img_w], double m[Img_h][Img_w][3]);
	bool inBoard(int x, int y, int height, int width);
	Mat getoutImg();
	void setAGB(double, double, double);
	
public:
	//void CalcTransmission(double t[Img_h][Img_w], int countT[Img_h][Img_w]);
	//double sigma[Img_h][Img_w];
	//bool Significant[7][7];
	void FindMchange();
	//double getgaussian(double x, double signma);//未使用
	//void laplacianInterpolation(double t[Img_h][Img_w]);//未使用
	//	void uniform(double tt[Img_h][Img_w], double m[Img_h][Img_w][3]); //未用
private:
	list<Patch> patchlist;
	Mat SrcImg;
	Mat outImg;
	IplImage* srcImg1;
	CvScalar scalar;
	double rt[Img_h][Img_w][3];
	//static double t[Img_h][Img_w];
	//double tt[Img_h][Img_w];
	double AR, AG, AB;
	//int srcImg_pixH;
	//int srcImg_pixW;

};