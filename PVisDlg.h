// PVisDlg.h : header file
//

#pragma once
#include "atlimage.h"
#include "afxwin.h"
#include "afxcmn.h"


// CPVisDlg dialog
class CPVisDlg : public CDialog
{
// Construction
public:
	CPVisDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PVIS_DIALOG };

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
	int *m_data;
	CImage m_vis;
	CStatic m_visb;
	void DrawVis(void);
	UINT_PTR m_nTimer1;
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	void mysine(void);
	int m_ampl;
	CSliderCtrl m_slider1;
	CSliderCtrl m_slider2;
	int m_angle;
	CSliderCtrl m_slider3;
	int m_speed;
	CSliderCtrl m_slider4;
	int m_centre;
	BOOL m_bRed;
};
