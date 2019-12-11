#pragma once

class CKeyBoardResponseDlg : public CDialog
{
public:
	CKeyBoardResponseDlg(CWnd* pParent = nullptr);	// 标准构造函数
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KEYBOARDRESPONSE_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	CString m_strResponse;
	CEdit m_MessagEditControl;
};
