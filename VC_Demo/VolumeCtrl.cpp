// VolumeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "Player.h"
#include "VolumeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVolumeCtrl

CVolumeCtrl::CVolumeCtrl() : m_brush(GetSysColor(COLOR_3DFACE)),
							 m_LightPen(PS_SOLID,1,RGB(255,255,255)),
							 m_ShadowPen(PS_SOLID,1,RGB(128,128,128))
{
}

CVolumeCtrl::~CVolumeCtrl()
{
}


BEGIN_MESSAGE_MAP(CVolumeCtrl, CSliderCtrl)
	//{{AFX_MSG_MAP(CVolumeCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVolumeCtrl message handlers

void CVolumeCtrl::OnPaint() 
{
	// ����Ĭ�ϵĴ��ڹ���Default()�����ؼ��ı�׼��״
	// call the defalut window procedure Default() to paint standard shape of the control
	Default();

	// Ĩ�������������������
	//clear other things exclude slider
	CWindowDC dc(this);
	CRect rcThumb, rcClient;
	GetThumbRect(&rcThumb);
	dc.ExcludeClipRect(&rcThumb);

	GetClientRect(&rcClient);
	dc.FillRect(&rcClient, &m_brush);

	// ��������
	//draw stomacher
	int half = rcThumb.Width() >> 1;
	rcClient.left   += 12 + half;
	rcClient.right  -= 12 + half;
	rcClient.top    += 3;
	rcClient.bottom -= 3;

	DrawTriangle(&dc, &rcClient);

	// Do not call CSliderCtrl::OnPaint() for painting messages
}


void CVolumeCtrl::DrawTriangle(CDC *pDC, CRect *prcDraw)
{
	// ���ƶ�����
	//pen moves to left-bottom
	pDC->MoveTo(prcDraw->left, prcDraw->bottom);

	// ѡ���������,������ԭ���Ļ���
	//select highlight pen, and save old pen
	CPen *pOldPen = pDC->SelectObject(&m_LightPen);
 
	// ���±�
	//draw bottom
	pDC->LineTo(prcDraw->BottomRight());

	// ���ұ�
	//draw right
	pDC->LineTo(prcDraw->right, prcDraw->top);

	// ѡ����Ӱ����
	//select hatched pen
	pDC->SelectObject(&m_ShadowPen);

	// ��б��
	//draw bevel edge
	pDC->LineTo(prcDraw->left, prcDraw->bottom); 

	// �ָ�ԭ���Ļ���
	//restore old pen
	pDC->SelectObject(pOldPen);
}


BOOL CVolumeCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// ֱ�ӷ���, ��ΪOnPaint��������һ��FillRect����, �������Ϊ��������
	//return directly, because there is a fillrect operation in OnPaint, it can be understood as erase background
    // û�б�Ҫ��������
	//no need to erase twice
	UNREFERENCED_PARAMETER(pDC);
	
	return TRUE;  // CSliderCtrl::OnEraseBkgnd(pDC);
}

BOOL CVolumeCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	CRect m_SliderRect;
	GetWindowRect(m_SliderRect);
	if(pMsg->message == WM_LBUTTONDOWN)
	{
		m_MousePt.x = pMsg->pt.x;
	}
	if(pMsg->message == WM_LBUTTONUP)
	{
		if(m_MousePt.x == pMsg->pt.x)
		{
			int max, min;
			this->GetRange(min, max);
			this->SetPos( min + (m_MousePt.x-m_SliderRect.left)*(max-min)/(m_SliderRect.right - m_SliderRect.left) );
			Invalidate();
		}			
	}

	return CSliderCtrl::PreTranslateMessage(pMsg);
}