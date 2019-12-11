#pragma once

#include "../Inlude/KeyHook.h"

class CGameKeyboardConnectorDlg : public CDialogEx
{
public:
	CGameKeyboardConnectorDlg(CWnd* pParent = nullptr);	// 标准构造函数
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEKEYBOARDCONNECTOR_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnStnClickedStaticIconFinderTool();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
private:
	HPEN		g_hRectanglePen;
	HCURSOR		g_hCursorPrevious;
	HCURSOR		g_hCursorSearchWindow;
	HBITMAP		g_hBitmapFinderToolFilled;
	HBITMAP		g_hBitmapFinderToolEmpty;

	HWND		g_hTarget;
	bool g_bStartSearchWindow = false;
	void OnLoadResouse(void);
public:
	void CreateResponseDlg(void);

	bool CheckWindowValidity(HWND hWnd);
	void HighlightFoundWindow(HWND hWnd);
	void DisplayInfoOnFoundWindow(HWND hWnd);
	afx_msg void OnBnClickedButtonSend();
};


DWORD WINAPI ThreadRespnseDlg(LPVOID lpParamter);