// 管道柔性计算器Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "管道柔性计算器.h"
#include "管道柔性计算器Dlg.h"
#include <math.h>
#include <TCHAR.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static TCHAR THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	m_do = 457;
	m_ta = 20;
	m_td = 540;
	m_la = 12.0;
	m_height = 0.8;
	m_ls = 23.0;
	m_ce = 14.58;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Text(pDX, IDC_EDT_DO, m_do);
	DDX_Text(pDX, IDC_EDT_TA, m_ta);
	DDX_Text(pDX, IDC_EDT_TD, m_td);
	DDX_Text(pDX, IDC_EDT_LA, m_la);
	DDX_Text(pDX, IDC_EDT_HEIGHT, m_height);
	DDX_Text(pDX, IDC_EDT_LS, m_ls);
	DDX_Text(pDX, IDC_EDT_CE, m_ce);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHK_AT, OnChkAt)
	ON_BN_CLICKED(IDC_BTN_CALCULATE, OnBtnCalculate)
	ON_BN_CLICKED(IDC_CHK_CE, OnChkCe)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetWindowPos(&wndTopMost , 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	SetDlgItemText(IDC_STT_INFO, _T("免责声明:\r\n本软件仅供交流学习，请谨慎使用!!!\r\n"));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyDlg::OnChkAt() 
{
	CButton *pCheckBox = (CButton *)GetDlgItem(IDC_CHK_AT);
	pCheckBox->GetCheck() ? GetDlgItem(IDC_EDT_TA)->EnableWindow() : GetDlgItem(IDC_EDT_TA)->EnableWindow(FALSE);
	
}


///////////////////////////////////////////////////////////////
//	Function Name : ReleaseResource
//	Function      : 释放资源
//	Author        : RyeCatcher
//	Time          : 2012-11-12
//	Return Value  : BOOL
//	Parameter     : UINT nRsrcID,				//资源ID		IDR_EXE1
//				 	const TCHAR * szRsrcType,	//资源类型     	"EXE"
//				 	const TCHAR * szFilePath	//释放路径		"c:\1.exe"
///////////////////////////////////////////////////////////////
BOOL ReleaseResource(UINT nRsrcID,  const TCHAR *szRsrcType,  const TCHAR *szFilePath, 
					 const BOOL bOverWritten = FALSE)
{
	
	CFileFind finder; 
	if (finder.FindFile(szFilePath) && !bOverWritten) return true;
	
	HRSRC hRsrc = ::FindResource(NULL, MAKEINTRESOURCE(nRsrcID), szRsrcType);	
	if(hRsrc)
	{   
		DWORD dwSize = ::SizeofResource(NULL, hRsrc);
		HGLOBAL  hGlobal = ::LoadResource(NULL, hRsrc);
		if(hGlobal)
		{   
			BYTE *MemPtr = (BYTE *)LockResource(hGlobal); 
			CFile file;
			if(file.Open(szFilePath, CFile::modeCreate|CFile::modeWrite))
			{
				file.Write(MemPtr, dwSize);
				file.Close();
			}
			::UnlockResource(hGlobal);
		}
		::FreeResource(hRsrc);
		return TRUE;
	}
	
	return FALSE;
}

// 复制到剪切板
void CMyDlg::Copy2Clipboard(const CString strContent)
{
	if(::OpenClipboard(m_hWnd) &&::EmptyClipboard())
	{
		HGLOBAL clipbuffer;
		TCHAR * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, strContent.GetLength()+1);
		buffer = (TCHAR*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(strContent));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
	}
}

// 计算线性膨胀量
double CMyDlg::foo(const double length)
{
	return m_ce * length * (m_td - m_ta) / 1000;
}


void CMyDlg::OnBtnCalculate() 
{
	UpdateData(TRUE);

	CString strLE, strResult;
	// 总位移量 = 各向位移量平方和再开根号
	double fle = sqrt(foo(m_ls)*foo(m_ls) + foo(m_la)*foo(m_la) + foo(m_height)*foo(m_height));

	// 计算值 = 总位移量 * 管道外径 / (管道总长-管道直线距离)^2
	double fResult = m_do * fle / (2*m_la+2*m_height) /  (2*m_la+2*m_height);

	strLE.Format(_T("%3.3f"), fle);
	strResult.Format(_T("%3.3f"), fResult);
	SetDlgItemText(IDC_EDT_LE, strLE);
	SetDlgItemText(IDC_EDT_RESULT, strResult);
//	UpdateData(FALSE);

	if (208.3<=fResult)
		AfxMessageBox(_T("管系柔性不合格!"));

	CString strContent;
	GetDlgItemText(IDC_EDT_LE, strContent);
	Copy2Clipboard(strContent);
}

void CMyDlg::OnChkCe() 
{
	CButton *pCheckBox = (CButton *)GetDlgItem(IDC_CHK_CE);
	pCheckBox->GetCheck() ? GetDlgItem(IDC_EDT_CE)->EnableWindow() : GetDlgItem(IDC_EDT_CE)->EnableWindow(FALSE);
	
}

void CMyDlg::OnBtnClear() 
{
	// 重新初始化所有变量
	m_do = 0;
	m_ta = 0;
	m_td = 0;
	m_la = 0;
	m_height = 0;
	m_ls = 0;
	m_ce = 0;

	UpdateData(FALSE);

	GetDlgItem(IDC_EDT_CE)->SetFocus();
	GetDlgItem(IDC_EDT_CE)->SendMessage(EM_SETSEL, 0, -1);
}

void CMyDlg::OnBtnSearch() 
{
	CString strFilePath;
	TCHAR vcTempPath[MAX_PATH] = {0};

	GetTempPath(MAX_PATH, vcTempPath);
	strFilePath.Format(_T("%s%s"), vcTempPath, _T("GB 50764-2012.jpg"));

	ReleaseResource(IDR_JPG, _T("JPG"), strFilePath, TRUE);
	ShellExecute(NULL, _T("open"), strFilePath, NULL, NULL, SW_SHOW);

	GetDlgItem(IDC_EDT_CE)->SetFocus();
	
}

BOOL CMyDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (WM_KEYDOWN == pMsg->message && VK_ESCAPE == pMsg->wParam)
	{
		TCHAR vcClassName[MAX_PATH] = {0};
		GetClassName(pMsg->hwnd, vcClassName, MAX_PATH);
		// 比较控件类名
		if (0 == _tcsicmp(vcClassName, _T("Edit")))	
		{
			SetDlgItemInt(GetFocus()->GetDlgCtrlID(), 0);
			GetFocus()->SendMessage(EM_SETSEL, 0, -1);
		}
		return TRUE;
	}
	if (WM_KEYDOWN == pMsg->message && VK_UP == pMsg->wParam)
	{
		 PrevDlgCtrl();
		 return TRUE;
	}
	if (WM_KEYDOWN == pMsg->message && VK_DOWN == pMsg->wParam)
	{
		NextDlgCtrl();
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH CMyDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkMode(TRANSPARENT );
		pDC->SetTextColor(RGB(0, 0, 255) );
		return hbr;
	}
	
	if (IDC_EDT_RESULT == pWnd->GetDlgCtrlID() || IDC_EDT_LE == pWnd->GetDlgCtrlID())
	{
		pDC->SetBkMode(TRANSPARENT );
		pDC->SetTextColor(RGB(255, 0, 0) );
		return hbr;
	}

	if (IDC_STT_INFO == pWnd->GetDlgCtrlID())
	{
	//	pDC->SetBkColor(RGB(0, 0, 0) );
		pDC->SetTextColor(RGB(125, 0, 125) );
		return hbr;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
