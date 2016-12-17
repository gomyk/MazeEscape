
// RandomMazeEscapeView.cpp : CRandomMazeEscapeView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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

// CRandomMazeEscapeView 생성/소멸

CRandomMazeEscapeView::CRandomMazeEscapeView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CRandomMazeEscapeView::~CRandomMazeEscapeView()
{
}

BOOL CRandomMazeEscapeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CRandomMazeEscapeView 그리기

void CRandomMazeEscapeView::OnDraw(CDC* /*pDC*/)
{
	CRandomMazeEscapeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_iGL.Display();
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CRandomMazeEscapeView 인쇄

BOOL CRandomMazeEscapeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CRandomMazeEscapeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CRandomMazeEscapeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CRandomMazeEscapeView 진단

#ifdef _DEBUG
void CRandomMazeEscapeView::AssertValid() const
{
	CView::AssertValid();
}

void CRandomMazeEscapeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRandomMazeEscapeDoc* CRandomMazeEscapeView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRandomMazeEscapeDoc)));
	return (CRandomMazeEscapeDoc*)m_pDocument;
}
#endif //_DEBUG


// CRandomMazeEscapeView 메시지 처리기



int CRandomMazeEscapeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(100, 1, NULL);
	return m_iGL.Initialize(new CClientDC(this));
	return 0;
}


void CRandomMazeEscapeView::OnDestroy()
{
	CView::OnDestroy();
	KillTimer(100);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_iGL.Release();
}


void CRandomMazeEscapeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_iGL.OnKeyDown(nChar, nRepCnt, nFlags);

	// invalidate client area for refresh. 모든 클라이언트 영역을 무효화 한다. 새로 그려줌 
	Invalidate(false);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CRandomMazeEscapeView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return CView::OnEraseBkgnd(pDC);
}


void CRandomMazeEscapeView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_iGL.OnTimer(nIDEvent);
	Invalidate(false);
	CView::OnTimer(nIDEvent);
}


void CRandomMazeEscapeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_iGL.SetProjectView(cx, cy);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
