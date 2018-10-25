// MainVideoWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EasyPlayerProActiveXCtrl.h"
#include "MainVideoWnd.h"


// CMainVideoWnd �Ի���

IMPLEMENT_DYNAMIC(CMainVideoWnd, CDialogEx)

	CMainVideoWnd::CMainVideoWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainVideoWnd::IDD, pParent)
{
	m_pEasyLogo = new CImageEx;
	m_bFuulScreen = FALSE;
	m_pMainCtrl = NULL;
}

CMainVideoWnd::~CMainVideoWnd()
{
	if (m_pEasyLogo)
	{
		SafeDelete(m_pEasyLogo);
	}
}

void CMainVideoWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainVideoWnd, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CMainVideoWnd ��Ϣ�������


void CMainVideoWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CBrush brushBkgnd; 
	CRect rcClient;
	brushBkgnd.CreateSolidBrush(RGB(0, 0, 0));
	GetClientRect(&rcClient);
	dc.FillRect(&rcClient, &brushBkgnd);
	brushBkgnd.DeleteObject(); //�ͷŻ�ˢ 

	if ( m_pEasyLogo != NULL && !m_pEasyLogo->IsNull() )
	{
		int nStartX = (rcClient.Width()-184)/2;
		int nStartY =  (rcClient.Height()-184)/2;
		m_pEasyLogo->DrawImage(CDC::FromHandle(dc.m_hDC),nStartX,nStartY);
	}
}


BOOL CMainVideoWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_pEasyLogo)
	{
		m_pEasyLogo->LoadImage( ::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_PNG_EASYLOGO), TEXT("PNG"));
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMainVideoWnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnLButtonDblClk(nFlags, point);
	SetFullScreen();
}

void CMainVideoWnd::SetFullScreen()
{
	m_bFuulScreen = !m_bFuulScreen;

	if (m_bFuulScreen)
	{
		m_pMainCtrl = this->GetParent();
		this->SetParent(GetDesktopWindow());

		m_pMainCtrl->ShowWindow(SW_HIDE);
		//WS_POPUP
		//WS_CHILD 
		//						m_pwndVideoClip[i]->ModifyStyle(WS_CHILD,WS_POPUP,0);
		// 						m_pwndVideoClip[i]->SetWindowPos(&CWnd::wndBottom,//&CWnd::wndTopMost ,//
		// 							m_rcVideoFull.left, m_rcVideoFull.top, 
		// 							m_rcVideoFull.Width(), m_rcVideoFull.Height(), 
		// 							SWP_NOOWNERZORDER | SWP_SHOWWINDOW );

		this->GetClientRect(&m_rcVideoSingle);

		CRect m_rcVideoFull;
		int cx=GetSystemMetrics(SM_CXSCREEN);
		int cy=GetSystemMetrics(SM_CYSCREEN);
		m_rcVideoFull.left=0;
		m_rcVideoFull.top=0;
		m_rcVideoFull.bottom=cy;
		m_rcVideoFull.right=cx;

		this->ModifyStyle(WS_CHILD,WS_POPUP,0);

		WINDOWPLACEMENT wndpl;
		wndpl.length  = sizeof(WINDOWPLACEMENT);
		wndpl.flags   = 0;
		wndpl.showCmd = SW_SHOWNORMAL;
		wndpl.rcNormalPosition = m_rcVideoFull;
		// ��MoveWindow���������´�����󻯵�ʱ���޷��˳�ȫ������SetWindowPos��360������ϲ�����ʾȫ�� [2012-8-25  12:59 dingshuai]
		this->SetWindowPlacement(&wndpl);
		//		this->MoveWindow(m_rcVideoFull, TRUE);

		// 		this->SetWindowPos(&CWnd::wndTop ,//&CWnd::wndBottom,//
		// 			m_rcVideoFull.left, m_rcVideoFull.top, 
		// 			m_rcVideoFull.Width(), m_rcVideoFull.Height(), 
		// 			/*SWP_NOOWNERZORDER | */SWP_SHOWWINDOW );

	} 
	else
	{
		m_pMainCtrl->ShowWindow(SW_SHOW);

		this->SetParent(m_pMainCtrl);						
		this->ModifyStyle(WS_POPUP,WS_CHILD,0);

		WINDOWPLACEMENT wndpl;
		wndpl.length  = sizeof(WINDOWPLACEMENT);
		wndpl.flags   = 0;
		wndpl.showCmd = SW_SHOWNORMAL;
		wndpl.rcNormalPosition = m_rcVideoSingle;
		// ��MoveWindow���������´�����󻯵�ʱ���޷��˳�ȫ������SetWindowPos��360������ϲ�����ʾȫ�� [2012-8-25  12:59 dingshuai]
		this->SetWindowPlacement(&wndpl);

		// 		this->SetWindowPos(&CWnd::wndTop   ,//&CWnd::wndBottom,
		// 			m_rcVideoSingle.left, m_rcVideoSingle.top, 
		// 			m_rcVideoSingle.Width(), m_rcVideoSingle.Height(), 
		// 			SWP_NOOWNERZORDER | SWP_SHOWWINDOW );

	}

	//	this->SetFocus();
}
