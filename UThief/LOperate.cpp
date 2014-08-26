#include "stdafx.h"
#include "LOperate.h"
#include "Dbt.h"

#include "UThiefDlg.h"

LOperate::LOperate()
{
}

char LOperate::firstDriveFromMask(DWORD unitmask)
{
	int i = 0;

	for (i; i < 26; i++) {
		if (unitmask & 0x1)
			break;
		unitmask = unitmask >> 1;
	}

	return (i + 'A');
}



int LOperate::checkDevice(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DEVICECHANGE:
		PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
		switch (wParam) {
		case WM_DEVICECHANGE: break;
		case DBT_DEVICEARRIVAL:
			if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
			{
				CString decDriver;
				PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
				decDriver = firstDriveFromMask(lpdbv->dbcv_unitmask);
				device = decDriver.GetBuffer(0);
				switch (lpdbv->dbcv_flags) {
				case 0: {               //UÅÌ
							TRACE1("¼ì²âµ½UÅÌ:[%s]²åÈë!\n", device);
							break;
				}
				case DBTF_MEDIA:    //¹âÅÌ
					TRACE1("¼ì²âµ½¹âÅÌ:[%c]²åÈë!\n", device);
					break;
				}
			}
			break;
		case DBT_DEVICEREMOVECOMPLETE: //DBT_DEVICEREMOVECOMPLETE,Éè±¸Ð¶ÔØ»òÕß°Î³ö
			if (lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)//Âß¼­¾í
			{
				PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
				switch (lpdbv->dbcv_flags) {
				case 0: {                //UÅÌ
							CString decDriver;
							decDriver = firstDriveFromMask(lpdbv->dbcv_unitmask);
							TRACE1("¼ì²âµ½UÅÌ:[%s]°Î³ö!\n", decDriver.GetBuffer(0));
				}
				case DBTF_MEDIA:    //¹âÅÌ
					break;
				}
			}
			break;
		}
		break;
	}

	return 0;
}

static CString info;
static CCriticalSection cSection;

/*
UINT LOperate::copyFileTo(CString srcPath, CString dstPath, CWnd *editHandle)
{
	CFileFind finder;
	CreateDirectory(dstPath, NULL);
	srcPath.Append(_T("/*.*"));

	//path.Format("%s/*.*", source);
	bool bWorking = finder.FindFile(srcPath);
	while (bWorking){
		bWorking = finder.FindNextFile();
		CString filename = finder.GetFileName();
		if (finder.IsDirectory() && !finder.IsDots()){
			CString dirPath = dstPath + "/" + filename;
			copyFileTo(finder.GetFilePath(), dirPath, editHandle);
		}
		else{
			CString srcFile = finder.GetFilePath();
			CString filePath = dstPath + "/" + filename;

			CopyFile(srcFile, filePath, FALSE);
			cSection.Lock();
			editHandle->GetWindowTextW(info);
			cSection.Unlock();
			cSection.Lock();
			info += srcFile; info += "\r\n";
			editHandle->SetWindowTextW(info);
			cSection.Unlock();
		}
	}

	return 0;
}
*/

UINT LOperate::copyFileTo(LPARAM lParam)
{
	CFileFind finder;
	threadParams * param = (threadParams *)lParam;
	CString srcPath = param->srcPath;
	CString dstPath = param->dstPath;
	CWnd *editHandle = param->editHandle;

	CreateDirectory(dstPath, NULL);
	srcPath.Append(_T("/*.*"));

	BOOL bWorking = finder.FindFile(srcPath);
	while (bWorking){
		bWorking = finder.FindNextFile();
		CString filename = finder.GetFileName();
		if (finder.IsDirectory() && !finder.IsDots()){
			CString dirPath = dstPath + "/" + filename;
			param->srcPath = finder.GetFilePath();
			param->dstPath = dirPath;
			copyFileTo((LPARAM)param);
		}
		else if (!finder.IsDots()) {
			CString srcFile = finder.GetFilePath();
			CString filePath = dstPath + "/" + filename;

			CopyFile(srcFile, filePath, FALSE);
			editHandle->GetWindowTextW(info);
			info += srcFile; info += "\r\n";
			editHandle->SetWindowTextW(info);
		}
	}

	return 0;
}

CString LOperate::getDevice() const
{
	return device;
}

LOperate::~LOperate()
{
}
