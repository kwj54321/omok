
// ExOmokGameView.cpp : CExOmokGameView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ExOmokGame.h"
#endif

#include "ExOmokGameDoc.h"
#include "ExOmokGameView.h"
#include "MainFrm.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExOmokGameView

IMPLEMENT_DYNCREATE(CExOmokGameView, CView)

BEGIN_MESSAGE_MAP(CExOmokGameView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CExOmokGameView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CExOmokGameView ����/�Ҹ�

CExOmokGameView::CExOmokGameView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CExOmokGameView::~CExOmokGameView()
{
}

BOOL CExOmokGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CExOmokGameView �׸���

void CExOmokGameView::OnDraw(CDC* pDC)
{
	CExOmokGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	int x, y;

	// �ٵ��� ��Ʈ�����
	m_bmpBoard.Blit(pDC, 17, 15);

	// ���� �׸���
	for (y=0; y < 19; y++)
	{
		pDC->MoveTo( 30, 30 + y * 30);
		pDC->LineTo(570, 30 + y * 30);
	}
	for (x=0; x < 19; x++)
	{
		pDC->MoveTo(30 + x * 30, 30);
		pDC->LineTo(30 + x * 30, 570);
	}

	// �ٵϾ� �׸���
	if (pDoc->m_Board[x][y] != NONE)
	{
		for (x=0; x < 19; x++)
		{
			for (y=0; y < 19; y++)
			{
				DrawSite(pDC, x, y, pDoc->m_Board[x][y]);
			}
		}
	}
}


// CExOmokGameView �μ�


void CExOmokGameView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CExOmokGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CExOmokGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CExOmokGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CExOmokGameView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CExOmokGameView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CExOmokGameView ����

#ifdef _DEBUG
void CExOmokGameView::AssertValid() const
{
	CView::AssertValid();
}

void CExOmokGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExOmokGameDoc* CExOmokGameView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExOmokGameDoc)));
	return (CExOmokGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CExOmokGameView �޽��� ó����


void CExOmokGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	int ax, ay;
	int rex, rey;
	CExOmokGameDoc* pDoc = GetDocument();
	
	ax = point.x / 30;
	rex = point.x % 30;
	if ((rex > 10) & (rex < 20))
		return;
	else if (rex < 10)
		ax = ax - 1;
	ay = point.y / 30;
	rey = point.y % 30;
	if ((rey > 10) & (rey < 20))
		return;
	else if (rey < 10)
		ay = ay - 1;

	if (ax < 0 || ax >= 19 || ay < 0 || ay >= 19)
		return;
	if (GetDocument()->m_Board[ax][ay] != NONE) return;
	pDoc->m_Board[ax][ay] = m_stone ? WHITE : BLACK;
		
	CClientDC dc(this);

	// ���� �׸���
	DrawSite(&dc, ax, ay, pDoc->m_Board[ax][ay]);
	CheckPointer(ax, ay, pDoc->m_Board[ax][ay]);
		
	// ���ʸ� �ٲ۴�
	m_stone = !m_stone;	
	m_nTimer = TURN_TIMER;
	pDoc->SetModifiedFlag();
	//UpdateData(FALSE);

	// �޺��ڽ� ���ð���
	CMainFrame* pFrame = (CMainFrame*) AfxGetMainWnd();
	CLeftView* pLV = (CLeftView*)pFrame->m_wndSplitter.GetPane(0, 1);
	CComboBox* pCB = (CComboBox*)pLV->GetDlgItem(IDC_COMBO_SELSTONE);
	pCB->SetCurSel(m_stone);

	CView::OnLButtonDown(nFlags, point);
}

void CExOmokGameView::DrawSite(CDC* pDC, int x, int y, SITE dol)
{
	//if (dol == BLACK)
	//	pDC->SelectStockObject(BLACK_BRUSH);	// �������귯�� ��
	//else if (dol == WHITE)
	//	pDC->SelectStockObject(WHITE_BRUSH);	// ����귯�� ��
	// ���� ������ �׸���
	//if (dol != NONE)
	//	pDC->Ellipse(x*30+14, y*30+14, x*30+44, y*30+44);	

	// ��Ʈ������ �ٵϾ��� ���
	if (dol == BLACK)
		m_bmpBlack.Blit(pDC, x*30+14, y*30+14);
	else if (dol == WHITE)
		m_bmpWhite.Blit(pDC, x*30+14, y*30+14);
}

void CExOmokGameView::CheckPointer(int _x, int _y, SITE dol)
{
	CExOmokGameDoc* pDoc = GetDocument();
	CMainFrame* pFrame = (CMainFrame*) AfxGetMainWnd();
	CLeftView* pLV = (CLeftView*)pFrame->m_wndSplitter.GetPane(0, 1);
	int x, y;
	int count;
		
	x = _x;
	y = _y;
	count = 0;
	
	while(pDoc->m_Board[x-1][_y] == dol && x > 0) x--;

	while(pDoc->m_Board[x++][_y] == dol && x <= 18) count++;

	if (count == 5)
	{
		KillTimer(1);
		PlayVictoryMusic();
		if (dol == BLACK)
		{
			pLV->m_gameResult = L"�浹�¸�";
			pLV->UpdateData(FALSE);
			MessageBox(L"�浹 �¸�", MB_OK);
		}
		else if (dol == WHITE)
		{
			pLV->m_gameResult = L"�鵹�¸�";
			pLV->UpdateData(FALSE);
			MessageBox(L"�鵹 �¸�", MB_OK);
		}
		// �������� �� ����ۿ���
		GameStop();
		if (AfxMessageBox(L"������ ������Ͻðڽ��ϱ�?", MB_ICONQUESTION|MB_YESNO) == IDYES)
		{
			SetTimer(1, 1000, NULL);
			pLV->m_gameResult = "";
			pLV->UpdateData(FALSE);	
			PlayBGM();
		}
	}


	x = _x;
	y = _y;
	count = 0;

	while(pDoc->m_Board[_x][y-1] == dol && y > 0)	 y--;
	while(pDoc->m_Board[_x][y++] == dol && y <= 18) count++;

	if (count == 5) 
	{
		KillTimer(1);
		PlayVictoryMusic();
		if (dol == BLACK)
		{
			pLV->m_gameResult = L"�浹�¸�";
			pLV->UpdateData(FALSE);
			MessageBox(L"�浹 �¸�", MB_OK);
		}
		else if (dol == WHITE)
		{
			pLV->m_gameResult = L"�鵹�¸�";
			pLV->UpdateData(FALSE);
			MessageBox(L"�鵹 �¸�", MB_OK);
		}
		GameStop();
		if (AfxMessageBox(L"������ ������Ͻðڽ��ϱ�?", MB_ICONQUESTION|MB_YESNO) == IDYES)
		{
			SetTimer(1, 1000, NULL);
			pLV->m_gameResult = "";
			pLV->UpdateData(FALSE);	
			PlayBGM();
		}
	}


	x = _x;
	y = _y;
	count = 0;


	while(pDoc->m_Board[x-1][y-1] == dol && x > 0 && y > 0)		{ y--; x--;	}
	while(pDoc->m_Board[x++][y++] == dol && x <= 18 && y <= 18) count++;
	if (count ==5)
	{
		KillTimer(1);
		PlayVictoryMusic();

		if (dol == BLACK)
		{
			pLV->m_gameResult = L"�浹�¸�";
			pLV->UpdateData(FALSE);
			MessageBox(L"�浹 �¸�", MB_OK);
		}
		else if (dol == WHITE)
		{
			pLV->m_gameResult = L"�鵹�¸�";
			pLV->UpdateData(FALSE);
			MessageBox(L"�鵹 �¸�", MB_OK);
		}
		GameStop();
		if (AfxMessageBox(L"������ ������Ͻðڽ��ϱ�?", MB_ICONQUESTION|MB_YESNO) == IDYES)
		{
			SetTimer(1, 1000, NULL);
			pLV->m_gameResult = "";
			pLV->UpdateData(FALSE);	
			PlayBGM();
		}
	}

	x = _x;
	y = _y;
	count = 0;

	while(pDoc->m_Board[x+1][y-1] == dol && x < 18 && y > 0)	{ x++; y--;	}
	while(pDoc->m_Board[x--][y++] == dol && x >= 0 && y <= 18) count++;
	if (count ==5)
	{
		KillTimer(1);
		PlayVictoryMusic();
		if (dol == BLACK)
		{
			pLV->m_gameResult = L"�浹�¸�";
			pLV->UpdateData(FALSE);
			MessageBox(L"�浹 �¸�", MB_OK);
		}
		else if (dol == WHITE)
		{
			pLV->m_gameResult = L"�鵹�¸�";
			pLV->UpdateData(FALSE);
			MessageBox(L"�鵹 �¸�", MB_OK);
		}

		GameStop();
		if (AfxMessageBox(L"������ ������Ͻðڽ��ϱ�?", MB_ICONQUESTION|MB_YESNO) == IDYES)
		{
			SetTimer(1, 1000, NULL);
			pLV->m_gameResult = "";
			pLV->UpdateData(FALSE);	
			PlayBGM();
		}
	}

}

int CExOmokGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_bmpBoard.Open(pDC, L".\\Data\\board.bmp");
	m_bmpBlack.Open(pDC, L".\\Data\\black.bmp", RGB(0, 255, 0));
	m_bmpWhite.Open(pDC, L".\\Data\\white.bmp", RGB(0, 255, 0));
	ReleaseDC(pDC);

	PlayBGM();

	SetTimer(1, 1000, NULL);
	m_stone = FALSE;
	m_nTimer = TURN_TIMER;
	UpdateData(FALSE);

	return 0;
}


void CExOmokGameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nIDEvent == 1)
	{
		m_nTimer--;
		if (m_nTimer == 0) 
		{
			m_nTimer = TURN_TIMER;
			m_stone = !m_stone;
			CMainFrame* pFrame = (CMainFrame*) AfxGetMainWnd();
			CLeftView* pLV = (CLeftView*)pFrame->m_wndSplitter.GetPane(0, 1);
			CComboBox* pCB = (CComboBox*)pLV->GetDlgItem(IDC_COMBO_SELSTONE);
			pCB->SetCurSel(m_stone);

		}

		// ���̵�� ����(Ÿ�̸�)
		CRect rcView;
		CLeftView* pView = (CLeftView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 1);		
		CWnd* pTimerView = pView->GetDlgItem(IDC_TIMER_VIEW);
		pView->Invalidate(FALSE);
		CClientDC dc(pView);
		dc.Rectangle(&rcView);
	}

	CView::OnTimer(nIDEvent);
}


void CExOmokGameView::OnDestroy()
{
	CView::OnDestroy();

	KillTimer(1);
}

void CExOmokGameView::GameStop()
{
	CExOmokGameDoc* pDoc = (CExOmokGameDoc*) GetDocument();
	pDoc->DeleteContents();
	Invalidate();		
	m_nTimer = TURN_TIMER;	
}

void CExOmokGameView::PlayBGM()
{
	mciSendString(L"close MediaFile", NULL, 0, 0);
	mciSendString(L"open .\\data\\bgm.mp3 type mpegvideo alias MediaFile", NULL, 0, 0);
    mciSendString(L"play MediaFile REPEAT", NULL, 0, 0);		
	mciSendString(L"setaudio MediaFile volume to 70", NULL, 0, 0);
}

void CExOmokGameView::PlayVictoryMusic()
{
	mciSendString(L"close MediaFile", NULL, 0, 0);
	mciSendString(L"open .\\data\\victory.mp3 type mpegvideo alias MediaFile", NULL, 0, 0);
	mciSendString(L"play MediaFile", NULL, 0, 0);	
	mciSendString(L"setaudio MediaFile volume to 80", NULL, 0, 0);
}