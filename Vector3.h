#pragma once
#include "math.h"
extern const double uZero;

class Vector3
{
public:
	double x, y, z;
	double sqr;
public:
	Vector3() :x(0), y(0), z(0) {}
	Vector3(double x1, double y1, double z1) :x(x1), y(y1), z(z1) {}
	Vector3(const Vector3 &v);
	~Vector3();
	void operator=(const Vector3 &v);
	Vector3 operator+(const Vector3 &v);
	Vector3 operator-(const Vector3 &v);
	Vector3 operator/(const Vector3 &v);
	Vector3 vec_X(const Vector3 &v);	//���
	double operator*(const Vector3 &v);//���(�ڻ�)
	double angle( Vector3 &v);
	Vector3 operator+(double f);
	Vector3 operator-(double f);
	Vector3 operator/(double f);
	Vector3 operator*(double f);//����
	double dot(const Vector3 &v);
//	double distance( Vector3 &vx,  Vector3 &v1,  Vector3 &v2);
	double length();	//ģ
	double getsqr();
	void normalize();
	Vector3 crossProduct(const Vector3 &v);
	void printVec3();
};