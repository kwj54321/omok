// LeftView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ExOmokGame.h"
#include "LeftView.h"
#include "ExOmokGameView.h"
#include "MainFrm.h"
#include "ExOmokGameDoc.h"


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CFormView)

CLeftView::CLeftView()
	: CFormView(CLeftView::IDD)
{

	m_stone = 0;
	m_gameFirst = _T("");
	m_gameResult = _T("");
	m_gameSecond = _T("");
}

CLeftView::~CLeftView()
{
}

void CLeftView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_SELSTONE, m_stone);
	DDX_Text(pDX, IDC_EDIT_FIRST, m_gameFirst);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_gameResult);
	DDX_Text(pDX, IDC_EDIT_SECOND, m_gameSecond);
}

BEGIN_MESSAGE_MAP(CLeftView, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO_SELSTONE, &CLeftView::OnCbnSelchangeComboSelstone)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CLeftView::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CLeftView::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CLeftView::OnBnClickedButtonExit)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CLeftView 진단입니다.

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftView 메시지 처리기입니다.


void CLeftView::OnCbnSelchangeComboSelstone()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 강제변경
	UpdateData(TRUE);
	CExOmokGameView* pView = (CExOmokGameView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 0);

	switch(m_stone)
	{
	case 0 : pView->m_stone = FALSE; break;
	case 1 : pView->m_stone = TRUE;  break;
	}		
	// 시간을 리셋한다	
	pView->m_nTimer = TURN_TIMER;
}


void CLeftView::OnBnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	CExOmokGameDoc* pDoc = (CExOmokGameDoc*) GetDocument();
	pDoc->DeleteContents();
	CExOmokGameView* pView = (CExOmokGameView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 0);	
	pView->Invalidate();
	pView->m_nTimer = TURN_TIMER;
	pView->KillTimer(1);
	pView->SetTimer(1, 1000, NULL);
	m_gameResult = "";
	UpdateData(FALSE);	
	pView->PlayBGM();	
}

void CLeftView::OnBnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (AfxMessageBox(L"게임을 중지하시겠습니까?", MB_ICONQUESTION|MB_YESNO) == IDYES)
	{	
		CExOmokGameDoc* pDoc = (CExOmokGameDoc*) GetDocument();
		pDoc->DeleteContents();
		CExOmokGameView* pView = (CExOmokGameView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 0);
		pView->Invalidate();		
		pView->m_nTimer = TURN_TIMER;
		pView->KillTimer(1);
	}
}


void CLeftView::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(L"게임을 종료합니다", MB_ICONSTOP);
	mciSendString(L"close MediaFile", NULL, 0, 0);
	AfxGetMainWnd()->PostMessage(WM_QUIT);
}

void CLeftView::OnDraw(CDC* pDC)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.		
	//// 폰트생성
	CFont font;    //CFont object

	font.CreateFont(          // object의 생성
		24,    // 문자 높이
		18,    // 문자 폭
		0,                   // 기울기 각도
		0,                   // 문자 방향
		FW_HEAVY,            // 문자 굵기
		FALSE,               // 문자 기울림 모양
		FALSE,               // 밑 줄
		FALSE,               // 취소선
		DEFAULT_CHARSET,     // 문자 셋
		OUT_DEFAULT_PRECIS,  // 출력 정확도
		CLIP_DEFAULT_PRECIS, // 킬립핑 정확도
		DEFAULT_QUALITY,     // 출력의 질
		DEFAULT_PITCH,       // 자간 거리
		L"굴림체"              // 문자 모양
	);

	//// 타이머
	CRect rcView;
	CString strInfo;
	CExOmokGameView* pView = (CExOmokGameView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 0);	
	CWnd* pTimerView = GetDlgItem(IDC_TIMER_VIEW);

	CClientDC dc(pTimerView);
	dc.SelectObject(&font);
	dc.SetTextColor(RGB(0, 0, 255));
	dc.SetBkMode(TRANSPARENT);
		
	pTimerView->GetClientRect(&rcView);

	dc.SelectStockObject(WHITE_BRUSH);
	dc.Rectangle(&rcView);
	// 타이머를 출력
	strInfo.Format(L"%d", pView->m_nTimer);
	dc.DrawText(strInfo, &rcView, DT_SINGLELINE | DT_CENTER | DT_VCENTER);	
}


int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.


	return 0;
}


void CLeftView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// 선공자
	CWnd* pWnd = GetDlgItem(IDC_EDIT_FIRST);
	pWnd->SetWindowText(L"흑 색돌");
	pWnd = GetDlgItem(IDC_EDIT_SECOND);
	pWnd->SetWindowText(L"백 색돌");
}
