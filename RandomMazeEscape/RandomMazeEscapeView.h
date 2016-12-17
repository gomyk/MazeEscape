
// RandomMazeEscapeView.h : CRandomMazeEscapeView 클래스의 인터페이스
//

#pragma once
#include "GLInterface.h"

class CRandomMazeEscapeView : public CView
{
protected: // serialization에서만 만들어집니다.
	CRandomMazeEscapeView();
	DECLARE_DYNCREATE(CRandomMazeEscapeView)

// 특성입니다.
public:
	CRandomMazeEscapeDoc* GetDocument() const;
	CGLInterface m_iGL;
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CRandomMazeEscapeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // RandomMazeEscapeView.cpp의 디버그 버전
inline CRandomMazeEscapeDoc* CRandomMazeEscapeView::GetDocument() const
   { return reinterpret_cast<CRandomMazeEscapeDoc*>(m_pDocument); }
#endif

