#include "qmainwindow.h"
#include <qbytearray.h>
#include <qmessagebox.h>



OMapApiTest::OMapApiTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);     
	setWindowTitle(QString("PersonalOMapApiTest"));
	WId wid = this->winId();
	 
	g_omapApi.Init((WORD*)APP_CLASS_NAME);
	//::SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	/*WNDCLASS   wc;
	::GetClassInfo(GetModuleHandle(0), L"Qt5QWindowIcon", &wc);
	wc.lpszClassName = APP_CLASS_NAME;
	::RegisterClass(&wc);*/
	//GetModuleHandle(NULL) AfxGetInstanceHandle()
	/*::GetClassInfo(AfxGetInstanceHandle(), L"#32770", &wc);
	wc.lpszClassName = APP_CLASS_NAME;
	::RegisterClass(&wc);*/
	
}

void OMapApiTest::on_pushButton_clicked()
{
	myProcess.start("D:\\OvalMap\\omap.exe");
}

//LRESULT OMapApiTest::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
//{
//	if (message == WM_COPYDATA && wParam == OMAP_WIN_API_FLAG)
//	{
//		COPYDATASTRUCT* pcd = (COPYDATASTRUCT*)lParam;
//		int nAppId = (pcd->dwData >> 16) & 0xffff;
//		int nCmdId = pcd->dwData & 0xffff;
//
//		if (nCmdId == OMAP_WIN_CMD_GET_LATLNG)
//		{
//			tagOmapLatlng oll;
//			memcpy(&oll, pcd->lpData, sizeof(oll));
//
//			CString ss;
//			ss.Format(L"%lf,%lf", oll.lat, oll.lng);
//			//m_edResult.SetWindowText(ss);
//		}
//		else if (nCmdId == OMAP_WIN_CMD_SHOW_PIC)
//		{
//			tagOPhotoMapPic* pom = (tagOPhotoMapPic*)pcd->lpData;
//			int nPom = pcd->cbData / sizeof(tagOPhotoMapPic);
//
//			CString ss;
//			ss.Format(L"id=%lld,%d,%d,%lf,%lf", pom->idPic, nPom, pom->iAction, pom->lat, pom->lng);
//			//m_edResult.SetWindowText(ss);
//		}
//		else if (nCmdId == OMAP_WIN_CMD_LATLNG_GEOCODE)
//		{
//			tagOmapGeoDecode* pgd = (tagOmapGeoDecode*)pcd->lpData;
//
//			CString ss;
//			// ss.Format(L"经纬度：%lf,%lf，解析结果:\r\n", pgd->oll.lat / 100000.0, pgd->oll.lng / 100000.0);
//			ss.Format(L"经纬度：%lf,%lf，解析结果:\r\n", pgd->oll.lat, pgd->oll.lng);
//
//			//如果是返回GEO_DECODE_ERR_WAIT，则需要等1秒后再请求，omap程序正从服务器下载行政地区数据
//			if (pgd->nLevel == GEO_DECODE_ERR_WAIT)
//				ss.AppendFormat(L"等待数据\r\n");
//			else if (pgd->nLevel == GEO_DECODE_ERR_NO_DATA)
//				ss.AppendFormat(L"找不到对应信息\r\n");
//
//			int i;
//			for (i = 0; i < pgd->nLevel; i++)
//			{
//				ss.AppendFormat(L"%s\r\n", Utf8ToCString(pgd->strArea[i]));
//			}
//			//m_edResult.SetWindowText(ss);
//		}
//		else if (nCmdId == OMAP_WIN_CMD_TIME_TO_LATLNG)
//		{
//			tagOPhotoMapPic* pOmp = (tagOPhotoMapPic*)pcd->lpData;
//			int nOmp = pcd->cbData / sizeof(tagOPhotoMapPic);
//
//			int nCount = 0;
//			int i;
//			for (i = 0; i < nOmp; i++)
//			{
//				if (pOmp[i].lat != 0 || pOmp[i].lng != 0)
//				{
//					nCount++;
//				}
//			}
//
//			CString ss;
//			ss.Format(L"共有%d张照片获得经纬度:\r\n", nCount);
//
//			for (i = 0; i < nOmp; i++)
//			{
//				if (pOmp[i].lat != 0 || pOmp[i].lng != 0)
//				{
//					ss.AppendFormat(L"第%d张经纬度：%lf,%lf\r\n", i + 1, pOmp[i].lat, pOmp[i].lng);
//				}
//			}
//			//m_edResult.SetWindowText(ss);
//		}
//		else if (nCmdId == OMAP_WIN_CMD_CLOSE)
//		{
//			/*if (g_dlgToolBox)
//			{
//				g_dlgToolBox->DestroyWindow();
//				this->ShowWindow(SW_SHOW);
//			}*/
//		}
//		else if (nCmdId == OMAP_API_CMD_GET_OBJ_LIST)
//		{
//			if (pcd->cbData == 0)
//			{
//				//MessageBox(_T("当前奥维地图绑定用户不是VIP用户，不支持此API接口"));
//				return TRUE;
//			}
//			BYTE* pData = (BYTE*)pcd->lpData;
//			int nList = (pcd->cbData - sizeof(tagOApiObjectOptHdr)) / sizeof(tagOApiItemListV1);
//			tagOApiItemListV1* pOlv = (tagOApiItemListV1*)(pData + sizeof(tagOApiObjectOptHdr));
//			//m_lcResult.DeleteAllItems();
//			for (int i = 0; i < nList; i++)
//			{
//				CString strType;
//				CString strName;
//				if (pOlv[i].iType == OMAP_OBJ_TYPE_GROUP)
//				{
//					strType = L"文件夹";
//				}
//				else if (pOlv[i].iType == OMAP_OBJ_TYPE_SIGN)
//				{
//					strType = L"标签";
//				}
//				else if (pOlv[i].iType == OMAP_OBJ_TYPE_TRACK)
//				{
//					strType = L"轨迹";
//				}
//				else if (pOlv[i].iType == OMAP_OBJ_TYPE_SHAPE)
//				{
//					strType = L"图形";
//				}
//				else if (pOlv[i].iType == OMAP_OBJ_TYPE_DIR)
//				{
//					strType = L"路线";
//				}
//				else
//					strType = L"未知";
//				/*m_lcResult.InsertItem(i, strType);
//				m_lcResult.SetItemText(i, 1, Utf8ToCString(pOlv[i].strName));
//				m_lcResult.SetItemData(i, pOlv[i].idObj);*/
//			}
//		}
//		else if (nCmdId == OMAP_API_CMD_GET_SEL_LIST)
//		{
//			if (pcd->cbData == 0)
//			{
//				//MessageBox(_T("当前奥维地图绑定用户不是VIP用户，不支持此API接口"));
//				return TRUE;
//			}
//			BYTE* pData = (BYTE*)pcd->lpData;
//			tagOApiItemListV1* pOlv = (tagOApiItemListV1*)(pData + sizeof(tagOApiObjectOptHdr));
//			int nList = (pcd->cbData - sizeof(tagOApiObjectOptHdr)) / sizeof(tagOApiItemListV1);
//		}
//		else if (nCmdId == OMAP_API_CMD_SRH_OBJ)
//		{
//			if (pcd->cbData == 0)
//			{
//				//MessageBox(_T("当前奥维地图绑定用户不是VIP用户，不支持此API接口"));
//				return TRUE;
//			}
//			BYTE* pData = (BYTE*)pcd->lpData;
//			tagOApiItemListV1* pOlv = (tagOApiItemListV1*)(pData + sizeof(tagOApiObjectOptHdr));
//			int nList = (pcd->cbData - sizeof(tagOApiObjectOptHdr)) / sizeof(tagOApiItemListV1);
//		}
//		else if (nCmdId == OMAP_API_CMD_GET_MAP_DATA)
//		{
//			if (pcd->cbData == 0)
//			{
//				//MessageBox(_T("当前奥维地图绑定用户不是VIP用户，不支持此API接口"));
//				return TRUE;
//			}
//
//			tagOApiObjectOptHdr* pOoh = (tagOApiObjectOptHdr*)pcd->lpData;
//			tagOmapGetMap *pGet = (tagOmapGetMap*)(pOoh + 1);
//			BYTE *pDataImg = (BYTE *)(pGet + 1);
//			int nDataIng = (pcd->cbData - sizeof(tagOApiObjectOptHdr) - sizeof(tagOmapGetMap));
//			if (nDataIng <= 0)
//			{
//				qDebug()<< "Unknown Error" << " ";
//				//MessageBox(_T("未知错误"));
//				return TRUE;
//			}
//
//		}
//		else if (nCmdId == OMAP_API_CMD_GET_OBJ)
//		{
//			tagOApiObjectOptHdr* pOoh = (tagOApiObjectOptHdr*)pcd->lpData;
//			CString strInfo;
//			if (pOoh->iType == OMAP_OBJ_TYPE_GROUP)
//			{
//				tagOApiObjGroupV1* pGroup = g_omapApi.GetOmapGroupFromBuf(pOoh + 1, pcd->cbData - sizeof(tagOApiObjectOptHdr));
//				strInfo.AppendFormat(_T("name = %s\r\n"), Utf8ToCString(pGroup->strName));
//				strInfo.AppendFormat(_T("child = %d\r\n"), pGroup->nChild);
//				g_omapApi.FreeOmapObject(pGroup, OMAP_OBJ_TYPE_GROUP);
//			}
//			else if (pOoh->iType == OMAP_OBJ_TYPE_SIGN)
//			{
//				tagOApiMapSignV1* pSign = g_omapApi.GetOmapSignFromBuf(pOoh + 1, pcd->cbData - sizeof(tagOApiObjectOptHdr));
//				strInfo.AppendFormat(_T("name = %s\r\n"), Utf8ToCString(pSign->strName));
//				strInfo.AppendFormat(_T("latlng = %lf,%lf\r\n"), pSign->lat, pSign->lng);
//				g_omapApi.FreeOmapObject(pSign, OMAP_OBJ_TYPE_SIGN);
//			}
//			else if (pOoh->iType == OMAP_OBJ_TYPE_TRACK)
//			{
//				tagOApiMapTrackV1* pTrack = g_omapApi.GetOmapTrackFromBuf(pOoh + 1, pcd->cbData - sizeof(tagOApiObjectOptHdr));
//				strInfo.AppendFormat(_T("name = %s\r\n"), Utf8ToCString(pTrack->strName));
//				strInfo.AppendFormat(_T("TrackPointCount = %d\r\n"), pTrack->nMtp);
//				g_omapApi.FreeOmapObject(pTrack, OMAP_OBJ_TYPE_TRACK);
//			}
//			else if (pOoh->iType == OMAP_OBJ_TYPE_SHAPE)
//			{
//				tagOApiMapShapeV1* pShape = g_omapApi.GetOmapShapeFromBuf(pOoh + 1, pcd->cbData - sizeof(tagOApiObjectOptHdr));
//				strInfo.AppendFormat(_T("name = %s\r\n"), Utf8ToCString(pShape->strName));
//				strInfo.AppendFormat(_T("VertexCount = %d\r\n"), pShape->nMtp);
//				g_omapApi.FreeOmapObject(pShape, OMAP_OBJ_TYPE_SHAPE);
//			}
//			else if (pOoh->iType == OMAP_OBJ_TYPE_DIR)
//			{
//				tagOApiMapDirectionsV1* pDir = g_omapApi.GetOmapDirFromBuf(pOoh + 1, pcd->cbData - sizeof(tagOApiObjectOptHdr));
//				strInfo.AppendFormat(_T("name = %s\r\n"), Utf8ToCString(pDir->strName));
//				strInfo.AppendFormat(_T("nUnit = %d\r\n"), pDir->nUnit);
//				g_omapApi.FreeOmapObject(pDir, OMAP_OBJ_TYPE_DIR);
//			}
//			else
//			{
//				strInfo = L"不支持的对象";
//			}
//			//m_edResult.SetWindowText(strInfo);
//		}
//		else if (nCmdId == OMAP_API_CMD_SET_BTN)
//		{
//			if (pcd->cbData < sizeof(int))
//				return TRUE;
//
//			// 返回状态
//			int iAdd = 0;
//			memcpy(&iAdd, pcd->lpData, sizeof(int));
//		}
//		else if (nCmdId == OMAP_API_CMD_CLICK_BTN)
//		{
//			// 奥维地图用户按下附件按钮
//		}
//		else if (nCmdId == OMAP_WIN_CMD_SAVE_CFG)
//		{
//			//奥维地图用户按下保存配置按钮
//		}
//		else if (nCmdId == OMAP_API_CMD_SET_SYS_COOR_POINT)
//		{
//			if (pcd->cbData < sizeof(int))
//				return TRUE;
//			int iRet = 0;
//			memcpy(&iRet, pcd->lpData, sizeof(int));
//		}
//		else if (nCmdId == OMAP_API_CMD_GET_SYS_COOR_INFO)
//		{
//			if (pcd->cbData < sizeof(tagOApiSysCoorInfo))
//				return TRUE;
//
//			char *pBuf = (char *)pcd->lpData;
//			tagOApiSysCoorInfo osi;
//			memcpy(&osi, pBuf, sizeof(osi));
//			osi.strInfo = pBuf + sizeof(osi);
//			// AfxMessageBox(Utf8ToCString(osi.strInfo));
//		}
//		else if (nCmdId == OMAP_API_CMD_REQ_INTERFACE_VER)
//		{
//			if (pcd->cbData < sizeof(tagOApiInterfaceVer))
//				return TRUE;
//
//			tagOApiInterfaceVer *pVer = (tagOApiInterfaceVer *)pcd->lpData;
//			// 传过来的时候默认会在字符串后面加结束符0, 因此可以直接使用
//			pVer->pBuf = (char *)(pVer + 1);
//
//			CString strInfo = Utf8ToCString(pVer->pBuf);
//			strInfo.AppendFormat(_T("\r\n%d"), pVer->iBuf);
//			AfxMessageBox(strInfo);
//		}
//		else if (nCmdId == OMAP_API_CMD_SRH_OBJ_EXT)
//		{
//			if (pcd->cbData < sizeof(tagOApiObjectSrhReq))
//				return TRUE;
//			int nRes = (pcd->cbData - sizeof(tagOApiObjectSrhReq)) / sizeof(tagOApiObjectSrhRes);
//			tagOApiObjectSrhRes *pRes = (tagOApiObjectSrhRes *)((BYTE *)pcd->lpData + sizeof(tagOApiObjectSrhReq));
//		}
//		else if (nCmdId == OMAP_WIN_CMD_FOLLW_OBJ_CHG_LIST)
//		{
//			if (pcd->cbData < sizeof(tagOApiObjChageHdr))
//				return TRUE;
//			tagOApiObjChageHdr *pObjChange = (tagOApiObjChageHdr *)pcd->lpData;
//			pObjChange->pdwList = (DWORD *)(pObjChange + 1);
//		}
//		else if (nCmdId == OMAP_API_CMD_GET_SHAPE_FILL_PAT_LIST)
//		{
//			tagOApiShapeFillCadPatHdr *pHdr = g_omapApi.DeocdeShapeFillPatList(pcd->lpData, pcd->cbData);
//			g_omapApi.FreeShapeFillPatList(pHdr, true);
//		}
//	}
//
//	return WindowProc(message, wParam, lParam);
//}

void OMapApiTest::on_SetTmpSign_clicked()
{
	g_omapApi.SetOmapTmpSign(149.12345, 31.23456, false);
	g_omapApi.SetOmapTmpSign(139.12345, 26.23456, false);
	g_omapApi.SetOmapTmpSign(159.12345, 17.23456, false);
}

void OMapApiTest::on_GetLatLig_clicked()
{
	g_omapApi.SendMessageToOmap(OMAP_WIN_CMD_GET_LATLNG, NULL, 0);
}

//LRESULT QT_WIN_CALLBACK OMapApiTest::QtWndProc( UINT message, WPARAM wParam, LPARAM lParam)
//{
//	if (message == WM_COPYDATA && wParam == OMAP_WIN_API_FLAG)
//	{
//		COPYDATASTRUCT* pcd = (COPYDATASTRUCT*)lParam;
//		int nAppId = (pcd->dwData >> 16) & 0xffff;
//		int nCmdId = pcd->dwData & 0xffff;
//
//		if (nCmdId == OMAP_WIN_CMD_GET_LATLNG)
//		{
//			tagOmapLatlng oll;
//			memcpy(&oll, pcd->lpData, sizeof(oll));
//
//			CString ss;
//			ss.Format(L"%lf,%lf", oll.lat, oll.lng);
//			//m_edResult.SetWindowText(ss);
//
//		}
//	}
//	return QtWndProc( message, wParam, lParam);
//}

bool OMapApiTest::winEvent(MSG * param, long * result)
{	
	return false;
}

//LRESULT QT_WIN_CALLBACK OMapApiTest::qt_internal_proc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp)
//{
//	qDebug() << "message:" << message << endl;
//	qDebug() << "wparam:" << wp << endl;
//	if (message == WM_COPYDATA && wp == OMAP_WIN_API_FLAG)
//	{
//		COPYDATASTRUCT* pcd = (COPYDATASTRUCT*)lp;
//		int nAppId = (pcd->dwData >> 16) & 0xffff;
//		int nCmdId = pcd->dwData & 0xffff;
//
//		if (nCmdId == OMAP_WIN_CMD_GET_LATLNG)
//		{
//			tagOmapLatlng oll;
//			memcpy(&oll, pcd->lpData, sizeof(oll));
//
//			CString ss;
//			ss.Format(L"%lf,%lf", oll.lat, oll.lng);
//		}
//	}
//
//	return qt_internal_proc(hwnd,message, wp, lp);
//	//return LRESULT QT_WIN_CALLBACK();
//}

bool OMapApiTest::nativeEvent(const QByteArray &eventType, void* message, long *result)
{

	Q_UNUSED(eventType);
	MSG* param = static_cast<MSG*>(message);
	qDebug() << "message:" << param->message << endl;
	qDebug() << "wparam:" << param->wParam << endl;
	qDebug() << "lparam:" << param->lParam << endl;
	qDebug() << "result:" << result << endl;
	
	if (param->message== WM_COPYDATA || param->wParam == OMAP_WIN_API_FLAG )
	{
		COPYDATASTRUCT* pcd = (COPYDATASTRUCT*)param->lParam;
		int nAppId = (pcd->dwData >> 16) & 0xffff;
		int nCmdId = pcd->dwData & 0xffff;

		if (nCmdId == OMAP_WIN_CMD_GET_LATLNG)
		{
			tagOmapLatlng oll;
			memcpy(&oll, pcd->lpData, sizeof(oll));

			QString ss;
			ss.asprintf("%lf,%lf", oll.lat, oll.lng);

			//ss.Format(L"%lf,%lf", oll.lat, oll.lng);
			QMessageBox::information(this, QString("返回结果"), ss);
			*result = 1;
			return true;
		}
	}
	//return winEvent(param,result);
	
	return QWidget::nativeEvent(eventType, param, result);
	
}
/*

bool OMapApiTest::nativeEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
	qDebug() << "message:" << message << endl;
	qDebug() << "wparam:" << wParam << endl;
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
		}
	}
	
	return nativeEvent(message, wParam, lParam);
}*/

CString OMapApiTest::Utf8ToCString(const char* strUtf8)
{
	if (strUtf8 == NULL)
		return _T("");

	WORD *strBuf = OApiUtf8ToUtf16((char*)strUtf8, NULL, NULL);
	CString strInfo = (TCHAR*)strBuf;
	free(strBuf);

	return strInfo;
}