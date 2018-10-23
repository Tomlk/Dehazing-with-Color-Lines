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
	static const int Img_w = 400;	//ͼ����
	static const int Img_h = 600;	//ͼ��߶�
	void ransac(double m[Img_h][Img_w][3]);
	void genDistnctRandomNumber(int n, int max);
	void findColorLine();
	bool test(double m[Img_h][Img_w][3]);

	bool SignificantLineSuport(); //��־��֧��
	bool PositiveReflectance();	  //��������
	bool largeIntersectionAngle();		//��Ƕ�
	bool Unimodality(double m[Img_h][Img_w][3]); //������
	bool CloseIntersection();		//���ܽ����
	bool ValidTransmission();		//��Ч����
	bool SufficientShading(double m[Img_h][Img_w][3]);	//�㹻��Ӱ�仯
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

