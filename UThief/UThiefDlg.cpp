
// UThiefDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UThief.h"
#include "UThiefDlg.h"
#include "afxdialogex.h"
#include "Dbt.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DEBUG 1

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUThiefDlg dialog



CUThiefDlg::CUThiefDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUThiefDlg::IDD, pParent)
{
	lOperate = new LOperate;

	stopped = FALSE;
	defaultPath = "C:";
	copyright = "Copyright (C) 2014 Youngcy. All rights reserved!";

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUThiefDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUThiefDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDITPATH, &CUThiefDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_RICHEDITINFO, &CUThiefDlg::OnEnChangeRichedit21)
	ON_BN_CLICKED(IDC_BUTTONEXIT, &CUThiefDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTONHIDE, &CUThiefDlg::OnBnClickedButtonHide)
	ON_BN_CLICKED(IDC_BUTTONBROWSER, &CUThiefDlg::OnBnClickedButtonBrowser)
	ON_BN_CLICKED(IDC_BUTTONBEGIN, &CUThiefDlg::OnBnClickedButtonBegin)
	ON_BN_CLICKED(IDC_BUTTONSTOP, &CUThiefDlg::OnBnClickedButtonStop)
	ON_STN_CLICKED(IDC_STATICBOTTOM, &CUThiefDlg::OnStnClickedStaticbottom)
END_MESSAGE_MAP()


// CUThiefDlg message handlers

BOOL CUThiefDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;

		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CFont font;

	begin = GetDlgItem(IDC_BUTTONBEGIN);
	stop = GetDlgItem(IDC_BUTTONSTOP);
	path = GetDlgItem(IDC_EDITPATH);
	showinfo = GetDlgItem(IDC_RICHEDITINFO);

	font.CreateFontW(0, 0, 0, 0, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
		FALSE, FALSE, FALSE, FALSE);
	path->SetWindowTextW(defaultPath);
	GetDlgItem(IDC_STATICBOTTOM)->SetFont(&font);
	GetDlgItem(IDC_STATICBOTTOM)->SetWindowTextW(copyright);

	stop->EnableWindow(FALSE);
	//GetDlgItem(IDD_UTHIEF_DIALOG);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUThiefDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUThiefDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUThiefDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

char FirstDriveFromMask(DWORD unitmask);

LRESULT CUThiefDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	CString driverId;

	lOperate->checkDevice(message, wParam, lParam);
	driverId = lOperate->getDevice();
	sourcePath = driverId;
	if (!sourcePath.IsEmpty())
	sourcePath.Append(_T(":\\"));

	return CDialogEx::DefWindowProc(message, wParam, lParam);
}


void CUThiefDlg::OnBnClickedButtonBegin()
{
	CFileFind finder;

	if (sourcePath.IsEmpty()) {
		MessageBeep(1);
		MessageBox(_T("No Flash Device!"));
		return;
	}

	if (!finder.FindFile(dstintPath))
	{
		dstintPath = defaultPath;
		GetDlgItem(IDC_EDITPATH)->SetWindowTextW(defaultPath + _T("(Path not found, default path!)"));
	}
	begin->EnableWindow(FALSE);
	MessageBeep(1);
	stop->EnableWindow(TRUE);
	if (stopped) {
		copyThread->ResumeThread();
		showinfo->GetWindowTextW(info);
		info += "Thread recovery ......\r\n";
		showinfo->SetWindowTextW(info);
		stopped = FALSE;		//sign of no thread running
		return;
	}

	CString str = CTime::GetCurrentTime().Format("%Y%m%d%H%m");
	dstintPath.Append(_T("\\") + str);

	threadParams *param = new threadParams;
	param->editHandle = showinfo;
	param->srcPath = sourcePath; param->dstPath = dstintPath;
	copyThread = AfxBeginThread((AFX_THREADPROC)LOperate::copyFileTo, (LPVOID)param);

	stopped = FALSE;		//sign of no thread running
	DWORD res = WaitForSingleObject(copyThread, INFINITE);
	if (res == WAIT_OBJECT_0) {
		showinfo->GetWindowTextW(info);
		info += "Copy completed!";
		showinfo->SetWindowTextW(info);
	} else {
		showinfo->GetWindowTextW(info);
		info += "Copying exceptional terminate!";
		showinfo->SetWindowTextW(info);
	}
}

void CUThiefDlg::OnBnClickedButtonBrowser()
{
	// TODO: Add your control notification handler code here

	BROWSEINFO broInfo = { 0 };
	TCHAR       szDisName[MAX_PATH] = { 0 };

	broInfo.hwndOwner = this->m_hWnd;
	broInfo.pidlRoot = NULL;
	broInfo.pszDisplayName = szDisName;
	broInfo.lpszTitle = _T("Chose the directory to store info:");
	broInfo.lpfn = NULL;
	broInfo.lParam = NULL;
	broInfo.iImage = IDR_MAINFRAME;
	broInfo.ulFlags = 0x0040 | BIF_EDITBOX;

	LPITEMIDLIST pIDList = SHBrowseForFolder(&broInfo);
	if (pIDList != NULL)
	{
		memset(szDisName, 0, sizeof(szDisName));
		SHGetPathFromIDList(pIDList, szDisName);
		dstintPath = szDisName;
		if (dstintPath.IsEmpty()) {
			TRACE("%s", "No info.");
			dstintPath = defaultPath;
		}
		path->SetWindowTextW(dstintPath);
	}
}

void CUThiefDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	path->GetWindowTextW(dstintPath);
}

void CUThiefDlg::OnEnChangeRichedit21()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	showinfo->ShowScrollBar(SB_VERT, TRUE);
}

void CUThiefDlg::OnBnClickedButtonHide()
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_HIDE);
}


void CUThiefDlg::OnBnClickedButtonExit()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

void CUThiefDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	CString info;

	begin->EnableWindow(TRUE);
	stop->EnableWindow(FALSE);
	if (!stopped) {
		stopped = TRUE;
		copyThread->SuspendThread();
		showinfo->GetWindowTextW(info);
		info += "Copying Paused!......\r\n";
		showinfo->SetWindowTextW(info);

	}
	else {
		MessageBeep(1);
		showinfo->GetWindowTextW(info);
		info += "Copy has completed ......\r\n";
		showinfo->SetWindowTextW(info);
	}
}


void CUThiefDlg::OnStnClickedStaticbottom()
{
	// TODO: Add your control notification handler code here
}
