#pragma once
#include "Ball.h"
#include <vector>

#define SIZE_BALLS 10

class CBallsView : public CView
{
protected: 
	CBallsView() noexcept;
	DECLARE_DYNCREATE(CBallsView)

public:
	CBallsDoc* GetDocument() const;

public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual ~CBallsView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();

private:
	UINT_PTR	m_nTimerID;
	BOOL		m_bPlay;
	CRect*		m_pRect;
	int			numBalls;
	std::vector<CBall*> vecBall;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPlay();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	afx_msg void OnIncrem();
	afx_msg void OnDecrem();
};

#ifndef _DEBUG 
inline CBallsDoc* CBallsView::GetDocument() const { return reinterpret_cast<CBallsDoc*>(m_pDocument); }
#endif

