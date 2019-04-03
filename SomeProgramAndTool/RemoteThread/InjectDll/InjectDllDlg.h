// InjectDllDlg.h : header file
//

#if !defined(AFX_INJECTDLLDLG_H__6B1D0408_168A_4409_AA6F_60733895FB55__INCLUDED_)
#define AFX_INJECTDLLDLG_H__6B1D0408_168A_4409_AA6F_60733895FB55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CInjectDllDlg dialog

#include <tlhelp32.h>
 
class CInjectDllDlg : public CDialog
{
// Construction
public:
	CInjectDllDlg(CWnd* pParent = NULL);	// standard constructor
	
	DWORD GetProcId(CString PName);
	void UnInjectDll(DWORD dwPid, char *szDllName);
	void InjectDll(DWORD dwPid, char *szDllName);
	int EnableDebugPrivilege(const LPTSTR name);
// Dialog Data
	//{{AFX_DATA(CInjectDllDlg)
	enum { IDD = IDD_INJECTDLL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInjectDllDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInjectDllDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInject();
	afx_msg void OnUninject();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INJECTDLLDLG_H__6B1D0408_168A_4409_AA6F_60733895FB55__INCLUDED_)
