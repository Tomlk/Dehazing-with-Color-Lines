#include "ColorLine.h"

ColorLine::ColorLine(String imgSource,double ar,double ag,double ab)
{
	AR = ar;
	AG = ag;
	AB = ab;
	//m[731][1024][3] = {0};
	for (int i = 0; i < Img_h; i++)
	{
		for (int j = 0; j < Img_w; j++)
		{
			//t[i][j] =0;
			//	GlobalClass::tt[i][j] = 0;
		}

	}
	for (int i = 0; i < Img_h; i++)
	{
		for (int j = 0; j < Img_w; j++)
		{
			countT[i][j] = 0;
		}

	}
	for (int i = 0; i < Img_h; i++)
	{
		for (int j = 0; j < Img_w; j++)
		{
			m[i][j][0] = 0;
			m[i][j][1] = 0;
			m[i][j][2] = 0;
		}

	}

	//t[731][1024] = { 0 };
	//countT[731][1024] = { 0 };
	const Mat img = imread(imgSource);
	this->SrcImg = img;
	
	srcImg1 = &IplImage(SrcImg);
	//const int Img_w = SrcImg.rows;
	//const int Img_h = SrcImg.cols;
	//srcImg_pixW = SrcImg.rows;
	//srcImg_pixH = SrcImg.cols;
	//qDebug() << "(" << Img_h << "," << Img_w << ")" << endl;
	//double m[Img_w][Img_h][3] = { {{0}} };
	//m数组的重新赋值
	

	//像素拷贝 0~255 ->0~1
	for (int i = 0; i < srcImg1->height; i++)
	{
		for (int j = 0; j < srcImg1->width; j++)
		{
			if (i == srcImg1->height)
				break;

				scalar = cvGet2D(srcImg1, i, j);

				//m[i][j][k] = SrcImg.at<Vec3b>(i, j)[k] / 255.0;
				m[i][j][0] = scalar.val[2] / 255.0;  //Red
			//	qDebug() << "m[" << i << "][" << j << "][0]:" << m[i][j][0];
				m[i][j][1] = scalar.val[1] / 255.0;	 //Green	
				//qDebug() << "m[" << i << "][" << j << "][1]:" << m[i][j][1];
				m[i][j][2] = scalar.val[0] / 255.0;		//Blue
				//qDebug() << "m[" << i << "][" << j << "][2]:" << m[i][j][2];
			

		}
	}

	for(int dx=0;dx<=3;dx+=3)
		for (int dy = 0; dy <= 3; dy += 3)
		{
			
			//if (dx > 3) break;
			qDebug() << "dx"<<dx<<",dy"<<dy<< endl;
			findPatches(dx, dy, m);
			//FindMchange();
			qDebug() << "ransac..." << endl;
			list<Patch>::iterator iter;
			for (iter = patchlist.begin(); iter != patchlist.end(); iter++)
			{
				iter->ransac(m); //RANSAC函数
				
			}
			//FindMchange();
			qDebug() << "find color lines..." << endl;
			for (iter = patchlist.begin(); iter != patchlist.end(); iter++)
			{
				iter->findColorLine();
			}

			qDebug() << "validating patches" << endl;
		
				for (iter = patchlist.begin(); iter != patchlist.end(); iter++)
				{
					if (iter->test(m))
					{
					
						iter->calcTransmission(GlobalClass::t, countT);
						//T赋值给t
					
					}

				}
			


		}


	qDebug() << "interpolating..." << endl;
	smooth();
	qDebug() << "gradientDecent..." << endl;
	gradientDecent(GlobalClass::t, m); //获得tt
	qDebug() << "recovering..." << endl;


	recover(m, GlobalClass::tt, AR, AG, AB);

	qDebug() << "generating image..." << endl;
	//IplImage*img_t = cvCreateImage(cvSize(ColorLine::Img_h, ColorLine::Img_w), IPL_DEPTH_8U, 3);
	//IplImage*img_tt = cvCreateImage(cvSize(ColorLine::Img_h, ColorLine::Img_w), IPL_DEPTH_8U, 3);
	IplImage*image = cvCreateImage(cvSize(Img_w, Img_h), IPL_DEPTH_8U, 3);


	//double colorRGB[3] = {0,0,0};
	//获取恢复图像像素值
	for (int h = 0; h < image->height; h++)
	{
		uchar* ptr1 = (uchar*)(image->imageData + h * image->widthStep);
		for (int w = 0; w < image->width; w++)
		{
			ptr1[3 * w + 2] = double2RGB(rt[h][w][0]);
			ptr1[3 * w + 1] = double2RGB(rt[h][w][1]);
			ptr1[3 * w ] = double2RGB(rt[h][w][2]);
		//	qDebug() << "rgb(" << h << "," << w << ")" <<"("<< ptr1[3 * h + 2]<<","<< 
		//		ptr1[3 * h + 1]<<","<<ptr1[3 * h ]<<")" << endl;
			
		}

		//qDebug() << "rgb(" << h << "," << w << ")" << "(" << ptr1[3 * h + 2] << "," <<
			//ptr1[3 * h + 1]<<","<<ptr1[3 * h ]<<")" << endl;
	}
	outImg = cvarrToMat(image);
	
}
bool ColorLine::inBoard(int x, int y, int height, int width)
{

	return x >= 0 && x < height&&y >= 0 && y < width;
}
/*
double ColorLine::getgaussian(double x, double signma)
{
	return exp(-x * x / (2 * signma*signma)) / (signma*sqrt(2 * M_PI));

}*/
void ColorLine::smooth()
{
	int r = 25;
	double threshold = 0.4;
	int height = Img_h;
	int width = Img_w;
	for(int i=0;i<height;i++)
		for (int j = 0; j < width; j++)
		{
			if (GlobalClass::t[i][j] < 0.3)
			{
				int sh = 0;
				int sl = 0;
				for(int dx=-r;dx<=r;dx++)
					for (int dy = -r; dy <= r; dy++)
					{
						int tx = i + dx;
						int ty = j + dy;
						if (inBoard(tx, ty, height, width))
						{
							if (GlobalClass::t[tx][ty] > threshold) sh += 1;
							else if (GlobalClass::t[tx][ty] > 0 && GlobalClass::t[tx][ty] < threshold) sl += 1;
						}
					}
				if (sh > sl)
					GlobalClass::t[i][j] = 0;
			}
		}

}
void ColorLine::findPatches(int dx, int dy, double m[Img_h][Img_w][3])
{ 
	patchlist.clear(); //清空一次 保证最开始无
	int step = 7;
	for (int i = 0; i < Img_h; i += step)
	{
		for (int j = 0; j < Img_w; j += step)
		{
			if (dx + i + Patch::Length <= Img_w && dy + j + Patch::Length <= Img_h)
			{
				//Patch* patch = new Patch(i + dx, j + dy);
				patchlist.push_back(Patch(i + dx, j + dy));
			}
		}
	}

}
int ColorLine::double2RGB(double color)
{
	int t = round(color* 255);
	//qDebug() << "t:" << t << endl;
	if (t > 255) t = 255;
	if (t < 0) t = 0;
	return t;
}
/*
int ColorLine::double2RGB(double color[3])
{
	int rgb = 0;
	if (color[1] == 0) return 0x00fffff;
	for (int i = 0; i < 3; i++)
	{
		int t = round(color[i] * 255);
		if (t > 255) t = 255;
		if (t < 0) t = 0;
		rgb += t << ((2 - i) * 8);
	}

	return rgb;

}*/
void ColorLine::recover(double I[Img_h][Img_w][3], double t[Img_h][Img_w], double AR, double AG, double AB)
{
	int height = Img_h;
	int width = Img_w;
	for(int i=0;i<height;i++)
		for (int j = 0; j < width; j++)
		{
			//qDebug() << "t[" << i << "]" << "[" << j << "]"  << t[i][j] << endl;
			rt[i][j][0] = (I[i][j][0] - ((1 - t[i][j])*AR)) / t[i][j];
			//qDebug() << "I[" << i << "]" << "[" << j << "]" << "[0]:" << I[i][j][0] << endl;
		//	qDebug() << "rt[" << i << "]" << "[" << j << "]" << "[0]:" << rt[i][j][0] << endl;
			//qDebug() << "m[" << i << "]" << "[" << j << "]" << "[0]:" << m[i][j][0] << endl;
			rt[i][j][1] = (I[i][j][1] - ((1 - t[i][j])*AG)) / t[i][j];
			//qDebug() << "I[" << i << "]" << "[" << j << "]" << "[1]:" << I[i][j][1] << endl;
			//qDebug() << "rt[" << i << "]" << "[" << j << "]" << "[1]:" << rt[i][j][1] << endl;
			//qDebug() << "m[" << i << "]" << "[" << j << "]" << "[1]:" << m[i][j][1] << endl;
			//qDebug() << "rt[" << i << "]" << "[" << j << "]" << "[1]:" << t[i][j] << endl;
			rt[i][j][2] = (I[i][j][2] - ((1 - t[i][j])*AB)) / t[i][j];
			//qDebug() << "I[" << i << "]" << "[" << j << "]" << "[2]:" << I[i][j][2] << endl;
			//qDebug() << "rt[" << i << "]" << "[" << j << "]" << "[2]:" << rt[i][j][2] << endl;
			//qDebug() << "m[" << i << "]" << "[" << j << "]" << "[2]:" << m[i][j][2] << endl;
			//qDebug() << "rt[" << i << "]" << "[" << j << "]" << "[2]:" << t[i][j] << endl;
		}

}
void ColorLine::gradientDecent(double raw_t[Img_h][Img_w], double m[Img_h][Img_w][3])
{

	int height = Img_h;
	int width = Img_w;
	//double sigma[Img_h][Img_w] = { {1} };
	/*for (int i = 0; i < Img_h; i++)
		for (int j = 0; j < Img_w; j++)
			sigma[i][j] = 1;*/


	for(int i=0;i<height;i++)
		for (int j = 0; j < width; j++)
		{
			if (raw_t[i][j] > 0)
				GlobalClass::tt[i][j] = raw_t[i][j];
			else
			{
				GlobalClass::tt[i][j] = 0.2;
				GlobalClass::sigma[i][j] = 1e+30;
				//sigma[i][j] = DBL_MAX;
			}

		}
	double lr = 0.05;
	double decay_rate = 0.9;
	int n_epoch = 10;
	int r = 15;
	//double gradient[Img_h][Img_w] = { {0} };
	/*for (int i = 0; i < Img_h; i++)
		for (int j = 0; j < Img_w; j++)
			gradient[i][j] = 0;
*/

	
	for (int ep = 0; ep < n_epoch; ep++)
	{
		qDebug() <<  "0123456789"+ep << endl;
		for(int i=0;i<height;i++)
			for (int j = 0; j < width; j++)
			{
				GlobalClass::gradient[i][j] = 1 * (GlobalClass::tt[i][j] - raw_t[i][j]) / GlobalClass::sigma[i][j];
				for(int dx=-r;dx<=r;dx++)
					for (int dy = -r; dy <= r; dy++)
					{
						if (dx != 0 || dy != 0)
						{
							int tx = i + dx;
							int ty = j + dy;
							if (inBoard(tx, ty, height, width))
							{
								Vector3 Ix = Vector3(m[i][j][0], m[i][j][1], m[i][j][2]);
								Vector3 Iy = Vector3(m[tx][ty][0], m[tx][ty][1], m[tx][ty][2]);
								GlobalClass::gradient[i][j] += 0.015*(GlobalClass::tt[i][j] - GlobalClass::tt[tx][ty]) / ((Ix - Iy).getsqr() + 0.002) / sqrt(dx*dx + dy * dy);
							}
						}
						
					}
				if (GlobalClass::gradient[i][j] > 1) GlobalClass::gradient[i][j] = 1;
				else if (GlobalClass::gradient[i][j] < -1) GlobalClass::gradient[i][j] = -1;
			}
		//update
		for(int i=0;i<height;i++)
			for (int j = 0; j < width; j++)
			{
				GlobalClass::tt[i][j] -= lr * GlobalClass::gradient[i][j];
				if (GlobalClass::tt[i][j] < 0)
				{
					GlobalClass::tt[i][j] = 0;
				}
				if (GlobalClass::tt[i][j] > 1)
				{
					GlobalClass::tt[i][j] = 1;
				}

			}
		lr *= decay_rate;


	}
	
	
}
/*void ColorLine::laplacianInterpolation(double t[Img_h][Img_w])
{

	int height = Img_h;
	int width = Img_w;
	for (int i = 0; i<height; i++)
		for (int j = 0; j < width; j++)
		{
			if (t[i][j] > 0) GlobalClass::tt[i][j] = t[i][j];
		}

}*/

/*
void ColorLine::uniform(double tt[Img_h][Img_w], double m[Img_h][Img_w][3])
{
	int height = Img_h;
	int width = Img_w;
	int sigma = 3;
	int n_epoch = 1;
	for (int ep = 0; ep < n_epoch; ep++)
	{
		for(int i=0;i<height;i++)
			for (int j = 0; j < width; j++)
			{
				double sum = 0.0;
				double sum_weight = 0.0;
				Vector3 c0 = Vector3(m[i][j][0], m[i][j][1], m[i][j][2]);
				for(int dx=-10;dx<=10;dx++)
					for(int dy=-10;dy<=10;dy++)
						if (inBoard(i + dx, j + dy, height, width))
						{
							int tx = i + dx;
							int ty = j + dy;
							Vector3 ct = Vector3(m[tx][ty][0], m[tx][ty][1], m[tx][ty][2]);
							double weight = getgaussian(dx*dx + dy * dy, sigma)*(c0 - ct).getsqr();
							sum_weight += weight;
							sum += tt[tx][ty] * weight;
						}
				tt[i][j] = sum / sum_weight;
			}
	}
}
*/
Mat ColorLine:: getoutImg()
{
	//outImg = SrcImg;
	return outImg;
}
void ColorLine::setAGB(double r, double g, double b)
{
	this->AR = r;
	this->AG = g;
	this->AB = b;

}
void ColorLine::FindMchange()
{
	for(int h=0;h<Img_h;h++)
		for (int w = 0; w < Img_w; w++)
		{
			qDebug() << "m[" << h << "]" << "[" << w << "]" << "[0]:" << m[h][w][0] << endl;
			qDebug() << "m[" << h << "]" << "[" << w << "]" << "[i]:" << m[h][w][1] << endl;
			qDebug() << "m[" << h << "]" << "[" << w << "]" << "[2]:" << m[h][w][2] << endl;
		}

}