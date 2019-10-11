#include "gapcoordinatetranslate.h"
#include <math.h>
#include <stdlib.h>

bool GAPCoordTranslate::m_crossDiffArea;

/*****************************************************************************
Function:   	GAPCoordTranslate()
Description:	 构造函数
Input:          		无
Output:         	无
Return:         	无
Others:         	无
*******************************************************************************/
GAPCoordTranslate::GAPCoordTranslate()
{
	EF = 500000;
	NF = 0;
}

/*****************************************************************************
Function:   	~GAPCoordTranslate()
Description:	 析构函数
Input:          		无
Output:         	无
Return:         	无
Others:         	无
*******************************************************************************/
GAPCoordTranslate::~GAPCoordTranslate()
{

}

/*******************************************************************************************************
Function:   	Dms2Rad
Description:    角度到弧度的转化
Input:          Dms 角度值
Output:         无
Return:         弧度值
Others:         无
*******************************************************************************************************/
double GAPCoordTranslate::Dms2Rad( double Dms )
{
	double Degree, Miniute;   
	double Second;   
	int Sign;   
	double Rad;
	//角度标注
	if(Dms >= 0)   
		Sign = 1;   
	else//否则为负数 
		Sign = -1;   
	Dms = fabs(Dms);   
	Degree = floor(Dms);   
	Miniute = floor(fmod(Dms * 100.0, 100.0));   
	Second = fmod(Dms * 10000.0, 100.0);   
	Rad = Sign * (Degree + Miniute / 60.0 + Second / 3600.0) * PI / 180.0;   
	return Rad;
}

/*******************************************************************************************************
Function:   	Rad2Dms
Description:    弧度到角度的转化
Input:          Rad 弧度值
Output:         无
Return:         角度值
Others:         无
*******************************************************************************************************/
double GAPCoordTranslate::Rad2Dms( double Rad )
{
	double Degree, Miniute;   
	double Second;   
	int Sign;   
	double Dms;
	//弧度标注
	if(Rad >= 0)   
		Sign = 1;   
	else//否则为负数
		Sign = -1;   
	Rad = fabs(Rad * 180.0 / PI);   
	Degree = floor(Rad);   
	Miniute = floor(fmod(Rad * 60.0, 60.0));   
	Second = fmod(Rad * 3600.0, 60.0);   
	Dms = Sign * (Degree + Miniute / 100.0 + Second / 10000.0);   
	return Dms; 
}

/*******************************************************************************************************
Function:   	LoLaToxy
Description:    经纬度坐标转为大地坐标
Input:         lo 经度, la 纬度
Output:         无
Return:         QPointF（纵坐标，横坐标）
Others:         当遇到出现跨带的情况时，需要单独处理，中央子午线需要针对每条经度线重新单独计算
*******************************************************************************************************/
QPointF GAPCoordTranslate::LoLaToxy(double lo,double la)
{
// 	SetParaDegree(0);
// 	SetZoneNum(lo,lo);
	SetParaDegree(6);//初始化为6度带
	SetZoneNum(lo,lo);
	SetCoordSysType(1);
	//判断是否跨带，如果跨带，则单独算每个经度点的中央子午线，分别进行转换
	if (m_crossDiffArea)
	{
		SetZoneNum(lo, lo); //对于经度线lo，重新衡量其中央子午线
	}
	a = 6378140;
	b = 6356755.28820;
	e2 = 1-(b/a)*(b/a);
	e12 = (a/b)*(a/b)-1;
	lo = lo*PI/180.0;    //经度
	la = la*PI/180.0;    //纬度
	double T = tan(la)*tan(la); 
	double C = e12*cos(la)*cos(la);
	double A = (lo - m_setOriginLongitude*PI/180.0)*cos(la);
	double M = a*((1-(e2/4)-(3*e2*e2/64)-(5*e2*e2*e2/256))*la-((3*e2/8)+(3*e2*e2/32)+(45*e2*e2*e2/1024))*sin(2*la)+
		((15*e2*e2/256)+(45*e2*e2*e2/1024))*sin(4*la)-(35*e2*e2*e2/3072)*sin(6*la));
	double N = (a*a/b)/sqrt(1+e12*cos(la)*cos(la));
	x = M + N*tan(la)*(A*A/2+(5-T+9*C+4*C*C)*A*A*A*A/24)+(61-58*T+T*T+270*C-330*T*C)*A*A*A*A*A*A/720;
	y = N*(A+(1-T+C)*A*A*A/6+(5-18*T+T*T+14*C-58*T*C)*A*A*A*A*A/120);
	
	x = x + NF;
	y = y + EF;
	QPointF realPnt = QPointF(y,x);
	return realPnt;
}

/*******************************************************************************************************
Function:   	xyToLoLa
Description:    大地坐标转为经纬度坐标
Input:          m_x 横坐标, m_y 纵坐标
Output:         无
Return:        经度纬度
Others:         无
*******************************************************************************************************/
QPointF GAPCoordTranslate::xyToLoLa(double m_x,double m_y)
{
// 	m_setOriginLongitude=Dms2Rad(m_setOriginLongitude);
// 	double ee = (1-b/a)/(1+b/a);
// 	double M = m_y;
// 	double e = M/a*(1-e2/4-3*e2*e2/64-5*e2*e2*e2/256);
// 	
// 	double B = (3*e/2-27*e*e*e/32)*sin(2.0)+(21*e*e/16-55*e*e*e*e/32)*sin(4.0)+(151*e*e*e/96)*sin(6.0);
// 	double R = a*(1-e2)/sqrt((1-e2*sin(B)*sin(B))*(1-e2*sin(B)*sin(B))*(1-e	2*sin(B)*sin(B)));
// 	double NN = a/sqrt(1-e2*sin(B)*sin(B));
// 	double N = (a*a/b)/sqrt(1+e12*cos(B)*cos(B));
// 	double T = tan(B)*tan(B);
// 	double C = e12*cos(B)*cos(B);
// 	double FE = 500000;
// 	double D = (m_x - FE)/N;
// 	m_La = B - (N*tan(B)/R)*(D*D/2-(5+3*T+C-9*T*C)*D*D*D*D/24+(61+90*T+45*T*T)*D*D*D*D*D*D/720);
// 	m_Lo = m_setOriginLongitude+(1/cos(B))*(D-(1+2*T+C)*D*D*D/6+(5+28*T+6*C+8*T*C+24*T*T)*D*D*D*D*D/120);
// 	m_Lo=m_Lo*180.0/PI;
// 	m_La=m_La*180.0/PI;
// 	QPointF LoLaPnt = QPointF(m_Lo,m_Lo);
// 	return LoLaPnt;
	int t_code = 18;//工区带号，默认18
	if (m_x/1000000>1)//有带号
	{
		t_code = int(m_x)/1000000;
		m_x = m_x - t_code*1000000;
	}

	if (m_ParaDegree==6)    //六度带
	{
		m_ZoneNum = t_code;    //工区带号
		m_setOriginLongitude = m_ZoneNum * m_ParaDegree - m_ParaDegree / 2;    //中央子午线经度
	}

	SetCoordSysType(1);
	double sinB, cosB, t, t2, N ,ng2, V, yN;   
	double preB0, B0;   
	double eta;   
	double dy=m_x;
	double t_originLongitude;

	dy-= EF;
	m_y -= NF;
	B0 = m_y / A1; 
	do   
	{   
		preB0 = B0;   
		B0 = B0 * PI / 180.0;   
		B0 = (m_y - (A2 * sin(2 * B0) + A3 * sin(4 * B0) + A4 * sin(6 * B0))) / A1;   
		eta = fabs(B0 - preB0);   
	}
	while(eta > 0.000000001);   
	B0 = B0 * PI / 180.0;   
	m_Lo = Rad2Dms(B0); 
	t_originLongitude=Dms2Rad(m_setOriginLongitude);
	sinB = sin(B0);   
	cosB = cos(B0);   
	t = tan(B0);   
	t2 = t * t;   
	N = a / sqrt(1 - e2 * sinB * sinB);   
	ng2 = cosB * cosB * e2 / (1 - e2);   
	V = sqrt(1 + ng2);   
	yN = dy / N;   
	m_La = B0 - (yN * yN - (5 + 3 * t2 + ng2 - 9 * ng2 * t2) * yN * yN * yN * yN /   
		12.0 + (61 + 90 * t2 + 45 * t2 * t2) * yN * yN * yN * yN * yN * yN / 360.0) * V * V * t / 2;   
	m_Lo = t_originLongitude + (yN - (1 + 2 * t2 + ng2) * yN * yN * yN / 6.0 + (5 + 28 * t2 + 24    
		* t2 * t2 + 6 * ng2 + 8 * ng2 * t2) * yN * yN * yN * yN * yN / 120.0) / cosB;   
	m_Lo=m_Lo*180.0/PI;
	m_La=m_La*180.0/PI;
	QPointF LoLaPnt = QPointF(m_Lo,m_La);
	return LoLaPnt;
}

/*******************************************************************************************************
Function:   	SetCoordSysType
Description:    设置标准椭球体类型,默认为0
Input:          type 标准椭球体类型
Output:         无
Return:         是否成功
Others:         0为克鲁索夫斯基椭球体，1为国家UGG1975椭球体，2为WGS84椭球体
*******************************************************************************************************/
bool GAPCoordTranslate::SetCoordSysType( int type )
{
	//防止类型不存在
	if((type<0)||(type>2))
	{   
		//    AfxMessageBox("类型错误，0为克鲁索夫斯椭球体，1为国家UGG1975椭球体,2为WGS84椭球体");   
		return false;   
	}   
	else//否则设置置顶纬线
	{   
		// 克鲁索夫斯椭球体   
		if(type==0)   
		{   
			a = 6378245;   
			b = 6356863.01880;   
		}
		else if(type==1)//国家UGG1975椭球
		{   
			a = 6378140;   
			b = 6356755.28820;   
		}
		else if(type==2)//WGS84椭球体
		{   
			a = 6378137.000;   
			b = 6356752.31420;     
		}   
		f = a/(a-b);   
		e2 = 1 - ((f - 1) / f) * ((f - 1) / f);   
		e12 = (f / (f - 1)) * (f / (f - 1)) - 1;   
		n=(a-b)/(a+b);   
		A1 = a*(1-n+(pow(n,2)-pow(n,3))*5/4+(pow(n,4)-pow(n,5))*81/64)*PI/180;   
		A2 = -(n-pow(n,2)+(pow(n,3)-pow(n,4))*7/8+pow(n,5)*55/64)*3*a/2;   
		A3 = (pow(n,2)-pow(n,3)+(pow(n,4)-pow(n,5))*3/4)*15*a/16;   
		A4 = -(pow(n,3)-pow(n,4)+pow(n,5)*11/16)*35*a/48;  
		return true;   
	} 
}

/*******************************************************************************************************
Function:   	SetAB
Description:    设置其他椭球体
Input:         da和db为椭球体的长半径和短半径
Output:         无
Return:         是否成功
Others:         无
*******************************************************************************************************/
bool GAPCoordTranslate::SetAB( double da, double db )
{
	a=da;   
	b=db;   
	f = a/(a-b);   
	e2 = 1 - ((f - 1) / f) * ((f - 1) / f);   
	e12 = (f / (f - 1)) * (f / (f - 1)) - 1;   
	n=(a-b)/(a+b);   
	A1 = a*(1-n+(pow(n,2)-pow(n,3))*5/4+(pow(n,4)-pow(n,5))*81/64)*PI/180;   
	A2 = (n-pow(n,2)+(pow(n,3)-pow(n,4))*7/8+pow(n,5)*55/64)*3*a/2;   
	A3 = (pow(n,2)-pow(n,3)+(pow(n,4)-pow(n,5))*3/4)*15*a/16;   
	A4 = (pow(n,3)-pow(n,4)+pow(n,5)*11/16)*35*a/48;   
	return true; 
}

/*******************************************************************************************************
Function:   	SetParaDegree
Description:    设置分段度数
Input:          ParaDegree 分段度数
Output:         无
Return:         是否成功
Others:         无
*******************************************************************************************************/
bool GAPCoordTranslate::SetParaDegree( double ParaDegree )
{
	m_ParaDegree=ParaDegree;   
	return true;
}

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
bool GAPCoordTranslate::SetZoneNum(double l_lo, double r_lo)
{
	if (m_ParaDegree==6)    //六度带
	{
		m_ZoneNum = floor(((l_lo+r_lo)/2)/6) + 1;    //工区带号
		m_setOriginLongitude = m_ZoneNum * m_ParaDegree - m_ParaDegree / 2;    //中央子午线经度
	}
	else if (m_ParaDegree==3)    //三度带
	{
		m_ZoneNum = floor(((l_lo+r_lo)/2+1.5)/3);
		m_setOriginLongitude = floor(((l_lo+r_lo)/2+1.5)/3) * 3;
	}
	else if (m_ParaDegree == 0)    //无带号
	{
		m_setOriginLongitude = (l_lo + r_lo) / 2;
	}
	else  return false; 
	return true;
}

/*******************************************************************************************************
Function:   	SetLoLa
Description:    设置经纬度坐标
Input:          dLo 经度, dLa 纬度
Output:         无
Return:         是否成功
Others:         无
*******************************************************************************************************/
bool GAPCoordTranslate::SetLoLa( double dLo, double dLa )
{
	//LoLaToxy(); 
	y=m_ZoneNum*1000000+y;
	return true; 
}

/*******************************************************************************************************
Function:   	SetTempxy
Description:    设置大地坐标
Input:          dx 横坐标,dy 纵坐标
Output:         无
Return:         是否成功
Others:         无
*******************************************************************************************************/
bool GAPCoordTranslate::SetTempxy( double dx, double dy )
{
	double tempy=fmod(dy,1000000);  
	m_setOriginLongitude=(int(dy/1000000)-1)*6+3;
	x = dx; 
	y = tempy;   
	/*xyToLoLa();*/   
	return true; 
}

/*******************************************************************************************************
Function:   	SetOriginLongitude
Description:    设置中央子午线经度
Input:         _OriginLongitude 中央子午线经度
Output:         无
Return:         无
Others:         无
*******************************************************************************************************/
void GAPCoordTranslate::SetOriginLongitude( double _OriginLongitude )
{
	m_setOriginLongitude = _OriginLongitude;
}

/*******************************************************************************************************
Function:   	setFirstOriginLongitude
Description:    设置第一次(即原始图件上设置的)中央子午线经度
Input:         _OriginLongitude 中央子午线经度
Output:         无
Return:         无
Others:         无
*******************************************************************************************************/
void GAPCoordTranslate::setFirstOriginLongitude( double _OriginLongitude )
{
	m_originLongitude = _OriginLongitude;
}

/*******************************************************************************************************
Function:   	SetEF
Description:    设置东偏移
Input:          ef 东偏移
Output:         无
Return:         是否成功
Others:         无
*******************************************************************************************************/
bool GAPCoordTranslate::setEF( double ef)
{
	EF = ef;
	return true; 
}

/*******************************************************************************************************
Function:   	SetNF
Description:    设置西偏移
Input:       nf 西偏移
Output:         无
Return:         是否成功
Others:         无
*******************************************************************************************************/
bool GAPCoordTranslate::setNF( double nf )
{
	NF = nf; 
	return true; 
}

/*******************************************************************************************************
Function:   	zoneNumToToLa
Description:    将含有带号的坐标转到当前区带上的经纬度
Input:          _pos传入的含有带号的点，_da长轴，_db短轴，_paraDegree几度带，_originLongitude中央子午线，_ef东偏移，_nf西偏移
Output:         无
Return:         经纬度
Others:         无
*******************************************************************************************************/
QPointF GAPCoordTranslate::zoneNumToLoLa( const QPointF &_pos,const double _da,const double _db,const double _paraDegree,const double _originLongitude,const double _ef,const double _nf )
{
	//获取传入点的带号
	int t_zoneNum = (int)(_pos.x() / 1000000);
	if (t_zoneNum == 0)
	{
		return noNumToZoneNum(_pos);
	}
	else//否则有带号
	{
		//长短轴
		double t_preda = a;
		double t_predb = b;
		double t_curda = _da;
		double t_curdb = _db;
		//几度带
		double t_preParaDegree = m_ParaDegree;
		double t_curParaDegree = _paraDegree;
		double t_noNumX = _pos.x() - t_zoneNum * 1000000;
		//中央子午线
		double t_preLongitude = m_originLongitude;
		double t_curLongitude = (t_zoneNum-1)*t_curParaDegree+t_curParaDegree/2;
		//三度带
		if (qFuzzyCompare(t_curParaDegree,3.0))
		{
			t_curLongitude = t_zoneNum*t_curParaDegree;
		}
		else if (qFuzzyCompare(_paraDegree,0.0))//无带号
		{
			t_curLongitude = _originLongitude;
		}
		//偏移
		double t_preEF = EF;
		double t_preNF = NF;
		double t_curEF = _ef;
		double t_curNF = _nf;

		SetAB(t_curda,t_curdb);
		SetParaDegree(t_curParaDegree);
		SetOriginLongitude(t_curLongitude);
		setEF(t_curEF);
		setNF(t_curNF);
		QPointF t_lolaPos = xyToLoLa(t_noNumX,_pos.y());
		SetAB(t_preda,t_predb);
		SetParaDegree(t_preParaDegree);
		SetOriginLongitude(t_preLongitude);
		setEF(t_preEF);
		setNF(t_preNF);

		return t_lolaPos;
	}
}

/*******************************************************************************************************
Function:   	zoneNumToNoNum
Description:    将含有带号的坐标转到无带号坐标
Input:           _pos传入的含有带号的点，_da长轴，_db短轴，_paraDegree几度带，_originLongitude中央子午线，_ef东偏移，_nf西偏移
Output:         无
Return:         无带号坐标
Others:         无
*******************************************************************************************************/
QPointF GAPCoordTranslate::zoneNumToNoNum( const QPointF &_pos,const double _da,const double _db,const double _paraDegree,const double _originLongitude,const double _ef,const double _nf)
{
	QPointF t_pos = _pos;
	int t_zoneNum = (int)(_pos.x() / 1000000);
	//有带号
	if ( t_zoneNum > 0 || (t_zoneNum == 0 && qFuzzyCompare(_paraDegree,0.0)))
	{
		//长短轴
		double t_preda = a;
		double t_predb = b;
		double t_curda = _da;
		double t_curdb = _db;
		//几度带
		double t_preParaDegree = m_ParaDegree;
		double t_curParaDegree = _paraDegree;
		double t_noNumX = _pos.x() - t_zoneNum * 1000000;
		//中央子午线
		double t_preLongitude = m_originLongitude;
		double t_curLongitude = (t_zoneNum-1)*t_curParaDegree+t_curParaDegree/2;
		//三度带
		if (qFuzzyCompare(t_curParaDegree,3.0))
		{
			t_curLongitude = t_zoneNum*t_curParaDegree;
		}
		else if (qFuzzyCompare(_paraDegree,0.0))//无带号
		{
			t_curLongitude = _originLongitude;
		}
		//偏移
		double t_preEF = EF;
		double t_preNF = NF;
		double t_curEF = _ef;
		double t_curNF = _nf;

		//防止坐标一样
		if (!qFuzzyCompare(t_preParaDegree,t_curParaDegree) || !qFuzzyCompare(t_preLongitude,t_curLongitude)
			|| !qFuzzyCompare(t_curda,t_preda) || !qFuzzyCompare(t_curdb,t_predb)
			|| !qFuzzyCompare(t_curEF,t_preEF) || !qFuzzyCompare(t_curNF,t_preNF))
		{
			QPointF t_lolaPos = zoneNumToLoLa(_pos,_da,_db,_paraDegree,_originLongitude,_ef,_nf);
			t_pos = LoLaToxy(t_lolaPos.x(),t_lolaPos.y());
		}
		else//否则直接去掉带号
		{
			t_pos = QPointF(t_noNumX,_pos.y());
		}
	}

	return t_pos;
}

/*******************************************************************************************************
Function:   	noNumToZoneNum
Description:    将无带号坐标转变为经纬度
Input:         &_pos 无带号坐标
Output:         无
Return:         经纬度
Others:         无
*******************************************************************************************************/
QPointF GAPCoordTranslate::noNumToLoLa( const QPointF &_pos )
{
	int t_zoneNum = (int)(_pos.x() / 1000000);
	//无带号
	if (t_zoneNum != 0)
	{
		return zoneNumToLoLa(_pos,a,b,m_ParaDegree,m_originLongitude);
	}
	else//否则有带号
	{
		return xyToLoLa(_pos.x(),_pos.y());
	}
}

/*******************************************************************************************************
Function:   	noNumToZoneNum
Description:    将无带号坐标转变成有带号坐标
Input:         _pos 无带号坐标
Output:         无
Return:         有带号坐标
Others:         无
*******************************************************************************************************/
QPointF GAPCoordTranslate::noNumToZoneNum( const QPointF &_pos )
{
	QPointF t_pos = _pos;
	int t_zoneNum = (int)(_pos.x() / 1000000);
	//防止有带号
	if (t_zoneNum == 0 && !qFuzzyCompare(m_ParaDegree,0.0))
	{
		double t_ParaDegree = m_ParaDegree;
		double t_pre = m_originLongitude;
		QPointF t_lolaPos = noNumToLoLa(_pos);
		double t_preZoneNum = floor(m_originLongitude/t_ParaDegree) + 1;
		double t_curZoneNum = floor(t_lolaPos.x()/t_ParaDegree) + 1;
		//三度带
		if (qFuzzyCompare(m_ParaDegree,3.0))
		{
			t_preZoneNum = floor((m_originLongitude+1.5)/3);
			t_curZoneNum = floor((t_lolaPos.x()+1.5)/3);
		}
		t_zoneNum = t_preZoneNum;
		//防止带号相同
		if (t_preZoneNum != t_curZoneNum)
		{
			t_zoneNum = t_curZoneNum;
		}
		double t_cur = (t_zoneNum-1)*t_ParaDegree+t_ParaDegree/2;
		//三度带
		if (qFuzzyCompare(m_ParaDegree,3.0))
		{
			t_cur = t_zoneNum*t_ParaDegree;
		}
		SetOriginLongitude(t_cur);
		t_pos = LoLaToxy(t_lolaPos.x(),t_lolaPos.y());
		SetOriginLongitude(t_pre);
		t_pos = QPointF(t_pos.y(), t_pos.x());
		t_pos.rx() += t_zoneNum * 1000000;
	}
	return t_pos;
}
