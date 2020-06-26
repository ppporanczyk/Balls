#pragma once
#include <afxwin.h>


class CBall : public CRect{

private:
	CPen* m_pBallPen;
	CBrush* m_pBallBrush;
	int m_nOffX;
	int m_nOffY;
	CRect* m_BoundRect;

public:
	CBall(const CRect& bound, int left, int top, int right, int bottom , COLORREF col, int X, int Y);
	CBall(const CRect& bound, const CRect& srcRect, COLORREF col, int X, int Y);
	CBall(const CRect& bound, CPoint point, CSize size, COLORREF col, int X, int Y);
	~CBall();

	CPen* GetPen();
	CBrush* GetBrush();
	void SetPen(CPen* pPen);
	void SetBrush(CBrush* pBrush);

	int GetX();
	int GetY();
	void SetX(int newX);
	void SetY(int newY);

	inline COLORREF SetColor(COLORREF col);
	inline void SetBallSize(const CRect& srcR);
	void PaintBall(CDC* pDC);

	void SetBall(const CRect& rec, COLORREF col, int nOffX, int nOffY);
	void SetOffset(int nOffX, int nOffY);
	void SetBoundRect(const CRect& rec);

private:
	void InitObjects(COLORREF BallColor);
	inline void CreateObjects(COLORREF BallColor);
	inline void DeleteObjects();
};
