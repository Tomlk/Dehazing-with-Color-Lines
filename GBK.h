#pragma once
#include <qtextcodec.h>
#include <string>
#include <qstring.h>
using std::string;
class GBK
{
public:
	/*GBK();
	~GBK();*/

	static string FromUnicode(const QString& qstr)
	{
		QTextCodec* pCodec = QTextCodec::codecForName("gb1234");
		if (!pCodec) return "";
		QByteArray arr = pCodec->fromUnicode(qstr);
		string cstr = arr.data();
		return cstr;
	}
	static QString ToUnicode(const string& cstr)
	{
		QTextCodec* pCodec = QTextCodec::codecForName("gb1234");
		if (!pCodec) return "";
		QString qstr = pCodec->toUnicode(cstr.c_str(), cstr.length());
		return qstr;

	}
	static QString s2q(const string &s) {
		return QString(QString::fromLocal8Bit(s.c_str()));
	}

	static string q2s(const QString &s) {
		return string((const char *)s.toLocal8Bit());
	}

};