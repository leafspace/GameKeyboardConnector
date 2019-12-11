
// KeyBoardResponseDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "KeyBoardResponse.h"
#include "KeyBoardResponseDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CKeyBoardResponseDlg 对话框



CKeyBoardResponseDlg::CKeyBoardResponseDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_KEYBOARDRESPONSE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyBoardResponseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MESSAGE_RESPONSE, m_MessagEditControl);
}

BEGIN_MESSAGE_MAP(CKeyBoardResponseDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CKeyBoardResponseDlg 消息处理程序

BOOL CKeyBoardResponseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CKeyBoardResponseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CKeyBoardResponseDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CKeyBoardResponseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CKeyBoardResponseDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		CString strTemp;
		if (pMsg->wParam >= 'A' && pMsg->wParam <= 'Z' ||
			pMsg->wParam >= '0' && pMsg->wParam <= '9')
		{
			strTemp.Format(_T("Response %c\r\n"), (char)(pMsg->wParam));
		}
		else if (pMsg->wParam >= VK_NUMPAD0 && pMsg->wParam <= VK_NUMPAD9)
		{
			strTemp.Format(_T("Response %c\r\n"), (char)(pMsg->wParam - VK_NUMPAD0 + '0'));
		}
		else if (pMsg->wParam >= VK_F1 && pMsg->wParam <= VK_F24)
		{
			int nKeyNum = pMsg->wParam - VK_F1 + 1;
			strTemp.Format(_T("Response F%d\r\n"), nKeyNum);
		}
		else if (pMsg->wParam == VK_HOME || pMsg->wParam == VK_END)
		{
			switch (pMsg->wParam)
			{
			case VK_HOME:
				strTemp.Format(_T("Response HOME\r\n"));
				break;
			case VK_END:
				strTemp.Format(_T("Response END\r\n"));
				break;
			default:
				break;
			}
		}
		else if (pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN ||
			pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT)
		{
			switch (pMsg->wParam)
			{
			case VK_UP:
				strTemp.Format(_T("Response UP\r\n"));
				break;
			case VK_DOWN:
				strTemp.Format(_T("Response DOWN\r\n"));
				break;
			case VK_LEFT:
				strTemp.Format(_T("Response LEFT\r\n"));
				break;
			case VK_RIGHT:
				strTemp.Format(_T("Response RIGHT\r\n"));
				break;
			default:
				break;
			}
		}
		else if (pMsg->wParam == VK_SPACE)
		{
			strTemp.Format(_T("Response SPACE\r\n"));
		}

		this->m_strResponse += strTemp;
		SetDlgItemText(IDC_EDIT_MESSAGE_RESPONSE, m_strResponse);
		this->m_MessagEditControl.LineScroll(this->m_MessagEditControl.GetLineCount());
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

