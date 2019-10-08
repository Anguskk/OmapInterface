#pragma once
//CLI���õ�ʱ����Ҫ 2019.3.22
#if defined WIN32 && !defined WIN10
//#include <Windows.h>
#include <afxwin.h>
#include <afxcmn.h>
#include "stdafx.h"
#include <afx.h>
#endif

#ifndef OMAP_WIN_API_H
#define OMAP_WIN_API_H
#define APP_CLASS_NAME L"Qt5QWindowIcon"
//#define APP_CLASS_NAME L"OMapApiTest"
#define OMAP_WIN_API_VERSION 101
#define OMAP_WIN_API_FLAG 1001

#define OMAP_WIN_CMD_REGISTER 20000
#define OMAP_WIN_CMD_GET_LATLNG 20001
#define OMAP_WIN_CMD_SET_LATLNG 20002
#define OMAP_WIN_CMD_LATLNG_GEOCODE 20003
#define OMAP_WIN_CMD_SHOW_PIC 20004
#define OMAP_WIN_CMD_TIME_TO_LATLNG 20005
#define OMAP_WIN_CMD_GET_VERSION 20006
#define OMAP_WIN_CMD_SET_MAP_LOCATION 20007
#define OMAP_WIN_CMD_CLOSE 20008
#define OMAP_WIN_CMD_SAVE_CFG 20009
#define OMAP_WIN_CMD_CLEAN_TMP_OBJ 20010
#define OMAP_WIN_CMD_SET_MAP_LOCATION_EXT 20011
#define OMAP_WIN_CMD_GET_MAP_INFO	20012
#define OMAP_WIN_CMD_FOLLW_MAP_INFO	20013
#define OMAP_WIN_CMD_FOLLW_OBJ_CHG_FLAG 20014
#define OMAP_WIN_CMD_FOLLW_OBJ_CHG_LIST 20015


#define OMAP_API_CMD_GET_OBJ_LIST 20100
#define OMAP_API_CMD_GET_OBJ 20101
#define OMAP_API_CMD_SET_OBJ 20102
#define OMAP_API_CMD_DEL_OBJ 20103
#define OMAP_API_CMD_GET_SEL_LIST 20104
#define OMAP_API_CMD_SRH_OBJ 20105
#define OMAP_API_CMD_SET_SEL_ID_LIST 20106
#define OMAP_API_CMD_SRH_OBJ_EXT 20107

#define OMAP_API_CMD_GET_SEL_OBJ_TREE 20110
// ����tagOApiObjDataItem����, ���Զ����(����)idParent��idObj
#define OMAP_API_CMD_SET_OBJ_TREE 20112

#define OMAP_API_CMD_SET_SYS_COOR_POINT 20201
#define OMAP_API_CMD_GET_SYS_COOR_INFO 20202

#define OMAP_API_CMD_REQ_INTERFACE_VER	20203

#define OMAP_API_CMD_GET_SYS_COOR_CENTER 20211
#define OMAP_API_CMD_GET_COOR_PIXEL_INFO 20212


#define OMAP_API_CMD_GET_MAP_DATA	20301
#define OMAP_API_CMD_GET_MAP_FILE	20302
#define OMAP_API_CMD_GET_CONTOUR	20303

#define OMAP_API_CMD_SET_BTN	20401
#define OMAP_API_CMD_CLICK_BTN	20402

#define OMAP_API_CMD_GET_STATUS_INFO	20501
#define OMAP_AIP_CMD_REQ_VIP5_DEMO		20503

#define OMAP_API_CMD_GET_SHAPE_FILL_PAT_LIST	20601



#define OMAP_RET_SYS_COOR_TYPE_ERR	-2
#define OMAP_RET_SYS_COOR_SIM_PARAM_ERR	-1
#define OMAP_RET_SYS_COOR_OK	0



#define ACTION_MOUSE_MOVE 1
#define ACTION_MOUSE_CLICK 2

#define GEO_DECODE_ERR_WAIT -1
#define GEO_DECODE_ERR_NO_DATA -2
#define MAX_API_NAME_LEN 100
#define MAX_API_DIR_WAYPOINTS 8

#define OMAP_OBJ_TYPE_GROUP 30
#define OMAP_OBJ_TYPE_SIGN 7
#define OMAP_OBJ_TYPE_TRACK 8
#define OMAP_OBJ_TYPE_SHAPE 13
#define OMAP_OBJ_TYPE_DIR 11

#define OMAP_API_ERR_OK	1
#define OMAP_API_ERR_WND -1
#define OMAP_API_ERR_REGISTER -2
#define OMAP_API_ERR_VER -3
#define OMAP_API_ERR_ARGV -4
#define OMAP_API_ERR_NOT_VIP -5
#define OMAP_API_ERR_DEAL -6
#define OMAP_API_ERR_NOT_VIP5 -7
#define OMAP_API_ERR_UNLOAD_OBJ	-8
#define OMAP_API_ERR_CMD	-9
#define OMAP_API_ERR_DISABLE	-10


#define IS_OMAP_API_INTERRUPT_ERR(x)	(x == OMAP_API_ERR_NOT_VIP || x == OMAP_API_ERR_DEAL || x == OMAP_API_ERR_NOT_VIP5|| x == OMAP_API_ERR_UNLOAD_OBJ)


#define MAKE_OMAP_API_STATUE_INFO(iVipLv, bLoadObj)	((iVipLv&0xff)|(bLoadObj?0x100:0x000))
#define GET_OMAP_API_STATUE_LV(status)		(status&0xff)
#define GET_OMAP_API_STATUE_LOAD(status)	((status&0x100) != 0)

#define OAPI_APP_ID_QUERY		-100
#define OAPI_APP_ID_ALL		-1
#define OAPI_APP_ID_NONE	0

#define OAPI_LL_TYPE_DEFAULT 0
#define OAPI_LL_TYPE_REAL	1
#define OAPI_LL_TYPE_OFFSET 2
#define OAPI_LL_TYPE_PLANE 3
#define OAPI_LL_TYPE_GOOGLE_PX	4

// ���ж���
#define OBJ_SELECT_CHECK_FLAG_ALL			0
// ѡ�ж���, ѡ�е��ļ����Զ����������Ӷ���
#define OBJ_SELECT_CHECK_FLAG_GROUP_JOIN	1
// ѡ�ж���, ѡ�е��ļ��в��Զ�������ѡ���Ӷ���
#define OBJ_SELECT_CHECK_FLAG_SEL_ONLY		2
// ѡ�ж���, ���ѡ�е����ļ���, ���ų��ļ��б���ȥѡ���ӽ��
#define OBJ_SELECT_CHECK_FLAG_NO_GROUP		3


//��ʱ�������ڵ�ID
#define OMAP_TMP_OBJ_GROUP_ID 202

#define OMAP_ALIGN_8_BYTE(x) ((x) % 8 == 0) ? x : ((x) / 8 * 8 + 8)
//��γ��
struct tagOmapLatlng {
	double lat;
	double lng;
	BYTE bReal;//�Ƿ���ʵ��γ��
};
/*
��ͼλ��
iMapID ��ͼid
100�ļ��У�С����ȸ��ͼ�����ļ���
130�ļ��У�������ȸ��ͼ�����ļ���

101�ļ��У��ȸ�����ͼ�����ļ���
160�ļ��У�С����ȸ�·��ͼ�����ļ���
161�ļ��У�������ȸ�·��ͼ�����ļ���

102�ļ��У�С����ȸ����ͼ�����ļ���
132�ļ��У�������ȸ����ͼ�����ļ���

103�ļ��У�bing����ͼ�����ļ���

104�ļ��У�OpenCycle�ȸ���ͼ�����ļ���

105�ļ��У�С����ٶȵ�ͼ�����ļ���
135�ļ��У�������ٶȵ�ͼ�����ļ���

106�ļ��У�С�����ѹ���ͼ�����ļ���
136�ļ��У��������ѹ���ͼ�����ļ���

200-1000�ļ��У��Զ����ͼ�����ļ��У��Ե�ͼID������
*/

struct tagOmapLocation {
	struct tagOmapLatlng ll;//��γ��
	int iMapID;//��ͼ����ID
	int iMapLevel;//��ͼ����
};

struct tagOmapLocationExt {
	tagOmapLocation ol;
	BYTE bActive;
	DWORD ret[10];
};

struct tagWinMapInfo {
	double lng;
	double lat;
	BYTE bReal;

	double x_lng;
	double y_lat;
	BYTE bReal2;

	int iMapLevel;
	int iMapType;

	// ��ά��ǰʹ��
	int iMapX;
	int iMapY;
	int iRet;

	DWORD ret[10];
};

struct tagOPhotoMapPic {
	INT64 idPic;//��Ƭid
	unsigned int tmPhoto;//��Ƭ����ʱ��
	double lat;//ά��
	double lng;//����
	int iAction;//ACTION_MOUSE_MOVE 1  ACTION_MOUSE_CLICK 2
	int iTmp;//����, OMAP_WIN_CMD_TIME_TO_LATLNG����ñ���������Ƭʱ����켣��ʱ��Ĳ�ֵ
};

struct tagOmapGeoDecode {
	struct tagOmapLatlng oll;
	int nLevel;//��ͼ�����Ĳ㼶  �� ʡ����3����ʡ����3��������2��
	char strArea[8][128];
};

struct tagOmapGetMap {
	double x_lng1;
	double y_lat1;
	double x_lng2;
	double y_lat2;
	BYTE bRealLl;

	INT64 iMaxPixel;
	int iMaxLevel;

	DWORD width;
	DWORD height;
	int ret[8];
};

#define OAPI_RET_ERR_VIP_LEVEL	-1 //��άVIP���𲻹�
#define OAPI_RET_ERR_VIP5_NEED	-2 //��ҪVIP5������
#define OAPI_RET_ERR_LATLNG_INVALID	-3 //����ϵ����
#define OAPI_RET_ERR_ARGV	-4 //��������
#define OAPI_RET_ERR_MEMORY_OUT	-5 //�ڴ��쳣
#define OAPI_RET_ERR_UNKNOWN	-6 //δ֪����
#define OAPI_RET_ERR_ARGV_REQ	-7 //��ȸ����������
#define OAPI_RET_ERR_MEMORY_END	-8 //�ڴ治�����ֹ

#define OAPI_DATA_HAS_FULL	1
#define OAPI_DATA_PART_ONLY	2
#define OAPI_DATA_IS_NONE	3



#define GET_MAP_FILE_RET_ERR_COORD_TYPE	-101//����ϵ���ô���(��λ��ƫ�����)
#define GET_MAP_FILE_RET_ERR_IGNORE	-102 //����
#define GET_MAP_FILE_RET_ERR_SIZE_EXCEED	-103//��ͼ�ߴ�̫��
#define GET_MAP_FILE_RET_ERR_PIXEL_EXCEED	-104//��ͼ����̫��
#define GET_MAP_FILE_RET_ERR_CREATE_IMG	-105 //������ͼʧ��
#define GET_MAP_FILE_RET_ERR_RESIZE	-106//��ͼŤ��̫��


#define GET_MAP_FILE_IMG_TYPE_PNG	0
#define GET_MAP_FILE_IMG_TYPE_JPG	1

extern unsigned int g_msgGetMapProcess;
struct tagOmapGetMapFile {

	INT64 idMap;	// ������ı��, �������ʱ��ͬ����µĻ��滻�ɵ�
	INT64 iValue;	// ��Ҫ�̶�

	int iFlag;		// 1��ʾͼ����ȫʱֱ�Ӻ���
	int iRet;		//  ����ֵ

	char strFile[256];	// �ļ���Ϊ��ʱ����д��ʧ��ʱ��ͨ��pData����
	bool bFile;			// ����д��״̬

	union {
		void *pData;
		double dAlignDate;
	};
	int nData;

	double x_lng1;
	double y_lat1;
	double x_lng2;
	double y_lat2;
	BYTE bRealLl;	// ��������

	int iMapLevel;
	int iMapType;

	DWORD width;
	DWORD height;

	union {
		void *hWnd;	// HWND hWnd
		double dAlignWnd;
	};

	int iTotalPic;
	int iHasPic;

	int iPostCnt;	// ȡͼ����ÿȡ�����ŷ���һ��g_msgGetMapProcess��Ϣ(WPARAM=iTotal, PARAM=iDeal);

	int iTmp;	// ��άʹ�õ���ʱ����
	BYTE bSendReq;	// 1��ʾͼ�����ڻ��߲���ȫʱ������������

	BYTE bImageType;	// GET_MAP_FILE_IMG_TYPE_XXX
	BYTE bRetUse[3];

	int iRetUse[19];
};


#define GET_CONTOUR_RET_ERR_EXCEED_ONE	-101
#define GET_CONTOUR_RET_ERR_PART_OK		-102
#define GET_CONTOUR_RET_ERR_PART_ERR		-103

extern unsigned int g_msgGetContourProcess;
struct tagOmapReqContour {

	INT64 idMap;	// ������ı��, �������ʱ��ͬ����µĻ��滻�ɵ�
	INT64 iValue;	// ��Ҫ�̶�

	double x_lng1;
	double y_lat1;
	double x_lng2;
	double y_lat2;
	BYTE bRealLl;

	int iMapLevel;	// ���󼶱�
	int iElevValue;	// �ȸ��߼��

	int iCheckFlag;	// 0: ��ʾֱ��ȡ, 1: ��ʾֻ�������Ϊ
	int iCheckResult;

	int iRet;		// ����ֵ
	int iNeedVip;	// ����Ҫ��VIP����
	BYTE bPart;


	// data�ṹ��װ��ʽ�ο�GetOmapSelObjectTree˵��
	union {
		void *pData;
		double dAlignDate;
	};
	int nData;

	union {
		void *hWnd;	// HWND hWnd
		double dAlignWnd;
	};



	int iPostCnt;	// ȡ�ȸ��߹���ÿȡ���ٴμ������һ��g_msgGetContourProcess��Ϣ(WPARAM=iTotal, PARAM=iDeal);

	int iRet1[20];	// Ԥ��
};


struct tagOMapBtnInfo {
	int ret0;
	int iAdd;
	char strTip[256];
	int ret1[10];
};

//����ղؼж���Ľṹ��
struct tagOApiObjectOptHdr {
	WORD iVersion;//��ά�汾
	BYTE iType;//�������ͣ��ļ��С���ǩ���켣��ͼ�Ρ�·��
	// BYTE bRet;//����
	BYTE bLlType;//��������
	DWORD idParent;//�ղؼж���ĸ��ڵ��id 0��ʾ�ö���Ϊ���ڵ�
	DWORD idObj;//�ղؼж����id
	int ret;//�ڵ�����λ��
};

//�ղؼж����б�
struct tagOApiItemListV1 {
	DWORD idObj;//����id
	int iType;//��������
	char strName[MAX_API_NAME_LEN];//��������
};

struct tagOApiObjGroupV1 {
	char strName[MAX_API_NAME_LEN];

	int nChild;//��һ������ĸ���
	int nAllChild;	//����������������ܸ�����δ����ʱ��ֵҲ��һ��
	BYTE bLoadOk;	//�Ƿ���سɹ�

	BYTE bSaveMerge;//����ʱpChild�������Ƿ�ϲ��洢���ϲ��洢�ɴ��ӿ�����ʱ�䣬��ʹ�޸�ʱ����ʱ���½�
	BYTE bGroup;	//�Ƿ���ϣ�����չ��
	BYTE bAutoLoad;	//�Ƿ��Զ�����
	BYTE iShowLevel;//�Ƿ�����
	BYTE iShowLevelMax;//��ʾ����
	BYTE bCrypt;	//�Ƿ����, ��������˼������Զ����ؽ��Զ�ʧЧ, �ӿڿ��Ի�ȡ��ֵ���޷������޸�
	BYTE bReadOnly;	//�Ƿ�ֻ��, 0: ������, 1: ������������, 2: ����������
	BYTE bNotHotId;	//�Ƿ���Ӧ����¼�
	BYTE bRelate;	//�Ƿ��ǹ�������Ŀǰ���ڱ�ǩ��켣������
	BYTE pwd[16];//���õ�����, ����, �޷���ȡ���޸�
	DWORD ret[10];	//returnֵ
};

//��ʾ��ǩ�Ľṹ��
struct tagOApiMapSignV1 {
	char strName[MAX_API_NAME_LEN];//��ǩ����
	union {
		//32λϵͳָ��ռ4���ֽڣ�64λϵͳָ��ռ8���ֽڣ�Ϊʹ�ṹ��С����union����������8�ֽ�dAlign������
		char* pstrComment;//��ǩ��ע
		double dAlign;
	};

	double lat;
	double lng;
	BYTE bRealLl;	//0:gcj02��γ��, 1:��ʵ��γ��, 2:��ǰ����ϵ�µ�ƽ������
	int iAltitude;	//����
	int iTime;		//����ʱ��

	BYTE bEditMode;//�Ƿ�ɱ༭
	BYTE iOverlayIdx;//���Ų㼶

	BYTE iSignAlignFlag;//��ǩͼ������־��0ΪĬ�����ж��룬1Ϊ���ж���
	int iSignPic;		//0:no picture,>=1 has sign picture
	DWORD dwSignClr;
	BYTE iPicScale;	//0:defalut,>=1 32*iPicScale/10

	BYTE iTxtType;	//0:not show txt,1:show txt ,2:show text with border, 3: custom txt
	BYTE iShowLevel;//��ǩ��ʾ����
	BYTE iShowLevelMax;	//show between iShowLevel-iShowLevelMax
	//�Զ����������Ϣ
	struct tagOApiMapSignExtInfo {
		char strFontName[MAX_API_NAME_LEN];
		BYTE bFontZoomWithMap;
		BYTE bFontWithBox;
		BYTE iFontAlpha;
		BYTE bFontEffect;
		BYTE bFontBkStyle;
		BYTE nFontBindLevel;
		BYTE nFontMinLevel;
		BYTE nFontMaxLevel;
		int iFontSize;
		DWORD dwFontClr;
		DWORD dwFontBkClr;
		float fFontRotateAngle;
		BYTE bNoHotFontEvent;

		INT64 idExt;
		INT64 idExtBak[10];
	}ei;

	struct tagOApiMapSignExtInfo2 {
		BYTE bShowComment;
		BYTE bCommentAlign;
		BYTE iNameShowStaSet;
		BYTE bRet1;
	}ei2;

	DWORD ret[9];
};

//
//struct tagOApiMapSignAttachmentV1{
//	INT64 idAtta;
//	union{
//		void* pData;
//		double dAlign;
//	};
//	int nDataLen;
//	unsigned int tCreate;
//	unsigned int tModify;
//	int nReference;
//	char strName[MAX_API_NAME_LEN];
//	char strExtTypeName[10];
//	BYTE bNeedSaveData;
//	BYTE bChange;
//
//	//����ǹ������ԣ����޸�ʱ�������ǩ�������й���������������
//	BYTE bShare;
//};

//�켣�ϵĵ����Ϣ
struct tagOApiMapTrackPointV1 {
	double lat;
	double lng;
	int time;//�켣���ʱ��
	int iAltitude;		// iAltitude >> 16 == 1 ��ʾ�õ�Ϊ����ͼ��(���ӹ켣)����ʼ�㼴ǰһ������

	//��չ��ʽ������CAD
	double dCadBulge;
	int iCadRet;
	union
	{
		double dd;
		struct tagCadLwpLineWidth {
			float fWidStart;
			float fWidEnd;
		}clw;
	}ext;
};

//��ʾ�켣�Ľṹ��
struct tagOApiMapTrackV1 {
	char strName[MAX_API_NAME_LEN];

	union {
		char* pstrComment;
		double dAlign1;
	};
	union {
		struct tagOApiMapTrackPointV1* pMtp;
		double dAlign2;//�����ֶ�
	};
	int nMtp;//�켣����

	BYTE bRealLl;	//tagOApiMapTrackPointV1�еľ�γ���Ƿ���ʵ��γ��

	BYTE iTrackType;	// �켣���: �Լ�, ��ɽ ...
	BYTE iOverlayIdx;	//���Ų㼶

	BYTE iShowLevel;//��ʾ����
	BYTE iShowLevelMax;//show between iShowLevel-iShowLevelMax
	BYTE bShowName;//�Ƿ���ʾ�켣����
	BYTE bEdit;//�켣�Ƿ�ɱ༭

	//�����Զ����ֶ����ڱ���켣���Զ�������
	BYTE iCustomType1;
	BYTE iCustomType2;
	BYTE iCustomType3;
	BYTE iCustomType4;
	int dwCustom1;
	int dwCustom2;

	//�켣���Ƶ��������
	struct tagOApiMapTrackDraw {
		DWORD dwLineClr;	//������ɫ
		int iLineWidth;		//�߿�
		BYTE iLineAlpha;	//����͸����
		BYTE iShowType;		// �켣���: ��ʾ��Ȩ����, CAD����� ...
		BYTE iLineType;		//����
		BYTE bNeedDrawDetail;	//�Ƿ���Ҫ���ƽǶȡ�������ʾ��Ϣ
		BYTE bClose;			//�Ƿ�պ�
	}mtd;
	DWORD ret[10];
};



//��ʾͼ�εĽṹ��
struct tagOApiMapShapeV1 {
	char strName[MAX_API_NAME_LEN];
	union {
		char* pstrComment;
		double dAlign1;
	};
	union {
		struct tagOApiMapTrackPointV1* pMtp;
		double dAlign2;
	};
	int nMtp;//ͼ�εĽڵ���
	BYTE bRealLl;

	//iShowFlag:0 ����ʾ���ԣ�1 ��ʾ���� 2 ��ʾ��� 3 ��ʾ���������
	BYTE iShowFlag;
	BYTE iOverlayIdx;
	double dStartAngle;	//��ͼ��Ϊ������ʱ��ͨ����ʼ�Ƕ�����ֹ�Ƕȱ�ʾԲ�����Ρ�����
	double dEndAngle;

	BYTE iLineWidth;	//�߿�
	BYTE iLineAlpha;	//����͸����
	BYTE iAreaAlpha;	//����͸����
	BYTE bEditMode;		//�Ƿ�ɱ༭
	BYTE iShowLevel;
	BYTE iShowLevelMax;
	//�ⲿRgn������0Ϊȫ�������ⲿ��>0Ϊǰ����ٸ����ⲿ���������ڲ������ڴ����ο�
	WORD iOuterRgnIdx;
	//change by houyb at 2018/03/27
	//BYTE iOuterRgnIdx;
	DWORD dwLineClr;	//������ɫ
	DWORD dwAreaClr;	//�����ɫ
#if 0
	DWORD ret[10];
#else
	//0:Ĭ����ɫ��䣬1������ɫ��䣬2��ͼ����䣬3��CADͼ�����
	int iFillType;
	//����ɫ���ʱ��0�������ҽ��䣬1�������м佥���ٵ��һ�ԭ��2������Χ�����Ľ���, CADͼ��ʱ��Ϊ�Ƿ���ͼ����
	int iFillSubType;
	//ͼ��ID
	DWORD dwFillPattern;
	// ����ɫ2, ��䱳��ɫ
	DWORD dwFillChgClr;
	float fFillRotate;
	//����CADͼ�����
	float fFillScale;

	// �洢����ľ���ֵ
	double fFillOffsetX;
	double fFillOffsetY;
#endif
};


struct tagOApiLatLngV1 {
	double lat;
	double lng;
};
//��ʾһ����������Ľṹ��
struct tagOApiMapDirectionsUnitV1 {
	char strTitle[128];//������
	char strSubTitle[10][128];//�Ӳ���
	int nSubCount;	//�Ӳ�����
	short iType;	//��ͨ��������
	int nLl;		//llList����
	union {
		struct tagOApiLatLngV1* llList;
		double dAlign;
	};
};
//��ʾ����·�ߵĽṹ��
struct tagOApiMapDirectionsV1 {
	char strName[MAX_API_NAME_LEN];
	union {
		char* pstrComment;
		double dAlign1;
	};
	union {
		struct tagOApiMapDirectionsUnitV1* punit;
		double dAlign2;
	};
	int nUnit;//����������
	char strTitle[128];
	//�������ĵ�������
	struct tagMapDirectionsSrh {
		struct tagOApiLatLngV1 mpStart;//������ľ�γ��
		struct tagOApiLatLngV1 mpEnd;//�յ�ľ�γ��
		struct tagOApiLatLngV1 mpVia[MAX_API_DIR_WAYPOINTS];//�м䵼����ľ�γ��
		int iDirMode;//???
	}dirSrh;
	BYTE bEdit;//�Ƿ�ɱ༭

	BYTE iLineWidth;	//�߿�
	BYTE iLineAlpha;	//͸����
	DWORD dwLineClr;	//������ɫ
	BYTE iOverlayIdx;	//���Ų㼶
	BYTE bRealLl;		//�Ƿ���ʵ��γ��

	BYTE iShowLevel;	//��ʾ����
	BYTE iShowLevelMax;//show between iShowLevel-iShowLevelMax

	DWORD ret[10];
};

struct tagOApiRelatePointV1 {
	double lng;
	double lat;
	BYTE bReal;
	double x;
	double y;
	DWORD ret[10];
};

struct tagOApiSysCoorInfo {
	int ret[10];

	int iCoorType;
	char hash[16];	// ���������Ч, �������ж��Ƿ����˱仯, [0, ��άƽ������, 4: ī��������ʱ]
	int nInfoLen;
	union {
		char* strInfo;
		double dAlign1;
	};
};

struct tagOApiPixelInfo {
	double dMeterX;
	double dMeterY;
	int iLevel;
	DWORD ret[20];
};


#define OAPI_INTERFACE_TYPE_CAD	1

struct tagOApiInterfaceVer {
	int iType;
	int iVer;
	int iBuf;
	union {
		char *pBuf;
		double dAlign1;
	};
	int iSendReq;
	DWORD ret[9];
	// DWORD ret[10];
};

struct tagOApiMemBuf {
	char *pBuf;
	int nBuf;
	int nMem;
};

struct tagOApiObjDataItem {
	int iDataLen;	// ����������ݵĳ���
	int iObjType;
	DWORD idObj;
	DWORD idParent;
	INT64 iCustomData;	// �ӿڿ����Զ�������
	DWORD ret[10];
};


#define SRH_OBJ_OPT_NAME_FUZZY		0
#define SRH_OBJ_OPT_NAME_HEADER		1
#define SRH_OBJ_OPT_COMMENT_FUZZY	2
#define SRH_OBJ_OPT_COMMENT_HEADER	3
#define SRH_OBJ_OPT_SRH_SAME		4
#define SRH_OBJ_OPT_NAME_MATCH		5
#define SRH_OBJ_OPT_COMMENT_MATCH	6

#define SRH_OBJ_OPT_SIGN_SHOW_STYLE		11
#define SRH_OBJ_OPT_SIGN_ICON_ID		12

#define SRH_OBJ_OPT_TRACK_LINET_TYPE	21
#define SRH_OBJ_OPT_TRACK_SHOW_STYLE	22
#define SRH_OBJ_OPT_TRACK_CLASS0		23

#define IS_TXT_SRH_OBJ_OPT(x)	(x == SRH_OBJ_OPT_NAME_FUZZY || x == SRH_OBJ_OPT_NAME_HEADER || x == SRH_OBJ_OPT_COMMENT_FUZZY || x == SRH_OBJ_OPT_COMMENT_HEADER || x == SRH_OBJ_OPT_NAME_MATCH || x == SRH_OBJ_OPT_COMMENT_MATCH)
#define IS_INT_SRH_OBJ_OPT(x)	(x == SRH_OBJ_OPT_SIGN_SHOW_STYLE || x == SRH_OBJ_OPT_SIGN_ICON_ID || x == SRH_OBJ_OPT_TRACK_LINET_TYPE || x == SRH_OBJ_OPT_TRACK_SHOW_STYLE || x == SRH_OBJ_OPT_TRACK_CLASS0)
#define IS_SAME_SRH_OBJ_OPT(x)	(x == SRH_OBJ_OPT_SRH_SAME)

// ��������
struct tagOApiObjectSrhReq {
	int iReqVer;	// �汾��, ĿǰΪ0

	int iSrhOpt;	// ���ն���SRH_OBJ_OPT_XXX
	int iObjType;	// 0��ʾ�κ�����

	DWORD idParent;	// 0��ʾ�ղؼ�
	DWORD idShapeSelect;	// 0��ʾ������ͼ��
	BYTE bNoChild;		// 0��ʾ�����������ļ���, 1��ʾֻ����idParentһ��
	int iMaxCnt;		// 0��ʾ������

	char strSrhTxt[MAX_API_NAME_LEN];
	int iSrhValue;

	BYTE bNoCase;

	BYTE bRet[3];
	DWORD dwRet[99];
};

// ������Ӧ
struct tagOApiObjectSrhRes {
	DWORD idObj;	//����id
	int iObjType;	//��������

	DWORD dwRet[10];
};

struct tagOApiObjChageHdr {
	int iVer;
	int iFlag;	// 0: ������޸�, 1: ɾ��

	int nList;
	union {
		DWORD* pdwList;
		double dAlign1;
	};

	DWORD dwRet[20];
};


// �ڴ沼��
// tagOApiShapeFillCadPatHdrָ�������n1����tagOApiShapeFillCadPatItem
// tagOApiShapeFillCadPatItemָ�������n2����tagOApiShapeFillCadPatUnit

struct tagOApiShapeFillCadPatUnit {
	double dAngle;
	double dxOrg;
	double dyOrg;
	double dxDelta;
	double dyDelta;
	int nDash;
	double dDashList[20];

	DWORD dwRet[10];
};

struct tagOApiShapeFillCadPatItem {
	char strName[64];
	char strComment[255];

	double dDefaultScale;
	DWORD id;

	int nSfcpu;
	union {
		tagOApiShapeFillCadPatUnit* pSfcpu;
		double dAlign1;
	};

	DWORD dwRet[10];
};

struct tagOApiShapeFillCadPatHdr {
	int iVer;

	int nSfcpi;
	union {
		tagOApiShapeFillCadPatItem* pSfcpi;
		double dAlign1;
	};

	DWORD dwRet[20];
};



int OApiUtf16ToUtf8(WORD* wsUtf16, BYTE* strUtf8, int nBuf);
WORD* OApiUtf8ToUtf16(char* strUtf8, WORD* utf16, int* pnU16);
tagOApiObjectOptHdr* OApiNewOptHdr(int iExtLen = 0);
char* OApiNewObjectComment(char* strComment);
char* OApiCopyComment(void* pBuf, int nComment);
void* OApiZeroMalloc(int iSize);
bool AppendMemBuf(tagOApiMemBuf *pMb, char *pBuf, int nBuf, bool bSetZero = true);




class OMapApi :public CWinApp
{

	int m_iAppID;
	WPARAM m_winid;
	WORD m_wsAppClassName[100];
	int m_iOmapVer;

#ifdef WIN32
	void RegisterToOmap();
	bool CmdCheck(int iCmdId);
#endif

public:
	
	OMapApi(void);
	~OMapApi(void);

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	void Init(WORD* wsAppClassName);


	tagOApiObjGroupV1* NewOmapGroup();
	tagOApiMapSignV1* NewOmapSign();
	tagOApiMapTrackV1* NewOmapTrack();
	tagOApiMapShapeV1* NewOmapShape();
	tagOApiMapDirectionsV1* NewOmapDir();
	void FreeOmapObject(void* pObject, int iObjType);

	tagOApiObjGroupV1* GetOmapGroupFromBuf(void* pBuf, int nBuf);
	tagOApiMapSignV1* GetOmapSignFromBuf(void* pBuf, int nBuf);
	tagOApiMapTrackV1* GetOmapTrackFromBuf(void* pBuf, int nBuf);
	tagOApiMapShapeV1* GetOmapShapeFromBuf(void* pBuf, int nBuf);
	tagOApiMapDirectionsV1* GetOmapDirFromBuf(void* pBuf, int nBuf);

	BYTE *SetOmapObjectToBuf(void *pObj, int iObjType, int &nBuf);


#ifdef WIN32
	
	int SendMessageToOmap(int iCmdId, void* pData, int nData, INT64 *plResult = NULL, int iTimeoutMs = -1);
	
	void SetOmapTmpSign(double lat, double lng, bool bGcj02);
	void GeoDecodeLatlng(double lat, double lng, bool bGcj02);

	// ��[2018/12/25]��������, ��ά�˵���Ӧ����Ҳ��ɾ��, ��ʹ���µĽӿ�SetOmapLevelAndLocationExt
	// int SetOmapLevelAndLocation(int iMapID, int iMapLevel, double lng, double lat);
	int SetOmapLevelAndLocationExt(int iMapID, int iMapLevel, double x_lng, double y_lat, BYTE bActive = FALSE, BYTE bReal = 0, int iTimeoutMs = -1);
	void CleanOmapTmpObject();

	int GetOmapSelObjectTree(BYTE bLlType = 0);
	int SetOmapSelObjectTree(int iCmd, tagOApiMemBuf tag, bool bFreeBuf = true);
	int GetOmapObjectList(DWORD idParent);
	int GetOmapObject(DWORD idObj, BYTE bLlType = 0);
	int DelOmapObject(DWORD* pidList, int nId, bool bNoGroup = false, bool bForceDel = false);
	int GetOmapSelectList(int iFlag = 1);
	int SetOmapSelectIdList(DWORD* pidList, int nId);
	// ��[2018/12/25]��������, ��ά�˵���Ӧ����Ҳ��ɾ��
	// int SrhOmapObject(char *strName, DWORD idParent, int iType);
	int SrhOmapObject(tagOApiObjectSrhReq *pSrhReq);
	int SetOmapButton(int iAdd, char *strTip, int iTimeoutMs = -1);
	int GetOmapStatusInfo();
	int ReqVip5Demo(bool bSend);

	int CheckInterfaceVer(int iType, int iVer, bool bSendReq);

	int GetOmapMapData(double x_lng1, double y_lat1, double x_lng2, double y_lat2, INT64 iMaxPixel, int iMaxLevel);
	int GetOmapMapFile(tagOmapGetMapFile *pReq, int nReq);
	int GetOmapContour(tagOmapReqContour *pReq, int nReq);

	int SetSysCoorPoint(int iCoorType, tagOApiRelatePointV1 *pPoint, int nPoint);
	void GetSysCoorInfo();
	void GetSysCoorCenter();
	void GetCoorPixelInfo(double lng_x, double lat_y);
	void GetWinMapInfo(BYTE bRealLL);
	int FollowWinMapInfo(int iFollowMs);
	int FollowObjChange(int iAppID = -1);

	int SetOmapObject(DWORD idObj, tagOApiObjGroupV1* pGroup, INT64 *pIdResult = NULL, DWORD idParent = 0, int iPosition = 0);
	int SetOmapObject(DWORD idObj, tagOApiMapSignV1* pSign, INT64 *pIdResult = NULL, DWORD idParent = 0, int iPosition = 0);
	int SetOmapObject(DWORD idObj, tagOApiMapTrackV1* pTrack, INT64 *pIdResult = NULL, DWORD idParent = 0, int iPosition = 0);
	int SetOmapObject(DWORD idObj, tagOApiMapShapeV1* pShape, INT64 *pIdResult = NULL, DWORD idParent = 0, int iPosition = 0);
	int SetOmapObject(DWORD idObj, tagOApiMapDirectionsV1* pDir, INT64 *pIdResult = NULL, DWORD idParent = 0, int iPosition = 0);
	int SetOmapObject(DWORD idObj, int iObjType, void* pObj, INT64 *pIdResult = NULL, DWORD idParent = 0, int iPosition = 0);

	int SendGetShapeFillPatList();
	tagOApiShapeFillCadPatHdr *DeocdeShapeFillPatList(void *pBuf, int nBuf);
	void FreeShapeFillPatList(tagOApiShapeFillCadPatHdr *pHdr, bool bFreeMe);
	DECLARE_MESSAGE_MAP()
#endif

};

extern OMapApi g_omapApi;
extern int g_iOmapApiVer;
#endif

