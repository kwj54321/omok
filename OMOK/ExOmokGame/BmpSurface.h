#pragma once

// ��Ʈ�� ������ �޸�DC�����Ͽ� blit�ϴ� ǥ�� Ŭ����
// �÷�Ű�� ��������� �����Ǿ� ��µ��� �ʴ´�
class CBmpSurface : public CBitmap
{
public:	
	CBmpSurface();
	~CBmpSurface();
		
	void Open(CDC* pDC, CString file, COLORREF colorKey=0);	// ��Ʈ�� ���� �б�
	void Blit(CDC* pDC, int x, int y);	// pDC�� Blit

	int	Width()  { return m_nWidth; }
	int	Height() { return m_nHeight; }	
	void SetColorKey(COLORREF colorKey) { m_ColorKey = colorKey; }

protected:
	void DeleteSurface();				// �޸� DC ����

	CDC*		m_pMemDC;	// ��Ʈ���� ����� �޸� DC
	int			m_nWidth;	// ��Ʈ���� ũ��
	int			m_nHeight;
	CBitmap*	m_pOldBmp;	// ��Ʈ�� ���������� ���� ���
	COLORREF	m_ColorKey;	// ��������Ʈ ����� ���� �÷�Ű(������ ������ �̹��� ���)
};
