
// ExOmokGameView.h : CExOmokGameView Ŭ������ �������̽�
//

#pragma once

#include "ExOmokGameDoc.h"
#include "BmpSurface.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")		

#define TURN_TIMER 30


class CExOmokGameView : public CView
{
protected: // serialization������ ��������ϴ�.
	CExOmokGameView();
	DECLARE_DYNCREATE(CExOmokGameView)

public:
	CExOmokGameDoc* GetDocument() const;

public:
	CBmpSurface		m_bmpBoard;
	CBmpSurface		m_bmpBlack;
	CBmpSurface		m_bmpWhite;

	BOOL			m_stone;
	int				m_nTimer;

	void DrawSite(CDC* pDC, int x, int y, SITE dol);	
	void CheckPointer(int _x, int _y, SITE dol);		
	void GameStop();									
	void PlayBGM();										
	void PlayVictoryMusic();							

public:
	virtual void OnDraw(CDC* pDC);  
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CExOmokGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // ExOmokGameView.cpp�� ����� ����
inline CExOmokGameDoc* CExOmokGameView::GetDocument() const
   { return reinterpret_cast<CExOmokGameDoc*>(m_pDocument); }
#endif

