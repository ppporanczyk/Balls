#include "pch.h"
#include "Ball.h"

CBall::CBall(const CRect& bound, int left = 0, int top = 0, int right = 0, int bottom = 0, COLORREF col = RGB(0, 0, 0), int X = 3, int Y = 2)
	:CRect(left, top, right, bottom)
{
	//SetBallSize(CRect(left, top, right, bottom));
	SetBall(bound, col, X, Y);
	InitObjects(col);
	
}

CBall::CBall(const CRect& bound, const CRect& srcRect, COLORREF col = RGB(0, 0, 0), int X = 3, int Y = 2)
	:CRect(left, top, right, bottom)
{
	//SetBallSize(CRect(srcRect));
	SetBall(bound, col, X, Y);
	InitObjects(col);
}

CBall::CBall(const CRect& bound, CPoint point, CSize size, COLORREF col = RGB(0, 0, 0), int X = 3, int Y = 2)
	:CRect(left, top, right, bottom)
{
	//SetBallSize(CRect(point, size));
	SetBall(bound, col, X, Y);
	InitObjects(col);
}

CBall::~CBall() {
	DeleteObjects();
}

CPen* CBall::GetPen() {return m_pBallPen;}
CBrush* CBall::GetBrush() {return m_pBallBrush;}
void CBall::SetPen(CPen* pPen) {m_pBallPen = pPen;}
void CBall::SetBrush(CBrush* pBrush) {m_pBallBrush = pBrush;}

int CBall::GetX() {return m_nOffX;}
int CBall::GetY() { return m_nOffY;}
void CBall::SetX(int newX) { m_nOffX = newX;}
void CBall::SetY(int newY) {m_nOffY = newY;}

inline COLORREF CBall::SetColor(COLORREF col) {
	return col;
}

inline void CBall::SetBallSize(const CRect& srcR) {
	CRect(srcR.left,srcR.top,srcR.right,srcR.bottom);
}

void CBall::PaintBall(CDC* pDC) {
	pDC->Ellipse(this);
}

void CBall::SetBall(const CRect& rec, COLORREF col, int nOffX, int nOffY) {
	
	SetBoundRect(rec);
	SetX(nOffX);
	SetY(nOffY);
}

void CBall::SetOffset(int nOffX, int nOffY) {
	SetX(GetX()*nOffX);
	SetY(GetY()*nOffY);
}

void CBall::SetBoundRect(const CRect& rec) {
	this->left = (rec.left > this->left) ? rec.left: this->left;
	this->top= (rec.top > this->top) ? rec.top : this->top;
	this->right= (rec.right < this->right) ? rec.right : this->right;
	this->bottom= (rec.bottom < this->bottom) ? rec.bottom : this->bottom;
}

void CBall::InitObjects(COLORREF BallColor)
{
	m_pBallPen = new CPen();
	m_pBallBrush = new CBrush();
	CreateObjects(BallColor);
}

inline void CBall::CreateObjects(COLORREF BallColor = RGB(0, 0, 0)) {
	m_pBallPen->CreatePen(PS_SOLID, 1, SetColor(BallColor));
	m_pBallBrush->CreateSolidBrush(SetColor(BallColor));
}

inline void CBall::DeleteObjects()
{
	delete m_pBallPen;
	delete m_pBallBrush;
}


