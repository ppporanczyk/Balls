#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "Balls.h"
#endif

#include "BallsDoc.h"
#include "BallsView.h"
#include "MainFrm.h"
#include <iostream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CBallsView, CView)

BEGIN_MESSAGE_MAP(CBallsView, CView)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_COMMAND(ID_PLAY, &CBallsView::OnPlay)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_INCREM, &CBallsView::OnIncrem)
	ON_COMMAND(ID_DECREM, &CBallsView::OnDecrem)
END_MESSAGE_MAP()


CBallsView::CBallsView() noexcept
{
	srand(time(NULL));

	m_bPlay = FALSE;
	m_pRect = new CRect(20, 20, 80, 80);
	numBalls = 0;

	OnIncrem();
}

CBallsView::~CBallsView()
{
	delete m_pRect;
}

BOOL CBallsView::PreCreateWindow(CREATESTRUCT& cs) {return CView::PreCreateWindow(cs);}

void CBallsView::OnDraw(CDC* pDC)
{
	CBallsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC memDC;
	BOOL b = memDC.CreateCompatibleDC(pDC);
	ASSERT(b);

	CBitmap bmp;
	b = bmp.CreateCompatibleBitmap(pDC, m_pRect->Width(), m_pRect->Height());
	ASSERT(b);
	CBitmap* pOldBitmap = memDC.SelectObject(&bmp);
	memDC.FillSolidRect(m_pRect, RGB(255, 255, 255));

	CPen* pOldPen = memDC.SelectObject(vecBall[0]->GetPen());
	CBrush* pOldBrush = memDC.SelectObject(vecBall[0]->GetBrush());


	for (int i = 0; i < numBalls; i++) {
		pOldPen = memDC.SelectObject(vecBall[i]->GetPen());
		pOldBrush = memDC.SelectObject(vecBall[i]->GetBrush());
		vecBall[i]->PaintBall(&memDC); 
	}


	memDC.SelectObject(pOldPen);
	memDC.SelectObject(pOldBrush);

	b = pDC->BitBlt(0, 0, m_pRect->Width(), m_pRect->Height(), &memDC, 0, 0, SRCCOPY);
	ASSERT(b);

	memDC.SelectObject(pOldBitmap);
	bmp.DeleteObject();
	memDC.DeleteDC();
}

#ifdef _DEBUG
void CBallsView::AssertValid() const {CView::AssertValid();}
void CBallsView::Dump(CDumpContext& dc) const {CView::Dump(dc);}
CBallsDoc* CBallsView::GetDocument() const 
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBallsDoc)));
	return (CBallsDoc*)m_pDocument;
}
#endif //_DEBUG

//////////////////////////////////////
// CALLBACK Timer procedure
//////////////////////////////////////
void CALLBACK ZfxTimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime) {
	::SendMessage(hWnd, WM_TIMER, 0, 0);
}

void CBallsView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_nTimerID = SetTimer(WM_USER + 1, 20, ZfxTimerProc);
}


void CBallsView::OnDestroy()
{
	KillTimer(m_nTimerID);
	CView::OnDestroy();
}


void CBallsView::OnTimer(UINT_PTR nIDEvent)
{
	if (m_bPlay) {
		for (int i = 0; i < numBalls; i++) {
			if (vecBall[i]->left < m_pRect->left || vecBall[i]->right >= m_pRect->right)
				vecBall[i]->SetOffset(-1, 1);

			if (vecBall[i]->top < m_pRect->top || vecBall[i]->bottom >= m_pRect->bottom)
				vecBall[i]->SetOffset(1, -1);

			vecBall[i]->OffsetRect(vecBall[i]->GetX(), vecBall[i]->GetY());
		}
		Invalidate();
	}
	CView::OnTimer(nIDEvent);
}


void CBallsView::OnPlay()
{
	m_bPlay = !m_bPlay;
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	pFrame->ResetButton(m_bPlay);
}

BOOL CBallsView::OnEraseBkgnd(CDC* pDC) {return 1;}

void CBallsView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	GetClientRect(m_pRect); 
	CView::OnPrepareDC(pDC, pInfo);
}

void CBallsView::OnIncrem()
{
	if (numBalls>=0 && numBalls<SIZE_BALLS){
		int temp = rand() % 80;
		CBall* pBall = new CBall(*m_pRect,10, 10, 20 + temp, 20 + temp, RGB(rand() % 255, rand() % 255, rand() % 255), rand() % 15, rand() % 15 );

		vecBall.push_back(pBall);
		numBalls++;
	}
}

void CBallsView::OnDecrem()
{
	if (numBalls > 1 && numBalls <= SIZE_BALLS)
	{
		CBall* pBall = vecBall.back();
		delete pBall;
		vecBall.pop_back();

		numBalls--;
	}
}
