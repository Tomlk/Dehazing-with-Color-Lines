#pragma once

class GlobalClass
{
public:
	GlobalClass();
	~GlobalClass();
public:
	static const int Img_h = 600;
	static const int Img_w = 400;
	static double t[Img_h][Img_w];
	static double tt[Img_h][Img_w];
	static double sigma[Img_h][Img_w];
	static double gradient[Img_h][Img_w];
};

