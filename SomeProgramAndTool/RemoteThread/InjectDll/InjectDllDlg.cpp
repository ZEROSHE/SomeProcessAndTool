// InjectDllDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InjectDll.h"
#include "InjectDllDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInjectDllDlg dialog

CInjectDllDlg::CInjectDllDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInjectDllDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInjectDllDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInjectDllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInjectDllDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInjectDllDlg, CDialog)
	//{{AFX_MSG_MAP(CInjectDllDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnInject)
	ON_BN_CLICKED(IDC_BUTTON2, OnUninject)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInjectDllDlg message handlers

BOOL CInjectDllDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInjectDllDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInjectDllDlg::OnPaint() 
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
HCURSOR CInjectDllDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInjectDllDlg::OnInject() 
{
	 char szDllName[MAX_PATH] = { 0 };
     char szProcessName[MAXBYTE] = { 0 };
     DWORD dwPid = 0;
	// TODO: Add your control notification handler code here
	 GetDlgItemText(IDC_EDIT_DLLFILE, szDllName, MAX_PATH);//Dll·��������
     GetDlgItemText(IDC_EDIT_PROCESSNAME, szProcessName, MAXBYTE);//������ 

	 dwPid = GetProcId(szProcessName); //����ID 
	 EnableDebugPrivilege(szDllName);

	 InjectDll(dwPid, szDllName);
}


void CInjectDllDlg::OnUninject() 
{
    // TODO: Add your control notification handler code here
    char szDllName[MAX_PATH] = { 0 };
    char szProcessName[MAXBYTE] = { 0 };
    DWORD dwPid = 0;
    
    GetDlgItemText(IDC_EDIT_DLLFILE, szDllName, MAX_PATH);
    GetDlgItemText(IDC_EDIT_PROCESSNAME, szProcessName, MAXBYTE);
    
    // �ɽ��������PID
    dwPid = GetProcId(szProcessName);
    // ע��szDllName��dwPid
    UnInjectDll(dwPid, szDllName);
}

void CInjectDllDlg::UnInjectDll(DWORD dwPid, char *szDllName)
{
    if ( dwPid == 0 || lstrlen(szDllName) == 0 )
    {
        return ;
    }
    HANDLE hSnap = CreateToolhelp32Snapshot(
                            TH32CS_SNAPMODULE, 
                            dwPid);
    MODULEENTRY32 me32;
    me32.dwSize = sizeof(me32);
    // ����ƥ��Ľ�������
    BOOL bRet = Module32First(hSnap, &me32);
    while ( bRet )
    {
        if ( lstrcmp(strupr(me32.szExePath), 
                     strupr(szDllName)) == 0 )
        {
			OutputDebugString("Find Modual");
            break;
        }
		OutputDebugString("path:");
		OutputDebugString(me32.szExePath);
        bRet = Module32Next(hSnap, &me32);
    }
    CloseHandle(hSnap);
    char *pFunName = "FreeLibrary";
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 
                                  FALSE, dwPid);
    if ( hProcess == NULL )
    {
        return ;
    }
    FARPROC pFunAddr = GetProcAddress(GetModuleHandle("kernel32.dll"),
                                      pFunName);
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, 
                                        (LPTHREAD_START_ROUTINE)pFunAddr,
                                        me32.hModule, 0, NULL);
//    WaitForSingleObject(hThread, INFINITE);
//    CloseHandle(hThread);
//    CloseHandle(hProcess);
}

void CInjectDllDlg::InjectDll(DWORD dwPid, char *szDllName)
{
    if ( dwPid == 0 || lstrlen(szDllName) == 0 )
    {
        return ;
    }

    char *pFunName = "LoadLibraryA";
    // ��Ŀ�����
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 
                                  FALSE, dwPid);
    if ( hProcess == NULL )
    {
        return ;
    }
    // ������ע��DLL�ļ�����·���ĳ���
    int nDllLen = lstrlen(szDllName) + sizeof(char);
    // ��Ŀ���������һ�鳤��ΪnDllLen��С���ڴ�ռ�
    PVOID pDllAddr = VirtualAllocEx(hProcess,
                                    NULL, nDllLen,
                                    MEM_COMMIT,
                                    PAGE_READWRITE);
    if ( pDllAddr == NULL )
    {
        CloseHandle(hProcess);
        return ;
    }
    DWORD dwWriteNum = 0;
    // ����ע��DLL�ļ�������·��д����Ŀ�����������Ŀռ���
    WriteProcessMemory(hProcess, pDllAddr, szDllName, 
                       nDllLen, &dwWriteNum);
    // ���LoadLibraryA()�����ĵ�ַ
    FARPROC pFunAddr = GetProcAddress(GetModuleHandle("kernel32.dll"),
                                      pFunName);
    // ����Զ���߳�
    HANDLE hThread = CreateRemoteThread(hProcess,
                         NULL, 0,
                         (LPTHREAD_START_ROUTINE)pFunAddr,
                         pDllAddr, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    CloseHandle(hProcess);
}



DWORD CInjectDllDlg::GetProcId(CString PName) 
{ 
	//��ȡ��ǰ���̿��� 
	HANDLE snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0 ); 
	//��ѯ���� 
	PROCESSENTRY32 processInfo; 
	CString strProcessName = ""; 
	DWORD nProcessID = 0; 
	int nProcessTerminate = 0; 
	//������Ҫ��������޷���ȡ��������Ϣ
	processInfo.dwSize = sizeof( PROCESSENTRY32 ); 
	//��ȡ��һ������ 
	BOOL status = Process32First( snapShot, &processInfo );
	while( status ) 
	{
		//��ȡ�������� 
		strProcessName = processInfo.szExeFile; 
		//��ѯ�Ƚ��Ƿ�ѡ�еĽ���
		if( strProcessName.CompareNoCase( PName ) == 0 )
		{ 
			//��ȡ����ID
			nProcessID = processInfo.th32ProcessID;
			break;
		} 
		//��ȡ��һ������ 
		status = Process32Next( snapShot, &processInfo ); 
	} 
	return nProcessID; 
}

void CInjectDllDlg::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
	// TODO: Add your message handler code here and/or call default
	char *lpszFileName=new char[512],cFileCount[10];
	int nFileCount,i;
	nFileCount=::DragQueryFile(hDropInfo,0xFFFFFFFF,NULL,512);
	::AfxMessageBox(itoa(nFileCount,cFileCount,10));
	for (i=0;i<nFileCount;i++)
	{
		UINT nChars=::DragQueryFile (hDropInfo,i,&lpszFileName[0],512);
		CString str( &lpszFileName[0],nChars);
		//m_list.AddString(str);
	//	GetDlgItemTextItem()
	}
	::DragFinish(hDropInfo);
	i=0;
	delete []lpszFileName;
//	CDialog::OnDropFiles(hDropInfo);
}



	//��������Ȩ��
int CInjectDllDlg::EnableDebugPrivilege(const LPTSTR name)
{

	HANDLE TokenHandle = NULL;
	TOKEN_PRIVILEGES TokenPrivilege;
	LUID uID;

	//��Ȩ������
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &TokenHandle))  
	{
		return FALSE;
	}

	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &uID))
	{

		CloseHandle(TokenHandle);
		TokenHandle = INVALID_HANDLE_VALUE;
		return FALSE;
	}

	TokenPrivilege.PrivilegeCount = 1;
	TokenPrivilege.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	TokenPrivilege.Privileges[0].Luid = uID;

	//���������ǽ��е���Ȩ��
	if (!AdjustTokenPrivileges(TokenHandle, FALSE, &TokenPrivilege, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
	{
		CloseHandle(TokenHandle);
		TokenHandle = INVALID_HANDLE_VALUE;
		return  FALSE;
	}

	CloseHandle(TokenHandle);
	TokenHandle = INVALID_HANDLE_VALUE;
	OutputDebugString("SE_DEBUG_NAME Successs");
	return TRUE;
}