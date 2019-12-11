#include "pch.h"
#include "framework.h"
#include "GameKeyboardConnector.h"
#include "GameKeyboardConnectorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hTarget = NULL;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CGameKeyboardConnectorDlg::CGameKeyboardConnectorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAMEKEYBOARDCONNECTOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGameKeyboardConnectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameKeyboardConnectorDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_STATIC_ICON_FINDER_TOOL, &CGameKeyboardConnectorDlg::OnStnClickedStaticIconFinderTool)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CGameKeyboardConnectorDlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()

BOOL CGameKeyboardConnectorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	HINSTANCE hDll;
	typedef bool (*Fun1)();
	hDll = LoadLibrary(_T("KeyHook.dll"));
	if (NULL == hDll) {
		AfxMessageBox(_T("unload"));
	}

	SetMainWind(this->m_hWnd);
	SetGetWindowHwndKey(VK_HOME);
	EnableKeyboardCapture();

	this->OnLoadResouse();
	((CStatic*)GetDlgItem(IDC_STATIC_ICON_FINDER_TOOL))->SetBitmap(g_hBitmapFinderToolFilled);
#ifdef _DEBUG
	CreateResponseDlg();
#endif
	return TRUE;
}

void CGameKeyboardConnectorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGameKeyboardConnectorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGameKeyboardConnectorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CGameKeyboardConnectorDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_SPACE:
		{
		}
		break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CGameKeyboardConnectorDlg::OnDestroy()
{
	::DeleteObject(this->g_hCursorSearchWindow);
	::DeleteObject(this->g_hBitmapFinderToolFilled);
	::DeleteObject(this->g_hBitmapFinderToolEmpty);
}

void CGameKeyboardConnectorDlg::OnStnClickedStaticIconFinderTool()
{
	g_bStartSearchWindow = true;
	((CStatic*)GetDlgItem(IDC_STATIC_ICON_FINDER_TOOL))->SetBitmap(g_hBitmapFinderToolEmpty);
	g_hCursorPrevious = SetCursor(g_hCursorSearchWindow);
	SetCapture();
}


void CGameKeyboardConnectorDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	POINT		screenpoint;
	HWND		hwndFoundWindow = NULL;
	CString		strTemp;
	long		lRet = 0;

	if (!g_bStartSearchWindow)
	{
		CDialogEx::OnMouseMove(nFlags, point);
		return;
	}
	
	g_hCursorPrevious = SetCursor(g_hCursorSearchWindow);
	// Must use GetCursorPos() instead of calculating from "lParam".
	GetCursorPos(&screenpoint);

	// Display global positioning in the dialog box.
	strTemp.Format(_T("%d"), screenpoint.x);
	SetDlgItemText(IDC_STATIC_X_POS, strTemp);

	strTemp.Format(_T("%d"), screenpoint.y);
	SetDlgItemText(IDC_STATIC_Y_POS, strTemp);

	// Determine the window that lies underneath the mouse cursor.
	hwndFoundWindow = WindowFromPoint(screenpoint)->m_hWnd;
	DisplayInfoOnFoundWindow(hwndFoundWindow);
	if (CheckWindowValidity(hwndFoundWindow))
	{
		// Check first for validity.
		HighlightFoundWindow(hwndFoundWindow);
	}
	g_hTarget = hwndFoundWindow;

	CDialogEx::OnMouseMove(nFlags, point);
}


void CGameKeyboardConnectorDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	g_bStartSearchWindow = false;
	SetCursor(g_hCursorPrevious);
	((CStatic*)GetDlgItem(IDC_STATIC_ICON_FINDER_TOOL))->SetBitmap(g_hBitmapFinderToolFilled);
	ReleaseCapture();

	/*g_hTarget = WindowFromPoint(point)->m_hWnd;

	if (!::GetParent(g_hTarget) || GetDesktopWindow()->m_hWnd == ::GetParent(g_hTarget) ||
		!(::GetWindowLong(g_hTarget, GWL_STYLE) & WS_CHILDWINDOW))
	{
	}
	else
	{
		g_hTarget = ::GetParent(g_hTarget);
	}

	while (TRUE) {
		HWND hWndChild = RealChildWindowFromPoint(g_hTarget, point);


		if (hWndChild && (hWndChild != g_hTarget))
			g_hTarget = hWndChild;
		else
			break;
	}*/


	//DisplayInfoOnFoundWindow(g_hTarget);
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CGameKeyboardConnectorDlg::OnLoadResouse(void)
{
	g_hRectanglePen = CreatePen(PS_SOLID, 3, RGB(256, 0, 0));
	g_hCursorSearchWindow = LoadCursor(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR_SEARCH_WINDOW));
	g_hBitmapFinderToolFilled = LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_FINDER_FILLED));
	g_hBitmapFinderToolEmpty = LoadBitmap(::AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_FINDER_EMPTY));
}

void CGameKeyboardConnectorDlg::CreateResponseDlg(void)
{
	CreateThread(NULL, 0, ThreadRespnseDlg, this, 0, NULL);
}

bool CGameKeyboardConnectorDlg::CheckWindowValidity(HWND hWnd)
{
	// The window must not be NULL.
	if (hWnd == NULL)
	{
		return false;
	}

	// It must also be a valid window as far as the OS is concerned.
	if (IsWindow(hWnd) == FALSE)
	{
		return false;
	}

	return true;
}

void CGameKeyboardConnectorDlg::HighlightFoundWindow(HWND hWnd)
{
	HDC		hWindowDC;  // The DC of the found window.
	HGDIOBJ	hPrevPen = NULL;   // Handle of the existing pen in the DC of the found window.
	HGDIOBJ	hPrevBrush = NULL; // Handle of the existing brush in the DC of the found window.
	RECT		rect;              // Rectangle area of the found window.

	// Get the screen coordinates of the rectangle of the found window.
	::GetWindowRect(hWnd, &rect);

	// Get the window DC of the found window.
	hWindowDC = ::GetWindowDC(hWnd);

	if (hWindowDC)
	{
		// Select our created pen into the DC and backup the previous pen.
		hPrevPen = ::SelectObject(hWindowDC, g_hRectanglePen);

		// Select a transparent brush into the DC and backup the previous brush.
		hPrevBrush = ::SelectObject(hWindowDC, GetStockObject(HOLLOW_BRUSH));

		// Draw a rectangle in the DC covering the entire window area of the found window.
		::Rectangle(hWindowDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top);

		// Reinsert the previous pen and brush into the found window's DC.
		::SelectObject(hWindowDC, hPrevPen);

		::SelectObject(hWindowDC, hPrevBrush);

		// Finally release the DC.
		::ReleaseDC(hWnd, hWindowDC);
	}
}

void CGameKeyboardConnectorDlg::DisplayInfoOnFoundWindow(HWND hWnd)
{
	RECT		rect;              // Rectangle area of the found window.
	CString		szText;
	WCHAR		szClassName[1000];
	long		lRet = 0;

	// Get the screen coordinates of the rectangle of the found window.
	::GetWindowRect(hWnd, &rect);

	// Get the class name of the found window.
	::GetClassNameW(hWnd, szClassName, sizeof(szClassName) - 1);

	// Display some information on the found window.
	szText.Format
	(
		_T("Window Handle == 0x%08X.\r\nClass Name : %s.\r\nRECT.left == %d.\r\nRECT.top == %d.\r\nRECT.right == %d.\r\nRECT.bottom == %d.\r\n"),
		hWnd,
		szClassName,
		rect.left,
		rect.top,
		rect.right,
		rect.bottom
	);

	SetDlgItemText(IDC_EDIT_STATUS, szText);
}

DWORD __stdcall ThreadRespnseDlg(LPVOID lpParamter)
{
	WinExec("KeyBoardResponse.exe", SW_SHOW);  // 打开记事本  
	return 0;
}


void CGameKeyboardConnectorDlg::OnBnClickedButtonSend()
{
	WPARAM wParam = 50;
	LPARAM lParam = 1;
	CWnd* QCWnd = CWnd::FromHandle(g_hTarget);
	if (QCWnd->GetSafeHwnd())
	{
		//QCWnd->ShowWindow(SW_NORMAL);
		QCWnd->SetForegroundWindow();
		keybd_event(wParam, 0, 0, 0);
		Sleep(100);
		keybd_event(wParam, 0, KEYEVENTF_KEYUP, 0);
	}

	::SendMessage(g_hTarget, WM_KICKIDLE, wParam, lParam);
	::SendMessage(g_hTarget, WM_KEYUP, wParam, lParam);
}
