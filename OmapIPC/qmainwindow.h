#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qmainwindow.h"
#include <qprocess.h>
#include <OMapApi.h>
#include <qdebug.h>
#include "gapcoordinatetranslate.h"

struct tagMyCoordinate
{
	int line; //线号
	int trace;//道号
	double lat;//纬度
	double ling;//经度
};
struct tagOriginData
{
	int line; //线号
	int trace;//道号
	double _x;
	double _y;
	double _h;	
	
};
class OMapApiTest : public QMainWindow
{
	Q_OBJECT

public:
	OMapApiTest(QWidget *parent = Q_NULLPTR);
	char* CStringToUtf8(CString &strTxt, char* strUtf8, int nBuf);
	void AlertErrSendOmapMsg(int ret);
	void DataTrans();
	void SetobjectToMap(int idParent);
	//LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public	slots:
		void on_pushButton_clicked();		
		void on_SetTmpSign_clicked();
		void on_GetLatLig_clicked();
		void on_ReadFile_clicked();
		void on_patchDataPush_clicked();
protected:
	
	 virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
	QMap<QPair<int, int>, QPair<double, double>> m_cdpMap; 
	QVector<tagMyCoordinate>  m_my_coordinates;
	QVector<tagOriginData>  m_origindata;
	void  TxtFileRead(QString fileName);
	static CString Utf8ToCString(const char * strUtf8);
	Ui::QMainWindowClass ui; 
	QProcess  myProcess;
};
