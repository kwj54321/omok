#include "stdafx.h"
#include "BmpSurface.h"

///////////////////////////////////////////////////////////////////

CBmpSurface::CBmpSurface()
{
	m_pMemDC = nullptr;
	m_ColorKey = 0;
}

CBmpSurface::~CBmpSurface()
{
	DeleteSurface();
}

void CBmpSurface::DeleteSurface()
{
	m_pMemDC->SelectObject(m_pOldBmp);	// ��Ʈ�� ��������
	DeleteObject();						// ��Ʈ�� ����
	if (m_pMemDC)
	{
		m_pMemDC->DeleteDC();			// �޸� dc ����
		delete m_pMemDC;
		m_pMemDC = nullptr;
	}
}

void CBmpSurface::Open(CDC* pDC, CString file, COLORREF colorKey)
{
	// ��Ʈ�������� �д´�
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (hBitmap) Attach(hBitmap);

	// �޸� dc�� �����ϰ� �޸� dc�� ��Ʈ���� �ø���
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(pDC);
	m_pOldBmp = (CBitmap*)m_pMemDC->SelectObject(this);

	BITMAP bmpInfo;
	GetBitmap(&bmpInfo);
	m_nWidth = bmpInfo.bmWidth;
	m_nHeight = bmpInfo.bmHeight;

	m_ColorKey = colorKey;
}

void CBmpSurface::Blit(CDC* pDC, int x, int y)
{
	// �÷�Ű ������ ������ ��������Ʈ ���
	if (m_ColorKey)
	{
		pDC->TransparentBlt(x, y, m_nWidth, m_nHeight, m_pMemDC, 0, 0, m_nWidth, m_nHeight, m_ColorKey);
	}
	else // �÷�Ű ������ ������ �̹��� ���
	{
		pDC->BitBlt(x, y, m_nWidth, m_nHeight, m_pMemDC, 0, 0, SRCCOPY);								
	}
}
