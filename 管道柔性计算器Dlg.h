// 管道柔性计算器Dlg.h : header file
//

#if !defined(AFX_DLG_H__C9A4B354_45D8_49E7_A221_0E007BB08A57__INCLUDED_)
#define AFX_DLG_H__C9A4B354_45D8_49E7_A221_0E007BB08A57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

class CMyDlg : public CDialog
{
// Construction
public:
	CMyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	double	m_do;
	double	m_ta;
	double	m_td;
	double	m_le;
	double	m_la;
	double	m_height;
	double	m_ls;
	double	m_result;
	double	m_ce;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChkAt();
	afx_msg void OnBtnCalculate();
	afx_msg void OnChkCe();
	afx_msg void OnBtnClear();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnSearch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	float foo(const float length);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__C9A4B354_45D8_49E7_A221_0E007BB08A57__INCLUDED_)
