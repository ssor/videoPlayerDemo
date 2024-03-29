// XColorStatic.cpp  Version 1.0
//
// Author:  Hans Dietrich
//          hdietrich2@hotmail.com
//
// This software is released into the public domain.
// You are free to use it in any way you like.
//
// This software is provided "as is" with no expressed
// or implied warranty.  I accept no liability for any
// damage or loss of business that this software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XColorStatic.h"
#include "FontSize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// CXColorStatic

BEGIN_MESSAGE_MAP(CXColorStatic, CStatic)
	//{{AFX_MSG_MAP(CXColorStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// ctor
CXColorStatic::CXColorStatic()
{
	m_rgbText       = GetSysColor(COLOR_BTNTEXT);
	m_rgbBackground = GetSysColor(COLOR_BTNFACE);
	m_pBrush        = new CBrush(m_rgbBackground);
	m_bBold         = FALSE;
	m_hIcon         = NULL;
	m_nXMargin		= 0;
	m_nYMargin      = 0;
	m_strText		= _T("");
}

///////////////////////////////////////////////////////////////////////////////
// dtor
CXColorStatic::~CXColorStatic()
{
	TRACE(_T("in CXColorStatic::~CXColorStatic\n"));

	if (m_font.GetSafeHandle())
	{
		m_font.DeleteObject();
	}

	if (m_pBrush)
	{
		m_pBrush->DeleteObject();
		delete m_pBrush;
	}
	m_pBrush = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// PreSubclassWindow
void CXColorStatic::PreSubclassWindow() 
{
	TRACE(_T("in CXColorStatic::PreSubclassWindow\n"));
	
	// get current font
	CFont* pFont = GetFont();
	if (!pFont)
	{
		HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		if (hFont == NULL)
		{
			hFont = (HFONT) GetStockObject(ANSI_VAR_FONT);
		}
		if (hFont)
		{
			pFont = CFont::FromHandle(hFont);
		}
	}
	ASSERT(pFont);
	ASSERT(pFont->GetSafeHandle());

	// create the font for this control
	LOGFONT lf;
	pFont->GetLogFont(&lf);
	m_font.CreateFontIndirect(&lf);
}

///////////////////////////////////////////////////////////////////////////////
// OnPaint
void CXColorStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(rect); 
	
	CDC		 memDC;	
	CBitmap  memBitmap;
	CBitmap* pOldBmp = NULL;

	memDC.CreateCompatibleDC(&dc);
	memBitmap.CreateCompatibleBitmap(&dc, rect.right, rect.bottom);
	pOldBmp = memDC.SelectObject(&memBitmap);

	memDC.SetTextColor(m_rgbText);
	memDC.SetBkColor(m_rgbBackground);
	memDC.SetBkMode(OPAQUE);
	memDC.SelectObject(m_pBrush);
	
	memDC.FillRect(&rect, m_pBrush);

	// cannot have both an icon and text

	if (m_hIcon)
	{
		int nIconX = ::GetSystemMetrics(SM_CXICON);
		int nIconY = ::GetSystemMetrics(SM_CYICON);

		rect.left = rect.left + (rect.Width() - nIconX) / 2;
		rect.top = rect.top + (rect.Height() - nIconY) / 2;

		memDC.DrawIcon(rect.left, rect.top, m_hIcon);
	}
	else
	{
		memDC.SelectObject(&m_font);

		// get static's text
//		GetWindowText(m_strText);

		UINT nFormat = 0;
		DWORD dwStyle = GetStyle();

		// set DrawText format from static style settings
		if (dwStyle & SS_CENTER)
		{
			nFormat |= DT_CENTER;
		}
		else if (dwStyle & SS_LEFT)
		{
			nFormat |= DT_LEFT;
		}
		else if (dwStyle & SS_RIGHT)
		{
			nFormat |= DT_RIGHT;
		}

		if (dwStyle & SS_CENTERIMAGE)	// vertical centering ==> single line only
		{
			nFormat |= DT_VCENTER | DT_SINGLELINE;
		}
		else
		{
			nFormat |= DT_WORDBREAK;
		}

		rect.left += m_nXMargin;
		rect.top  += m_nYMargin;
		memDC.DrawText(m_strText, rect, nFormat);
	}
	
	dc.BitBlt(rect.left, rect.top, rect.right, rect.bottom, &memDC, 0, 0, SRCCOPY);

	//�ͷ��ڴ����λͼ
	//release memory compatible bitmap
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
	memBitmap.DeleteObject();
}

///////////////////////////////////////////////////////////////////////////////
// OnEraseBkgnd
BOOL CXColorStatic::OnEraseBkgnd(CDC* pDC) 
{
	UNREFERENCED_PARAMETER(pDC);
	return TRUE; //CStatic::OnEraseBkgnd(pDC);
}

///////////////////////////////////////////////////////////////////////////////
// SetFont
void CXColorStatic::SetFont(LOGFONT *pLogFont, BOOL bRedraw /*= TRUE*/)
{
	ASSERT(pLogFont);
	if (!pLogFont)
	{
		return;
	}

	if (m_font.GetSafeHandle())
	{
		m_font.DeleteObject();
	}

	LOGFONT lf = *pLogFont;

	lf.lfWeight = m_bBold ? FW_BOLD : FW_NORMAL;

	m_font.CreateFontIndirect(&lf);

	if (bRedraw)
	{
		RedrawWindow();
	}
}

///////////////////////////////////////////////////////////////////////////////
// SetFont
void CXColorStatic::SetFont(LPCTSTR lpszFaceName, 
							int nPointSize, 
							BOOL bRedraw /*= TRUE*/)
{
	// null face name is ok - we will use current font

	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));

	if (lpszFaceName == NULL)
	{
		CFont *pFont = GetFont();
		ASSERT(pFont);
		pFont->GetLogFont(&lf);
	}
	else
	{
		_tcsncpy(lf.lfFaceName, lpszFaceName, sizeof(lf.lfFaceName)/sizeof(TCHAR)-1);
	}

	lf.lfHeight = GetFontHeight(nPointSize);

	SetFont(&lf, bRedraw);
}

///////////////////////////////////////////////////////////////////////////////
// SetFont
void CXColorStatic::SetFont(CFont *pFont, BOOL bRedraw /*= TRUE*/)
{
	ASSERT(pFont);
	if (!pFont)
	{
		return;
	}

	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));

	pFont->GetLogFont(&lf);

	SetFont(&lf, bRedraw);
}

///////////////////////////////////////////////////////////////////////////////
// SetTextColor
void CXColorStatic::SetTextColor(COLORREF rgb, BOOL bRedraw /*= TRUE*/) 
{ 
	m_rgbText = rgb; 
	if (bRedraw)
	{
		RedrawWindow();
	}
}

///////////////////////////////////////////////////////////////////////////////
// SetBold
void CXColorStatic::SetBold(BOOL bFlag, BOOL bRedraw /*= TRUE*/)
{ 
	m_bBold = bFlag;

	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));

	CFont *pFont = GetFont();
	ASSERT(pFont);
	pFont->GetLogFont(&lf);

	lf.lfWeight = m_bBold ? FW_BOLD : FW_NORMAL;

	SetFont(&lf, bRedraw);
}

///////////////////////////////////////////////////////////////////////////////
// SetBackgroundColor
void CXColorStatic::SetBackgroundColor(COLORREF rgb, BOOL bRedraw /*= TRUE*/) 
{ 
	m_rgbBackground = rgb; 
	if (m_pBrush)
	{
		m_pBrush->DeleteObject();
		delete m_pBrush;
	}
	m_pBrush = new CBrush(m_rgbBackground);
	if (bRedraw)
	{
		RedrawWindow();
	}
}

///////////////////////////////////////////////////////////////////////////////
// SetIcon
void CXColorStatic::SetIcon(HICON hIcon, BOOL bRedraw /*= TRUE*/)
{
	ASSERT(hIcon);

	m_hIcon = hIcon;
	if (bRedraw)
	{
		RedrawWindow();
	}
}
