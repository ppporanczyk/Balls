#include "pch.h"
#include "framework.h"
#include "Balls.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

UINT CMainFrame::m_buttonsIDs[] =
{
	ID_PLAY,
	ID_INCREM,
	ID_DECREM,
	ID_APP_ABOUT
};

static UINT indicators[] =
{
	ID_SEPARATOR,           
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame() noexcept{}
CMainFrame::~CMainFrame(){}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	/*if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}*/

	if (!m_wndToolBar.Create(this) || !m_wndToolBar.LoadBitmapW(IDR_MAINFRAME)
		|| !m_wndToolBar.SetButtons(m_buttonsIDs, sizeof(m_buttonsIDs) / sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	CToolBarCtrl& BarCtrl = m_wndToolBar.GetToolBarCtrl();
	BarCtrl.SetBitmapSize(CSize(31, 24));
	BarCtrl.SetButtonSize(CSize(38, 32));

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));


	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const {CFrameWnd::AssertValid();}
void CMainFrame::Dump(CDumpContext& dc) const {CFrameWnd::Dump(dc);}
#endif //_DEBUG


void CMainFrame::ResetButton(BOOL  b) {
	int buttonIx = sizeof(m_buttonsIDs) / sizeof(UINT);
	if (b)
		m_wndToolBar.SetButtonInfo(0, ID_PLAY, TBBS_BUTTON, buttonIx);
	else
		m_wndToolBar.SetButtonInfo(0, ID_PLAY, TBBS_BUTTON, 0);
	m_wndToolBar.Invalidate(); 
}