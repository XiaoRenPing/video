#include "stdafx.h"
#include "EasyPlayerPro.h"
#include "EasyPlayerProDlg.h"
#include "afxdialogex.h"
#include "DlgAbout.h"
#include "xmlConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "./libEasyPlayerPro/libEasyPlayerPro.lib")


#pragma comment (lib, "Version.lib")
wchar_t wszApplicationVersion[64] = {0};
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLivePlayerDlg �Ի���




CLivePlayerDlg::CLivePlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLivePlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	M_bMaxWnd = FALSE;
	InitialComponents();
}

void CLivePlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLivePlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_WINDOW_MAXIMIZED, OnWindowMaximized)
	ON_MESSAGE(WM_EXIT_FULLSCREEN, OnExitFullScreen)
	ON_CBN_SELCHANGE(IDC_COMBO_SPLIT_SCREEN, &CLivePlayerDlg::OnCbnSelchangeComboSplitScreen)
	ON_CBN_SELCHANGE(IDC_COMBO_RENDER_FORMAT, &CLivePlayerDlg::OnCbnSelchangeComboRenderFormat)
	ON_BN_CLICKED(IDC_CHECK_SHOWNTOSCALE, &CLivePlayerDlg::OnBnClickedCheckShowntoscale)
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_CHECKMULTIPLEX, &CLivePlayerDlg::OnBnClickedCheckmultiplex)
	ON_BN_CLICKED(IDC_CHECK_FULLSCREEN, &CLivePlayerDlg::OnBnClickedCheckFullscreen)
	ON_WM_CTLCOLOR()
	ON_WM_HSCROLL()

END_MESSAGE_MAP()


// CLivePlayerDlg ��Ϣ�������

BOOL CLivePlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetBackgroundColor(RGB(0x5b,0x5b,0x5b));
	MoveWindow(0, 0, 1200, 640);

	CreateComponents();

    int ret = libEasyPlayerPro_Activate("64687538665969576B5A73416E727062704556687065354659584E35554778686557567955484A764C6D56345A56634D5671442F70654E4659584E355247467964326C755647566862556C7A5647686C516D567A644541794D4445345A57467A65513D3D");
    if(ret != EASY_ACTIVATE_SUCCESS)
    {
        MessageBox(TEXT("Active Error! Please contact support@easydarwin.org !"), TEXT("OK"), MB_OK);
    }
	
	XMLConfig		xmlConfig;
	memset(&proConfig, 0x00, sizeof(PRO_CONFIG_T));
	xmlConfig.LoadConfig(XML_CONFIG_FILENAME, &proConfig);


	if (NULL!=pVideoWindow)		pVideoWindow->channels		=	proConfig.splitWindow;
	if (NULL != pComboxSplitScreen)
	{
		if (4 == proConfig.splitWindow)	pComboxSplitScreen->SetCurSel(0);
		else if (8 == proConfig.splitWindow)	pComboxSplitScreen->SetCurSel(1);
		else if (9 == proConfig.splitWindow)	pComboxSplitScreen->SetCurSel(2);
		else if (16 == proConfig.splitWindow)	pComboxSplitScreen->SetCurSel(3);
	}


	if (NULL!=pChkShownToScale)		pChkShownToScale->SetCheck(proConfig.scale);
	if (NULL!=pChkMultiplex)		pChkMultiplex->SetCheck(proConfig.multiple);
	if (NULL!=pChkFullScreen)		pChkFullScreen->SetCheck(proConfig.fullScreen);
	if (proConfig.fullScreen==0x01)
	{
		FullScreen();
	}

	if (NULL != pVideoWindow && NULL!=pVideoWindow->pDlgVideo)
	{
		const char url_header[4][16] = {"rtsp://", "rtmp://", "http://", "file://"};
		int idx = 0;
		for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
		{
			pVideoWindow->pDlgVideo[i].SetURL((char *)url_header[idx++], 0, 1, 1, 1, 3, 1, 0);

			if (idx>=4)	idx = 0;
		}

		int cfg_channel_num = sizeof(proConfig.channel)/sizeof(proConfig.channel[0]);
		for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
		{
			if (i>=cfg_channel_num)		break;

			if ( (int)strlen(proConfig.channel[i].url) < 10)		continue;

			pVideoWindow->pDlgVideo[i].SetURL(proConfig.channel[i].url, 
				proConfig.scale, proConfig.channel[i].showOSD, 
				proConfig.channel[i].protocol, proConfig.multiple, 
				proConfig.channel[i].cache, proConfig.channel[i].showToolbar,
				proConfig.channel[i].autoPlay);
		}
		/*
		FILE *f = fopen("url.txt", "rb");
		if (NULL != f)
		{
			int idx = 0;
			char szURL[128] = {0};
			while (! feof(f) && idx+1<_SURV_MAX_WINDOW_NUM)
			{
				memset(szURL, 0x00, sizeof(szURL));
				fgets(szURL, sizeof(szURL), f);

				if (0 != strcmp(szURL, "\0"))
				{
					pVideoWindow->pDlgVideo[idx++].SetURL(szURL);
				}
			}
		}
		*/
	}





	OnCbnSelchangeComboRenderFormat();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLivePlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
#if 0
		CAboutDlg dlgAbout;
		CWnd *pWnd = dlgAbout.GetDlgItem(IDC_STATIC_VER);
		if (NULL != pWnd)
		{
			pWnd->SetWindowTextW(wszApplicationVersion);
		}
		dlgAbout.DoModal();
#else
		CDlgAbout	dlgAbout(wszApplicationVersion);
		dlgAbout.DoModal();
#endif
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLivePlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLivePlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CLivePlayerDlg::DestroyWindow()
{
	libEasyPlayerPro_Release(&playerHandle);
	DeleteComponents();

	return CDialogEx::DestroyWindow();
}


LRESULT CLivePlayerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (WM_PAINT == message || WM_SIZE==message)
	{
		UpdateComponents();
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}



void	CLivePlayerDlg::InitialComponents()
{
	pComboxSplitScreen	=	NULL;
	pComboxRenderFormat	=	NULL;
	pVideoWindow		=	NULL;
	pChkShownToScale	=	NULL;
	pChkMultiplex		=	NULL;
	pChkFullScreen		=	NULL;
	pStaticVolume		=	NULL;
	pSliderCtrlVolume	=	NULL;
	pStaticCopyright	=	NULL;

	RenderFormat	=	RENDER_FORMAT_RGB24_GDI;//RGB565

	m_BrushStatic = ::CreateSolidBrush(RGB(0x5b,0x5b,0x5b));

	libEasyPlayerPro_Create(&playerHandle, 128);
}

void	CLivePlayerDlg::CreateComponents()
{
	__CREATE_WINDOW(pComboxSplitScreen, CComboBox,		IDC_COMBO_SPLIT_SCREEN);
	__CREATE_WINDOW(pComboxRenderFormat, CComboBox,		IDC_COMBO_RENDER_FORMAT);
	__CREATE_WINDOW(pChkShownToScale, CButton,		IDC_CHECK_SHOWNTOSCALE);
	__CREATE_WINDOW(pChkMultiplex, CButton,		IDC_CHECKMULTIPLEX);
	__CREATE_WINDOW(pChkFullScreen, CButton,		IDC_CHECK_FULLSCREEN);
	__CREATE_WINDOW(pStaticVolume, CStatic,		IDC_STATIC_VOLUME);
	__CREATE_WINDOW(pSliderCtrlVolume, CSliderCtrl,		IDC_SLIDER_VOLUME);
	
	__CREATE_WINDOW(pStaticCopyright, CStatic,		IDC_STATIC_COPYRIGHT);

	pStaticCopyright->ShowWindow(FALSE);
	GetApplicationVersion(wszApplicationVersion);
	SetWindowText(wszApplicationVersion);

	if (NULL != pChkShownToScale)		pChkShownToScale->SetWindowText(TEXT("��������ʾ"));
	if (NULL != pChkMultiplex)			pChkMultiplex->SetWindowText(TEXT("����Դ"));
	if (NULL != pChkFullScreen)			pChkFullScreen->SetWindowText(TEXT("ȫ��"));
	if (NULL != pSliderCtrlVolume)	
	{
		pSliderCtrlVolume->SetRange(0, 100);

		int volume = libEasyPlayerPro_GetAudioVolume(playerHandle);
		pSliderCtrlVolume->SetPos(volume);
	}

	if (NULL == pVideoWindow)
	{
		pVideoWindow = new VIDEO_NODE_T;
		pVideoWindow->fullscreen    = false;
		pVideoWindow->maximizedId	=	-1;
		pVideoWindow->selectedId	=	-1;
		pVideoWindow->channels		=	4;
		if (pVideoWindow->channels>_SURV_MAX_WINDOW_NUM)	pVideoWindow->channels=_SURV_MAX_WINDOW_NUM;
		pVideoWindow->pDlgVideo	=	new CDlgVideo[_SURV_MAX_WINDOW_NUM];//gAppInfo.maxchannels
		for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
		{
			pVideoWindow->pDlgVideo[i].SetWindowId(i);
			pVideoWindow->pDlgVideo[i].Create(IDD_DIALOG_VIDEO, this);
			pVideoWindow->pDlgVideo[i].ShowWindow(SW_HIDE);
		}
	}

	if (NULL != pComboxSplitScreen)
	{
		pComboxSplitScreen->AddString(TEXT("4����"));
		pComboxSplitScreen->AddString(TEXT("8����"));
		pComboxSplitScreen->AddString(TEXT("9����"));
		pComboxSplitScreen->AddString(TEXT("16����"));
		//pComboxSplitScreen->AddString(TEXT("36����"));
		//pComboxSplitScreen->AddString(TEXT("64����"));
		pComboxSplitScreen->SetCurSel(0);
	}
	if (NULL != pComboxRenderFormat)
	{
		pComboxRenderFormat->AddString(TEXT("YV12"));
		pComboxRenderFormat->AddString(TEXT("YUY2"));
		pComboxRenderFormat->AddString(TEXT("RGB565"));
		pComboxRenderFormat->AddString(TEXT("X8R8G8B8"));
		pComboxRenderFormat->AddString(TEXT("GDI"));

		pComboxRenderFormat->SetCurSel(4);
	}
}
void	CLivePlayerDlg::UpdateComponents()
{
	CRect	rcClient;
	GetClientRect(&rcClient);
	if (rcClient.IsRectEmpty())		return;

	CRect	rcVideo;
	rcVideo.SetRect(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom-(proConfig.fullScreen?0:30));
	UpdateVideoPosition(&rcVideo);

	CRect	rcSplitScreen;
	rcSplitScreen.SetRect(rcClient.left+5, rcVideo.bottom+3, rcClient.left+100, rcVideo.bottom+3+90);
	__MOVE_WINDOW(pComboxSplitScreen, rcSplitScreen);

	CRect	rcRenderFormat;
	rcRenderFormat.SetRect(rcSplitScreen.right+5, rcSplitScreen.top, rcSplitScreen.right+5+100, rcSplitScreen.bottom);
	__MOVE_WINDOW(pComboxRenderFormat, rcRenderFormat);

	CRect	rcShownToScale;
	rcShownToScale.SetRect(rcRenderFormat.right+10, rcRenderFormat.top, rcRenderFormat.right+10+110, rcRenderFormat.top+30);
	__MOVE_WINDOW(pChkShownToScale, rcShownToScale);

	CRect	rcMultiplex;
	rcMultiplex.SetRect(rcShownToScale.right+10, rcShownToScale.top, rcShownToScale.right+10+70, rcShownToScale.bottom);
	__MOVE_WINDOW(pChkMultiplex, rcMultiplex);

	CRect	rcFullScreen;
	rcFullScreen.SetRect(rcMultiplex.right+10, rcMultiplex.top, rcMultiplex.right+10+70, rcMultiplex.bottom);
	__MOVE_WINDOW(pChkFullScreen, rcFullScreen);
	
	CRect	rcVolume;
	rcVolume.SetRect(rcFullScreen.right+10, rcFullScreen.top+5, rcFullScreen.right+10+35, rcFullScreen.bottom);
	__MOVE_WINDOW(pStaticVolume, rcVolume);
	rcVolume.SetRect(rcVolume.right+2, rcVolume.top, rcVolume.right+2+160, rcVolume.bottom-3);
	__MOVE_WINDOW(pSliderCtrlVolume, rcVolume);


	CRect	rcCopyright;
	rcCopyright.SetRect(rcClient.right-200, rcSplitScreen.top+5, rcClient.right-2, rcClient.bottom);
	__MOVE_WINDOW(pStaticCopyright, rcCopyright);
}
void	CLivePlayerDlg::DeleteComponents()
{
	if (NULL != pVideoWindow)
	{
		if (NULL != pVideoWindow->pDlgVideo)
		{
			for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
			{
				pVideoWindow->pDlgVideo[i].DestroyWindow();
			}
			delete []pVideoWindow->pDlgVideo;
			pVideoWindow->pDlgVideo = NULL;
		}
		delete pVideoWindow;
		pVideoWindow = NULL;
	}

	DeleteObject(m_BrushStatic);
}


void	CLivePlayerDlg::UpdateVideoPosition(LPRECT lpRect)
{
	CRect rcClient;
	if (NULL == lpRect)
	{
		GetClientRect(&rcClient);
		lpRect = &rcClient;
	}

	if (NULL == pVideoWindow)		return;

	//CRect rcClient;
	rcClient.CopyRect(lpRect);

	CRect rcTmp;
	rcTmp.SetRect(rcClient.left, rcClient.top, rcClient.left+rcClient.Width()/2, rcClient.top+rcClient.Height()/2);

	//

	if (pVideoWindow->maximizedId==-1)
	{
		int nTimes = 2;
		int nLeft = lpRect->left;
		int nTop  = lpRect->top;

		for (int i=pVideoWindow->channels; i<_SURV_MAX_WINDOW_NUM; i++)
		{
			if (pVideoWindow->pDlgVideo[i].IsWindowVisible())
				pVideoWindow->pDlgVideo[i].ShowWindow(SW_HIDE);
		}

		switch (pVideoWindow->channels)
		{
		case 4:
		case 9:
		case 16:
		case 25:
		case 36:
		case 64:
		default:
			{
				nTimes = 2;
				if (pVideoWindow->channels == 4)		nTimes	=	2;
				if (pVideoWindow->channels == 9)		nTimes	=	3;
				if (pVideoWindow->channels == 16)		nTimes	=	4;
				if (pVideoWindow->channels == 25)		nTimes	=	5;
				if (pVideoWindow->channels == 36)		nTimes	=	6;
				if (pVideoWindow->channels == 64)		nTimes	=	8;

				RECT rcTmp;
				SetRectEmpty(&rcTmp);

				int n = 0;//videoPatrol.patrolStartId;
				for (int i = 0; i < nTimes; i++)
				{
					for (int j = 0; j < nTimes; j ++)
					{
						//SetRect(&rcTmp, nLeft, nTop, nLeft + imgSize.cx / nTimes, nTop + imgSize.cy / nTimes);
						SetRect(&rcTmp, nLeft, nTop, nLeft + rcClient.Width() / nTimes, nTop + rcClient.Height() / nTimes);
						//CopyRect(&vidRenderHandle[n].drawvid.rect, &rcTmp);

						if (j+1==nTimes && rcTmp.right<rcClient.right)
						{
							rcTmp.right = rcClient.right;
						}
						if (i+1==nTimes && rcTmp.bottom<rcClient.bottom)
						{
							rcTmp.bottom = rcClient.bottom;
						}


						if (! pVideoWindow->pDlgVideo[n].IsWindowVisible())
						{
							pVideoWindow->pDlgVideo[n].ShowWindow(SW_SHOW);
						}

						pVideoWindow->pDlgVideo[n].MoveWindow(&rcTmp);

						n ++;

						nLeft += rcClient.Width() / nTimes;
					}
					nLeft = rcClient.left;
					nTop  += (rcClient.Height()) / nTimes;
				}
			}
			break;
		case 6:		//6��??��
			{
				int nWidth = rcClient.Width() / 3;
				int nHeight= rcClient.Height()/ 3;

				int nRight = 0;
				int nBottom= 0;
				if (rcClient.right > nWidth*3)	nRight = rcClient.Width()-nWidth*3;
				if (rcClient.bottom> nHeight*3)	nBottom= rcClient.Height()-nHeight*3;
			
				nLeft = rcClient.left;
				nTop  = rcClient.top+nHeight*2;
				for (int i=3; i<6; i++)
				{
					rcTmp.SetRect(nLeft, nTop, nLeft+nWidth, nTop+nHeight);
					if (i+1==6)			rcTmp.right += nRight;
					if (nBottom > 0)	rcTmp.bottom += nBottom;
					pVideoWindow->pDlgVideo[i].MoveWindow(&rcTmp);
					if (! pVideoWindow->pDlgVideo[i].IsWindowVisible())
						pVideoWindow->pDlgVideo[i].ShowWindow(SW_SHOW);
				
					nLeft += nWidth;
				}
				nLeft -= nWidth;
				nTop  = rcClient.top;
				for (int i=1; i<3; i++)
				{
					rcTmp.SetRect(nLeft, nTop, nLeft+nWidth, nTop+nHeight);
					if (nRight>0)	rcTmp.right += nRight;
					pVideoWindow->pDlgVideo[i].MoveWindow(&rcTmp);
					if (! pVideoWindow->pDlgVideo[i].IsWindowVisible())
						pVideoWindow->pDlgVideo[i].ShowWindow(SW_SHOW);
					nTop += nHeight;
				}
			
				rcTmp.SetRect(rcClient.left, rcClient.top, rcTmp.left, rcTmp.bottom);
				pVideoWindow->pDlgVideo[0].MoveWindow(&rcTmp);
				if (! pVideoWindow->pDlgVideo[0].IsWindowVisible())
					pVideoWindow->pDlgVideo[0].ShowWindow(SW_SHOW);
			}
			break;
		case 8:		//8����
			{

				int nWidth = rcClient.Width() / 4;
				int nHeight= rcClient.Height()/ 4;

				int nRight = 0;
				int nBottom= 0;
				if (rcClient.right > nWidth*4)	nRight = rcClient.Width()-nWidth*4;
				if (rcClient.bottom> nHeight*4)	nBottom= rcClient.Height()-nHeight*4;

				nLeft = rcClient.left;
				nTop  = rcClient.top+nHeight*3;
				for (int i=4; i<8; i++)
				{
					rcTmp.SetRect(nLeft, nTop, nLeft+nWidth, nTop+nHeight);
					if (i+1==8)			rcTmp.right += nRight;
					if (nBottom > 0)	rcTmp.bottom += nBottom;
					pVideoWindow->pDlgVideo[i].MoveWindow(&rcTmp);
					if (! pVideoWindow->pDlgVideo[i].IsWindowVisible())
							pVideoWindow->pDlgVideo[i].ShowWindow(SW_SHOW);

					nLeft += nWidth;
				}
				nLeft -= nWidth;
				nTop  = rcClient.top;
				for (int i=1; i<4; i++)
				{
					rcTmp.SetRect(nLeft, nTop, nLeft+nWidth, nTop+nHeight);
					if (nRight>0)	rcTmp.right += nRight;
					pVideoWindow->pDlgVideo[i].MoveWindow(&rcTmp);
					if (! pVideoWindow->pDlgVideo[i].IsWindowVisible())
						pVideoWindow->pDlgVideo[i].ShowWindow(SW_SHOW);
					nTop += nHeight;
				}

				rcTmp.SetRect(rcClient.left, rcClient.top, rcTmp.left, rcTmp.bottom);
				pVideoWindow->pDlgVideo[0].MoveWindow(&rcTmp);
				if (! pVideoWindow->pDlgVideo[0].IsWindowVisible())
					pVideoWindow->pDlgVideo[0].ShowWindow(SW_SHOW);

			}
			break;
		}

		for (int vid=0; vid<_SURV_MAX_WINDOW_NUM; vid++)
		{
			//pVideoWindow->pDlgVideo[vid].SetSelectedChannel(pVideoWindow->selectedId==vid);
		}
	}
	else
	{
		for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
		{
			if (pVideoWindow->pDlgVideo[i].IsWindowVisible() && i!=pVideoWindow->maximizedId)
			{
				pVideoWindow->pDlgVideo[i].ShowWindow(SW_HIDE);
			}
		}
		rcTmp.SetRect(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
		pVideoWindow->pDlgVideo[pVideoWindow->maximizedId].ShowWindow(SW_SHOW);
		pVideoWindow->pDlgVideo[pVideoWindow->maximizedId].MoveWindow(&rcTmp);
	}
}



LRESULT CLivePlayerDlg::OnWindowMaximized(WPARAM wParam, LPARAM lParam)
{
	int nCh = (int)wParam;

	if (pVideoWindow->maximizedId == -1)
	{
		pVideoWindow->maximizedId = nCh;
	}
	else
	{
		pVideoWindow->maximizedId = -1;
	}
	UpdateComponents();

	return 0;
}




void CLivePlayerDlg::OnCbnSelchangeComboSplitScreen()
{
	if (NULL == pVideoWindow)		return;

	int nSplitWindow = 4;
	int nIdx = pComboxSplitScreen->GetCurSel();
	if (nIdx == 0)	nSplitWindow = 4;
	else if (nIdx == 1)	nSplitWindow = 8;
	else if (nIdx == 2)	nSplitWindow = 9;
	else if (nIdx == 3)	nSplitWindow = 16;
	else if (nIdx == 4)	nSplitWindow = 36;
	else if (nIdx == 5)	nSplitWindow = 64;

	pVideoWindow->channels		=	nSplitWindow;
	UpdateComponents();
}


void CLivePlayerDlg::OnCbnSelchangeComboRenderFormat()
{
	if (NULL == pComboxRenderFormat)		return;

	int iIdx = pComboxRenderFormat->GetCurSel();
	if (iIdx == 0)	RenderFormat	=	RENDER_FORMAT_YV12;//YV12
	else if (iIdx == 1)	RenderFormat	=	RENDER_FORMAT_YUY2;//YUY2
	else if (iIdx == 2)	RenderFormat	=	RENDER_FORMAT_RGB565;//RGB565
	else if (iIdx == 3)	RenderFormat	=	RENDER_FORMAT_X8R8G8B8;//X8R8G8B8
	else if (iIdx == 4)	RenderFormat	=	RENDER_FORMAT_RGB24_GDI;//GDI
}


void CLivePlayerDlg::OnBnClickedCheckShowntoscale()
{
	//IDC_CHECK_SHOWNTOSCALE
	if (NULL == pVideoWindow)					return;
	if (NULL == pVideoWindow->pDlgVideo)		return;

	int shownToScale = pChkShownToScale->GetCheck();
	//static int shownToScale = 0x00;
	//shownToScale = (shownToScale==0x00?0x01:0x00);

	for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
	{
		pVideoWindow->pDlgVideo[i].SetShownToScale(shownToScale);
	}
}

void CLivePlayerDlg::OnBnClickedCheckmultiplex()
{
	if (NULL == pVideoWindow)					return;
	if (NULL == pVideoWindow->pDlgVideo)		return;

	unsigned char multiplex = (unsigned char)pChkMultiplex->GetCheck();

	for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
	{
		pVideoWindow->pDlgVideo[i].SetMultiplex(multiplex);
	}
}

BOOL CLivePlayerDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	POINT	point;
	point.x = pt.x;
	point.y = pt.y;

	//ScreenToClient(&point);

	//TRACE("CLivePlayerDlg::OnMouseWheel  zDelta: %d  pt.x[%d] pt.y[%d]\n", zDelta, point.x, point.y);

	if (NULL != pVideoWindow && NULL != pVideoWindow->pDlgVideo)
	{
		for (int i=0; i<_SURV_MAX_WINDOW_NUM; i++)
		{
			if (! pVideoWindow->pDlgVideo[i].IsWindowVisible() )	continue;

			CRect rcVideo;
			pVideoWindow->pDlgVideo[i].GetWindowRect(&rcVideo);
			//TRACE("Window[%d]  L:%d\tT:%d\tR:%d\tB:%d\n", i, rcVideo.left, rcVideo.top, rcVideo.right, rcVideo.bottom);

			if (PtInRect(&rcVideo, point))
			{
				//TRACE("���λ�ڵ�[%d]������.\n", i);

				pVideoWindow->pDlgVideo[i].OnMouseWheel(zDelta, pt);

				break;
			}

		}
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}



LRESULT CLivePlayerDlg::OnExitFullScreen(WPARAM wParam, LPARAM lParam)
{
	FullScreen();

	return 0;
}

void	CLivePlayerDlg::FullScreen()
{
	INT		x, y, w, h;
	DWORD dwStyle = GetWindowLong( this->m_hWnd, GWL_STYLE );

	proConfig.fullScreen = (proConfig.fullScreen==0x01?0x00:0x01);

	bool bFullScreen = proConfig.fullScreen;
	if (bFullScreen)
	{


		x = 0;
		y = 0;
		w = GetSystemMetrics(SM_CXSCREEN);
		h = GetSystemMetrics(SM_CYSCREEN);

		DWORD dsStyle = GetStyle();
		if (dsStyle&WS_MAXIMIZE)
		{
			M_bMaxWnd = TRUE;
		}else{
			M_bMaxWnd = FALSE;
		}
		ShowWindow(SW_NORMAL);
		ShowWindow(SW_HIDE);
		this->GetWindowRect(&m_rcVideoSingle);

		//SetWindowPos(NULL, 0, 0, w, h, 0);
		// ȥ��������  
		ModifyStyle(WS_CAPTION|WS_MAXIMIZE, 0); //	
		 // ȥ���߿�
		ModifyStyleEx(WS_EX_DLGMODALFRAME, 0);  
		//����λ�úʹ�С����ԭ������
		SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED); 
// 		this->SetWindowPos(&CWnd::wndTopMost ,//&CWnd::wndBottom,//
// 			0, 0, w, h, 
// 			/*SWP_NOOWNERZORDER | */SWP_SHOWWINDOW );

		//��󻯴���
		ShowWindow(SW_MAXIMIZE);
	}
	else
	{
		ModifyStyle(0, WS_CAPTION);
		ModifyStyleEx(0, WS_EX_DLGMODALFRAME);
		SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);

// 		WINDOWPLACEMENT wndpl;
// 		wndpl.length  = sizeof(WINDOWPLACEMENT);
// 		wndpl.flags   = 0;
// 		wndpl.showCmd = SW_SHOWNORMAL;
// 		wndpl.rcNormalPosition = m_rcVideoSingle;
// 		// ��MoveWindow���������´�����󻯵�ʱ���޷��˳�ȫ������SetWindowPos��360������ϲ�����ʾȫ�� [2012-8-25  12:59 dingshuai]
// 		this->SetWindowPlacement(&wndpl);
		if (M_bMaxWnd)
		{
			ShowWindow(SW_MAXIMIZE);
		} 
		else
		{
			ShowWindow(SW_NORMAL);
		}
	}

	if (NULL != pComboxSplitScreen)		pComboxSplitScreen->ShowWindow(bFullScreen ? SW_HIDE : SW_SHOW);
	if (NULL != pComboxRenderFormat)		pComboxRenderFormat->ShowWindow(bFullScreen ? SW_HIDE : SW_SHOW);
	if (NULL != pChkShownToScale)		pChkShownToScale->ShowWindow(bFullScreen ? SW_HIDE : SW_SHOW);
	if (NULL != pChkMultiplex)		pChkMultiplex->ShowWindow(bFullScreen ? SW_HIDE : SW_SHOW);
	if (NULL != pChkFullScreen)		pChkFullScreen->ShowWindow(bFullScreen ? SW_HIDE : SW_SHOW);
	if (NULL != pStaticVolume)		pStaticVolume->ShowWindow(bFullScreen ? SW_HIDE : SW_SHOW);
	if (NULL != pSliderCtrlVolume)	pSliderCtrlVolume->ShowWindow(bFullScreen ? SW_HIDE : SW_SHOW);

	if (NULL != pChkFullScreen)		pChkFullScreen->SetCheck(bFullScreen?1:0);
}


void CLivePlayerDlg::OnBnClickedCheckFullscreen()
{
	FullScreen();
}


HBRUSH CLivePlayerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:	
		{
			pDC->SetBkColor(RGB(0x5b,0x5b,0x5b));
			pDC->SetTextColor(DIALOG_BASE_TEXT_COLOR);
			return m_BrushStatic;
		}
		break;
	default:
		break;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CLivePlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if( NULL != pScrollBar && NULL != pSliderCtrlVolume &&
		pSliderCtrlVolume->GetDlgCtrlID() == pScrollBar->GetDlgCtrlID())
	{
		int iPos = pSliderCtrlVolume->GetPos();
		
		libEasyPlayerPro_SetAudioVolume(playerHandle, iPos);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}




void CLivePlayerDlg::GetApplicationVersion(wchar_t *pVersion)
{
    TCHAR szFullPath[MAX_PATH];
    DWORD dwVerInfoSize = 0;
    DWORD dwVerHnd;
    VS_FIXEDFILEINFO * pFileInfo;
   
    GetModuleFileName(NULL, szFullPath, sizeof(szFullPath));
    dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
    if (dwVerInfoSize)
    {
        // If we were able to get the information, process it:
        HANDLE hMem;
        LPVOID lpvMem;
        unsigned int uInfoSize = 0;
       
        hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
        lpvMem = GlobalLock(hMem);
        GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpvMem);
       
        ::VerQueryValue(lpvMem, TEXT("\\"), (void**)&pFileInfo, &uInfoSize);
       
        int ret = GetLastError();
        WORD m_nProdVersion[4];
       
        // Product version from the FILEVERSION of the version info resource
        m_nProdVersion[0] = HIWORD(pFileInfo->dwProductVersionMS);
        m_nProdVersion[1] = LOWORD(pFileInfo->dwProductVersionMS);
        m_nProdVersion[2] = HIWORD(pFileInfo->dwProductVersionLS);
        m_nProdVersion[3] = LOWORD(pFileInfo->dwProductVersionLS);
       
        CString strVersion ;
        strVersion.Format(_T("EasyPlayerPro V%d.%d.%d%d"),m_nProdVersion[0],
            m_nProdVersion[1],m_nProdVersion[2],m_nProdVersion[3]);
       
        GlobalUnlock(hMem);
        GlobalFree(hMem);
       
		wcscpy(pVersion, strVersion);
    }
}


BOOL CLivePlayerDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_ESCAPE)
	{
		if (proConfig.fullScreen==0x01)
		{
			FullScreen();
		}

		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
