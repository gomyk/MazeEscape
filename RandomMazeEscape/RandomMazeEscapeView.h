
// RandomMazeEscapeView.h : CRandomMazeEscapeView Ŭ������ �������̽�
//

#pragma once
#include "GLInterface.h"

class CRandomMazeEscapeView : public CView
{
protected: // serialization������ ��������ϴ�.
	CRandomMazeEscapeView();
	DECLARE_DYNCREATE(CRandomMazeEscapeView)

// Ư���Դϴ�.
public:
	CRandomMazeEscapeDoc* GetDocument() const;
	CGLInterface m_iGL;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CRandomMazeEscapeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // RandomMazeEscapeView.cpp�� ����� ����
inline CRandomMazeEscapeDoc* CRandomMazeEscapeView::GetDocument() const
   { return reinterpret_cast<CRandomMazeEscapeDoc*>(m_pDocument); }
#endif

