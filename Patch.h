#pragma once
#include "Vector3.h"
#include "cstdlib"
#include "cmath"
#include "ctime"
#include "GlobalClass.h"
#include "qdebug.h"
#define M_PI       3.1415926535897932384
using namespace std;
class Patch
{
public:
	const 
	Patch(int x,int y);
	void Initial();
	static const int Length = 7;
	static const int Img_w = 400;	//图像宽度
	static const int Img_h = 600;	//图像高度
	void ransac(double m[Img_h][Img_w][3]);
	void genDistnctRandomNumber(int n, int max);
	void findColorLine();
	bool test(double m[Img_h][Img_w][3]);

	bool SignificantLineSuport(); //标志线支持
	bool PositiveReflectance();	  //正反射率
	bool largeIntersectionAngle();		//大角度
	bool Unimodality(double m[Img_h][Img_w][3]); //单峰性
	bool CloseIntersection();		//紧密交叉口
	bool ValidTransmission();		//有效传输
	bool SufficientShading(double m[Img_h][Img_w][3]);	//足够阴影变化
	void calcTransmission(double t[Img_h][Img_w], int countT[Img_h][Img_w]);
	double distance(Vector3 &vx, Vector3 &v1, Vector3 &v2);

	~Patch();


public:
	//double(*T)[Img_w];
	//double T[Img_h][Img_w];
private:
	
	int* rt;
	bool significant[Length][Length];
	Vector3  LineD;
	Vector3  LineV;
	int OmiGa;
	double transmission;
	int X;
	int Y;
	Vector3 A;


};

