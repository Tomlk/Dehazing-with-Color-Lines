#include "Patch.h"
Patch::Patch(int x,int y)
{
	X = x;
	Y = y;
	//T = new double[Img_h][Img_w];
	A = Vector3(0.65, 0.7, 0.71);

	Initial();

}


Patch::~Patch()
{

	//delete T;
}
void Patch::Initial()
{
	for (int i = 0; i<Length; i++)
		for (int j = 0; j < Length; j++)
		{
			significant[i][j] = true;

		}
	LineD =Vector3(0, 0, 0);
	LineV =  Vector3(0, 0, 0);
	OmiGa = 0;
	transmission = 0.0;

}
void Patch::ransac(double m[Img_h][Img_w][3])
{
	double threshold = 0.02;
	int n_pairs = 30;
	Vector3 vx = Vector3(0, 0, 0);
	Vector3 v1 = Vector3(0, 0, 0);
	Vector3 v2 = Vector3(0, 0, 0);
	int x1, y1, x2, y2, tx, ty = 0;
	double dist = 0.0;
	int countNearPoints, bestCount = 0;
	for (int k = 0; k < n_pairs; k++)
	{
		//qDebug() << "n_pairs:" << k << endl;
		//使用rt
		genDistnctRandomNumber(2, Length*Length);
		//int randa[2];
		int i= rt[0];
		int j = rt[1];
		if (i != j)
		{
			x1 = i % Length + X;
			y1 = i / Length + Y;
			x2 = j % Length + X;
			y2 = j / Length + Y;
			v1 = Vector3(m[x1][y1][0], m[x1][y1][1], m[x1][y1][2]);
			v2 = Vector3(m[x2][y2][0], m[x2][y2][1], m[x2][y2][2]);
			if ((v1 - v2).length() != 0)
			{
				countNearPoints = 0;
				for(int tx=X;tx++;tx<X+Length)
					for (int ty = Y; ty++; ty < Y + Length)
					{
						vx = Vector3(m[tx][ty][0], m[tx][ty][1], m[tx][ty][2]);
						//Vector3 vTest;
						dist = distance(vx, v1, v2);
						if (dist < threshold)
							countNearPoints += 1;
					}
				if (countNearPoints > bestCount)
				{
					int c1 = 0;
					bestCount = countNearPoints;
					for (int dx = 0; dx < Length; dx++)
					{
						for (int dy = 0; dy < Length; dy++)
						{
							tx = dx + X;
							ty = dy + Y;
							Vector3 vT(m[tx][ty][0], m[tx][ty][1], m[tx][ty][2]);
							int d = distance(vT,v1,v2);
							significant[dx][dy] = (d < threshold);
							if (d < threshold)
								c1 += 1;
							LineD = v2 - v1;
							LineV = v1;
						}
					}
				}
			}
		}

	}


}
void  Patch::genDistnctRandomNumber(int num, int max)
{
	rt = new int(num);
	for (int i = 0; i < num; i++)
		rt[i] = 0;
	int count = 0;
	/*bool* flag = new bool(max);
	for (int j = 0; j < max; j++)
		flag[j] = false;
	int t = 0;*/
	srand((unsigned)time(NULL));
	while (count < num)
	{
		rt[num] = rand() % max;
		count++;
	}
	//return rt

}
double Patch::distance(Vector3 &vx, Vector3 &v1, Vector3 &v2)
{
	Vector3 vec1 = (v2 - v1).vec_X(v1 - vx);

	double rt= abs((vec1 / (v2 - v1).length()).length());
	return rt;
}
void Patch::findColorLine()
{
	if (LineD.x < 0) LineD = LineD * -1;

}
bool Patch::test(double m[Img_h][Img_w][3])
{
	return (SignificantLineSuport() && PositiveReflectance()
		&& largeIntersectionAngle() && Unimodality(m) && CloseIntersection() &&
		ValidTransmission() && SufficientShading(m));

}
bool Patch::ValidTransmission()
{
	if (transmission < 0 || transmission>1)
		return false;
	return true;
}
bool Patch::SufficientShading(double m[Img_h][Img_w][3])
{
	double s = 0.0;
	double s2 = 0.0;
	int tx, ty = 0;
	for(int dx=0;dx<Length;dx++)
		for (int dy = 0; dy < Length; dy++)
		{
			tx = X + dx;
			ty = Y + dy;
			double v = (Vector3(m[tx][ty][0], m[tx][ty][1], m[tx][ty][2]) - LineV)*LineD;
			s2 += v;
			if (significant[dx][dy])
				s += v;

		}
	int avg = s / OmiGa;
	int OmiGa_variance = (s2 - OmiGa * avg*avg) / (OmiGa - 1);
	if (sqrt(OmiGa_variance) / transmission < 0.02)
		return false;
	return true;
}
bool Patch::CloseIntersection()
{
	Vector3 D = LineD / LineD.length();
	Vector3 A_ = A / A.length();
	Vector3 V = LineV;
	double AD = A_ * D;
	double DV = D * V;
	double AV = A_ * V;
	double l = (-DV + AD * AV) / (1 - AD * AD) / LineD.length();
	double s = (-DV * AD + AV) / (1 - AD * AD) / A.length();
	transmission = 1 - s;	//t
	Vector3 v = LineD * 1 + V - A * s;  //
	double d = v * v;
	if (d > 0.05)		//不在color line上
		return false;
	return true;
	
}
bool Patch::Unimodality(double m[Img_h][Img_w][3])
{
	double minv = 10000.0;
	double maxv = 10000.0;
	double s_angle = 0.0;
	for(int dx=0;dx<Length;dx++)
		for (int dy = 0; dy < Length; dy++)
		{
			if (significant[dx][dy])
			{
				int tx = X + dx;
				int ty = Y + dy;
				double v = (Vector3(m[tx][ty][0], m[tx][ty][1], m[tx][ty][2]) - LineV)*LineD;
				double angle = v / (LineD.length()*(Vector3(m[tx][ty][0], m[tx][ty][1], m[tx][ty][2]) - LineV).length());
				if (angle > M_PI / 2) angle = M_PI - angle;
				s_angle += angle;
				if (v > maxv) maxv = v;
				if (v < minv) minv = v;
			}
		}

			double a = 1 / (maxv - minv)*M_PI;
			double b = -minv;
			double s = 0.0;

			for(int dx=0;dx<Length;dx++)
				for (int dy = 0; dy < Length; dy++)
				{
					if (significant[dx][dy])
					{
						int tx = X + dx;
						int ty = Y + dy;
						double v = (Vector3(m[tx][ty][0], m[tx][ty][1], m[tx][ty][2]) - LineV)*LineD;
						s += cos(a*(v + b) - M_PI);
					}
				}
			if (s / OmiGa > 0.07)
				return false;
			return true;

		

}
bool Patch::SignificantLineSuport()
{
	//统计siginificant数组中true的个数
	int sum = 0;
	for(int i=0;i<Length;i++)
		for (int j = 0; j < Length; j++)
		{
			if (significant[i][j] == true)
				sum++;
		}
//wait to finish
	OmiGa = sum;
	if (OmiGa > (Length*Length * 2 / 5)) //丢弃在patches中少于40%像素支持的line
		return true;
	return false;
}
bool Patch::PositiveReflectance() //阳性反应
{
	if (LineD.y > 0 && LineD.z > 0)
		return true;
	return false;

}
bool Patch::largeIntersectionAngle()
{
	if (A.angle(LineD) > M_PI / 12)			//15°
		return true;
	return false;

}
void Patch::calcTransmission(double t[Img_h][Img_w], int countT[Img_h][Img_w])
{
	int tx, ty = 0;
	for(int dx=0;dx<Length;dx++)
		for (int dy = 0; dy < Length; dy++)
		{
			tx = dx + X;  //图像中坐标
			ty = dy + Y; //图像中坐标
			if (significant[dx][dy])
			{
				t[tx][ty] = (t[tx][ty] * countT[tx][ty] + transmission) / (countT[tx][ty] + 1)*1.35;
				if (t[tx][ty] > 1) t[tx][ty] = 1;
				countT[tx][ty] += 1;
			}

			GlobalClass::t[tx][ty] = t[tx][ty];
		}

}