#pragma once
#include "opencv2/imgproc/imgproc.hpp"    
#include "opencv2/highgui/highgui.hpp"   
#include <QtWidgets/QMainWindow>
#include "ui_Project.h"
#include "qfileinfo.h"
#include "qfiledialog.h"
#include "qmessagebox.h"
#include "ColorLine.h"
#include "GBK.h"
#include "qdebug.h"
using namespace cv;
class Project : public QMainWindow
{
	Q_OBJECT

public:
	Project(QWidget *parent = Q_NULLPTR);
	QImage MatToQImage(const cv::Mat& mat);

private:
	Ui::ProjectClass ui;
	QFileInfo fi;
	QString file_full;
	QString file_name; 
	QString file_path;
	QString realAd;
	ColorLine* colorLine;
private slots:
	void Bt_OPEN();
	void Bt_DEAL();



private:
	double Ar, Ag, Ab;
	QImage srcImg;
	QImage outImg;
	IplImage saveoutImage;
};
