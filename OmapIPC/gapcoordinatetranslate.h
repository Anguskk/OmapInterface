#ifndef GAPCOORDINATETRANSLATE_H
#define GAPCOORDINATETRANSLATE_H
#include <math.h> 
#include <QPointF>

#ifndef PI
#define PI 3.14159265353846
#endif

#ifndef E
#define E 2.718281828
#endif

class GAPCoordTranslate
{
public:
	/*****************************************************************************
	Function:   	GAPCoordTranslate()
	Description:	 构造函数
	Input:          		无
	Output:         	无
	Return:         	无
	Others:         	无
	*******************************************************************************/
	GAPCoordTranslate();

	/*****************************************************************************
	Function:   	~GAPCoordTranslate()
	Description:	 析构函数
	Input:          		无
	Output:         	无
	Return:         	无
	Others:         	无
	*******************************************************************************/
	~GAPCoordTranslate();

	/*******************************************************************************************************
	Function:   	Dms2Rad
	Description:    角度到弧度的转化
	Input:          Dms 角度值
	Output:         无
	Return:         弧度值
	Others:         无
	*******************************************************************************************************/
	double Dms2Rad(double Dms);

	/*******************************************************************************************************
	Function:   	Rad2Dms
	Description:    弧度到角度的转化
	Input:          Rad 弧度值
	Output:         无
	Return:         角度值
	Others:         无
	*******************************************************************************************************/
	double Rad2Dms(double Rad);

	/*******************************************************************************************************
	Function:   	LoLaToxy
	Description:    经纬度坐标转为大地坐标
	Input:         lo 经度, la 纬度
	Output:         无
	Return:         QPointF（纵坐标，横坐标）
	Others:         当遇到出现跨带的情况时，需要单独处理，中央子午线需要针对每条经度线重新单独计算
	*******************************************************************************************************/
	 QPointF LoLaToxy(double lo,double la);

	/*******************************************************************************************************
	Function:   	xyToLoLa
	Description:    大地坐标转为经纬度坐标
	Input:          m_x 横坐标, m_y 纵坐标
	Output:         无
	Return:        经度纬度
	Others:         无
	*******************************************************************************************************/
	 QPointF xyToLoLa(double x,double y);

	/*******************************************************************************************************
	Function:   	SetCoordSysType
	Description:    设置标准椭球体类型,默认为0
	Input:          type 标准椭球体类型
	Output:         无
	Return:         是否成功
	Others:         0为克鲁索夫斯基椭球体，1为国家UGG1975椭球体，2为WGS84椭球体
	*******************************************************************************************************/
	bool SetCoordSysType(int type);

	/*******************************************************************************************************
	Function:   	SetAB
	Description:    设置其他椭球体
	Input:         da和db为椭球体的长半径和短半径
	Output:         无
	Return:         是否成功
	Others:         无
	*******************************************************************************************************/
	bool SetAB(double da,double db);

	/*******************************************************************************************************
	Function:   	SetParaDegree
	Description:    设置分段度数
	Input:          ParaDegree 分段度数
	Output:         无
	Return:         是否成功
	Others:         无
	*******************************************************************************************************/
	bool SetParaDegree(double ParaDegree);

	/*******************************************************************************************************
	Function:   	SetZoneNum
	Description:    设置工区带号和中央子午线经度
	Input:          l_lo 左经度, r_lo 右经度
	Output:         无
	Return:         是否成功
	Others:         1、六度带计算工区带号，是根据中线所在的带号来算的
					2、无论三度带还是六度带，计算中央子午线经度时均是取的它们中线所在区的中央子午线
					3、对于无带号的情况，中央子午线经度为它们中线的经度
	*******************************************************************************************************/
	bool SetZoneNum(double l_lo, double r_lo);

	/*******************************************************************************************************
	Function:   	SetLoLa
	Description:    设置经纬度坐标
	Input:          dLo 经度, dLa 纬度
	Output:         无
	Return:         是否成功
	Others:         无
	*******************************************************************************************************/
	bool SetLoLa(double dLo, double dLa);

	/*******************************************************************************************************
	Function:   	SetTempxy
	Description:    设置大地坐标
	Input:          dx 横坐标,dy 纵坐标
	Output:         无
	Return:         是否成功
	Others:         无
	*******************************************************************************************************/
	bool SetTempxy(double dx, double dy);

	/*******************************************************************************************************
	Function:   	SetOriginLongitude
	Description:    设置中央子午线经度
	Input:        _OriginLongitude 中央子午线经度
	Output:         无
	Return:         无
	Others:         无
	*******************************************************************************************************/
	void SetOriginLongitude(double _OriginLongitude);

	/*******************************************************************************************************
	Function:   	setFirstOriginLongitude
	Description:    设置第一次(即原始图件上设置的)中央子午线经度
	Input:         _OriginLongitude 中央子午线经度
	Output:         无
	Return:         无
	Others:         无
	*******************************************************************************************************/
	void setFirstOriginLongitude(double _OriginLongitude);

	/*******************************************************************************************************
	Function:   	SetEF
	Description:    设置东偏移（默认设置为500000）
	Input:         ef 东偏移
	Output:         无
	Return:         是否成功
	Others:         无
	*******************************************************************************************************/
	bool setEF(double ef = 500000.0);

	/*******************************************************************************************************
	Function:   	SetNF
	Description:    设置西偏移（默认设置为0）
	Input:          nf 西偏移
	Output:         无
	Return:         是否成功
	Others:         无
	*******************************************************************************************************/
	bool setNF(double nf = 0.0);

	/*******************************************************************************************************
	Function:   	zoneNumToToLa
	Description:    将含有带号的坐标转到当前区带上的经纬度
	Input:          _pos传入的含有带号的点，_da长轴，_db短轴，_paraDegree几度带，_originLongitude中央子午线，_ef东偏移，_nf西偏移
	Output:         无
	Return:         经纬度
	Others:         无
	*******************************************************************************************************/
	QPointF zoneNumToLoLa(const QPointF &_pos,const double _da,const double _db,const double _paraDegree,
		const double _originLongitude,const double _ef = 500000.0,const double _nf = 0.0);

	/*******************************************************************************************************
	Function:   	zoneNumToNoNum
	Description:    将含有带号的坐标转到无带号坐标
	Input:           _pos传入的含有带号的点，_da长轴，_db短轴，_paraDegree几度带，_originLongitude中央子午线，_ef东偏移，_nf西偏移
	Output:         无
	Return:         无带号坐标
	Others:         无
	*******************************************************************************************************/
	QPointF zoneNumToNoNum(const QPointF &_pos,const double _da,const double _db,const double _paraDegree,
		const double _originLongitude,const double _ef = 500000.0,const double _nf = 0.0);

	/*******************************************************************************************************
	Function:   	noNumToZoneNum
	Description:    将无带号坐标转变为经纬度
	Input:         &_pos 无带号坐标
	Output:         无
	Return:         经纬度
	Others:         无
	*******************************************************************************************************/
	QPointF noNumToLoLa(const QPointF &_pos);

	/*******************************************************************************************************
	Function:   	noNumToZoneNum
	Description:    将无带号坐标转变成有带号坐标
	Input:         _pos 无带号坐标
	Output:         无
	Return:         有带号坐标
	Others:         无
	*******************************************************************************************************/
	QPointF noNumToZoneNum(const QPointF &_pos);

protected:
	double a,b,n, f, e2, e12;//基本椭球参数,a长半径,b短半径,n=(a-b)/(a+b),f扁率,e2第一偏心率平方,e12第二偏心率平方
	double A1, A2, A3, A4;//用于计算X的椭球参数

public:
	double m_setOriginLongitude;//中央子午线经度
	double m_originLongitude;//创建图件时设置的中央子午线(不要修改)
	double m_Lo, m_La;//经纬度坐标
	double x, y;//高斯投影平面坐标
	double BK;//标准纬度
	double m_ZoneNum;//工作区带号
	double m_ParaDegree;//分段度数
	int m_CoordSysType;//标准类型(0为克鲁索夫斯基标准，1为国家UGG1975标准,2为WGS84椭球体)
	static bool m_crossDiffArea;//判断是否跨带
	double EF;//东偏移
	double NF;//北偏移
};

#endif //COORDINATETRANSLATE_H
