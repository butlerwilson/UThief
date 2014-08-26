
// UThiefDlg.h : header file
//

#pragma once

#include "LOperate.h"
#include "Resource.h"

// CUThiefDlg dialog
class CUThiefDlg : public CDialogEx
{
// Construction
public:
	CUThiefDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_UTHIEF_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButtonBegin();
	afx_msg void OnBnClickedButtonBrowser();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeRichedit21();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonHide();
	afx_msg void OnBnClickedButtonStop();

private:
	LOperate *lOperate;

	bool	stopped;
	CString info;
	CString copyright;
	CString sourcePath;
	CString dstintPath;
	CString defaultPath;

	CWinThread *copyThread;

	CWnd *begin;
	CWnd *stop;
	CWnd *path;
	CWnd *showinfo;
public:
	afx_msg void OnStnClickedStaticbottom();
};

struct threadParams {
	CString srcPath;
	CString dstPath;
	CWnd *editHandle;
};
