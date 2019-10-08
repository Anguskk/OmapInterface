#pragma once
//CLI引用的时候需要 2019.3.22
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
// 返回tagOApiObjDataItem数组, 会自动填充(修正)idParent与idObj
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

// 所有对象
#define OBJ_SELECT_CHECK_FLAG_ALL			0
// 选中对象, 选中的文件夹自动包含所有子对象
#define OBJ_SELECT_CHECK_FLAG_GROUP_JOIN	1
// 选中对象, 选中的文件夹不自动包括非选中子对象
#define OBJ_SELECT_CHECK_FLAG_SEL_ONLY		2
// 选中对象, 如果选中的是文件夹, 则排除文件夹本身去选中子结点
#define OBJ_SELECT_CHECK_FLAG_NO_GROUP		3


//临时对象分组节点ID
#define OMAP_TMP_OBJ_GROUP_ID 202

#define OMAP_ALIGN_8_BYTE(x) ((x) % 8 == 0) ? x : ((x) / 8 * 8 + 8)
//经纬度
struct tagOmapLatlng {
	double lat;
	double lng;
	BYTE bReal;//是否真实经纬度
};
/*
地图位置
iMapID 地图id
100文件夹：小字体谷歌地图下载文件夹
130文件夹：大字体谷歌地图下载文件夹

101文件夹：谷歌卫星图下载文件夹
160文件夹：小字体谷歌路网图下载文件夹
161文件夹：大字体谷歌路网图下载文件夹

102文件夹：小字体谷歌地形图下载文件夹
132文件夹：大字体谷歌地形图下载文件夹

103文件夹：bing卫星图下载文件夹

104文件夹：OpenCycle等高线图下载文件夹

105文件夹：小字体百度地图下载文件夹
135文件夹：大字体百度地图下载文件夹

106文件夹：小字体搜狗地图下载文件夹
136文件夹：大字体搜狗地图下载文件夹

200-1000文件夹：自定义地图下载文件夹（以地图ID命名）
*/

struct tagOmapLocation {
	struct tagOmapLatlng ll;//经纬度
	int iMapID;//地图类型ID
	int iMapLevel;//地图级别
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

	// 奥维当前使用
	int iMapX;
	int iMapY;
	int iRet;

	DWORD ret[10];
};

struct tagOPhotoMapPic {
	INT64 idPic;//照片id
	unsigned int tmPhoto;//照片拍摄时间
	double lat;//维度
	double lng;//经度
	int iAction;//ACTION_MOUSE_MOVE 1  ACTION_MOUSE_CLICK 2
	int iTmp;//备用, OMAP_WIN_CMD_TIME_TO_LATLNG命令该变量返回照片时间减轨迹点时间的差值
};

struct tagOmapGeoDecode {
	struct tagOmapLatlng oll;
	int nLevel;//地图解析的层级  如 省市区3级、省市县3级、市区2级
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

#define OAPI_RET_ERR_VIP_LEVEL	-1 //奥维VIP级别不够
#define OAPI_RET_ERR_VIP5_NEED	-2 //需要VIP5及以上
#define OAPI_RET_ERR_LATLNG_INVALID	-3 //坐标系错误
#define OAPI_RET_ERR_ARGV	-4 //参数错误
#define OAPI_RET_ERR_MEMORY_OUT	-5 //内存异常
#define OAPI_RET_ERR_UNKNOWN	-6 //未知错误
#define OAPI_RET_ERR_ARGV_REQ	-7 //与等高线请求相关
#define OAPI_RET_ERR_MEMORY_END	-8 //内存不足而终止

#define OAPI_DATA_HAS_FULL	1
#define OAPI_DATA_PART_ONLY	2
#define OAPI_DATA_IS_NONE	3



#define GET_MAP_FILE_RET_ERR_COORD_TYPE	-101//坐标系设置错误(或位置偏差过大)
#define GET_MAP_FILE_RET_ERR_IGNORE	-102 //忽略
#define GET_MAP_FILE_RET_ERR_SIZE_EXCEED	-103//地图尺寸太大
#define GET_MAP_FILE_RET_ERR_PIXEL_EXCEED	-104//地图像素太高
#define GET_MAP_FILE_RET_ERR_CREATE_IMG	-105 //创建地图失败
#define GET_MAP_FILE_RET_ERR_RESIZE	-106//地图扭曲太大


#define GET_MAP_FILE_IMG_TYPE_PNG	0
#define GET_MAP_FILE_IMG_TYPE_JPG	1

extern unsigned int g_msgGetMapProcess;
struct tagOmapGetMapFile {

	INT64 idMap;	// 该请求的编号, 多次请求时相同编号新的会替换旧的
	INT64 iValue;	// 重要程度

	int iFlag;		// 1表示图不完全时直接忽略
	int iRet;		//  返回值

	char strFile[256];	// 文件名为空时或者写入失败时将通过pData返回
	bool bFile;			// 表明写入状态

	union {
		void *pData;
		double dAlignDate;
	};
	int nData;

	double x_lng1;
	double y_lat1;
	double x_lng2;
	double y_lat2;
	BYTE bRealLl;	// 必须设置

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

	int iPostCnt;	// 取图过程每取多少张发送一次g_msgGetMapProcess消息(WPARAM=iTotal, PARAM=iDeal);

	int iTmp;	// 奥维使用的临时变量
	BYTE bSendReq;	// 1表示图不存在或者不完全时发送网络请求

	BYTE bImageType;	// GET_MAP_FILE_IMG_TYPE_XXX
	BYTE bRetUse[3];

	int iRetUse[19];
};


#define GET_CONTOUR_RET_ERR_EXCEED_ONE	-101
#define GET_CONTOUR_RET_ERR_PART_OK		-102
#define GET_CONTOUR_RET_ERR_PART_ERR		-103

extern unsigned int g_msgGetContourProcess;
struct tagOmapReqContour {

	INT64 idMap;	// 该请求的编号, 多次请求时相同编号新的会替换旧的
	INT64 iValue;	// 重要程度

	double x_lng1;
	double y_lat1;
	double x_lng2;
	double y_lat2;
	BYTE bRealLl;

	int iMapLevel;	// 请求级别
	int iElevValue;	// 等高线间隔

	int iCheckFlag;	// 0: 表示直接取, 1: 表示只做检测行为
	int iCheckResult;

	int iRet;		// 返回值
	int iNeedVip;	// 所需要的VIP级别
	BYTE bPart;


	// data结构封装形式参考GetOmapSelObjectTree说明
	union {
		void *pData;
		double dAlignDate;
	};
	int nData;

	union {
		void *hWnd;	// HWND hWnd
		double dAlignWnd;
	};



	int iPostCnt;	// 取等高线过程每取多少次间隔发送一下g_msgGetContourProcess消息(WPARAM=iTotal, PARAM=iDeal);

	int iRet1[20];	// 预留
};


struct tagOMapBtnInfo {
	int ret0;
	int iAdd;
	char strTip[256];
	int ret1[10];
};

//存放收藏夹对象的结构体
struct tagOApiObjectOptHdr {
	WORD iVersion;//奥维版本
	BYTE iType;//对象类型：文件夹、标签、轨迹、图形、路线
	// BYTE bRet;//备用
	BYTE bLlType;//坐标类型
	DWORD idParent;//收藏夹对象的父节点的id 0表示该对象为根节点
	DWORD idObj;//收藏夹对象的id
	int ret;//节点所在位置
};

//收藏夹对象列表
struct tagOApiItemListV1 {
	DWORD idObj;//对象id
	int iType;//对象类型
	char strName[MAX_API_NAME_LEN];//对象名称
};

struct tagOApiObjGroupV1 {
	char strName[MAX_API_NAME_LEN];

	int nChild;//下一级子项的个数
	int nAllChild;	//所有子项及其下属的总个数，未加载时该值也是一样
	BYTE bLoadOk;	//是否加载成功

	BYTE bSaveMerge;//存盘时pChild的内容是否合并存储，合并存储可大大加快载入时间，但使修改时存盘时间下降
	BYTE bGroup;	//是否组合，不可展开
	BYTE bAutoLoad;	//是否自动加载
	BYTE iShowLevel;//是否隐藏
	BYTE iShowLevelMax;//显示级别
	BYTE bCrypt;	//是否加密, 如果设置了加密则自动加载将自动失效, 接口可以获取该值但无法设置修改
	BYTE bReadOnly;	//是否只读, 0: 不锁定, 1: 不带密码锁定, 2: 带密码锁定
	BYTE bNotHotId;	//是否不响应鼠标事件
	BYTE bRelate;	//是否是关联对象（目前用于标签与轨迹关联）
	BYTE pwd[16];//设置的密码, 不用, 无法获取与修改
	DWORD ret[10];	//return值
};

//表示标签的结构体
struct tagOApiMapSignV1 {
	char strName[MAX_API_NAME_LEN];//标签名称
	union {
		//32位系统指针占4个字节，64位系统指针占8个字节，为使结构大小采用union联合体增加8字节dAlign变量，
		char* pstrComment;//标签备注
		double dAlign;
	};

	double lat;
	double lng;
	BYTE bRealLl;	//0:gcj02经纬度, 1:真实经纬度, 2:当前坐标系下的平面坐标
	int iAltitude;	//海拔
	int iTime;		//生成时间

	BYTE bEditMode;//是否可编辑
	BYTE iOverlayIdx;//叠放层级

	BYTE iSignAlignFlag;//标签图标对齐标志，0为默认下中对齐，1为正中对齐
	int iSignPic;		//0:no picture,>=1 has sign picture
	DWORD dwSignClr;
	BYTE iPicScale;	//0:defalut,>=1 32*iPicScale/10

	BYTE iTxtType;	//0:not show txt,1:show txt ,2:show text with border, 3: custom txt
	BYTE iShowLevel;//标签显示级别
	BYTE iShowLevelMax;	//show between iShowLevel-iShowLevelMax
	//自定义字体的信息
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
//	//如果是共享属性，则修改时会遍历标签，将所有关联附件都做更改
//	BYTE bShare;
//};

//轨迹上的点的信息
struct tagOApiMapTrackPointV1 {
	double lat;
	double lng;
	int time;//轨迹点的时间
	int iAltitude;		// iAltitude >> 16 == 1 表示该点为新子图形(新子轨迹)的起始点即前一个点间断

	//扩展格式，用于CAD
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

//表示轨迹的结构体
struct tagOApiMapTrackV1 {
	char strName[MAX_API_NAME_LEN];

	union {
		char* pstrComment;
		double dAlign1;
	};
	union {
		struct tagOApiMapTrackPointV1* pMtp;
		double dAlign2;//对齐字段
	};
	int nMtp;//轨迹点数

	BYTE bRealLl;	//tagOApiMapTrackPointV1中的经纬度是否真实经纬度

	BYTE iTrackType;	// 轨迹类别: 自驾, 爬山 ...
	BYTE iOverlayIdx;	//叠放层级

	BYTE iShowLevel;//显示级别
	BYTE iShowLevelMax;//show between iShowLevel-iShowLevelMax
	BYTE bShowName;//是否显示轨迹名称
	BYTE bEdit;//轨迹是否可编辑

	//六个自定义字段用于保存轨迹的自定义属性
	BYTE iCustomType1;
	BYTE iCustomType2;
	BYTE iCustomType3;
	BYTE iCustomType4;
	int dwCustom1;
	int dwCustom2;

	//轨迹绘制的相关属性
	struct tagOApiMapTrackDraw {
		DWORD dwLineClr;	//线条颜色
		int iLineWidth;		//线宽
		BYTE iLineAlpha;	//线条透明度
		BYTE iShowType;		// 轨迹风格: 显示加权距离, CAD多段线 ...
		BYTE iLineType;		//线型
		BYTE bNeedDrawDetail;	//是否需要绘制角度、距离提示信息
		BYTE bClose;			//是否闭合
	}mtd;
	DWORD ret[10];
};



//表示图形的结构体
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
	int nMtp;//图形的节点数
	BYTE bRealLl;

	//iShowFlag:0 不显示属性，1 显示名字 2 显示面积 3 显示名字与面积
	BYTE iShowFlag;
	BYTE iOverlayIdx;
	double dStartAngle;	//当图形为两个点时，通过起始角度与终止角度表示圆、扇形、矩形
	double dEndAngle;

	BYTE iLineWidth;	//线宽
	BYTE iLineAlpha;	//线条透明度
	BYTE iAreaAlpha;	//区域透明度
	BYTE bEditMode;		//是否可编辑
	BYTE iShowLevel;
	BYTE iShowLevelMax;
	//外部Rgn索引，0为全部都是外部，>0为前面多少个是外部，后面是内部，用于处理镂空
	WORD iOuterRgnIdx;
	//change by houyb at 2018/03/27
	//BYTE iOuterRgnIdx;
	DWORD dwLineClr;	//线条颜色
	DWORD dwAreaClr;	//填充颜色
#if 0
	DWORD ret[10];
#else
	//0:默认颜色填充，1，渐变色填充，2：图案填充，3：CAD图案填充
	int iFillType;
	//渐变色填充时，0，从左到右渐变，1，从左到中间渐变再到右还原，2：从外围到中心渐变, CAD图案时，为是否随图缩放
	int iFillSubType;
	//图案ID
	DWORD dwFillPattern;
	// 渐变色2, 填充背景色
	DWORD dwFillChgClr;
	float fFillRotate;
	//用于CAD图案填充
	float fFillScale;

	// 存储填充点的绝对值
	double fFillOffsetX;
	double fFillOffsetY;
#endif
};


struct tagOApiLatLngV1 {
	double lat;
	double lng;
};
//表示一个导航步骤的结构体
struct tagOApiMapDirectionsUnitV1 {
	char strTitle[128];//主步骤
	char strSubTitle[10][128];//子步骤
	int nSubCount;	//子步骤数
	short iType;	//交通工具类型
	int nLl;		//llList个数
	union {
		struct tagOApiLatLngV1* llList;
		double dAlign;
	};
};
//表示导航路线的结构体
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
	int nUnit;//导航步骤数
	char strTitle[128];
	//搜索到的导航步骤
	struct tagMapDirectionsSrh {
		struct tagOApiLatLngV1 mpStart;//出发点的经纬度
		struct tagOApiLatLngV1 mpEnd;//终点的经纬度
		struct tagOApiLatLngV1 mpVia[MAX_API_DIR_WAYPOINTS];//中间导航点的经纬度
		int iDirMode;//???
	}dirSrh;
	BYTE bEdit;//是否可编辑

	BYTE iLineWidth;	//线宽
	BYTE iLineAlpha;	//透明度
	DWORD dwLineClr;	//线条颜色
	BYTE iOverlayIdx;	//叠放层级
	BYTE bRealLl;		//是否真实经纬度

	BYTE iShowLevel;	//显示级别
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
	char hash[16];	// 以下情况有效, 可用于判断是否发生了变化, [0, 奥维平面坐标, 4: 墨卡托坐标时]
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
	int iDataLen;	// 后面紧跟数据的长度
	int iObjType;
	DWORD idObj;
	DWORD idParent;
	INT64 iCustomData;	// 接口可以自定义数据
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

// 搜索请求
struct tagOApiObjectSrhReq {
	int iReqVer;	// 版本号, 目前为0

	int iSrhOpt;	// 参照定义SRH_OBJ_OPT_XXX
	int iObjType;	// 0表示任何类型

	DWORD idParent;	// 0表示收藏夹
	DWORD idShapeSelect;	// 0表示不限制图形
	BYTE bNoChild;		// 0表示遍历搜索子文件夹, 1表示只搜索idParent一级
	int iMaxCnt;		// 0表示不限制

	char strSrhTxt[MAX_API_NAME_LEN];
	int iSrhValue;

	BYTE bNoCase;

	BYTE bRet[3];
	DWORD dwRet[99];
};

// 搜索响应
struct tagOApiObjectSrhRes {
	DWORD idObj;	//对象id
	int iObjType;	//对象类型

	DWORD dwRet[10];
};

struct tagOApiObjChageHdr {
	int iVer;
	int iFlag;	// 0: 添加与修改, 1: 删除

	int nList;
	union {
		DWORD* pdwList;
		double dAlign1;
	};

	DWORD dwRet[20];
};


// 内存布局
// tagOApiShapeFillCadPatHdr指定后面跟n1个的tagOApiShapeFillCadPatItem
// tagOApiShapeFillCadPatItem指定后面跟n2个的tagOApiShapeFillCadPatUnit

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

	// 从[2018/12/25]算起半年后, 奥维端的响应代码也将删除, 请使用新的接口SetOmapLevelAndLocationExt
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
	// 从[2018/12/25]算起半年后, 奥维端的响应代码也将删除
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

