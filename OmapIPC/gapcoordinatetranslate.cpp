#include "gapcoordinatetranslate.h"
#include <math.h>
#include <stdlib.h>

bool GAPCoordTranslate::m_crossDiffArea;

/*****************************************************************************
Function:   	GAPCoordTranslate()
Description:	 ���캯��
Input:          		��
Output:         	��
Return:         	��
Others:         	��
*******************************************************************************/
GAPCoordTranslate::GAPCoordTranslate()
{
	EF = 500000;
	NF = 0;
}

/*****************************************************************************
Function:   	~GAPCoordTranslate()
Description:	 ��������
Input:          		��
Output:         	��
Return:         	��
Others:         	��
*******************************************************************************/
GAPCoordTranslate::~GAPCoordTranslate()
{

}

/*******************************************************************************************************
Function:   	Dms2Rad
Description:    �Ƕȵ����ȵ�ת��
Input:          Dms �Ƕ�ֵ
Output:         ��
Return:         ����ֵ
Others:         ��
*******************************************************************************************************/
double GAPCoordTranslate::Dms2Rad( double Dms )
{
	double Degree, Miniute;   
	double Second;   
	int Sign;   
	double Rad;
	//�Ƕȱ�ע
	if(Dms >= 0)   
		Sign = 1;   
	else//����Ϊ���� 
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
Description:    ���ȵ��Ƕȵ�ת��
Input:          Rad ����ֵ
Output:         ��
Return:         �Ƕ�ֵ
Others:         ��
*******************************************************************************************************/
double GAPCoordTranslate::Rad2Dms( double Rad )
{
	double Degree, Miniute;   
	double Second;   
	int Sign;   
	double Dms;
	//���ȱ�ע
	if(Rad >= 0)   
		Sign = 1;   
	else//����Ϊ����
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
Description:    ��γ������תΪ�������
Input:         lo ����, la γ��
Output:         ��
Return:         QPointF�������꣬�����꣩
Others:         ���������ֿ�������ʱ����Ҫ��������������������Ҫ���ÿ�����������µ�������
*******************************************************************************************************/
QPointF GAPCoordTranslate::LoLaToxy(double lo,double la)
{
// 	SetParaDegree(0);
// 	SetZoneNum(lo,lo);
	SetParaDegree(6);//��ʼ��Ϊ6�ȴ�
	SetZoneNum(lo,lo);
	SetCoordSysType(1);
	//�ж��Ƿ��������������򵥶���ÿ�����ȵ�����������ߣ��ֱ����ת��
	if (m_crossDiffArea)
	{
		SetZoneNum(lo, lo); //���ھ�����lo�����º���������������
	}
	a = 6378140;
	b = 6356755.28820;
	e2 = 1-(b/a)*(b/a);
	e12 = (a/b)*(a/b)-1;
	lo = lo*PI/180.0;    //����
	la = la*PI/180.0;    //γ��
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
Description:    �������תΪ��γ������
Input:          m_x ������, m_y ������
Output:         ��
Return:        ����γ��
Others:         ��
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
	int t_code = 18;//�������ţ�Ĭ��18
	if (m_x/1000000>1)//�д���
	{
		t_code = int(m_x)/1000000;
		m_x = m_x - t_code*1000000;
	}

	if (m_ParaDegree==6)    //���ȴ�
	{
		m_ZoneNum = t_code;    //��������
		m_setOriginLongitude = m_ZoneNum * m_ParaDegree - m_ParaDegree / 2;    //���������߾���
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
Description:    ���ñ�׼����������,Ĭ��Ϊ0
Input:          type ��׼����������
Output:         ��
Return:         �Ƿ�ɹ�
Others:         0Ϊ��³����˹�������壬1Ϊ����UGG1975�����壬2ΪWGS84������
*******************************************************************************************************/
bool GAPCoordTranslate::SetCoordSysType( int type )
{
	//��ֹ���Ͳ�����
	if((type<0)||(type>2))
	{   
		//    AfxMessageBox("���ʹ���0Ϊ��³����˹�����壬1Ϊ����UGG1975������,2ΪWGS84������");   
		return false;   
	}   
	else//���������ö�γ��
	{   
		// ��³����˹������   
		if(type==0)   
		{   
			a = 6378245;   
			b = 6356863.01880;   
		}
		else if(type==1)//����UGG1975����
		{   
			a = 6378140;   
			b = 6356755.28820;   
		}
		else if(type==2)//WGS84������
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
Description:    ��������������
Input:         da��dbΪ������ĳ��뾶�Ͷ̰뾶
Output:         ��
Return:         �Ƿ�ɹ�
Others:         ��
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
Description:    ���÷ֶζ���
Input:          ParaDegree �ֶζ���
Output:         ��
Return:         �Ƿ�ɹ�
Others:         ��
*******************************************************************************************************/
bool GAPCoordTranslate::SetParaDegree( double ParaDegree )
{
	m_ParaDegree=ParaDegree;   
	return true;
}

/*******************************************************************************************************
Function:   	SetZoneNum
Description:    ���ù������ź����������߾���
Input:          l_lo �󾭶�, r_lo �Ҿ���
Output:         ��
Return:         �Ƿ�ɹ�
Others:         1�����ȴ����㹤�����ţ��Ǹ����������ڵĴ��������
                2���������ȴ��������ȴ����������������߾���ʱ����ȡ����������������������������
			    3�������޴��ŵ���������������߾���Ϊ�������ߵľ���
*******************************************************************************************************/
bool GAPCoordTranslate::SetZoneNum(double l_lo, double r_lo)
{
	if (m_ParaDegree==6)    //���ȴ�
	{
		m_ZoneNum = floor(((l_lo+r_lo)/2)/6) + 1;    //��������
		m_setOriginLongitude = m_ZoneNum * m_ParaDegree - m_ParaDegree / 2;    //���������߾���
	}
	else if (m_ParaDegree==3)    //���ȴ�
	{
		m_ZoneNum = floor(((l_lo+r_lo)/2+1.5)/3);
		m_setOriginLongitude = floor(((l_lo+r_lo)/2+1.5)/3) * 3;
	}
	else if (m_ParaDegree == 0)    //�޴���
	{
		m_setOriginLongitude = (l_lo + r_lo) / 2;
	}
	else  return false; 
	return true;
}

/*******************************************************************************************************
Function:   	SetLoLa
Description:    ���þ�γ������
Input:          dLo ����, dLa γ��
Output:         ��
Return:         �Ƿ�ɹ�
Others:         ��
*******************************************************************************************************/
bool GAPCoordTranslate::SetLoLa( double dLo, double dLa )
{
	//LoLaToxy(); 
	y=m_ZoneNum*1000000+y;
	return true; 
}

/*******************************************************************************************************
Function:   	SetTempxy
Description:    ���ô������
Input:          dx ������,dy ������
Output:         ��
Return:         �Ƿ�ɹ�
Others:         ��
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
Description:    �������������߾���
Input:         _OriginLongitude ���������߾���
Output:         ��
Return:         ��
Others:         ��
*******************************************************************************************************/
void GAPCoordTranslate::SetOriginLongitude( double _OriginLongitude )
{
	m_setOriginLongitude = _OriginLongitude;
}

/*******************************************************************************************************
Function:   	setFirstOriginLongitude
Description:    ���õ�һ��(��ԭʼͼ�������õ�)���������߾���
Input:         _OriginLongitude ���������߾���
Output:         ��
Return:         ��
Others:         ��
*******************************************************************************************************/
void GAPCoordTranslate::setFirstOriginLongitude( double _OriginLongitude )
{
	m_originLongitude = _OriginLongitude;
}

/*******************************************************************************************************
Function:   	SetEF
Description:    ���ö�ƫ��
Input:          ef ��ƫ��
Output:         ��
Return:         �Ƿ�ɹ�
Others:         ��
*******************************************************************************************************/
bool GAPCoordTranslate::setEF( double ef)
{
	EF = ef;
	return true; 
}

/*******************************************************************************************************
Function:   	SetNF
Description:    ������ƫ��
Input:       nf ��ƫ��
Output:         ��
Return:         �Ƿ�ɹ�
Others:         ��
*******************************************************************************************************/
bool GAPCoordTranslate::setNF( double nf )
{
	NF = nf; 
	return true; 
}

/*******************************************************************************************************
Function:   	zoneNumToToLa
Description:    �����д��ŵ�����ת����ǰ�����ϵľ�γ��
Input:          _pos����ĺ��д��ŵĵ㣬_da���ᣬ_db���ᣬ_paraDegree���ȴ���_originLongitude���������ߣ�_ef��ƫ�ƣ�_nf��ƫ��
Output:         ��
Return:         ��γ��
Others:         ��
*******************************************************************************************************/
QPointF GAPCoordTranslate::zoneNumToLoLa( const QPointF &_pos,const double _da,const double _db,const double _paraDegree,const double _originLongitude,const double _ef,const double _nf )
{
	//��ȡ�����Ĵ���
	int t_zoneNum = (int)(_pos.x() / 1000000);
	if (t_zoneNum == 0)
	{
		return noNumToZoneNum(_pos);
	}
	else//�����д���
	{
		//������
		double t_preda = a;
		double t_predb = b;
		double t_curda = _da;
		double t_curdb = _db;
		//���ȴ�
		double t_preParaDegree = m_ParaDegree;
		double t_curParaDegree = _paraDegree;
		double t_noNumX = _pos.x() - t_zoneNum * 1000000;
		//����������
		double t_preLongitude = m_originLongitude;
		double t_curLongitude = (t_zoneNum-1)*t_curParaDegree+t_curParaDegree/2;
		//���ȴ�
		if (qFuzzyCompare(t_curParaDegree,3.0))
		{
			t_curLongitude = t_zoneNum*t_curParaDegree;
		}
		else if (qFuzzyCompare(_paraDegree,0.0))//�޴���
		{
			t_curLongitude = _originLongitude;
		}
		//ƫ��
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
Description:    �����д��ŵ�����ת���޴�������
Input:           _pos����ĺ��д��ŵĵ㣬_da���ᣬ_db���ᣬ_paraDegree���ȴ���_originLongitude���������ߣ�_ef��ƫ�ƣ�_nf��ƫ��
Output:         ��
Return:         �޴�������
Others:         ��
*******************************************************************************************************/
QPointF GAPCoordTranslate::zoneNumToNoNum( const QPointF &_pos,const double _da,const double _db,const double _paraDegree,const double _originLongitude,const double _ef,const double _nf)
{
	QPointF t_pos = _pos;
	int t_zoneNum = (int)(_pos.x() / 1000000);
	//�д���
	if ( t_zoneNum > 0 || (t_zoneNum == 0 && qFuzzyCompare(_paraDegree,0.0)))
	{
		//������
		double t_preda = a;
		double t_predb = b;
		double t_curda = _da;
		double t_curdb = _db;
		//���ȴ�
		double t_preParaDegree = m_ParaDegree;
		double t_curParaDegree = _paraDegree;
		double t_noNumX = _pos.x() - t_zoneNum * 1000000;
		//����������
		double t_preLongitude = m_originLongitude;
		double t_curLongitude = (t_zoneNum-1)*t_curParaDegree+t_curParaDegree/2;
		//���ȴ�
		if (qFuzzyCompare(t_curParaDegree,3.0))
		{
			t_curLongitude = t_zoneNum*t_curParaDegree;
		}
		else if (qFuzzyCompare(_paraDegree,0.0))//�޴���
		{
			t_curLongitude = _originLongitude;
		}
		//ƫ��
		double t_preEF = EF;
		double t_preNF = NF;
		double t_curEF = _ef;
		double t_curNF = _nf;

		//��ֹ����һ��
		if (!qFuzzyCompare(t_preParaDegree,t_curParaDegree) || !qFuzzyCompare(t_preLongitude,t_curLongitude)
			|| !qFuzzyCompare(t_curda,t_preda) || !qFuzzyCompare(t_curdb,t_predb)
			|| !qFuzzyCompare(t_curEF,t_preEF) || !qFuzzyCompare(t_curNF,t_preNF))
		{
			QPointF t_lolaPos = zoneNumToLoLa(_pos,_da,_db,_paraDegree,_originLongitude,_ef,_nf);
			t_pos = LoLaToxy(t_lolaPos.x(),t_lolaPos.y());
		}
		else//����ֱ��ȥ������
		{
			t_pos = QPointF(t_noNumX,_pos.y());
		}
	}

	return t_pos;
}

/*******************************************************************************************************
Function:   	noNumToZoneNum
Description:    ���޴�������ת��Ϊ��γ��
Input:         &_pos �޴�������
Output:         ��
Return:         ��γ��
Others:         ��
*******************************************************************************************************/
QPointF GAPCoordTranslate::noNumToLoLa( const QPointF &_pos )
{
	int t_zoneNum = (int)(_pos.x() / 1000000);
	//�޴���
	if (t_zoneNum != 0)
	{
		return zoneNumToLoLa(_pos,a,b,m_ParaDegree,m_originLongitude);
	}
	else//�����д���
	{
		return xyToLoLa(_pos.x(),_pos.y());
	}
}

/*******************************************************************************************************
Function:   	noNumToZoneNum
Description:    ���޴�������ת����д�������
Input:         _pos �޴�������
Output:         ��
Return:         �д�������
Others:         ��
*******************************************************************************************************/
QPointF GAPCoordTranslate::noNumToZoneNum( const QPointF &_pos )
{
	QPointF t_pos = _pos;
	int t_zoneNum = (int)(_pos.x() / 1000000);
	//��ֹ�д���
	if (t_zoneNum == 0 && !qFuzzyCompare(m_ParaDegree,0.0))
	{
		double t_ParaDegree = m_ParaDegree;
		double t_pre = m_originLongitude;
		QPointF t_lolaPos = noNumToLoLa(_pos);
		double t_preZoneNum = floor(m_originLongitude/t_ParaDegree) + 1;
		double t_curZoneNum = floor(t_lolaPos.x()/t_ParaDegree) + 1;
		//���ȴ�
		if (qFuzzyCompare(m_ParaDegree,3.0))
		{
			t_preZoneNum = floor((m_originLongitude+1.5)/3);
			t_curZoneNum = floor((t_lolaPos.x()+1.5)/3);
		}
		t_zoneNum = t_preZoneNum;
		//��ֹ������ͬ
		if (t_preZoneNum != t_curZoneNum)
		{
			t_zoneNum = t_curZoneNum;
		}
		double t_cur = (t_zoneNum-1)*t_ParaDegree+t_ParaDegree/2;
		//���ȴ�
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
