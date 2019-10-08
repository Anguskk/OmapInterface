#include "qmainwindow.h"
#include <QtWidgets/QApplication>
//#include <qstringlist.h>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	//QProcess *qp1=new QProcess;
	//QString program = "C:\\Windows\\System32\\cmd.exe";
	//QStringList arguments1;
	//arguments1 << "-style" << "first";
	//qp1->start(program, arguments1);
	OMapApiTest w;
	
	//::RegisterHotKey((HWND)w.winId());
	/*HWND appwnd;
	appwnd = (HWND)w.winId();
	SetWindowLong(appwnd, GWLP_WNDPROC, GWLP_ID);*/
	
	w.show();
	return app.exec();
}
