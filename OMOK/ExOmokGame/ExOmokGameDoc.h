
// ExOmokGameDoc.h : CExOmokGameDoc Ŭ������ �������̽�
//


#pragma once

enum SITE { NONE, BLACK, WHITE };

class CExOmokGameDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CExOmokGameDoc();
	DECLARE_DYNCREATE(CExOmokGameDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:
	SITE	m_Board[19][19];

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CExOmokGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual void DeleteContents();
};
