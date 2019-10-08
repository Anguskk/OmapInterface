
#include "OMapApi.h"
//CLI引用的时候需要 2019.3.22
#if defined WIN32 && !defined WIN10
#include <tchar.h>
#include <malloc.h>
#endif

OMapApi g_omapApi;
int g_iOmapApiVer = 220;
BEGIN_MESSAGE_MAP(OMapApi, CWinApp)

END_MESSAGE_MAP()
#ifdef WIN32
#ifdef WIN10
unsigned int g_msgGetMapProcess = 0;
unsigned int g_msgGetContourProcess = 0;
#else 
unsigned int g_msgGetMapProcess = ::RegisterWindowMessage(_T("O_MAP_API_MSG_GET_MAP_FILE_PROGRESS"));
unsigned int g_msgGetContourProcess = ::RegisterWindowMessage(_T("O_MAP_API_MSG_GET_CONTOUR_LINE_PROGRESS"));
#endif
#else
unsigned int g_msgGetMapProcess = 0;
unsigned int g_msgGetContourProcess = 0;
#endif

#ifndef RGB
#define RGB(r,g,b)          ((DWORD)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif

WORD* OApiUtf8ToUtf16(char* strUtf8, WORD* utf16, int* pnU16)
{
	int len = (int)strlen(strUtf8);
	WORD* wszString;
	if (utf16)
		wszString = utf16;
	else
		wszString = (WORD*)malloc((len + 1) * 2);

	if (pnU16)
		*pnU16 = 0;

	BYTE* u8 = (BYTE*)strUtf8;
	int i;
	int wSta = 0;
	for (i = 0; i < len; i++)
	{
		if (wSta == 316)
			wSta = wSta;
		if (u8[i] == 0)
			break;
		else if (u8[i] < 128)
		{
			wszString[wSta++] = u8[i];
		}
		else if (u8[i] >= 192 && u8[i] < 224)
		{
			if (i >= len - 1)
				break;//invalid
			if (!(u8[i + 1] >= 128 && u8[i + 1] < 192))
				break;//invalid

			wszString[wSta++] = ((u8[i] - 192) << 6) + (u8[i + 1] - 128);
			i++;
		}
		else if (u8[i] >= 224 && u8[i] < 240)
		{
			if (i >= len - 2)
				break;//invalid
			if (!(u8[i + 1] >= 128 && u8[i + 1] < 192))
				break;//invalid
			if (!(u8[i + 2] >= 128 && u8[i + 2] < 192))
				break;//invalid

			wszString[wSta++] = ((u8[i] - 224) << 12) + ((u8[i + 1] - 128) << 6) + (u8[i + 2] - 128);
			i += 2;
		}
		else
		{
			//ignore utf32
			if (u8[i] >= 240 && u8[i] < 248)
			{
				i += 3;
			}
			else if (u8[i] >= 248 && u8[i] < 252)
			{
				i += 4;
			}
			else if (u8[i] >= 252 && u8[i] < 254)
			{
				i += 5;
			}
			else
			{
				//invalid utf8 code
				break;
			}
		}
	}
	wszString[wSta] = 0;

	if (pnU16)
		*pnU16 = wSta;
	return wszString;
}

int OApiUtf16ToUtf8(WORD* wsUtf16, BYTE* strUtf8, int nBuf)
{
	int i;
	int iSta = 0;
	for (i = 0; wsUtf16[i] != 0 && iSta < nBuf - 1; i++)
	{
		if (wsUtf16[i] < 0x80)
			strUtf8[iSta++] = (BYTE)wsUtf16[i];
		else if (wsUtf16[i] < 0x800)
		{
			if (iSta >= nBuf - 2)
				break;

			strUtf8[iSta++] = (wsUtf16[i] >> 6) | 0xc0;
			strUtf8[iSta++] = (wsUtf16[i] & 0x3f) | 0x80;
		}
		else
		{
			if (iSta >= nBuf - 3)
				break;

			strUtf8[iSta++] = (wsUtf16[i] >> 12) | 0xe0;
			strUtf8[iSta++] = ((wsUtf16[i] >> 6) & 0x3f) | 0x80;
			strUtf8[iSta++] = (wsUtf16[i] & 0x3f) | 0x80;
		}
	}
	strUtf8[iSta] = 0;
	return iSta;
}

void* OApiZeroMalloc(int iSize)
{
	void* pp = malloc(iSize);
	if (!pp)
		return NULL;
	memset(pp, 0, iSize);
	return pp;
}

bool AppendMemBuf(tagOApiMemBuf *pMb, char *pBuf, int nBuf, bool bSetZero)
{
	if (nBuf < 0)
		return false;
	if (pMb->nBuf + nBuf > pMb->nMem)
	{
		int nMem = (pMb->nBuf + nBuf) * 2 + 10;
		char *pTmp = (char *)realloc(pMb->pBuf, nMem);
		if (pTmp == NULL)
			return false;
		if (bSetZero)
		{
			memset(pTmp + pMb->nBuf, 0, nMem - pMb->nBuf);
		}
		pMb->pBuf = pTmp;
		pMb->nMem = nMem;
	}

	memcpy(pMb->pBuf + pMb->nBuf, pBuf, nBuf);
	pMb->nBuf += nBuf;
	return true;
}

char* OApiNewObjectComment(char* strComment)
{
	int nn = (int)strlen(strComment) + 1;
	char* pp = (char*)OApiZeroMalloc(nn);
	memcpy(pp, strComment, nn);
	return pp;
}

char* OApiCopyComment(void* pBuf, int nComment)
{
	char* pp = (char*)OApiZeroMalloc(nComment + 1);
	memcpy(pp, pBuf, nComment);
	return pp;
}

tagOApiObjectOptHdr* OApiNewOptHdr(int iExtLen)
{
	tagOApiObjectOptHdr* pOoh = (tagOApiObjectOptHdr*)OApiZeroMalloc(sizeof(tagOApiObjectOptHdr) + iExtLen);
	if (!pOoh)
		return NULL;

	pOoh->iVersion = OMAP_WIN_API_VERSION;
	return pOoh;
}

OMapApi::OMapApi(void)
{
	m_iAppID = 0;
	m_iOmapVer = 0;
	m_winid = 0;
	memset(m_wsAppClassName, 0, sizeof(m_wsAppClassName));
	WNDCLASS   wc;
	//GetModuleHandle(NULL) AfxGetInstanceHandle()
	/*::GetClassInfo(GetModuleHandle(NULL), L"#32770", &wc);
	wc.lpszClassName = APP_CLASS_NAME;
	::RegisterClass(&wc);*/
}

OMapApi::~OMapApi(void)
{

}

LRESULT OMapApi::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_COPYDATA && wParam == OMAP_WIN_API_FLAG)
	{
		COPYDATASTRUCT* pcd = (COPYDATASTRUCT*)lParam;
		int nAppId = (pcd->dwData >> 16) & 0xffff;
		int nCmdId = pcd->dwData & 0xffff;

		if (nCmdId == OMAP_WIN_CMD_GET_LATLNG)
		{
			tagOmapLatlng oll;
			memcpy(&oll, pcd->lpData, sizeof(oll));

			CString ss;
			ss.Format(L"%lf,%lf", oll.lat, oll.lng);
			//m_edResult.SetWindowText(ss);

		}
	}
	return WindowProc(message, wParam, lParam);
	
}

void OMapApi::Init(WORD* wsAppClassName)
{
	int nn = (int)wcslen((wchar_t*)wsAppClassName) + 1;
	if (nn > 100)
		nn = 100;
	memcpy(m_wsAppClassName, wsAppClassName, nn * 2);
	//m_winid =  wid;
	//
	/*WNDCLASS   wc;
	::GetClassInfo(GetModuleHandle(0), L"#32770", &wc);
	wc.lpszClassName = APP_CLASS_NAME;
	::RegisterClass(&wc);*/
}


tagOApiObjGroupV1* OMapApi::NewOmapGroup()
{
	tagOApiObjGroupV1* pGroup = (tagOApiObjGroupV1*)OApiZeroMalloc(sizeof(tagOApiObjGroupV1));
	pGroup->bAutoLoad = 1;
	return pGroup;
}

tagOApiMapSignV1* OMapApi::NewOmapSign()
{
	tagOApiMapSignV1* pSign = (tagOApiMapSignV1*)OApiZeroMalloc(sizeof(tagOApiMapSignV1));
	return pSign;
}

tagOApiMapTrackV1* OMapApi::NewOmapTrack()
{
	tagOApiMapTrackV1* pTrack = (tagOApiMapTrackV1*)OApiZeroMalloc(sizeof(tagOApiMapTrackV1));
	pTrack->mtd.iLineWidth = 3;
	pTrack->mtd.iLineAlpha = 50;
	pTrack->mtd.dwLineClr = RGB(0, 0, 255);
	return pTrack;
}

tagOApiMapShapeV1* OMapApi::NewOmapShape()
{
	tagOApiMapShapeV1* pShape = (tagOApiMapShapeV1*)OApiZeroMalloc(sizeof(tagOApiMapShapeV1));
	pShape->iLineAlpha = 50;
	pShape->iAreaAlpha = 50;
	pShape->iLineWidth = 1;
	pShape->dwLineClr = RGB(0, 0, 255);
	pShape->dwAreaClr = RGB(0, 0, 255);
	return pShape;
}

tagOApiMapDirectionsV1* OMapApi::NewOmapDir()
{
	tagOApiMapDirectionsV1* pDir = (tagOApiMapDirectionsV1*)OApiZeroMalloc(sizeof(tagOApiMapDirectionsV1));
	pDir->dwLineClr = RGB(255, 0, 0);
	pDir->iLineAlpha = 60;
	pDir->iLineWidth = 7;
	return pDir;
}

void OMapApi::FreeOmapObject(void* pObject, int iObjType)
{
	if (pObject == NULL)
		return;

	if (iObjType == OMAP_OBJ_TYPE_GROUP)
		free(pObject);
	else if (iObjType == OMAP_OBJ_TYPE_SIGN)
	{
		tagOApiMapSignV1* pSign = (tagOApiMapSignV1*)pObject;
		if (pSign->pstrComment)
			free(pSign->pstrComment);
		free(pSign);
	}
	else if (iObjType == OMAP_OBJ_TYPE_TRACK)
	{
		tagOApiMapTrackV1* pTrack = (tagOApiMapTrackV1*)pObject;
		if (pTrack->pstrComment)
			free(pTrack->pstrComment);
		if (pTrack->pMtp)
			free(pTrack->pMtp);
		free(pTrack);
	}
	else if (iObjType == OMAP_OBJ_TYPE_SHAPE)
	{
		tagOApiMapShapeV1* pShape = (tagOApiMapShapeV1*)pObject;
		if (pShape->pstrComment)
			free(pShape->pstrComment);
		if (pShape->pMtp)
			free(pShape->pMtp);
		free(pShape);
	}
	else if (iObjType == OMAP_OBJ_TYPE_DIR)
	{
		tagOApiMapDirectionsV1* pDir = (tagOApiMapDirectionsV1*)pObject;
		if (pDir->pstrComment)
			free(pDir->pstrComment);
		if (pDir->punit)
		{
			for (int i = 0; i < pDir->nUnit; i++)
			{
				if (pDir->punit[i].llList)
					free(pDir->punit[i].llList);
			}
			free(pDir->punit);
		}
		free(pDir);
	}
	else
		free(pObject);
}

tagOApiObjGroupV1* OMapApi::GetOmapGroupFromBuf(void* pBuf, int nBuf)
{
	if (nBuf != sizeof(tagOApiObjGroupV1))
		return NULL;

	tagOApiObjGroupV1* pGroup = NewOmapGroup();
	memcpy(pGroup, pBuf, sizeof(tagOApiObjGroupV1));

	return pGroup;
}

tagOApiMapSignV1* OMapApi::GetOmapSignFromBuf(void* pBuf, int nBuf)
{
	if (nBuf < (int)sizeof(tagOApiMapSignV1) + 4)
		return NULL;
	int nComment;
	memcpy(&nComment, (BYTE*)pBuf + sizeof(tagOApiMapSignV1), 4);
	if (nBuf != (int)sizeof(tagOApiMapSignV1) + 4 + nComment)
		return NULL;

	tagOApiMapSignV1* pSign = NewOmapSign();
	memcpy(pSign, pBuf, sizeof(tagOApiMapSignV1));
	if (nComment > 0)
		pSign->pstrComment = OApiCopyComment((BYTE*)pBuf + sizeof(tagOApiMapSignV1) + 4, nComment);
	else
		pSign->pstrComment = NULL;

	return pSign;
}

tagOApiMapTrackV1* OMapApi::GetOmapTrackFromBuf(void* pBuf, int nBuf)
{
	if (nBuf < (int)sizeof(tagOApiMapTrackV1) + 4)
		return NULL;
	int nComment;
	memcpy(&nComment, (BYTE*)pBuf + sizeof(tagOApiMapTrackV1), 4);
	int iMtOffset = sizeof(tagOApiMapTrackV1) + 4 + nComment;
	iMtOffset = OMAP_ALIGN_8_BYTE(iMtOffset);
	if (nBuf < iMtOffset)
		return NULL;

	tagOApiMapTrackV1* pTrack = NewOmapTrack();
	memcpy(pTrack, pBuf, sizeof(tagOApiMapTrackV1));
	if (nComment > 0)
		pTrack->pstrComment = OApiCopyComment((BYTE*)pBuf + sizeof(tagOApiMapTrackV1) + 4, nComment);
	else
		pTrack->pstrComment = NULL;
	pTrack->pMtp = NULL;

	if (nBuf != iMtOffset + pTrack->nMtp*((int)sizeof(tagOApiMapTrackPointV1)))
	{
		FreeOmapObject(pTrack, OMAP_OBJ_TYPE_TRACK);
		return NULL;
	}
	pTrack->pMtp = (tagOApiMapTrackPointV1*)malloc(pTrack->nMtp * sizeof(tagOApiMapTrackPointV1));
	memcpy(pTrack->pMtp, (BYTE*)pBuf + iMtOffset, pTrack->nMtp * sizeof(tagOApiMapTrackPointV1));

	return pTrack;
}

tagOApiMapShapeV1* OMapApi::GetOmapShapeFromBuf(void* pBuf, int nBuf)
{
	if (nBuf < (int)sizeof(tagOApiMapShapeV1) + 4)
		return NULL;
	int nComment;
	memcpy(&nComment, (BYTE*)pBuf + sizeof(tagOApiMapShapeV1), 4);
	int iMtOffset = sizeof(tagOApiMapShapeV1) + 4 + nComment;
	iMtOffset = OMAP_ALIGN_8_BYTE(iMtOffset);
	if (nBuf < iMtOffset)
		return NULL;

	tagOApiMapShapeV1* pShape = NewOmapShape();
	memcpy(pShape, pBuf, sizeof(tagOApiMapShapeV1));
	if (nComment > 0)
		pShape->pstrComment = OApiCopyComment((BYTE*)pBuf + sizeof(tagOApiMapShapeV1) + 4, nComment);
	else
		pShape->pstrComment = NULL;
	pShape->pMtp = NULL;

	if (nBuf != iMtOffset + pShape->nMtp*((int)sizeof(tagOApiMapTrackPointV1)))
	{
		FreeOmapObject(pShape, OMAP_OBJ_TYPE_SHAPE);
		return NULL;
	}
	pShape->pMtp = (tagOApiMapTrackPointV1*)malloc(pShape->nMtp * sizeof(tagOApiMapTrackPointV1));
	memcpy(pShape->pMtp, (BYTE*)pBuf + iMtOffset, pShape->nMtp * sizeof(tagOApiMapTrackPointV1));

	return pShape;
}

tagOApiMapDirectionsV1* OMapApi::GetOmapDirFromBuf(void* pBuf, int nBuf)
{
	if (nBuf < (int)sizeof(tagOApiMapDirectionsV1) + 4)
		return NULL;
	int nComment;
	memcpy(&nComment, (BYTE*)pBuf + sizeof(tagOApiMapDirectionsV1), 4);
	int iUnitOffset = sizeof(tagOApiMapDirectionsV1) + 4 + nComment;
	iUnitOffset = OMAP_ALIGN_8_BYTE(iUnitOffset);
	if (nBuf < iUnitOffset)
		return NULL;

	tagOApiMapDirectionsV1* pDir = NewOmapDir();
	memcpy(pDir, pBuf, sizeof(tagOApiMapDirectionsV1));
	if (nComment > 0)
		pDir->pstrComment = OApiCopyComment((BYTE*)pBuf + sizeof(tagOApiMapDirectionsV1) + 4, nComment);
	else
		pDir->pstrComment = NULL;
	pDir->punit = NULL;

	if (nBuf < iUnitOffset + pDir->nUnit*(int)sizeof(tagOApiMapDirectionsUnitV1))
	{
		FreeOmapObject(pDir, OMAP_OBJ_TYPE_DIR);
		return NULL;
	}
	pDir->punit = (tagOApiMapDirectionsUnitV1*)malloc(pDir->nUnit * sizeof(tagOApiMapDirectionsUnitV1));
	memcpy(pDir->punit, (BYTE*)pBuf + iUnitOffset, pDir->nUnit * sizeof(tagOApiMapDirectionsUnitV1));

	int iLlOffset = iUnitOffset + pDir->nUnit * sizeof(tagOApiMapDirectionsUnitV1);
	tagOApiLatLngV1* pll = (tagOApiLatLngV1*)((BYTE*)pBuf + iLlOffset);
	int idx = 0;
	for (int i = 0; i < pDir->nUnit; i++)
	{
		pDir->punit[i].llList = NULL;
		if (pDir->punit[i].nLl <= 0)
			continue;

		pDir->punit[i].llList = (tagOApiLatLngV1*)malloc(pDir->punit[i].nLl * sizeof(tagOApiLatLngV1));
		memcpy(pDir->punit[i].llList, pll + idx, pDir->punit[i].nLl * sizeof(tagOApiLatLngV1));
		idx += pDir->punit[i].nLl;
	}

	return pDir;
}

BYTE *OMapApi::SetOmapObjectToBuf(void *pObj, int iObjType, int &nBuf)
{
	BYTE *pBuf = NULL;
	if (iObjType == OMAP_OBJ_TYPE_GROUP)
	{
		tagOApiObjGroupV1* pGroup = (tagOApiObjGroupV1*)pObj;

		nBuf = sizeof(tagOApiObjGroupV1);
		pBuf = (BYTE *)OApiZeroMalloc(nBuf);

		memcpy(pBuf, pGroup, nBuf);
	}
	else if (iObjType == OMAP_OBJ_TYPE_SIGN)
	{
		tagOApiMapSignV1* pSign = (tagOApiMapSignV1*)pObj;

		nBuf = sizeof(tagOApiMapSignV1);
		int nComment = 0;
		if (pSign->pstrComment)
		{
			nComment = (int)strlen(pSign->pstrComment);
		}
		nBuf += nComment + 4;
		pBuf = (BYTE *)OApiZeroMalloc(nBuf);

		BYTE *pp = pBuf;
		memcpy(pp, pSign, sizeof(tagOApiMapSignV1));
		pp += sizeof(tagOApiMapSignV1);
		memcpy(pp, &nComment, 4);
		if (pSign->pstrComment)
			memcpy(pp + 4, pSign->pstrComment, nComment);
	}
	else if (iObjType == OMAP_OBJ_TYPE_TRACK)
	{
		tagOApiMapTrackV1* pTrack = (tagOApiMapTrackV1*)pObj;

		nBuf = sizeof(tagOApiMapTrackV1);
		int nComment = 0;
		if (pTrack->pstrComment)
		{
			nComment = (int)strlen(pTrack->pstrComment);
		}
		nBuf = OMAP_ALIGN_8_BYTE(nBuf + nComment + 4);
		pBuf = (BYTE *)OApiZeroMalloc(nBuf + pTrack->nMtp * sizeof(tagOApiMapTrackPointV1));

		BYTE *pp = pBuf;
		memcpy(pp, pTrack, sizeof(tagOApiMapTrackV1));
		memcpy(pp + sizeof(tagOApiMapTrackV1), &nComment, 4);
		if (pTrack->pstrComment)
			memcpy(pp + sizeof(tagOApiMapTrackV1) + 4, pTrack->pstrComment, nComment);

		memcpy(pp + nBuf, pTrack->pMtp, sizeof(tagOApiMapTrackPointV1)*pTrack->nMtp);
		nBuf += sizeof(tagOApiMapTrackPointV1)*pTrack->nMtp;
	}
	else if (iObjType == OMAP_OBJ_TYPE_SHAPE)
	{
		tagOApiMapShapeV1* pShape = (tagOApiMapShapeV1*)pObj;

		nBuf = sizeof(tagOApiMapShapeV1);
		int nComment = 0;
		if (pShape->pstrComment)
		{
			nComment = (int)strlen(pShape->pstrComment);
		}
		nBuf = OMAP_ALIGN_8_BYTE(nBuf + nComment + 4);
		pBuf = (BYTE *)OApiZeroMalloc(nBuf + pShape->nMtp * sizeof(tagOApiMapTrackPointV1));

		BYTE* pp = pBuf;
		memcpy(pp, pShape, sizeof(tagOApiMapShapeV1));
		memcpy(pp + sizeof(tagOApiMapShapeV1), &nComment, 4);
		if (pShape->pstrComment)
			memcpy(pp + sizeof(tagOApiMapShapeV1) + 4, pShape->pstrComment, nComment);

		memcpy(pp + nBuf, pShape->pMtp, sizeof(tagOApiMapTrackPointV1)*pShape->nMtp);
		nBuf += sizeof(tagOApiMapTrackPointV1)*pShape->nMtp;
	}
	else if (iObjType == OMAP_OBJ_TYPE_DIR)
	{
		tagOApiMapDirectionsV1* pDir = (tagOApiMapDirectionsV1*)pObj;

		nBuf = sizeof(tagOApiMapDirectionsV1);
		int nComment = 0;
		if (pDir->pstrComment)
		{
			nComment = (int)strlen(pDir->pstrComment);
		}
		nBuf = OMAP_ALIGN_8_BYTE(nBuf + nComment + 4);

		int nLl = 0;
		for (int i = 0; i < pDir->nUnit; i++)
			nLl += pDir->punit[i].nLl;
		pBuf = (BYTE *)OApiZeroMalloc(nBuf + pDir->nUnit * sizeof(tagOApiMapDirectionsUnitV1) + nLl * sizeof(tagOApiLatLngV1));
		BYTE* pp = pBuf;
		memcpy(pp, pDir, sizeof(tagOApiMapDirectionsV1));
		memcpy(pp + sizeof(tagOApiMapDirectionsV1), &nComment, 4);
		if (pDir->pstrComment)
			memcpy(pp + sizeof(tagOApiMapDirectionsV1) + 4, pDir->pstrComment, nComment);

		memcpy(pp + nBuf, pDir->punit, pDir->nUnit * sizeof(tagOApiMapDirectionsUnitV1));
		nBuf += pDir->nUnit * sizeof(tagOApiMapDirectionsUnitV1);
		tagOApiLatLngV1* pll = (tagOApiLatLngV1*)(pp + nBuf);
		int nn = 0;
		for (int i = 0; i < pDir->nUnit; i++)
		{
			for (int j = 0; j < pDir->punit[i].nLl; j++)
			{
				pll[nn++] = pDir->punit[i].llList[j];
			}
		}
		nBuf += nLl * sizeof(tagOApiLatLngV1);
	}

	return pBuf;
}

#ifdef WIN32
//三方接口向OvalMap注册
void OMapApi::RegisterToOmap()
{
#ifndef WINRT
	HWND hwnd = ::FindWindow(L"omapWin", NULL);
	if (!hwnd)
		return;

	wchar_t* wsClass = (wchar_t*)m_wsAppClassName;
	COPYDATASTRUCT cd1;
	memset(&cd1, 0, sizeof(cd1));
	cd1.dwData = OMAP_WIN_CMD_REGISTER;
	cd1.cbData = (int)wcslen(wsClass) * 2 + 2;
	cd1.lpData = wsClass;
	m_iAppID = (int)SendMessage(hwnd, WM_COPYDATA, OMAP_WIN_API_FLAG, (LPARAM)&cd1);
	if (m_iAppID != 0)
	{
		memset(&cd1, 0, sizeof(cd1));
		cd1.dwData = (m_iAppID << 16) | OMAP_WIN_CMD_GET_VERSION;
		m_iOmapVer = (int)SendMessage(hwnd, WM_COPYDATA, OMAP_WIN_API_FLAG, (LPARAM)&cd1);
		if (m_iOmapVer < 0)
			m_iOmapVer = 0;
	}
#endif
}

bool OMapApi::CmdCheck(int iCmdId)
{
	if (m_iOmapVer < 621 && (iCmdId == OMAP_WIN_CMD_SET_MAP_LOCATION || iCmdId == OMAP_API_CMD_GET_OBJ_LIST
		|| iCmdId == OMAP_API_CMD_GET_OBJ || iCmdId == OMAP_API_CMD_SET_OBJ || iCmdId == OMAP_API_CMD_DEL_OBJ))
		return false;
	return true;
}

int OMapApi::SendMessageToOmap(int iCmdId, void* pData, int nData, INT64 *plResult, int iTimeoutMs)
{
#ifndef WINRT
	HWND hwnd = ::FindWindow(L"omapWin", NULL);
	if (!hwnd)
	{
		m_iAppID = 0;
		m_iOmapVer = 0;
		return OMAP_API_ERR_WND;
	}

	if (m_iAppID == 0)
		RegisterToOmap();
	if (m_iAppID == 0)
		return OMAP_API_ERR_REGISTER;

	if (!CmdCheck(iCmdId))
		return OMAP_API_ERR_VER;

	COPYDATASTRUCT cd;
	memset(&cd, 0, sizeof(cd));
	cd.dwData = (m_iAppID << 16) | iCmdId;
	cd.cbData = nData;
	cd.lpData = pData;
	LRESULT r = 0, lResult = 0;
	if (iTimeoutMs > 0)
	{
		// 0的话就相当于SendMessage
		DWORD_PTR dwResult = 0;
		r = SendMessageTimeout(hwnd, WM_COPYDATA, OMAP_WIN_API_FLAG, (LPARAM)&cd, SMTO_NORMAL, iTimeoutMs, &dwResult);
		// 返回值, 0:表示超时, 1: 成功并且已经处理, -1: 失败
		if (r != 0)
		{
			if (plResult != NULL)
				*plResult = dwResult;
			return 1;
		}
		return GetLastError() == ERROR_TIMEOUT ? 0 : -1;
	}

	r = SendMessage(hwnd, WM_COPYDATA, OMAP_WIN_API_FLAG, (LPARAM)&cd);
	
	lResult = r;
	int ret = 0;
	if (IS_OMAP_API_INTERRUPT_ERR(r))
	{
		ret = (int)r;
		r = 0;
	}
	if (r < 0)
	{
		m_iAppID = 0;
		m_iOmapVer = 0;
		RegisterToOmap();
		if (m_iAppID == 0)
			return OMAP_API_ERR_REGISTER;
		if (!CmdCheck(iCmdId))
			return OMAP_API_ERR_VER;

		r = SendMessage(hwnd, WM_COPYDATA, OMAP_WIN_API_FLAG, (LPARAM)&cd);
		lResult = r;
		if (IS_OMAP_API_INTERRUPT_ERR(r))
			ret = (int)r;
	}
	if (plResult != NULL)
		*plResult = lResult;
	return ret;
#else 
	return 0;
#endif
}

void OMapApi::SetOmapTmpSign(double lat, double lng, bool bGcj02)
{
	tagOmapLatlng oll;
	oll.bReal = bGcj02 ? 0 : 1;
	oll.lat = lat;
	oll.lng = lng;
	SendMessageToOmap(OMAP_WIN_CMD_SET_LATLNG, &oll, sizeof(oll));
}

void OMapApi::GeoDecodeLatlng(double lat, double lng, bool bGcj02)
{
	tagOmapGeoDecode ogd;
	memset(&ogd, 0, sizeof(ogd));
	ogd.oll.bReal = bGcj02 ? 0 : 1;
	ogd.oll.lat = lat;
	ogd.oll.lng = lng;
	SendMessageToOmap(OMAP_WIN_CMD_LATLNG_GEOCODE, &ogd, sizeof(ogd));
}

/*
int OMapApi::SetOmapLevelAndLocation(int iMapID, int iMapLevel, double lng, double lat)
{
	tagOmapLocation ol;
	memset(&ol, 0, sizeof(ol));
	ol.iMapID = iMapID;
	ol.iMapLevel = iMapLevel;
	ol.ll.lat = lat;
	ol.ll.lng = lng;
	return SendMessageToOmap(OMAP_WIN_CMD_SET_MAP_LOCATION, &ol, sizeof(ol));
}
*/



int OMapApi::SetOmapLevelAndLocationExt(int iMapID, int iMapLevel, double x_lng, double y_lat, BYTE bActive, BYTE bReal, int iTimeoutMs)
{
	tagOmapLocationExt ole;
	memset(&ole, 0, sizeof(ole));
	ole.ol.iMapID = iMapID;
	ole.ol.iMapLevel = iMapLevel;
	ole.ol.ll.lat = y_lat;
	ole.ol.ll.lng = x_lng;
	ole.ol.ll.bReal = bReal;
	ole.bActive = bActive;

	return SendMessageToOmap(OMAP_WIN_CMD_SET_MAP_LOCATION_EXT, &ole, sizeof(ole), NULL, iTimeoutMs);
}
void OMapApi::CleanOmapTmpObject()
{
	SendMessageToOmap(OMAP_WIN_CMD_CLEAN_TMP_OBJ, NULL, 0);
}

int OMapApi::SetOmapSelObjectTree(int iCmd, tagOApiMemBuf tag, bool bFreeBuf)
{
	int r = SendMessageToOmap(iCmd, tag.pBuf, tag.nBuf);
	if (bFreeBuf)
	{
		free(tag.pBuf);
		tag.pBuf = NULL;
	}

	return r;
}
int OMapApi::GetOmapSelObjectTree(BYTE bLlType)
{
	// 命令返回值的结构说明
	// Get与Set时结构一致
	// tagOApiObjectOptHdr[必选, Get时需要填充bLlType, Set时需要填充idParent]
	// tagOApiObjDataItem[必选, iDataLen指明后面跟着的数据总长度]
	// tagOApiObjDataItem+具体数据[可选, iDataLen指明后面具体数据的长度, 当该 条目为文件夹时后面紧接着的数据是作为同级还是子结点主要看nChild值]

	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(0);
	pOoh->bLlType = bLlType;

	int r = SendMessageToOmap(OMAP_API_CMD_GET_SEL_OBJ_TREE, pOoh, sizeof(tagOApiObjectOptHdr) + 0);
	free(pOoh);
	return r;
}

//idParent：要获取的父节点的ID，0表示根节点  idObj为1表示取根节点
int OMapApi::GetOmapObjectList(DWORD idParent)
{
	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(0);
	pOoh->idObj = idParent == 0 ? 1 : idParent;
	int r = SendMessageToOmap(OMAP_API_CMD_GET_OBJ_LIST, pOoh, sizeof(tagOApiObjectOptHdr));
	free(pOoh);
	return r;
}

int OMapApi::GetOmapObject(DWORD idObj, BYTE bLlType)
{
	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(0);
	pOoh->idObj = idObj;
	pOoh->bLlType = bLlType;
	int r = SendMessageToOmap(OMAP_API_CMD_GET_OBJ, pOoh, sizeof(tagOApiObjectOptHdr));
	free(pOoh);
	return r;
}

int OMapApi::DelOmapObject(DWORD* pidList, int nId, bool bNoGroup, bool bForceDel)
{
	// bNoGroup为真时, 不删除最顶层的本身文件夹
	// bForceDel为真时会强行删除, 忽略只读属性

	if (nId <= 0)
		return OMAP_API_ERR_ARGV;

	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(nId * 4);
	int ret = 0;
	if (bNoGroup)
		ret |= 0x1;
	if (bForceDel)
		ret |= 0x2;
	pOoh->ret = ret;
	DWORD* pdwObj = (DWORD*)(pOoh + 1);
	for (int i = 0; i < nId; i++)
	{
		pdwObj[i] = pidList[i];
	}

	int r = SendMessageToOmap(OMAP_API_CMD_DEL_OBJ, pOoh, sizeof(tagOApiObjectOptHdr) + nId * 4);
	free(pOoh);
	return r;
}

int OMapApi::GetOmapSelectList(int iFlag)
{
	// iFlag支持的参数为OBJ_SELECT_CHECK_FLAG_GROUP_JOIN, OBJ_SELECT_CHECK_FLAG_SEL_ONLY
	int iExtLen = sizeof(int);
	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(iExtLen);
	int *piFlag = (int*)(pOoh + 1);
	*piFlag = iFlag;
	int r = SendMessageToOmap(OMAP_API_CMD_GET_SEL_LIST, pOoh, sizeof(tagOApiObjectOptHdr) + iExtLen);
	free(pOoh);
	return r;
}

int OMapApi::SetOmapSelectIdList(DWORD* pidList, int nId)
{
	if (nId <= 0)
		return OMAP_API_ERR_ARGV;

	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(nId * 4);
	DWORD* pdwObj = (DWORD*)(pOoh + 1);
	for (int i = 0; i < nId; i++)
	{
		pdwObj[i] = pidList[i];
	}

	int r = SendMessageToOmap(OMAP_API_CMD_SET_SEL_ID_LIST, pOoh, sizeof(tagOApiObjectOptHdr) + nId * 4);
	free(pOoh);
	return r;
}

/*
int OMapApi::SrhOmapObject(char *strName, DWORD idParent, int iType)
{
	// idParent为0时表示搜索整个收藏夹
	// 注意若传入的是收藏夹ID时搜索的直接子结点, 而不是整个收藏夹的树
	// iType为0时表示不限制类型
	const int iExtLen = MAX_API_NAME_LEN;
	char strName1[iExtLen] = { 0 };
	if (strName != NULL)
		strncpy(strName1, strName, iExtLen - 1);
	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(iExtLen);
	pOoh->idParent = idParent;
	pOoh->iType = iType;
	memcpy(pOoh + 1, strName1, iExtLen);
	int r = SendMessageToOmap(OMAP_API_CMD_SRH_OBJ, pOoh, sizeof(tagOApiObjectOptHdr)+iExtLen);
	free(pOoh);
	return r;
}
*/

int OMapApi::SrhOmapObject(tagOApiObjectSrhReq *pSrhReq)
{
	// 命令回调返回sizeof(tagOApiObjectSrhReq)+sizeof(tagOApiObjectSrhRes)*n
	return SendMessageToOmap(OMAP_API_CMD_SRH_OBJ_EXT, pSrhReq, sizeof(tagOApiObjectSrhReq));
}

int OMapApi::SetOmapButton(int iAdd, char *strTip, int iTimeoutMs)
{
	// 0: 删除, 1: 添加, -1: 查询
	const int iExtLen = sizeof(tagOMapBtnInfo);
	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(iExtLen);
	tagOMapBtnInfo *pBtnInfo = (tagOMapBtnInfo*)(pOoh + 1);
	pBtnInfo->iAdd = iAdd;
	if (strTip)
		strncpy(pBtnInfo->strTip, strTip, sizeof(pBtnInfo->strTip) - 1);
	int r = SendMessageToOmap(OMAP_API_CMD_SET_BTN, pOoh, sizeof(tagOApiObjectOptHdr) + iExtLen, NULL, iTimeoutMs);
	free(pOoh);
	return r;
}

int OMapApi::GetOmapStatusInfo()
{
	// 两种方式均可判断返回值
	// 1. 函数返回值, 2. 命令返回值
	INT64 lResult = 0;
	int ret = g_omapApi.SendMessageToOmap(OMAP_API_CMD_GET_STATUS_INFO, NULL, 0, &lResult);

	// 判断方式
	// int iLv = GET_OMAP_API_STATUE_LV(r);
	// bool bLoad = GET_OMAP_API_STATUE_LOAD(r)
	if (ret < 0)
	{
		return ret;
	}
	return (int)lResult;
}

int OMapApi::ReqVip5Demo(bool bSend)
{
	// 参考bSend, 如果可以发送请求时, 是否发送[最好要让用户确认一下, 因为只有一次试用机会]

	// 成功时, 返回值lResult, 2: 可以发送请求, 1: 之前已经请求过了

	int iSend = bSend ? 1 : 0;

	INT64 lResult = 0;
	int ret = g_omapApi.SendMessageToOmap(OMAP_AIP_CMD_REQ_VIP5_DEMO, &iSend, 4, &lResult);

	if (ret < 0)
	{
		return ret;
	}
	return (int)lResult;
}


int OMapApi::CheckInterfaceVer(int iType, int iVer, bool bSendReq)
{
	// iType: OAPI_INTERFACE_TYPE_XXX
	// 通过命令返回, 有可能是异常
	// 存在不返回的情况, 如版本号相同以及从服务器请求信息失败
	tagOApiInterfaceVer ver;
	memset(&ver, 0, sizeof(ver));
	ver.iType = iType;
	ver.iVer = iVer;
	if (bSendReq)
		ver.iSendReq = 1;	// bSendReq为真时忽略iVer的值
	int r = SendMessageToOmap(OMAP_API_CMD_REQ_INTERFACE_VER, &ver, sizeof(ver));
	return r;
}

int OMapApi::GetOmapMapData(double x_lng1, double y_lat1, double x_lng2, double y_lat2, INT64 iMaxPixel, int iMaxLevel)
{
	int iExtLen = sizeof(tagOmapGetMap);
	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(iExtLen);
	tagOmapGetMap *pGet = (tagOmapGetMap*)(pOoh + 1);
	pGet->x_lng1 = x_lng1;
	pGet->y_lat1 = y_lat1;
	pGet->x_lng2 = x_lng2;
	pGet->y_lat2 = y_lat2;
	pGet->y_lat2 = y_lat2;
	pGet->bRealLl = 2;
	pGet->iMaxPixel = iMaxPixel;
	pGet->iMaxLevel = iMaxLevel;
	int r = SendMessageToOmap(OMAP_API_CMD_GET_MAP_DATA, pOoh, sizeof(tagOApiObjectOptHdr) + iExtLen);
	free(pOoh);
	return r;
}

int OMapApi::GetOmapMapFile(tagOmapGetMapFile *pReq, int nReq)
{
	// 命令可能分多次返回, 每次返回一个tagOmapGetMapFile, 后面还有多余数据时为图片数据
	int iExtLen = sizeof(tagOmapGetMapFile)*nReq;
	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(iExtLen);
	memcpy(pOoh + 1, pReq, iExtLen);

	int r = SendMessageToOmap(OMAP_API_CMD_GET_MAP_FILE, pOoh, sizeof(tagOApiObjectOptHdr) + iExtLen);
	free(pOoh);
	return r;
}

int OMapApi::GetOmapContour(tagOmapReqContour *pReq, int nReq)
{
	// 命令可能分多次返回, 每次返回一个tagOmapReqContour
	int iExtLen = sizeof(tagOmapReqContour)*nReq;
	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(iExtLen);
	memcpy(pOoh + 1, pReq, iExtLen);

	int r = SendMessageToOmap(OMAP_API_CMD_GET_CONTOUR, pOoh, sizeof(tagOApiObjectOptHdr) + iExtLen);
	free(pOoh);
	return r;
}

int OMapApi::SetSysCoorPoint(int iCoorType, tagOApiRelatePointV1 *pPoint, int nPoint)
{
	// iCoorType, 0: 奥维平面坐标, 3, 关联点, 4: 简化参数
	// 0与4只有第1个关联点有效, 3支持多个关联点

	// 命令返回值: OMAP_RET_SYS_COOR_XXX
	if (nPoint <= 0)
		return -1;

	int iValueList[10];
	memset(iValueList, 0, sizeof(iValueList));
	iValueList[0] = iCoorType;

	int iValueLen = sizeof(iValueList);
	int iPointLen = sizeof(tagOApiRelatePointV1)*nPoint;
	int iExtLen = iValueLen + iPointLen;
	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(iExtLen);
	BYTE *pBuf = (BYTE*)(pOoh + 1);
	memcpy(pBuf, iValueList, iValueLen);
	memcpy(pBuf + iValueLen, pPoint, iPointLen);
	int r = SendMessageToOmap(OMAP_API_CMD_SET_SYS_COOR_POINT, pOoh, sizeof(tagOApiObjectOptHdr) + iExtLen);
	free(pOoh);
	return r;
}

void OMapApi::GetSysCoorInfo()
{
	g_omapApi.SendMessageToOmap(OMAP_API_CMD_GET_SYS_COOR_INFO, NULL, 0);
}

void OMapApi::GetSysCoorCenter()
{
	// 命令返回tagOApiRelatePointV1, 目前只有x, y可用

	g_omapApi.SendMessageToOmap(OMAP_API_CMD_GET_SYS_COOR_CENTER, NULL, 0);
}

void OMapApi::GetCoorPixelInfo(double lng_x, double lat_y)
{
	// 命令返回tagOApiPixelInfo数组
	tagOApiRelatePointV1 rp;
	memset(&rp, 0, sizeof(rp));
	rp.x = lng_x;
	rp.y = lat_y;
	g_omapApi.SendMessageToOmap(OMAP_API_CMD_GET_COOR_PIXEL_INFO, &rp, sizeof(rp));
}
void OMapApi::GetWinMapInfo(BYTE bRealLL)
{
	tagWinMapInfo wmi;
	memset(&wmi, 0, sizeof(wmi));
	wmi.bReal2 = bRealLL;
	g_omapApi.SendMessageToOmap(OMAP_WIN_CMD_GET_MAP_INFO, &wmi, sizeof(wmi));
}

int OMapApi::FollowWinMapInfo(int iFollowMs)
{
	// -1表示查询, 1: 停止, > 10: ms, 建议值, 500, 1*1000, 2*1000, 5*1000, 因此奥维检测精度本身也不高 
	INT64 lResult = 0;
	int ret = g_omapApi.SendMessageToOmap(OMAP_WIN_CMD_FOLLW_MAP_INFO, &iFollowMs, sizeof(iFollowMs), &lResult);
	if (ret < 0)
	{
		return ret;
	}
	return (int)lResult;
}

int OMapApi::FollowObjChange(int iAppID)
{
	// iAppID
	// OAPI_APP_ID_QUERY: 查询当前值
	// OAPI_APP_ID_ALL:奥维发送所有注册AppID
	// OAPI_APP_ID_NONE: 不跟随
	// >0: 指定AppID

	// 返回最新的跟随值

	// 对象改变时, 奥维主动发送OMAP_WIN_CMD_FOLLW_OBJ_CHG_LIST命令
	// int nLen = sizeof(tagOApiObjChageHdr) + sizeof(DWORD)*nId;
	// tagOApiObjChageHdr *pObjChange = (tagOApiObjChageHdr *)zMalloc(nLen);

	INT64 lResult = 0;
	int ret = g_omapApi.SendMessageToOmap(OMAP_WIN_CMD_FOLLW_OBJ_CHG_FLAG, &iAppID, sizeof(iAppID), &lResult);
	if (ret < 0)
	{
		return ret;
	}
	return (int)lResult;
}



//idObj:对象ID，为0时则表示要添加，此时需要设置idParent
//idParent:当指定了idObj的值时，此项值无用，当idObj=0时，指示要插入的父节点的ID，此时idParent=0表示插入到根节点下
//iPosition:当指定了idObj的值时，此项值无用，当idObj=0时，指示要插入到父节点下的哪个位置，0表示最后
int OMapApi::SetOmapObject(DWORD idObj, tagOApiObjGroupV1* pGroup, INT64 *pIdResult, DWORD idParent, int iPosition)
{
	if (idObj == 0 && idParent == 0)
	{
		//奥维地图收藏夹根节点ID为1
		idParent = 1;
	}

	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(sizeof(tagOApiObjGroupV1));
	pOoh->idObj = idObj;
	pOoh->idParent = idParent;
	pOoh->iType = OMAP_OBJ_TYPE_GROUP;
	pOoh->iVersion = OMAP_WIN_API_VERSION;
	pOoh->ret = iPosition;

	memcpy(pOoh + 1, pGroup, sizeof(tagOApiObjGroupV1));
	int r = g_omapApi.SendMessageToOmap(OMAP_API_CMD_SET_OBJ, pOoh, sizeof(tagOApiObjectOptHdr) + sizeof(tagOApiObjGroupV1), pIdResult);
	free(pOoh);
	return r;
}

int OMapApi::SetOmapObject(DWORD idObj, tagOApiMapSignV1* pSign, INT64 *pIdResult, DWORD idParent, int iPosition)
{
	if (idObj == 0 && idParent == 0)
		idParent = 1;

	int iExtLen = sizeof(tagOApiMapSignV1);
	int nComment = 0;
	if (pSign->pstrComment)
	{
		nComment = (int)strlen(pSign->pstrComment);
	}
	iExtLen += nComment + 4;
	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(iExtLen);
	pOoh->idObj = idObj;
	pOoh->idParent = idParent;
	pOoh->iType = OMAP_OBJ_TYPE_SIGN;
	pOoh->iVersion = OMAP_WIN_API_VERSION;
	pOoh->ret = iPosition;

	BYTE* pp = (BYTE*)(pOoh + 1);
	memcpy(pp, pSign, sizeof(tagOApiMapSignV1));
	pp += sizeof(tagOApiMapSignV1);
	memcpy(pp, &nComment, 4);
	if (pSign->pstrComment)
		memcpy(pp + 4, pSign->pstrComment, nComment);

	int r = g_omapApi.SendMessageToOmap(OMAP_API_CMD_SET_OBJ, pOoh, sizeof(tagOApiObjectOptHdr) + iExtLen, pIdResult);
	free(pOoh);
	return r;
}

int OMapApi::SetOmapObject(DWORD idObj, tagOApiMapTrackV1* pTrack, INT64 *pIdResult, DWORD idParent, int iPosition)
{
	if (idObj == 0 && idParent == 0)
		idParent = 1;

	int iExtLen = sizeof(tagOApiMapTrackV1);
	int nComment = 0;
	if (pTrack->pstrComment)
	{
		nComment = (int)strlen(pTrack->pstrComment);
	}
	iExtLen = OMAP_ALIGN_8_BYTE(iExtLen + nComment + 4);

	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(iExtLen + pTrack->nMtp * sizeof(tagOApiMapTrackPointV1));
	pOoh->idObj = idObj;
	pOoh->idParent = idParent;
	pOoh->iType = OMAP_OBJ_TYPE_TRACK;
	pOoh->iVersion = OMAP_WIN_API_VERSION;
	pOoh->ret = iPosition;

	BYTE* pp = (BYTE*)(pOoh + 1);
	memcpy(pp, pTrack, sizeof(tagOApiMapTrackV1));
	memcpy(pp + sizeof(tagOApiMapTrackV1), &nComment, 4);
	if (pTrack->pstrComment)
		memcpy(pp + sizeof(tagOApiMapTrackV1) + 4, pTrack->pstrComment, nComment);

	memcpy(pp + iExtLen, pTrack->pMtp, sizeof(tagOApiMapTrackPointV1)*pTrack->nMtp);
	iExtLen += sizeof(tagOApiMapTrackPointV1)*pTrack->nMtp;

	int r = g_omapApi.SendMessageToOmap(OMAP_API_CMD_SET_OBJ, pOoh, sizeof(tagOApiObjectOptHdr) + iExtLen, pIdResult);
	free(pOoh);
	return r;
}

int OMapApi::SetOmapObject(DWORD idObj, tagOApiMapShapeV1* pShape, INT64 *pIdResult, DWORD idParent, int iPosition)
{
	if (idObj == 0 && idParent == 0)
		idParent = 1;

	int iExtLen = sizeof(tagOApiMapShapeV1);
	int nComment = 0;
	if (pShape->pstrComment)
	{
		nComment = (int)strlen(pShape->pstrComment);
	}
	iExtLen = OMAP_ALIGN_8_BYTE(iExtLen + nComment + 4);

	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(iExtLen + pShape->nMtp * sizeof(tagOApiMapTrackPointV1));
	pOoh->idObj = idObj;
	pOoh->idParent = idParent;
	pOoh->iType = OMAP_OBJ_TYPE_SHAPE;
	pOoh->iVersion = OMAP_WIN_API_VERSION;
	pOoh->ret = iPosition;

	BYTE* pp = (BYTE*)(pOoh + 1);
	memcpy(pp, pShape, sizeof(tagOApiMapShapeV1));
	memcpy(pp + sizeof(tagOApiMapShapeV1), &nComment, 4);
	if (pShape->pstrComment)
		memcpy(pp + sizeof(tagOApiMapShapeV1) + 4, pShape->pstrComment, nComment);

	memcpy(pp + iExtLen, pShape->pMtp, sizeof(tagOApiMapTrackPointV1)*pShape->nMtp);
	iExtLen += sizeof(tagOApiMapTrackPointV1)*pShape->nMtp;

	int r = g_omapApi.SendMessageToOmap(OMAP_API_CMD_SET_OBJ, pOoh, sizeof(tagOApiObjectOptHdr) + iExtLen, pIdResult);
	free(pOoh);
	return r;
}

int OMapApi::SetOmapObject(DWORD idObj, tagOApiMapDirectionsV1* pDir, INT64 *pIdResult, DWORD idParent, int iPosition)
{
	if (idObj == 0 && idParent == 0)
		idParent = 1;

	int iExtLen = sizeof(tagOApiMapDirectionsV1);
	int nComment = 0;
	if (pDir->pstrComment)
	{
		nComment = (int)strlen(pDir->pstrComment);
	}
	iExtLen = OMAP_ALIGN_8_BYTE(iExtLen + nComment + 4);

	int nLl = 0;
	for (int i = 0; i < pDir->nUnit; i++)
		nLl += pDir->punit[i].nLl;

	tagOApiObjectOptHdr* pOoh = OApiNewOptHdr(iExtLen + pDir->nUnit * sizeof(tagOApiMapDirectionsUnitV1) + nLl * sizeof(tagOApiLatLngV1));
	pOoh->idObj = idObj;
	pOoh->idParent = idParent;
	pOoh->iType = OMAP_OBJ_TYPE_DIR;
	pOoh->iVersion = OMAP_WIN_API_VERSION;
	pOoh->ret = iPosition;

	BYTE* pp = (BYTE*)(pOoh + 1);
	memcpy(pp, pDir, sizeof(tagOApiMapDirectionsV1));
	memcpy(pp + sizeof(tagOApiMapDirectionsV1), &nComment, 4);
	if (pDir->pstrComment)
		memcpy(pp + sizeof(tagOApiMapDirectionsV1) + 4, pDir->pstrComment, nComment);

	memcpy(pp + iExtLen, pDir->punit, pDir->nUnit * sizeof(tagOApiMapDirectionsUnitV1));
	iExtLen += pDir->nUnit * sizeof(tagOApiMapDirectionsUnitV1);
	tagOApiLatLngV1* pll = (tagOApiLatLngV1*)(pp + iExtLen);
	int nn = 0;
	for (int i = 0; i < pDir->nUnit; i++)
	{
		for (int j = 0; j < pDir->punit[i].nLl; j++)
		{
			pll[nn++] = pDir->punit[i].llList[j];
		}
	}
	iExtLen += nLl * sizeof(tagOApiLatLngV1);

	int r = g_omapApi.SendMessageToOmap(OMAP_API_CMD_SET_OBJ, pOoh, sizeof(tagOApiObjectOptHdr) + iExtLen, pIdResult);
	free(pOoh);
	return r;
}

int OMapApi::SetOmapObject(DWORD idObj, int iObjType, void* pObj, INT64 *pIdResult, DWORD idParent, int iPosition)
{
	if (iObjType == OMAP_OBJ_TYPE_GROUP)
		return SetOmapObject(idObj, (tagOApiObjGroupV1*)pObj, pIdResult, idParent, iPosition);
	else if (iObjType == OMAP_OBJ_TYPE_SIGN)
		return SetOmapObject(idObj, (tagOApiMapSignV1*)pObj, pIdResult, idParent, iPosition);
	else if (iObjType == OMAP_OBJ_TYPE_TRACK)
		return SetOmapObject(idObj, (tagOApiMapTrackV1*)pObj, pIdResult, idParent, iPosition);
	else if (iObjType == OMAP_OBJ_TYPE_SHAPE)
		return SetOmapObject(idObj, (tagOApiMapShapeV1*)pObj, pIdResult, idParent, iPosition);
	else if (iObjType == OMAP_OBJ_TYPE_DIR)
		return SetOmapObject(idObj, (tagOApiMapDirectionsV1*)pObj, pIdResult, idParent, iPosition);
	else
		return 0;
}

int OMapApi::SendGetShapeFillPatList()
{
	return g_omapApi.SendMessageToOmap(OMAP_API_CMD_GET_SHAPE_FILL_PAT_LIST, NULL, 0, NULL);
}


tagOApiShapeFillCadPatHdr *OMapApi::DeocdeShapeFillPatList(void *pBuf, int nBuf)
{
	if (nBuf < sizeof(tagOApiShapeFillCadPatHdr))
		return NULL;

	tagOApiShapeFillCadPatHdr *pHdrSrc = (tagOApiShapeFillCadPatHdr *)pBuf;
	tagOApiShapeFillCadPatItem *pSfcpi = (tagOApiShapeFillCadPatItem *)(pHdrSrc + 1);

	tagOApiShapeFillCadPatHdr *pHdrDst = (tagOApiShapeFillCadPatHdr *)OApiZeroMalloc(sizeof(tagOApiShapeFillCadPatHdr));
	memcpy(pHdrDst, pHdrSrc, sizeof(tagOApiShapeFillCadPatHdr));

	pHdrDst->pSfcpi = (tagOApiShapeFillCadPatItem *)OApiZeroMalloc(sizeof(tagOApiShapeFillCadPatItem)*pHdrSrc->nSfcpi);

	bool bErr = pHdrDst->pSfcpi == NULL;
	for (int i = 0; i < pHdrSrc->nSfcpi && !bErr; i++)
	{
		int iUnitLen = sizeof(tagOApiShapeFillCadPatUnit)*pSfcpi->nSfcpu;
		int iItemLen = sizeof(tagOApiShapeFillCadPatItem) + iUnitLen;
		if ((BYTE*)pSfcpi + iItemLen > (BYTE *)pBuf + nBuf)
		{
			bErr = true;
			break;
		}

		memcpy(pHdrDst->pSfcpi + i, pSfcpi, sizeof(tagOApiShapeFillCadPatItem));
		pHdrDst->pSfcpi[i].pSfcpu = (tagOApiShapeFillCadPatUnit *)OApiZeroMalloc(iUnitLen);
		if (pHdrDst->pSfcpi[i].pSfcpu == NULL)
		{
			bErr = true;
			break;
		}
		memcpy(pHdrDst->pSfcpi[i].pSfcpu, pSfcpi + 1, iUnitLen);

		pSfcpi = (tagOApiShapeFillCadPatItem *)((BYTE *)pSfcpi + iItemLen);
	}

	if (bErr)
	{
		FreeShapeFillPatList(pHdrDst, true);
		pHdrDst = NULL;
	}

	return pHdrDst;
}

void OMapApi::FreeShapeFillPatList(tagOApiShapeFillCadPatHdr *pHdr, bool bFreeMe)
{
	if (pHdr == NULL)
		return;

	for (int i = 0; i < pHdr->nSfcpi; i++)
	{
		tagOApiShapeFillCadPatItem* pSfcpi = pHdr->pSfcpi + i;
		if (pSfcpi->pSfcpu != NULL)
			free(pSfcpi->pSfcpu);
	}
	if (pHdr->pSfcpi != NULL)
		free(pHdr->pSfcpi);

	if (bFreeMe)
		free(pHdr);
}

#endif