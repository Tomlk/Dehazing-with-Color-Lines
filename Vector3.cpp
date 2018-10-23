//Vector3.cpp
#include "Vector3.h"
#include<iostream>

const double uZero = 1e-6;

//复制构造函数，必须为常量引用参数，否则编译不通过
Vector3::Vector3(const Vector3 &v) :x(v.x), y(v.y), z(v.z)
{
}

Vector3::~Vector3()
{
}

void Vector3::operator=(const Vector3 &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3 Vector3::operator+(const Vector3 &v)
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3 &v)
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator/(const Vector3 &v)
{
	if (fabsf(v.x) <= uZero || fabsf(v.y) <= uZero || fabsf(v.z) <= uZero)
	{
		std::cerr << "Over flow!\n";
		return *this;
	}
	return Vector3(x / v.x, y / v.y, z / v.z);
}

double Vector3::operator*(const Vector3 &v)
{
	return x*v.x+y*v.y+z*v.z;
}
Vector3 Vector3::vec_X(const Vector3 &v)
{
	//return Vector3(x*v.x, y*v.y, z *v.z);
	return Vector3(y*v.z - z * v.y, z*v.x - x * v.z, x*v.y - y * v.x);
}
Vector3 Vector3::operator+(double f)
{
	return Vector3(x + f, y + f, z + f);
}

Vector3 Vector3::operator-(double f)
{
	return Vector3(x - f, y - f, z - f);
}

Vector3 Vector3::operator/(double f)
{
	if (fabsf(f) < uZero)
	{
		std::cerr << "Over flow!\n";
		return *this;
	}
	return Vector3(x / f, y / f, z / f);
}
double Vector3::angle( Vector3 &v)
{
	double r = this->length()*v.length();
	return acos((*this)*v / r);
	

}
Vector3 Vector3::operator*(double f)
{
	return Vector3(x*f, y*f, z*f);
}

double Vector3::dot(const Vector3 &v)
{
	return x * v.x + y * v.y + z * v.z;
}

double Vector3::length()
{
	return sqrtf(dot(*this));
}
double Vector3::getsqr()
{
	sqr = (*this)*(*this);
	return sqr;
}
//double Vector3::distance( Vector3 &vx,  Vector3 &v1,  Vector3 &v2)
//{
//	return abs(((v2 - v1)*(v1 - vx) / (v2 - v1).length()).length());
//}
void Vector3::normalize()
{
	float len = length();
	if (len < uZero) len = 1;
	len = 1 / len;

	x *= len;
	y *= len;
	z *= len;
}

/*
Cross Product叉乘公式
aXb = | i,  j,  k  |
| a.x a.y a.z|
| b.x b.y b.z| = (a.y*b.z -a.z*b.y)i + (a.z*b.x - a.x*b.z)j + (a.x*b.y - a.y*b.x)k
*/
Vector3 Vector3::crossProduct(const Vector3 &v)
{
	return Vector3(y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x);
}

void Vector3::printVec3()
{
	std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}