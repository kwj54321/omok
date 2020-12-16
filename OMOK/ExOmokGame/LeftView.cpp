// LeftView.cpp : ���� �����Դϴ�.
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


// CLeftView �����Դϴ�.

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


// CLeftView �޽��� ó�����Դϴ�.


void CLeftView::OnCbnSelchangeComboSelstone()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ��������
	UpdateData(TRUE);
	CExOmokGameView* pView = (CExOmokGameView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 0);

	switch(m_stone)
	{
	case 0 : pView->m_stone = FALSE; break;
	case 1 : pView->m_stone = TRUE;  break;
	}		
	// �ð��� �����Ѵ�	
	pView->m_nTimer = TURN_TIMER;
}


void CLeftView::OnBnClickedButtonReset()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.	
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (AfxMessageBox(L"������ �����Ͻðڽ��ϱ�?", MB_ICONQUESTION|MB_YESNO) == IDYES)
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	AfxMessageBox(L"������ �����մϴ�", MB_ICONSTOP);
	mciSendString(L"close MediaFile", NULL, 0, 0);
	AfxGetMainWnd()->PostMessage(WM_QUIT);
}

void CLeftView::OnDraw(CDC* pDC)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.		
	//// ��Ʈ����
	CFont font;    //CFont object

	font.CreateFont(          // object�� ����
		24,    // ���� ����
		18,    // ���� ��
		0,                   // ���� ����
		0,                   // ���� ����
		FW_HEAVY,            // ���� ����
		FALSE,               // ���� ��︲ ���
		FALSE,               // �� ��
		FALSE,               // ��Ҽ�
		DEFAULT_CHARSET,     // ���� ��
		OUT_DEFAULT_PRECIS,  // ��� ��Ȯ��
		CLIP_DEFAULT_PRECIS, // ų���� ��Ȯ��
		DEFAULT_QUALITY,     // ����� ��
		DEFAULT_PITCH,       // �ڰ� �Ÿ�
		L"����ü"              // ���� ���
	);

	//// Ÿ�̸�
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
	// Ÿ�̸Ӹ� ���
	strInfo.Format(L"%d", pView->m_nTimer);
	dc.DrawText(strInfo, &rcView, DT_SINGLELINE | DT_CENTER | DT_VCENTER);	
}


int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.


	return 0;
}


void CLeftView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	// ������
	CWnd* pWnd = GetDlgItem(IDC_EDIT_FIRST);
	pWnd->SetWindowText(L"�� ����");
	pWnd = GetDlgItem(IDC_EDIT_SECOND);
	pWnd->SetWindowText(L"�� ����");
}
