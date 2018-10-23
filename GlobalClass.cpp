#include "GlobalClass.h"
double GlobalClass::t[Img_h][Img_w] = { {0} };
double GlobalClass::tt[Img_h][Img_w] = { { 0 } };
double GlobalClass::sigma[Img_h][Img_w] = { {1} };
double GlobalClass::gradient[Img_h][Img_w] = { { 0 } };
GlobalClass::GlobalClass()
{
}


GlobalClass::~GlobalClass()
{
}
