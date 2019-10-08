#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qmainwindow.h"
#include <qprocess.h>
#include <OMapApi.h>
#include <qdebug.h>

class OMapApiTest : public QMainWindow
{
	Q_OBJECT

public:
	OMapApiTest(QWidget *parent = Q_NULLPTR);
	
	//LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public	slots:
		void on_pushButton_clicked();		
		void on_SetTmpSign_clicked();
		void on_GetLatLig_clicked();
protected:
	//LRESULT QT_WIN_CALLBACK QtWndProc( UINT message, WPARAM wParam, LPARAM lParam);
	 bool winEvent(MSG *message, long *result);	
	 //virtual LRESULT QT_WIN_CALLBACK qt_internal_proc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp);
	 virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
	 //bool nativeEvent(UINT message, WPARAM wParam, LPARAM lParam);
private:
	CString Utf8ToCString(const char * strUtf8);
	Ui::QMainWindowClass ui; 
	QProcess  myProcess;
};
