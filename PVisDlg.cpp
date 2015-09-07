// PVisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PVis.h"
#include "PVisDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPVisDlg dialog



CPVisDlg::CPVisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPVisDlg::IDD, pParent)
	, m_nTimer1(0)
	, m_data(NULL)
	, m_ampl(70)
	, m_angle(20)
	, m_speed(16)
	, m_centre(120)
	, m_bRed(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPVisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VISBORDER, m_visb);
	DDX_Slider(pDX, IDC_SLIDER1, m_ampl);
	DDX_Control(pDX, IDC_SLIDER1, m_slider1);
	DDX_Control(pDX, IDC_SLIDER2, m_slider2);
	DDX_Slider(pDX, IDC_SLIDER2, m_angle);
	DDX_Control(pDX, IDC_SLIDER3, m_slider3);
	DDX_Slider(pDX, IDC_SLIDER3, m_speed);
	DDX_Control(pDX, IDC_SLIDER4, m_slider4);
	DDX_Slider(pDX, IDC_SLIDER4, m_centre);
	DDX_Check(pDX, IDC_CHECK1, m_bRed);
}

BEGIN_MESSAGE_MAP(CPVisDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CPVisDlg message handlers

BOOL CPVisDlg::OnInitDialog()
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
	m_data = new int[400];
	m_vis.Create( 400, 250, 24 );
	m_nTimer1 = SetTimer( 1, 1, 0 );

	m_slider1.SetRange( 0, 300, TRUE );
	m_slider2.SetRange( 1, 1000, TRUE );
	m_slider3.SetRange( 1, 100, TRUE );
	m_slider4.SetRange( 1, 249, TRUE );
	
	UpdateData( FALSE );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPVisDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPVisDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPVisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPVisDlg::DrawVis(void)
{
	mysine();

	RECT rc;
	m_visb.GetClientRect( &rc );

	CDC *dc   = GetDC();
	HDC srcdc = m_vis.GetDC();
	
	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID; 
    lb.lbColor = RGB(100,0,0); 
    lb.lbHatch = 0; 

	HPEN pen = ExtCreatePen( 
		PS_SOLID,
		1,
		&lb,
		0,
		NULL
	);

	BitBlt( srcdc, 0, 0, 400, 250, NULL, 0, 0, BLACKNESS );

	SelectObject( srcdc, pen );

	for( int i = 0; i < 400; i += 10 )
	{
		MoveToEx( srcdc, i, 0, NULL );
		LineTo( srcdc, i, 250 );
	}

	for( int i = 0; i < 250; i += 10 )
	{
		MoveToEx( srcdc, 0, i, NULL );
		LineTo( srcdc, 400, i );
	}


	DeleteObject( pen );

	lb.lbColor = RGB( 0, 255, 0 );
	pen = ExtCreatePen( 
		PS_SOLID,
		1,
		&lb,
		0,
		NULL
	);

	SelectObject( srcdc, pen );

	MoveToEx( srcdc, 0, m_data[0], NULL );

	for( int i = 1; i < 400; i ++ )
	{
		if( m_bRed )
		{
			LineTo( srcdc, i, m_data[i] );
		}
		else
		{
			SetPixel( srcdc, i, m_data[i], RGB( 0, 255, 0) );
		}
	}

	DeleteObject( pen );

	lb.lbColor = RGB( 255, 0, 0 );
	pen = ExtCreatePen( 
		PS_SOLID,
		1,
		&lb,
		0,
		NULL
	);

	SelectObject( srcdc, pen );

	MoveToEx( srcdc,   0, m_centre, NULL );
	LineTo(   srcdc, 399, m_centre );

	DeleteObject( pen );

	lb.lbColor = RGB( 0, 0, 255 );
	pen = ExtCreatePen( 
		PS_SOLID,
		1,
		&lb,
		0,
		NULL
	);

	SelectObject( srcdc, pen );

	MoveToEx( srcdc,  13, 10, NULL );
	LineTo(   srcdc,  10,  0 );
	LineTo(   srcdc,   7, 10 );
	MoveToEx( srcdc,  10,  0, NULL );  
	LineTo(   srcdc,  10, 249 );
	MoveToEx( srcdc,   0, 239, NULL );
	LineTo(   srcdc, 399, 239 );
	LineTo(   srcdc, 389, 236 );
	MoveToEx( srcdc, 399, 239, NULL);
	LineTo(   srcdc, 389, 242 );

	dc->StretchBlt( 
		rc.left + 45, 
		rc.top  + 15, 
		rc.right - rc.left - 9, 
		rc.bottom - rc.top - 15,
		CDC::FromHandle( srcdc ),
		0,
		0,
		400,
		250,
		SRCCOPY
	);

	m_vis.ReleaseDC();
	ReleaseDC( dc );
	DeleteObject( pen );
}

void CPVisDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	KillTimer( m_nTimer1 );
	delete[] m_data;

	CDialog::OnClose();
}

void CPVisDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch( nIDEvent )
	{
	case 1:
		DrawVis();
	}

	CDialog::OnTimer(nIDEvent);
}

void CPVisDlg::mysine(void)
{
	UpdateData( TRUE );

	static double pi    = 3.1415926535;
	static double angle = 0;

	for( int i = 0; i < 400; i++ )
	{
		m_data[i] = int( m_centre + m_ampl * sin( angle + ( pi/m_angle * i ) ) );
	}

	angle += pi/m_speed;

	CString temp;
	temp.Format( "m_centre = %d, m_ampl = %d, m_angle = %d, m_speed = %d", m_centre, m_ampl, m_angle, m_speed );
	SetWindowText( temp );
}
