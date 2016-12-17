
// RandomMazeEscapeView.cpp : CRandomMazeEscapeView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "RandomMazeEscape.h"
#endif

#include "RandomMazeEscapeDoc.h"
#include "RandomMazeEscapeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRandomMazeEscapeView

IMPLEMENT_DYNCREATE(CRandomMazeEscapeView, CView)

BEGIN_MESSAGE_MAP(CRandomMazeEscapeView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CRandomMazeEscapeView ����/�Ҹ�

CRandomMazeEscapeView::CRandomMazeEscapeView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CRandomMazeEscapeView::~CRandomMazeEscapeView()
{
}

BOOL CRandomMazeEscapeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CRandomMazeEscapeView �׸���

void CRandomMazeEscapeView::OnDraw(CDC* /*pDC*/)
{
	CRandomMazeEscapeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_iGL.Display();
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CRandomMazeEscapeView �μ�

BOOL CRandomMazeEscapeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CRandomMazeEscapeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CRandomMazeEscapeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CRandomMazeEscapeView ����

#ifdef _DEBUG
void CRandomMazeEscapeView::AssertValid() const
{
	CView::AssertValid();
}

void CRandomMazeEscapeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRandomMazeEscapeDoc* CRandomMazeEscapeView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRandomMazeEscapeDoc)));
	return (CRandomMazeEscapeDoc*)m_pDocument;
}
#endif //_DEBUG


// CRandomMazeEscapeView �޽��� ó����



int CRandomMazeEscapeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	SetTimer(100, 1, NULL);
	return m_iGL.Initialize(new CClientDC(this));
	return 0;
}


void CRandomMazeEscapeView::OnDestroy()
{
	CView::OnDestroy();
	KillTimer(100);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	m_iGL.Release();
}


void CRandomMazeEscapeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_iGL.OnKeyDown(nChar, nRepCnt, nFlags);

	// invalidate client area for refresh. ��� Ŭ���̾�Ʈ ������ ��ȿȭ �Ѵ�. ���� �׷��� 
	Invalidate(false);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CRandomMazeEscapeView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CView::OnEraseBkgnd(pDC);
}


void CRandomMazeEscapeView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_iGL.OnTimer(nIDEvent);
	Invalidate(false);
	CView::OnTimer(nIDEvent);
}


void CRandomMazeEscapeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_iGL.SetProjectView(cx, cy);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
