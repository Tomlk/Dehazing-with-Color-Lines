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
	Vector3 vec_X(const Vector3 &v);	//叉乘
	double operator*(const Vector3 &v);//点乘(内积)
	double angle( Vector3 &v);
	Vector3 operator+(double f);
	Vector3 operator-(double f);
	Vector3 operator/(double f);
	Vector3 operator*(double f);//数乘
	double dot(const Vector3 &v);
//	double distance( Vector3 &vx,  Vector3 &v1,  Vector3 &v2);
	double length();	//模
	double getsqr();
	void normalize();
	Vector3 crossProduct(const Vector3 &v);
	void printVec3();
};