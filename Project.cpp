#include "Project.h"
Project::Project(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Ar = 0;
	Ag = 0;
	Ab = 0;

	connect(ui.Bt_openImg, SIGNAL(clicked()), this, SLOT(Bt_OPEN()));
	connect(ui.Bt_start, SIGNAL(clicked()), this, SLOT(Bt_DEAL()));

}
void Project::Bt_OPEN()
{

	file_full = QFileDialog::getOpenFileName(this);
	fi = QFileInfo(file_full);
	file_name = fi.fileName();
	file_path = fi.absolutePath();
	realAd = file_path + "/" + file_name;
	QMessageBox::information(this, " ", realAd, QMessageBox::Yes);
	srcImg.load(realAd);
	QPixmap pixmap(QPixmap::fromImage(srcImg));
	ui.Img_label->setPixmap(pixmap);
}
void Project::Bt_DEAL()
{
	Ar = ui.Edit_R->text().toDouble();
	Ag = ui.Edit_G->text().toDouble();
	Ab = ui.Edit_B->text().toDouble();
	if (Ar >2||Ar<0 )
	{
		QMessageBox::information(this, "parameter invalid!", "please input proper parameter", QMessageBox::Yes);
		return;
	}
	if (Ag >2 || Ag<0)
	{
		QMessageBox::information(this, "parameter invalid!", "please input proper parameter", QMessageBox::Yes);
		return;
	}
	if (Ab >2 || Ab<0)
	{
		QMessageBox::information(this, "parameter invalid!", "please input proper parameter", QMessageBox::Yes);
		return;
	}

	colorLine = new ColorLine(GBK::q2s(realAd), Ar, Ag, Ab);
	Mat mOutImg=colorLine->getoutImg();
	imwrite(GBK::q2s(file_name)+"_out.jpg", mOutImg);
	//saveoutImage = IplImage(mOutImg);
	//cvSaveImage("./out.jpg", &saveoutImage);
	QImage qimag = MatToQImage(mOutImg);
	outImg = qimag;
	ui.ImgOut_label->setPixmap((QPixmap::fromImage(outImg)));
	qDebug() << "noerror!" << endl;
	/*
	cv::cvtColor(mOutImg, mOutImg, CV_RGB2RGBA);
	outImg = QImage((const unsigned char*)(mOutImg.data),
		mOutImg.cols, mOutImg.rows, QImage::Format_RGB32);
	ui.ImgOut_label->setPixmap((QPixmap::fromImage(outImg)));
	*/
}
QImage Project::MatToQImage(const cv::Mat& mat)
{
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)  
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat  
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3  
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		qDebug() << "CV_8UC4";
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}


}