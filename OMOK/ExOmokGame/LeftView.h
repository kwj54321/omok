#pragma once



// CLeftView Æû ºäÀÔ´Ï´Ù.

class CLeftView : public CFormView
{
	DECLARE_DYNCREATE(CLeftView)

protected:
	CLeftView();         
	virtual ~CLeftView();

public:
	enum { IDD = IDD_LEFTVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   

	DECLARE_MESSAGE_MAP()

public:
	int m_stone;
	CString m_gameFirst;
	CString m_gameResult;
	CString m_gameSecond;
	afx_msg void OnCbnSelchangeComboSelstone();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonExit();
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
};


