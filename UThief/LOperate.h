#pragma once
class LOperate
{
private:
	CString device;
	static CWnd *editHandle;

public:
	LOperate();
	char firstDriveFromMask(DWORD unitmask);
	int checkDevice(UINT message, WPARAM wParam, LPARAM lParam);
	static UINT LOperate::copyFileTo(LPARAM lParam);
//	static UINT copyFileTo(CString srcPath, CString dstPath, CWnd *editHandle);
	CString getDevice() const;

	~LOperate();
};

