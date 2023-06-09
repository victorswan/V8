// SkinButton.cpp : implementation file
//

#include "stdafx.h"
#include "ImageBase.h"
#include "SkinEngine.h"
#include "SkinButton.h"
#include "SkinItemDialog.h"
#include ".\skinbutton.h"
#include "ImageType.h"

// CSkinButton

IMPLEMENT_DYNCREATE(CSkinButton, CSkinBase)


CSkinButton::CSkinButton()
{
	EnableAutomation();

	m_pNormalImage = NULL;
	m_pHoverImage = NULL;
	m_pDownImage = NULL;
	m_pDisabledImage = NULL;
	m_strNormalImage = _T("");
	m_strHoverImage = _T("");
	m_strDownImage = _T("");
	m_strDisabledImage = _T("");
    m_bSideStretch = TRUE;
    m_lSideStretchWidth = 0;
    m_lSideStretchHeight = 0;
    m_bHotColorTransform = TRUE;

    m_bTextColorTransform = FALSE;
    m_bTextHotColorTransform = TRUE;

    m_textStyleNormal.Setcolor(RGB(0, 0, 0));
	m_textStyleHover.Setcolor(RGB(0, 0, 0));
	m_textStyleDown.Setcolor(RGB(0, 0, 0));
	m_textStyleDisabled.Setcolor(RGB(149, 149, 149));

	m_pIconImageUncheckedNormal = NULL;
	m_strIconImageUncheckedNormal = _T("");
    m_pIconImageUncheckedHover = NULL;
    m_strIconImageUncheckedHover = _T("");
    m_pIconImageUncheckedDown = NULL;
    m_strIconImageUncheckedDown = _T("");
    m_pIconImageUncheckedDisabled = NULL;
    m_strIconImageUncheckedDisabled = _T("");
    m_pIconImageCheckedNormal = NULL;
    m_strIconImageCheckedNormal = _T("");
    m_pIconImageCheckedHover = NULL;
    m_strIconImageCheckedHover = _T("");
    m_pIconImageCheckedDown = NULL;
    m_strIconImageCheckedDown = _T("");
    m_pIconImageCheckedDisabled = NULL;
    m_strIconImageCheckedDisabled = _T("");
	m_nIconMargin = 4;
    m_nIconTopMargin = -1;
    m_bIconColorTransform = FALSE;
    m_bIconAlpha = FALSE;
    m_szIcon = CSize(0, 0);

    m_pAbsIconImageUncheckedNormal = NULL;

    m_pBackIconImageUncheckedNormal = NULL;
    m_strBackIconImageUncheckedNormal = _T("");
    m_pBackIconImageUncheckedHover = NULL;
    m_strBackIconImageUncheckedHover = _T("");
    m_pBackIconImageUncheckedDown = NULL;
    m_strBackIconImageUncheckedDown = _T("");
    m_pBackIconImageUncheckedDisabled = NULL;
    m_strBackIconImageUncheckedDisabled = _T("");
    m_pBackIconImageCheckedNormal = NULL;
    m_strBackIconImageCheckedNormal = _T("");
    m_pBackIconImageCheckedHover = NULL;
    m_strBackIconImageCheckedHover = _T("");
    m_pBackIconImageCheckedDown = NULL;
    m_strBackIconImageCheckedDown = _T("");
    m_pBackIconImageCheckedDisabled = NULL;
    m_strBackIconImageCheckedDisabled = _T("");
    m_nBackIconMargin = 4;
    m_nBackIconTopMargin = -1;
    m_szBackIcon = CSize(0, 0);

    m_strTip = _T("");
	m_nMaxTipWidth = 0;

    m_bLabelNormalUnderline = FALSE;
	m_nTextMargin = 2;

	m_bHyperLink = false;
	m_strHyperLinkAddress = _T("");

	m_nCmdID = 0;

	m_nMouseState = BUTTON_STATE_NORMAL;

	m_eSBStyle = BUTTONSTYLE_NORMAL;

    m_enTextPlacement = RIGHT;

	m_bChecked = FALSE;

    m_nDownOffset = 1;

    m_bShowBkAlways = TRUE;

	m_uButtonFlag = UseDefaultSize;

	m_bClickable = TRUE;
	m_bHandleTip = FALSE;
}

CSkinButton::~CSkinButton()
{
    if (m_pAbsIconImageUncheckedNormal != NULL) {
        delete m_pAbsIconImageUncheckedNormal;
        m_pAbsIconImageUncheckedNormal = NULL;
    }
}

void CSkinButton::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CSkinButton, CSkinBase)

END_MESSAGE_MAP()


BEGIN_SKIN_DISPATCH_MAP(CSkinButton, CSkinBase)
	SKINBASE_DISP_PROPERTIES(CSkinButton)

	SKIN_DISP_PROPERTY(CSkinButton, style, VT_BSTR)
	SKIN_DISP_PROPERTY(CSkinButton, checked, VT_BOOL)
    SKIN_DISP_PROPERTY(CSkinButton, textColorTransform, VT_BOOL)
    SKIN_DISP_PROPERTY(CSkinButton, textHotColorTransform, VT_BOOL)
	SKIN_DISP_PROPERTY(CSkinButton, normalImage, VT_BSTR)
	SKIN_DISP_PROPERTY(CSkinButton, hoverImage, VT_BSTR)
	SKIN_DISP_PROPERTY(CSkinButton, downImage, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, disabledImage, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, sideStretch, VT_BOOL)
    SKIN_DISP_PROPERTY(CSkinButton, sideStretchWidth, VT_I4)
    SKIN_DISP_PROPERTY(CSkinButton, sideStretchHeight, VT_I4)
    SKIN_DISP_PROPERTY(CSkinButton, hotColorTransform, VT_BOOL)
	SKIN_DISP_PROPERTY(CSkinButton, iconImageUncheckedNormal, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, iconImageUncheckedHover, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, iconImageUncheckedDown, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, iconImageUncheckedDisabled, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, iconImageCheckedNormal, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, iconImageCheckedHover, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, iconImageCheckedDown, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, iconImageCheckedDisabled, VT_BSTR)

    SKIN_DISP_PROPERTY(CSkinButton, absIconImageUncheckedNormal, VT_BSTR)

	SKIN_DISP_PROPERTY(CSkinButton, iconMargin, VT_I4)
    SKIN_DISP_PROPERTY(CSkinButton, iconTopMargin, VT_I4)
    SKIN_DISP_PROPERTY(CSkinButton, iconColorTransform, VT_BOOL)
    SKIN_DISP_PROPERTY(CSkinButton, iconAlpha, VT_BOOL)
    SKIN_DISP_PROPERTY(CSkinButton, iconWidth, VT_I4)
    SKIN_DISP_PROPERTY(CSkinButton, iconHeight, VT_I4)
    SKIN_DISP_PROPERTY(CSkinButton, backIconImageUncheckedNormal, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, backIconImageUncheckedHover, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, backIconImageUncheckedDown, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, backIconImageUncheckedDisabled, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, backIconImageCheckedNormal, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, backIconImageCheckedHover, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, backIconImageCheckedDown, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, backIconImageCheckedDisabled, VT_BSTR)
    SKIN_DISP_PROPERTY(CSkinButton, backIconMargin, VT_I4)
    SKIN_DISP_PROPERTY(CSkinButton, backIconTopMargin, VT_I4)
    SKIN_DISP_PROPERTY(CSkinButton, backIconWidth, VT_I4)
    SKIN_DISP_PROPERTY(CSkinButton, backIconHeight, VT_I4)
	SKIN_DISP_PROPERTY(CSkinButton, labelFontSize, VT_I4)
	SKIN_DISP_PROPERTY(CSkinButton, labelFontWeight, VT_I4)
	SKIN_DISP_PROPERTY(CSkinButton, labelItalic, VT_BOOL)
	SKIN_DISP_PROPERTY(CSkinButton, labelUnderline, VT_BOOL)
    SKIN_DISP_PROPERTY(CSkinButton, labelNormalUnderline, VT_BOOL)
	SKIN_DISP_PROPERTY(CSkinButton, labelStrikeOut, VT_BOOL)
	SKIN_DISP_PROPERTY(CSkinButton, labelFontFamily, VT_BSTR)
	SKIN_DISP_PROPERTY(CSkinButton, labelNormalColor, VT_I4)
	SKIN_DISP_PROPERTY(CSkinButton, labelHoverColor, VT_I4)
	SKIN_DISP_PROPERTY(CSkinButton, labelDownColor, VT_I4)
	SKIN_DISP_PROPERTY(CSkinButton, labelDisabledColor, VT_I4)
	SKIN_DISP_PROPERTY(CSkinButton, labelWordBreak, VT_BOOL)
    SKIN_DISP_PROPERTY(CSkinButton, labelEndEllipsis, VT_BOOL)
	SKIN_DISP_PROPERTY(CSkinButton, labelSingleLine, VT_BOOL)
	SKIN_DISP_PROPERTY(CSkinButton, labelHorizAlign, VT_BSTR)
	SKIN_DISP_PROPERTY(CSkinButton, labelVertiAlign, VT_BSTR)
	SKIN_DISP_PROPERTY(CSkinButton, labelUnderlineMargin, VT_I4)
	SKIN_DISP_PROPERTY(CSkinButton, textMargin, VT_I4)
    SKIN_DISP_PROPERTY(CSkinButton, textPlacement, VT_BSTR)
	SKIN_DISP_PROPERTY(CSkinButton, hyperLink, VT_BOOL)
	SKIN_DISP_PROPERTY(CSkinButton, hyperLinkAddress, VT_BSTR)
	SKIN_DISP_PROPERTY(CSkinButton, tip, VT_BSTR)
	SKIN_DISP_PROPERTY(CSkinButton, cmdID, VT_I4)
	SKIN_DISP_PROPERTY(CSkinButton, useDefaultSize, VT_BOOL)
    SKIN_DISP_PROPERTY(CSkinButton, downOffset, VT_I4)
    SKIN_DISP_PROPERTY(CSkinButton, showBkAlways, VT_BOOL)
	SKIN_DISP_PROPERTY(CSkinButton, clickable, VT_BOOL)
	SKIN_DISP_PROPERTY(CSkinButton, handleTip, VT_BOOL)
	SKIN_DISP_PROPERTY(CSkinButton, maxTipWidth, VT_I4)

	SKIN_DISP_PROPERTY_ALIAS(CSkinButton, image, normalImage, VT_BSTR)
    SKIN_DISP_PROPERTY_ALIAS(CSkinButton, iconImage, iconImageUncheckedNormal, VT_BSTR)
    SKIN_DISP_PROPERTY_ALIAS(CSkinButton, absIconImage, absIconImageUncheckedNormal, VT_BSTR)
    SKIN_DISP_PROPERTY_ALIAS(CSkinButton, backIconImage, backIconImageUncheckedNormal, VT_BSTR)
    SKIN_DISP_PROPERTY_ALIAS(CSkinButton, iconImageUnchecked, iconImageUncheckedNormal, VT_BSTR)
    SKIN_DISP_PROPERTY_ALIAS(CSkinButton, backIconImageUnchecked, backIconImageUncheckedNormal, VT_BSTR)
    SKIN_DISP_PROPERTY_ALIAS(CSkinButton, iconImageChecked, iconImageCheckedNormal, VT_BSTR)
    SKIN_DISP_PROPERTY_ALIAS(CSkinButton, backIconImageChecked, backIconImageCheckedNormal, VT_BSTR)
    SKIN_DISP_PROPERTY_ALIAS(CSkinButton, labelValue, text, VT_BSTR)
	SKIN_DISP_PROPERTY_ALIAS(CSkinButton, label, text, VT_BSTR)

END_SKIN_DISPATCH_MAP(CSkinButton)

// Note: we add support for IID_ISkinButton to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {14703C10-706C-40CB-AC25-1F0FD76CD383}
static const IID IID_ISkinButton =
{ 0x14703C10, 0x706C, 0x40CB, { 0xAC, 0x25, 0x1F, 0xF, 0xD7, 0x6C, 0xD3, 0x83 } };

BEGIN_INTERFACE_MAP(CSkinButton, CSkinBase)
	INTERFACE_PART(CSkinButton, IID_ISkinButton, Dispatch)
END_INTERFACE_MAP()


// CSkinButton message handlers
BOOL CSkinButton::OnMouseEnter()
{
	if( GetDisabled()  
		|| (m_eSBStyle == BUTTONSTYLE_CHECK && m_nMouseState == BUTTON_STATE_DOWN) ) {
		return FALSE;
	}

	m_nMouseState = BUTTON_STATE_LIGHT;

	InvalidateRect();

	if(m_bHandleTip){
		CSkinBase* pParent = GetSkinParent();
		if(pParent != NULL){
			HWND hWnd = pParent->GetSkinHwnd();
			if(hWnd != NULL){
				::SendMessage(hWnd, WM_SKIN_MOUSEENTER, NULL, NULL);
			}
		}
	}
	else if(! m_strTip.IsEmpty()) {
		ShowToolTip(m_strTip, m_nMaxTipWidth);
	}

	return CSkinBase::OnMouseEnter();
}

BOOL CSkinButton::OnMouseLeave()
{
	if( GetDisabled()  
		|| (m_eSBStyle == BUTTONSTYLE_CHECK && m_nMouseState == BUTTON_STATE_DOWN) ) {
		return FALSE;
	}

	m_nMouseState = BUTTON_STATE_NORMAL;

	InvalidateRect();

	if(m_bHandleTip){
		CSkinBase* pParent = GetSkinParent();
		if(pParent != NULL){
			HWND hWnd = pParent->GetSkinHwnd();
			if(hWnd != NULL){
				::SendMessage(hWnd, WM_SKIN_MOUSELEAVE, NULL, NULL);
			}
		}
	}
	else if(! m_strTip.IsEmpty()) {
		PopToolTip();
	}

	return CSkinBase::OnMouseLeave();
}

BOOL CSkinButton::OnLButtonDown(LONG x, LONG y, UINT flag)
{
	if(!m_bClickable)
	{
		return FALSE;
	}

	if(	GetDisabled() 
		|| m_eSBStyle == BUTTONSTYLE_CHECK) {
		return FALSE;
	}

	if (IsPointInSkinRgn(x, y)) {
		SetCaptureSkin();
	} else {
		ReleaseCaptureSkin();
	}

	m_nMouseState = BUTTON_STATE_DOWN;

	InvalidateRect();

	return CSkinBase::OnLButtonDown(x, y, flag);
}

BOOL CSkinButton::OnLButtonUp(LONG x, LONG y, UINT flag)
{
	if(GetDisabled()) {
		return FALSE;
	}

	ReleaseCaptureSkin();
	if ( IsPointInSkinRgn(x, y) 
		&& m_nMouseState == BUTTON_STATE_DOWN) {
		OnClick(0);
	} else {
		OnMouseLeave();
	}

	return CSkinBase::OnLButtonUp(x, y, flag);
}

BOOL CSkinButton::OnClick(LONG iTab)
{
	if(GetDisabled()) {
		return FALSE;
	}

	if (m_eSBStyle == BUTTONSTYLE_CHECK){
		if (m_bChecked) {
			m_nMouseState = BUTTON_STATE_NORMAL;
		} else {
			m_nMouseState = BUTTON_STATE_DOWN;
		}
		m_bChecked = !m_bChecked;
	}else{
		m_nMouseState = BUTTON_STATE_NORMAL;
	}
	InvalidateRect();

	if (m_nCmdID != 0) {
		::SendMessage(GetSkinHwnd(), WM_COMMAND, m_nCmdID, NULL);
	}

	//转到超链接
	if (m_bHyperLink) {
		CString command;
		if (GetOpenCommand(command)) {
			command += m_strHyperLinkAddress;
			UINT ret = ::WinExec(CT2A(command), SW_SHOW);
		}
	}

	return CSkinBase::OnClick(0);
}

BOOL CSkinButton::GetOpenCommand(CString& command)
{
	HKEY			hkRoot = NULL;
	HKEY			hSubKey = NULL;
	TCHAR			ValueName[1024];
	DWORD			dwType;
	unsigned long	cbValueName = 1024;
	unsigned long	cbDataValue = 1024;
	BYTE	DataValue[1024];

	if(RegOpenKey(HKEY_CLASSES_ROOT,NULL, &hkRoot) == ERROR_SUCCESS) {  
		if(RegOpenKeyEx(hkRoot, _T("htmlfile\\shell\\open\\command"), 0, KEY_ALL_ACCESS, &hSubKey) == ERROR_SUCCESS) {
			RegEnumValue(hSubKey, 0, ValueName, &cbValueName, NULL, &dwType, DataValue, &cbDataValue);  
		}
	}
	RegCloseKey(hSubKey);
	RegCloseKey(hkRoot);
	command = (TCHAR*)DataValue;
	int pos = command.ReverseFind(_T('\"'));
	if (pos >= 0){
		command = command.Left(pos+1);
	}
	CString commandNoCase = command;
	commandNoCase.MakeLower();
	if (commandNoCase.Find(_T("firefox")) >= 0){
		command += _T(" -new-window ");
	}else{
		command += _T(" -new ");
	}
	return TRUE;
}

HCURSOR CSkinButton::GetSkinCursor(LPPOINT lpPoint)
{
	if (! GetDisabled()) {
		if (m_hCursor == NULL && ! m_strCursor.IsEmpty()){
			m_hCursor = GetCursorHelper(m_strCursor);
		}
		return m_hCursor;
	} else {
		return NULL;
	}
}

BOOL CSkinButton::OnSetFocus(CSkinBase* pOldFocus)
{
	InvalidateRect();
	return CSkinBase::OnSetFocus(pOldFocus);
}

BOOL CSkinButton::OnKillFocus(CSkinBase* pOldFocus)
{
	InvalidateRect();
	return CSkinBase::OnKillFocus(pOldFocus);
}

void CSkinButton::ShowToolTip(CString pszTooltip, LONG maxTipWidth )
{
    CSkinItem* pItem = GetSkinHwndItem();
    ASSERT(pItem != NULL);
    if (pItem == NULL)
        return;

    pItem->ShowToolTip(pszTooltip, GetSkinRect(), maxTipWidth);
}

void CSkinButton::PopToolTip()
{
    CSkinItem* pItem = GetSkinHwndItem();
    ASSERT(pItem != NULL);
    if (pItem == NULL)
        return;

    pItem->PopToolTip();
}

BOOL CSkinButton::UpdateLabelFont(HDC hDC)
{
	if (hDC == NULL)
		return FALSE;

	return m_textStyleNormal.UpdateFont(hDC);
}

CImageBase* CSkinButton::GetButtonImageHelper(CImageBase* pNormal, CImageBase* pHover, CImageBase* pDown)
{
    switch (m_nMouseState) 
    {
    case BUTTON_STATE_NORMAL:
        return pNormal;
    case BUTTON_STATE_LIGHT:
        return pHover;
    case BUTTON_STATE_DOWN:
        return pDown;
    }

    return NULL;
}

void CSkinButton::Draw(CDC* pDC, LPRECT lpInvalidRect, CRgn* pInvalidRgn)
{
	CRect skinRect = GetSkinRect();

	//绘制背景图片
	CImageBase* pImage = NULL;
	if (GetDisabled()) {
		pImage = m_pDisabledImage;
        if (pImage == NULL) {
            pImage = m_pNormalImage;
        }
	} else {
		if (! Getchecked()) {
            if (m_bShowBkAlways) {
                pImage = GetButtonImageHelper(m_pNormalImage, m_pHoverImage, m_pDownImage);
                if (pImage == NULL) {
                    pImage = m_pNormalImage;
                }
            } else {
                pImage = m_pNormalImage;
            }
		} else {
            if (m_bShowBkAlways) {
                pImage = GetButtonImageHelper(m_pDownImage, m_pHoverImage, m_pNormalImage);
                if (pImage == NULL) {
                    pImage = m_pDownImage;
                }
            } else {
                pImage = m_pDownImage;
            }
		}
	}
	if (pImage != NULL) {
		if (GetColorTransform()) {
            if (m_bHotColorTransform || m_nMouseState == BUTTON_STATE_NORMAL) {
			    pImage->Draw(*pDC, &skinRect, NULL, GetImageParam(), GetTransformedTransparentColor(), m_bAlpha, 
                    m_bSideStretch, m_lSideStretchWidth, m_lSideStretchHeight);
            } else {
                pImage->Draw(*pDC, &skinRect, NULL, NULL, GetTransparentColor(), m_bAlpha, 
                    m_bSideStretch, m_lSideStretchWidth, m_lSideStretchHeight);
            }
		} else {
            pImage->Draw(*pDC, &skinRect, NULL, NULL, GetTransparentColor(), m_bAlpha, 
                m_bSideStretch, m_lSideStretchWidth, m_lSideStretchHeight);
		}
	}

	int right = skinRect.left;
    int bottom = skinRect.top;
    CImageBase* pIconImage = NULL;
    if (Getchecked()) {
        if (GetDisabled()) {
            pIconImage = m_pIconImageCheckedDisabled;
            if (pIconImage == NULL) {
                pIconImage = m_pIconImageCheckedNormal;
            }
        } else {
            pIconImage = GetButtonImageHelper(m_pIconImageCheckedNormal, m_pIconImageCheckedHover, m_pIconImageCheckedDown);
            if (pIconImage == NULL)
                pIconImage = m_pIconImageCheckedNormal;
        }
    } else {
        if (GetDisabled()) {
            pIconImage = m_pIconImageUncheckedDisabled;
            if (pIconImage == NULL) {
                pIconImage = m_pIconImageUncheckedNormal;
            }
        } else {
            pIconImage = GetButtonImageHelper(m_pIconImageUncheckedNormal, m_pIconImageUncheckedHover, m_pIconImageUncheckedDown);
            if (pIconImage == NULL)
                pIconImage = m_pIconImageUncheckedNormal;
        }
    }
    if (pIconImage == NULL)
        pIconImage = m_pIconImageUncheckedNormal;
    if (m_pAbsIconImageUncheckedNormal != NULL)
        pIconImage = m_pAbsIconImageUncheckedNormal;
	//绘制icon
	if (pIconImage != NULL) {
		CRect iconRect = CRect(0, 0, m_szIcon.cx, m_szIcon.cy);
		iconRect.OffsetRect(skinRect.left, skinRect.top);
		int xOffset = m_nIconMargin;
		int yOffset = (skinRect.Height() - iconRect.Height()) / 2;
        if (m_nIconTopMargin >= 0)
            yOffset = m_nIconTopMargin;
		iconRect.OffsetRect(xOffset, yOffset);
		if (! Getchecked()) {
			if (m_nMouseState == BUTTON_STATE_DOWN) {
				iconRect.OffsetRect(m_nDownOffset, m_nDownOffset);
			}
		} else {
			if ( (m_nMouseState == BUTTON_STATE_NORMAL || m_nMouseState == BUTTON_STATE_LIGHT)) {
				iconRect.OffsetRect(m_nDownOffset, m_nDownOffset);
			}
		}
		//pIconImage->Draw(*pDC, &iconRect, NULL, NULL, GetTransparentColor());	//不变换
        if (m_bIconColorTransform) {
            pIconImage->Draw(*pDC, &iconRect, NULL, GetImageParam(), GetTransformedTransparentColor(), m_bIconAlpha);
        } else {
            pIconImage->Draw(*pDC, &iconRect, NULL, NULL, GetTransparentColor(), m_bIconAlpha);
        }
		right = iconRect.right;
        bottom = iconRect.bottom;
	}

    int left = skinRect.right;
    CImageBase* pBackIconImage = NULL;
    if (Getchecked()) {
        if (GetDisabled()) {
            pBackIconImage = m_pBackIconImageCheckedDisabled;
            if (pBackIconImage == NULL) {
                pBackIconImage = m_pBackIconImageCheckedNormal;
            }
        } else {
            pBackIconImage = GetButtonImageHelper(m_pBackIconImageCheckedNormal, m_pBackIconImageCheckedHover, m_pBackIconImageCheckedDown);
            if (pBackIconImage == NULL)
                pBackIconImage = m_pBackIconImageCheckedNormal;
        }
    } else {
        if (GetDisabled()) {
            pBackIconImage = m_pBackIconImageUncheckedDisabled;
            if (pBackIconImage == NULL) {
                pBackIconImage = m_pBackIconImageUncheckedNormal;
            }
        } else {
            pBackIconImage = GetButtonImageHelper(m_pBackIconImageUncheckedNormal, m_pBackIconImageUncheckedHover, m_pBackIconImageUncheckedDown);
            if (pBackIconImage == NULL)
                pBackIconImage = m_pBackIconImageUncheckedNormal;
        }
    }
    if (pBackIconImage == NULL)
        pBackIconImage = m_pBackIconImageUncheckedNormal;
    //绘制icon
    if (pBackIconImage != NULL) {
        CRect iconRect = CRect(0, 0, m_szBackIcon.cx, m_szBackIcon.cy);
        iconRect.OffsetRect((skinRect.right - iconRect.Width()), skinRect.top);
        int xOffset = - m_nBackIconMargin;
        int yOffset = (skinRect.Height() - iconRect.Height()) / 2;
        if (m_nBackIconTopMargin >= 0)
            yOffset = m_nBackIconTopMargin;
        iconRect.OffsetRect(xOffset, yOffset);
        if (! Getchecked()) {
            if (m_nMouseState == BUTTON_STATE_DOWN) {
                iconRect.OffsetRect(m_nDownOffset, m_nDownOffset);
            }
        } else {
            if ( (m_nMouseState == BUTTON_STATE_NORMAL || m_nMouseState == BUTTON_STATE_LIGHT)) {
                    iconRect.OffsetRect(m_nDownOffset, m_nDownOffset);
            }
        }
        //pBackIconImage->Draw(*pDC, &iconRect, NULL, NULL, GetTransparentColor());	//不变换
        if (m_bIconColorTransform) {
            pBackIconImage->Draw(*pDC, &iconRect, NULL, GetImageParam(), GetTransformedTransparentColor(), m_bIconAlpha);
        } else {
            pBackIconImage->Draw(*pDC, &iconRect, NULL, NULL, GetTransparentColor(), m_bIconAlpha);
        }
        left = iconRect.left;
    }

	//绘制文字
	if (m_strText.IsEmpty())
		return;
	CRect textRect = skinRect;
    if (m_enTextPlacement == BOTTOM) {
        textRect.top = bottom + m_nTextMargin;
        if (! Getchecked()) {
            if (m_nMouseState == BUTTON_STATE_DOWN) {
                textRect.OffsetRect(m_nDownOffset, 0);
                if (pIconImage == NULL) {
                    textRect.OffsetRect(0, m_nDownOffset);
                }
            }
        } else {
            if ((m_nMouseState == BUTTON_STATE_NORMAL || m_nMouseState == BUTTON_STATE_LIGHT)) {
                textRect.OffsetRect(m_nDownOffset, 0);
                if (pIconImage == NULL) {
                    textRect.OffsetRect(0, m_nDownOffset);
                }
            }
        }
    } else {
	    textRect.left = right + m_nTextMargin;
        if (pBackIconImage != NULL)
            textRect.right = left - m_nTextMargin;
	    if (! Getchecked()) {
		    if (m_nMouseState == BUTTON_STATE_DOWN) {
			    textRect.OffsetRect(0, m_nDownOffset);
                if (pIconImage == NULL) {
                    textRect.OffsetRect(m_nDownOffset, 0);
                }
		    }
	    } else {
		    if ((m_nMouseState == BUTTON_STATE_NORMAL || m_nMouseState == BUTTON_STATE_LIGHT)) {
			    textRect.OffsetRect(0, m_nDownOffset);
                if (pIconImage == NULL) {
                    textRect.OffsetRect(m_nDownOffset, 0);
                }
		    }
	    }
    }

	CRect realTextRect;
	if (! GetDisabled()) {
		LONG oldNormalColor = m_textStyleNormal.Getcolor();
		LONG newColor = oldNormalColor;
        VARIANT_BOOL newUnderline = GetlabelNormalUnderline();
		if (m_nMouseState == BUTTON_STATE_LIGHT) {
			newColor = m_textStyleHover.Getcolor();
            newUnderline = m_textStyleNormal.Getunderline();
		} else if (m_nMouseState == BUTTON_STATE_DOWN) {
			newColor = m_textStyleDown.Getcolor();
            newUnderline = m_textStyleNormal.Getunderline();
        }
		if (newColor != -1) {
            LONG newTransColor = newColor;
            if (m_bTextColorTransform) {
                if (m_bTextHotColorTransform || m_nMouseState == BUTTON_STATE_NORMAL)
                    GetEngine()->TransformColor(newColor, newTransColor);
            }
			m_textStyleNormal.Setcolor(newTransColor);
		}
        VARIANT_BOOL oldUnderline = m_textStyleNormal.Getunderline();
        m_textStyleNormal.Setunderline(newUnderline);
		if(m_textStyleNormal.IsFontChanged()){
			UpdateLabelFont(*pDC);
		}
		m_textStyleNormal.DrawText(*pDC, m_strText, &textRect, &realTextRect);
		m_textStyleNormal.Setcolor(oldNormalColor);
        m_textStyleNormal.Setunderline(oldUnderline);
	} else {
        LONG oldDisabledColor = m_textStyleDisabled.Getcolor();
        LONG transDisabledColor = oldDisabledColor;
        if (m_bTextColorTransform)
            GetEngine()->TransformColor(oldDisabledColor, transDisabledColor);
        m_textStyleDisabled.Setcolor(transDisabledColor);
		if(m_textStyleDisabled.IsFontChanged()){
			UpdateLabelFont(*pDC);
		}
		//vertiAlign;
		CComBSTR bstrVertiAlign;
		bstrVertiAlign.Attach(m_textStyleNormal.GetvertiAlign());
		CString strAlign = bstrVertiAlign;
		m_textStyleDisabled.SetvertiAlign(strAlign);

		//horizAlign
		CComBSTR bstrHorizAlign;
		bstrHorizAlign.Attach(m_textStyleNormal.GethorizAlign());
		strAlign = bstrHorizAlign;
		m_textStyleDisabled.SethorizAlign(strAlign);

		m_textStyleDisabled.DrawText(*pDC, m_strText, &textRect, &realTextRect);

        m_textStyleDisabled.Setcolor(oldDisabledColor);
	}

	CSkinBase* pFocus = NULL;
	BOOL bFocus = FALSE;
	if (GetFocusSkin(&pFocus) &&
		pFocus == this) {
		bFocus = TRUE;
	}
	if (bFocus) {
		realTextRect.InflateRect(1, 1);
		//pDC->DrawFocusRect(&realTextRect);   //DragonZ:去掉点击后获得焦点有虚框的效果
	}

	m_rcRealRect = realTextRect;
	m_rcRealRect.left = skinRect.left;

	if(m_bHandleTip)
	{
		this->Setwidth(m_rcRealRect.Width());
	}	
}

//////////////////////////////////////////////////////////////////////////
//check状态
//////////////////////////////////////////////////////////////////////////
VARIANT_BOOL CSkinButton::Getchecked(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return m_bChecked ? (VARIANT_TRUE) : (VARIANT_FALSE);
}

void CSkinButton::Setchecked(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	newVal = (newVal != FALSE);

	if (m_bChecked == newVal)
		return;

	m_bChecked = newVal;
	InvalidateRect();

    CSkinBase::OnSetCheck(m_bChecked);
}

VARIANT_BOOL CSkinButton::GettextColorTransform(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码

    return m_bTextColorTransform ? (VARIANT_TRUE) : (VARIANT_FALSE);
}

void CSkinButton::SettextColorTransform(VARIANT_BOOL newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    newVal = (newVal != FALSE);

    if (m_bTextColorTransform == newVal)
        return;

    m_bTextColorTransform = newVal;
    InvalidateRect();
}

VARIANT_BOOL CSkinButton::GettextHotColorTransform(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码

    return m_bTextHotColorTransform ? (VARIANT_TRUE) : (VARIANT_FALSE);
}

void CSkinButton::SettextHotColorTransform(VARIANT_BOOL newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    newVal = (newVal != FALSE);

    if (m_bTextHotColorTransform == newVal)
        return;

    m_bTextHotColorTransform = newVal;
    InvalidateRect();
}

//////////////////////////////////////////////////////////////////////////
//设置图片
//////////////////////////////////////////////////////////////////////////
BSTR CSkinButton::GetnormalImage()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strNormalImage.AllocSysString();
}

void CSkinButton::SetnormalImage(LPCTSTR newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    SetImageHelper(m_pNormalImage, m_strNormalImage, newVal, GetuseDefaultSize() != VARIANT_FALSE);
}

BSTR CSkinButton::GethoverImage()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strHoverImage.AllocSysString();
}

void CSkinButton::SethoverImage(LPCTSTR newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    SetImageHelper(m_pHoverImage, m_strHoverImage, newVal, GetuseDefaultSize() != VARIANT_FALSE);
}

BSTR CSkinButton::GetdownImage()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strDownImage.AllocSysString();
}

void CSkinButton::SetdownImage(LPCTSTR newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    SetImageHelper(m_pDownImage, m_strDownImage, newVal, GetuseDefaultSize() != VARIANT_FALSE);
}

BSTR CSkinButton::GetdisabledImage()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strDisabledImage.AllocSysString();
}

void CSkinButton::SetdisabledImage(LPCTSTR newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    SetImageHelper(m_pDisabledImage, m_strDisabledImage, newVal, GetuseDefaultSize() != VARIANT_FALSE);
}

VARIANT_BOOL CSkinButton::GetsideStretch(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码

    return m_bSideStretch ? (VARIANT_TRUE) : (VARIANT_FALSE);
}

void CSkinButton::SetsideStretch(VARIANT_BOOL newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    newVal = (newVal != FALSE);

    if (m_bSideStretch == newVal)
        return;

    m_bSideStretch = newVal;
    InvalidateRect();
}

LONG CSkinButton::GetsideStretchWidth(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_lSideStretchWidth;
}

void CSkinButton::SetsideStretchWidth(LONG newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    if (m_lSideStretchWidth == newVal)
        return;

    m_lSideStretchWidth = newVal;
    InvalidateRect();
}

LONG CSkinButton::GetsideStretchHeight(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_lSideStretchHeight;
}

void CSkinButton::SetsideStretchHeight(LONG newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    if (m_lSideStretchHeight == newVal)
        return;

    m_lSideStretchHeight = newVal;
    InvalidateRect();
}

VARIANT_BOOL CSkinButton::GethotColorTransform(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码

    return m_bHotColorTransform ? (VARIANT_TRUE) : (VARIANT_FALSE);
}

void CSkinButton::SethotColorTransform(VARIANT_BOOL newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    newVal = (newVal != FALSE);

    if (m_bHotColorTransform == newVal)
        return;

    m_bHotColorTransform = newVal;
    InvalidateRect();
}

VARIANT_BOOL CSkinButton::GeticonColorTransform(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码

    return m_bIconColorTransform ? (VARIANT_TRUE) : (VARIANT_FALSE);
}

void CSkinButton::SeticonColorTransform(VARIANT_BOOL newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    newVal = (newVal != FALSE);

    if (m_bIconColorTransform == newVal)
        return;

    m_bIconColorTransform = newVal;
    InvalidateRect();
}

VARIANT_BOOL CSkinButton::GeticonAlpha(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码

    return m_bIconAlpha ? (VARIANT_TRUE) : (VARIANT_FALSE);
}

void CSkinButton::SeticonAlpha(VARIANT_BOOL newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    newVal = (newVal != FALSE);

    if (m_bIconAlpha == newVal)
        return;

    m_bIconAlpha = newVal;
    InvalidateRect();
}

BSTR CSkinButton::GeticonImageUncheckedNormal()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strIconImageUncheckedNormal.AllocSysString();
}

void CSkinButton::SeticonImageUncheckedNormal(LPCTSTR newVal)
{
    SetImageHelper(m_pIconImageUncheckedNormal, m_strIconImageUncheckedNormal, newVal);
    if (m_szIcon.cx == 0 && 
    	m_szIcon.cy == 0 && 
    	m_pIconImageUncheckedNormal != NULL) {
    	m_szIcon.cx = m_pIconImageUncheckedNormal->Width();
    	m_szIcon.cy = m_pIconImageUncheckedNormal->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GeticonImageUncheckedHover()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strIconImageUncheckedHover.AllocSysString();
}

void CSkinButton::SeticonImageUncheckedHover(LPCTSTR newVal)
{
    SetImageHelper(m_pIconImageUncheckedHover, m_strIconImageUncheckedHover, newVal);
    if (m_szIcon.cx == 0 && 
        m_szIcon.cy == 0 && 
        m_pIconImageUncheckedHover != NULL) {
            m_szIcon.cx = m_pIconImageUncheckedHover->Width();
            m_szIcon.cy = m_pIconImageUncheckedHover->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GeticonImageUncheckedDown()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strIconImageUncheckedDown.AllocSysString();
}

void CSkinButton::SeticonImageUncheckedDown(LPCTSTR newVal)
{
    SetImageHelper(m_pIconImageUncheckedDown, m_strIconImageUncheckedDown, newVal);
    if (m_szIcon.cx == 0 && 
        m_szIcon.cy == 0 && 
        m_pIconImageUncheckedDown != NULL) {
            m_szIcon.cx = m_pIconImageUncheckedDown->Width();
            m_szIcon.cy = m_pIconImageUncheckedDown->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GeticonImageUncheckedDisabled()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strIconImageUncheckedDisabled.AllocSysString();
}

void CSkinButton::SeticonImageUncheckedDisabled(LPCTSTR newVal)
{
    SetImageHelper(m_pIconImageUncheckedDisabled, m_strIconImageUncheckedDisabled, newVal);
    if (m_szIcon.cx == 0 && 
        m_szIcon.cy == 0 && 
        m_pIconImageUncheckedDisabled != NULL) {
            m_szIcon.cx = m_pIconImageUncheckedDisabled->Width();
            m_szIcon.cy = m_pIconImageUncheckedDisabled->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GeticonImageCheckedNormal()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strIconImageCheckedNormal.AllocSysString();
}

void CSkinButton::SeticonImageCheckedNormal(LPCTSTR newVal)
{
    SetImageHelper(m_pIconImageCheckedNormal, m_strIconImageCheckedNormal, newVal);
    if (m_szIcon.cx == 0 && 
        m_szIcon.cy == 0 && 
        m_pIconImageCheckedNormal != NULL) {
            m_szIcon.cx = m_pIconImageCheckedNormal->Width();
            m_szIcon.cy = m_pIconImageCheckedNormal->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GeticonImageCheckedHover()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strIconImageCheckedHover.AllocSysString();
}

void CSkinButton::SeticonImageCheckedHover(LPCTSTR newVal)
{
    SetImageHelper(m_pIconImageCheckedHover, m_strIconImageCheckedHover, newVal);
    if (m_szIcon.cx == 0 && 
        m_szIcon.cy == 0 && 
        m_pIconImageCheckedHover != NULL) {
            m_szIcon.cx = m_pIconImageCheckedHover->Width();
            m_szIcon.cy = m_pIconImageCheckedHover->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GeticonImageCheckedDown()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strIconImageCheckedDown.AllocSysString();
}

void CSkinButton::SeticonImageCheckedDown(LPCTSTR newVal)
{
    SetImageHelper(m_pIconImageCheckedDown, m_strIconImageCheckedDown, newVal);
    if (m_szIcon.cx == 0 && 
        m_szIcon.cy == 0 && 
        m_pIconImageCheckedDown != NULL) {
            m_szIcon.cx = m_pIconImageCheckedDown->Width();
            m_szIcon.cy = m_pIconImageCheckedDown->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GeticonImageCheckedDisabled()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strIconImageCheckedDisabled.AllocSysString();
}

void CSkinButton::SeticonImageCheckedDisabled(LPCTSTR newVal)
{
    SetImageHelper(m_pIconImageCheckedDisabled, m_strIconImageCheckedDisabled, newVal);
    if (m_szIcon.cx == 0 && 
        m_szIcon.cy == 0 && 
        m_pIconImageCheckedDisabled != NULL) {
            m_szIcon.cx = m_pIconImageCheckedDisabled->Width();
            m_szIcon.cy = m_pIconImageCheckedDisabled->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GetabsIconImageUncheckedNormal()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strAbsIconImageUncheckedNormal.AllocSysString();
}

void CSkinButton::SetabsIconImageUncheckedNormal(LPCTSTR newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    CString filePathName = newVal;
    if (filePathName.IsEmpty()) {
        if (m_pAbsIconImageUncheckedNormal != NULL) {
            delete m_pAbsIconImageUncheckedNormal;
            m_pAbsIconImageUncheckedNormal = NULL;
        }
        m_strAbsIconImageUncheckedNormal.Empty();
        InvalidateRect();
        return;
    }

    CImageBase* pImage = new CImageType;
    if (! pImage->LoadFromFile(filePathName) ){
        delete pImage;
        pImage = NULL;
        return;
    }

    if (m_pAbsIconImageUncheckedNormal != NULL) {
        delete m_pAbsIconImageUncheckedNormal;
        m_pAbsIconImageUncheckedNormal = NULL;
    }
    m_pAbsIconImageUncheckedNormal = pImage;
    m_strAbsIconImageUncheckedNormal = newVal;

    if (m_szIcon.cx == 0 && 
        m_szIcon.cy == 0 && 
        m_pAbsIconImageUncheckedNormal != NULL) {
            m_szIcon.cx = m_pAbsIconImageUncheckedNormal->Width();
            m_szIcon.cy = m_pAbsIconImageUncheckedNormal->Height();
    }

    InvalidateRect();
}

LONG CSkinButton::GeticonMargin(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	return m_nIconMargin;
}

void CSkinButton::SeticonMargin(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (m_nIconMargin == newVal)
		return;

	m_nIconMargin = newVal;
	InvalidateRect();
}

LONG CSkinButton::GeticonTopMargin(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	return m_nIconTopMargin;
}

void CSkinButton::SeticonTopMargin(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (m_nIconTopMargin == newVal)
		return;

	m_nIconTopMargin = newVal;
	InvalidateRect();
}

LONG CSkinButton::GeticonWidth()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    return m_szIcon.cx;
}

void CSkinButton::SeticonWidth(LONG newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    if (m_szIcon.cx == newVal)
        return;

    m_szIcon.cx = newVal;
    InvalidateRect();
}

LONG CSkinButton::GeticonHeight()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    return m_szIcon.cy;
}

void CSkinButton::SeticonHeight(LONG newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    if (m_szIcon.cy == newVal)
        return;

    m_szIcon.cy = newVal;
    InvalidateRect();
}

LONG CSkinButton::GetbackIconMargin(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_nBackIconMargin;
}

void CSkinButton::SetbackIconMargin(LONG newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    if (m_nBackIconMargin == newVal)
        return;

    m_nBackIconMargin = newVal;
    InvalidateRect();
}

LONG CSkinButton::GetbackIconTopMargin(void)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_nBackIconTopMargin;
}

void CSkinButton::SetbackIconTopMargin(LONG newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    if (m_nBackIconTopMargin == newVal)
        return;

    m_nBackIconTopMargin = newVal;
    InvalidateRect();
}

BSTR CSkinButton::GetbackIconImageUncheckedNormal()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strBackIconImageUncheckedNormal.AllocSysString();
}

void CSkinButton::SetbackIconImageUncheckedNormal(LPCTSTR newVal)
{
    SetImageHelper(m_pBackIconImageUncheckedNormal, m_strBackIconImageUncheckedNormal, newVal);
    if (m_szBackIcon.cx == 0 && 
        m_szBackIcon.cy == 0 && 
        m_pBackIconImageUncheckedNormal != NULL) {
            m_szBackIcon.cx = m_pBackIconImageUncheckedNormal->Width();
            m_szBackIcon.cy = m_pBackIconImageUncheckedNormal->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GetbackIconImageUncheckedHover()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strBackIconImageUncheckedHover.AllocSysString();
}

void CSkinButton::SetbackIconImageUncheckedHover(LPCTSTR newVal)
{
    SetImageHelper(m_pBackIconImageUncheckedHover, m_strBackIconImageUncheckedHover, newVal);
    if (m_szBackIcon.cx == 0 && 
        m_szBackIcon.cy == 0 && 
        m_pBackIconImageUncheckedHover != NULL) {
            m_szBackIcon.cx = m_pBackIconImageUncheckedHover->Width();
            m_szBackIcon.cy = m_pBackIconImageUncheckedHover->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GetbackIconImageUncheckedDown()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strBackIconImageUncheckedDown.AllocSysString();
}

void CSkinButton::SetbackIconImageUncheckedDown(LPCTSTR newVal)
{
    SetImageHelper(m_pBackIconImageUncheckedDown, m_strBackIconImageUncheckedDown, newVal);
    if (m_szBackIcon.cx == 0 && 
        m_szBackIcon.cy == 0 && 
        m_pBackIconImageUncheckedDown != NULL) {
            m_szBackIcon.cx = m_pBackIconImageUncheckedDown->Width();
            m_szBackIcon.cy = m_pBackIconImageUncheckedDown->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GetbackIconImageUncheckedDisabled()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strBackIconImageUncheckedDisabled.AllocSysString();
}

void CSkinButton::SetbackIconImageUncheckedDisabled(LPCTSTR newVal)
{
    SetImageHelper(m_pBackIconImageUncheckedDisabled, m_strBackIconImageUncheckedDisabled, newVal);
    if (m_szBackIcon.cx == 0 && 
        m_szBackIcon.cy == 0 && 
        m_pBackIconImageUncheckedDisabled != NULL) {
            m_szBackIcon.cx = m_pBackIconImageUncheckedDisabled->Width();
            m_szBackIcon.cy = m_pBackIconImageUncheckedDisabled->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GetbackIconImageCheckedNormal()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strBackIconImageCheckedNormal.AllocSysString();
}

void CSkinButton::SetbackIconImageCheckedNormal(LPCTSTR newVal)
{
    SetImageHelper(m_pBackIconImageCheckedNormal, m_strBackIconImageCheckedNormal, newVal);
    if (m_szBackIcon.cx == 0 && 
        m_szBackIcon.cy == 0 && 
        m_pBackIconImageCheckedNormal != NULL) {
            m_szBackIcon.cx = m_pBackIconImageCheckedNormal->Width();
            m_szBackIcon.cy = m_pBackIconImageCheckedNormal->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GetbackIconImageCheckedHover()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strBackIconImageCheckedHover.AllocSysString();
}

void CSkinButton::SetbackIconImageCheckedHover(LPCTSTR newVal)
{
    SetImageHelper(m_pBackIconImageCheckedHover, m_strBackIconImageCheckedHover, newVal);
    if (m_szBackIcon.cx == 0 && 
        m_szBackIcon.cy == 0 && 
        m_pBackIconImageCheckedHover != NULL) {
            m_szBackIcon.cx = m_pBackIconImageCheckedHover->Width();
            m_szBackIcon.cy = m_pBackIconImageCheckedHover->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GetbackIconImageCheckedDown()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strBackIconImageCheckedDown.AllocSysString();
}

void CSkinButton::SetbackIconImageCheckedDown(LPCTSTR newVal)
{
    SetImageHelper(m_pBackIconImageCheckedDown, m_strBackIconImageCheckedDown, newVal);
    if (m_szBackIcon.cx == 0 && 
        m_szBackIcon.cy == 0 && 
        m_pBackIconImageCheckedDown != NULL) {
            m_szBackIcon.cx = m_pBackIconImageCheckedDown->Width();
            m_szBackIcon.cy = m_pBackIconImageCheckedDown->Height();
    }
    InvalidateRect();
}

BSTR CSkinButton::GetbackIconImageCheckedDisabled()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码
    return m_strBackIconImageCheckedDisabled.AllocSysString();
}

void CSkinButton::SetbackIconImageCheckedDisabled(LPCTSTR newVal)
{
    SetImageHelper(m_pBackIconImageCheckedDisabled, m_strBackIconImageCheckedDisabled, newVal);
    if (m_szBackIcon.cx == 0 && 
        m_szBackIcon.cy == 0 && 
        m_pBackIconImageCheckedDisabled != NULL) {
            m_szBackIcon.cx = m_pBackIconImageCheckedDisabled->Width();
            m_szBackIcon.cy = m_pBackIconImageCheckedDisabled->Height();
    }
    InvalidateRect();
}

LONG CSkinButton::GetbackIconWidth()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    return m_szBackIcon.cx;
}

void CSkinButton::SetbackIconWidth(LONG newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    if (m_szBackIcon.cx == newVal)
        return;

    m_szBackIcon.cx = newVal;
    InvalidateRect();
}

LONG CSkinButton::GetbackIconHeight()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    return m_szBackIcon.cy;
}

void CSkinButton::SetbackIconHeight(LONG newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    if (m_szBackIcon.cy == newVal)
        return;

    m_szBackIcon.cy = newVal;
    InvalidateRect();
}

//////////////////////////////////////////////////////////////////////////
//设置提示
//////////////////////////////////////////////////////////////////////////
BSTR CSkinButton::Gettip()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_strTip.AllocSysString();
}

void CSkinButton::Settip(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if (m_strTip.Compare(newVal) == 0)
		return;

	m_strTip = newVal;
}

//////////////////////////////////////////////////////////////////////////
//设置文字及其属性
//////////////////////////////////////////////////////////////////////////
LONG CSkinButton::GetlabelNormalColor()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_textStyleNormal.Getcolor();
}

void CSkinButton::SetlabelNormalColor(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_textStyleNormal.Setcolor(newVal);
	InvalidateRect();
}

LONG CSkinButton::GetlabelHoverColor()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_textStyleHover.Getcolor();
}

void CSkinButton::SetlabelHoverColor(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_textStyleHover.Setcolor(newVal);
	InvalidateRect();
}

LONG CSkinButton::GetlabelDownColor()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_textStyleDown.Getcolor();
}

void CSkinButton::SetlabelDownColor(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_textStyleDown.Setcolor(newVal);
	InvalidateRect();
}

LONG CSkinButton::GetlabelDisabledColor()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_textStyleDisabled.Getcolor();
}

void CSkinButton::SetlabelDisabledColor(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_textStyleDisabled.Setcolor(newVal);
	InvalidateRect();
}

LONG CSkinButton::GetlabelFontSize()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_textStyleNormal.GetfontSize();
}

void CSkinButton::SetlabelFontSize(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_textStyleNormal.SetfontSize(newVal);
	//DragonZ:Disabled状态下字体大小不变
	m_textStyleDisabled.SetfontSize(newVal);
	InvalidateRect();
}

LONG CSkinButton::GetlabelFontWeight(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	return m_textStyleNormal.GetfontWeight();
}

void CSkinButton::SetlabelFontWeight(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	m_textStyleNormal.SetfontWeight(newVal);
	InvalidateRect();
}

VARIANT_BOOL CSkinButton::GetlabelItalic()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_textStyleNormal.Getitalic();
}

void CSkinButton::SetlabelItalic(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_textStyleNormal.Setitalic(newVal);
	InvalidateRect();
}

VARIANT_BOOL CSkinButton::GetlabelUnderline()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_textStyleNormal.Getunderline();
}

void CSkinButton::SetlabelUnderline(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_textStyleNormal.Setunderline(newVal);
	InvalidateRect();
}

VARIANT_BOOL CSkinButton::GetlabelNormalUnderline()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
    return m_bLabelNormalUnderline ? (VARIANT_TRUE) : (VARIANT_FALSE);
}

void CSkinButton::SetlabelNormalUnderline(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
    newVal = (newVal != FALSE);

    if (m_bLabelNormalUnderline == newVal)
        return;

    m_bLabelNormalUnderline = newVal;
    InvalidateRect();
}

VARIANT_BOOL CSkinButton::GetlabelStrikeOut()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_textStyleNormal.GetstrikeOut();
}

void CSkinButton::SetlabelStrikeOut(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_textStyleNormal.SetstrikeOut(newVal);
	InvalidateRect();
}

BSTR CSkinButton::GetlabelFontFamily()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_textStyleNormal.GetfontFamily();
}

void CSkinButton::SetlabelFontFamily(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_textStyleNormal.SetfontFamily(newVal);
	InvalidateRect();
}

VARIANT_BOOL CSkinButton::GetlabelWordBreak()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_textStyleNormal.GetwordBreak();
}

void CSkinButton::SetlabelWordBreak(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_textStyleNormal.SetwordBreak(newVal);
	InvalidateRect();
}

VARIANT_BOOL CSkinButton::GetlabelEndEllipsis()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    return m_textStyleNormal.GetendEllipsis();
}

void CSkinButton::SetlabelEndEllipsis(VARIANT_BOOL newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    m_textStyleNormal.SetendEllipsis(newVal);
    InvalidateRect();
}

VARIANT_BOOL CSkinButton::GetlabelSingleLine()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_textStyleNormal.GetsingleLine();
}

void CSkinButton::SetlabelSingleLine(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_textStyleNormal.SetsingleLine(newVal);
	InvalidateRect();
}

BSTR CSkinButton::GetlabelHorizAlign()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_textStyleNormal.GethorizAlign();
}

void CSkinButton::SetlabelHorizAlign(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_textStyleNormal.SethorizAlign(newVal);
	InvalidateRect();
}

BSTR CSkinButton::GetlabelVertiAlign()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_textStyleNormal.GetvertiAlign();
}

void CSkinButton::SetlabelVertiAlign(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_textStyleNormal.SetvertiAlign(newVal);
	InvalidateRect();
}

LONG CSkinButton::GettextMargin(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	return m_nTextMargin;
}

void CSkinButton::SettextMargin(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	if (m_nTextMargin == newVal)
		return;

	m_nTextMargin = newVal;
	InvalidateRect();
}

BSTR CSkinButton::GettextPlacement()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    CString strResult;
    switch(m_enTextPlacement)
    {
    case TOP:
        strResult = _T("top");
        break;
    case RIGHT:
        strResult = _T("right");
        break;
    case LEFT:
        strResult = _T("left");
        break;
    case BOTTOM:
        strResult = _T("bottom");
        break;
    default:
        strResult = _T("");
        break;
    }

    return strResult.AllocSysString();
}

void CSkinButton::SettextPlacement(LPCTSTR newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    CString strTextPlacement = newVal;
    TEXT_PLACEMENT enTextPlacement = RIGHT;
    if (strTextPlacement.CompareNoCase(_T("top")) == 0) {
        enTextPlacement = TOP;
    } else if (strTextPlacement.CompareNoCase(_T("right")) == 0) {
        enTextPlacement = RIGHT;
    } else if (strTextPlacement.CompareNoCase(_T("left")) == 0) {
        enTextPlacement = LEFT;
    } else if (strTextPlacement.CompareNoCase(_T("bottom")) == 0) {
        enTextPlacement = BOTTOM;
    }

    if (m_enTextPlacement == enTextPlacement)
        return;

    m_enTextPlacement = enTextPlacement;

    InvalidateRect();
}

//////////////////////////////////////////////////////////////////////////
//超链接
//////////////////////////////////////////////////////////////////////////
VARIANT_BOOL CSkinButton::GethyperLink(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return m_bHyperLink ? (VARIANT_TRUE) : (VARIANT_FALSE);
}

void CSkinButton::SethyperLink(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	newVal = (newVal != FALSE);

	if (m_bHyperLink == newVal)
		return;

	m_bHyperLink = newVal;
	InvalidateRect();
}

BSTR CSkinButton::GethyperLinkAddress(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码
	return m_strHyperLinkAddress.AllocSysString();
}

void CSkinButton::SethyperLinkAddress(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if (m_strHyperLinkAddress.Compare(newVal) == 0)
		return;

	m_strHyperLinkAddress = newVal;
}

//////////////////////////////////////////////////////////////////////////
//命令ID
//////////////////////////////////////////////////////////////////////////
LONG CSkinButton::GetcmdID()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return m_nCmdID;
}

void CSkinButton::SetcmdID(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	if (m_nCmdID == newVal)
		return;

	m_nCmdID = newVal;
}

//////////////////////////////////////////////////////////////////////////
//按钮样式
//////////////////////////////////////////////////////////////////////////
BSTR CSkinButton::Getstyle()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	CString strResult;
	switch(m_eSBStyle)
	{
	case BUTTONSTYLE_NORMAL:
		strResult = _T("normal");
		break;
	case BUTTONSTYLE_CHECK:
		strResult = _T("check");
		break;
	default:
		strResult = _T("");
		break;
	}

	return strResult.AllocSysString();
}

void CSkinButton::Setstyle(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	CString strStyle = newVal;
	SKINBUTTON_STYLE enStyle = BUTTONSTYLE_NON;
	if (strStyle.CompareNoCase(_T("normal")) == 0){
		enStyle = BUTTONSTYLE_NORMAL;
	}else if (strStyle.CompareNoCase(_T("check")) == 0){
		enStyle = BUTTONSTYLE_CHECK;
	}
	if (m_eSBStyle == enStyle && enStyle != BUTTONSTYLE_NON)
		return;

	m_eSBStyle = enStyle;

	InvalidateRect();
}

VARIANT_BOOL CSkinButton::GetuseDefaultSize()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	return (m_uButtonFlag & UseDefaultSize) != 0 ? (VARIANT_TRUE) : (VARIANT_FALSE);
}

void CSkinButton::SetuseDefaultSize(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	newVal = (newVal != 0);
	if (newVal){
		m_uButtonFlag |= UseDefaultSize;
	}else{
		m_uButtonFlag &= ~UseDefaultSize;
	}
}

//下划线间距
LONG CSkinButton::GetlabelUnderlineMargin(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return m_textStyleNormal.GetunderlineMargin();
}

void CSkinButton::SetlabelUnderlineMargin(LONG newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	m_textStyleNormal.SetunderlineMargin(newVal);
	InvalidateRect();
}

LONG CSkinButton::GetdownOffset()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码

    return m_nDownOffset;
}

void CSkinButton::SetdownOffset(LONG newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    if (m_nDownOffset == newVal)
        return;

    m_nDownOffset = newVal;
    InvalidateRect();
}

VARIANT_BOOL CSkinButton::GetshowBkAlways()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加调度处理程序代码

    return m_bShowBkAlways ? (VARIANT_TRUE) : (VARIANT_FALSE);
}

void CSkinButton::SetshowBkAlways(VARIANT_BOOL newVal)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());

    // TODO: 在此添加属性处理程序代码
    newVal = (newVal != FALSE);

    if (m_bShowBkAlways == newVal)
        return;

    m_bShowBkAlways = newVal;
    InvalidateRect();
}

VARIANT_BOOL CSkinButton::Getclickable()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return m_bClickable ? (VARIANT_TRUE) : (VARIANT_FALSE);
}

void CSkinButton::Setclickable(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	newVal = (newVal != FALSE);

	m_bClickable = newVal;
}

VARIANT_BOOL CSkinButton::GethandleTip()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加调度处理程序代码

	return m_bHandleTip ? (VARIANT_TRUE) : (VARIANT_FALSE);
}

void CSkinButton::SethandleTip(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码
	newVal = (newVal != FALSE);

	m_bHandleTip = newVal;
}

LONG CSkinButton::GetmaxTipWidth( void )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return m_nMaxTipWidth;
}

void CSkinButton::SetmaxTipWidth( LONG newVal )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (newVal <=0 || newVal == m_nMaxTipWidth)
	{
		return;
	}

	m_nMaxTipWidth = newVal;
}