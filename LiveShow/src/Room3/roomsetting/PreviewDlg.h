#pragma once

#include "..\Resource.h"
#include "Skin_i.h"
#include "..\..\HTMLEdit\HtmlEditLogic.h"
#include "..\iectrl\OutputHtmlLogic.h"
// CPreviewDlg 对话框

class CPreviewDlg : public CDialog
{
	DECLARE_DYNAMIC(CPreviewDlg)

public:
	CPreviewDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPreviewDlg();

	void SetInitContent(std::wstring strContent);
	void SetContent(std::wstring strContent);

// 对话框数据
	enum { IDD = IDD_PREVIEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()
	
private:
	CComPtr<ISkinEngine> m_pSkinEngine;

	HtmlEditImpl *m_pPreviewHtml;
//	HtmlEditLogic m_PreviewLogic;
	COutputHtmlLogic m_PreviewLogic ;
	std::wstring m_strContent;
	
};
