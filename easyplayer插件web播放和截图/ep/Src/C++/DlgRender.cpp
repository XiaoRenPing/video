#include "stdafx.h"
#include "EasyPlayerPro.h"
#include "DlgRender.h"
#include "afxdialogex.h"

#include "./libEasyPlayerPro/libEasyPlayerProAPI.h"
#include "./libEasyPlayerPro/libVideoAnalysisAPI.h"

#include "DlgMediaInfo.h"
// CDlgRender �Ի���

IMPLEMENT_DYNAMIC(CDlgRender, CDialogEx)

CDlgRender::CDlgRender(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRender::IDD, pParent)
{
	memset(&channelStatus, 0x00, sizeof(CHANNELSTATUS));
	hMenu		=	NULL;
	mDrag		=	false;
	scaleMultiple=	1;
	memset(&pt_start, 0x00, sizeof(POINT));
	memset(&pt_start_org, 0x00, sizeof(POINT));

	mChannelId	=	0;
}

CDlgRender::~CDlgRender()
{
	ClosePopupMenu();
}

void CDlgRender::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgRender, CDialogEx)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgRender ��Ϣ�������

BOOL CDlgRender::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetBackgroundColor(RGB(0x92,0x92,0x92));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgRender::ClosePopupMenu()
{
	if (NULL != hMenu)
	{
		DestroyMenu(hMenu);
		hMenu = NULL;
	}
}

void	CDlgRender::SetSourceType(EASY_CHANNEL_SOURCE_TYPE_ENUM sourceType)
{
	mSourceType	=	sourceType;
}

void	CDlgRender::ResetChannel()
{
	memset(&channelStatus, 0x00, sizeof(CHANNELSTATUS));
}

void CDlgRender::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (libVA_GetRenderMode(playerHandle,mChannelId) !=RENDER_MODE_VIDEO  && channelStatus.drag == 0x01)
	{
		libVA_EndCustomZoneNode(playerHandle, mChannelId, 0x00);
		channelStatus.drag = 0x00;

		//channelStatus.zoneId ++;
	}
	::PostMessage(GetParent()->GetSafeHwnd(), WM_LBUTTONDBLCLK, 0, 0);

	CDialogEx::OnLButtonDblClk(nFlags, point);
}

#define POP_MENU_SEPARATOR	10000

#define	POP_MENU_OPEN_FILE	10005

#define	POP_MENU_AUDIO	10009

#define	POP_MENU_RECORDING	10010
#define POP_MENU_DECODE_KEYFRAME_ONLY		10011
#define POP_MENU_SNAPSHOT_BMP	10012
#define POP_MENU_SNAPSHOT_JPG	10013
#define POP_MENU_STREAM_PAUSE	10014
#define POP_MENU_STREAM_RESUME	10015

#define POP_MENU_STREAM_INSTANT_REPLAY	10016		//��ʱ�ط�
#define POP_MENU_STREAM_PREVIOUS_FRAME	10017
#define POP_MENU_STREAM_NEXT_FRAME	10018
#define POP_MENU_STREAM_INSTANT_REPLAY_RECORDING		10019		//��ʱ�ط�¼��

#define POP_MENU_STREAM_FAST_X2			10020		//2���ٲ���
#define POP_MENU_STREAM_FAST_X4			10021		//4���ٲ���
#define POP_MENU_STREAM_FAST_X8			10022		//8���ٲ���
#define POP_MENU_STREAM_FAST_X16		10023
#define POP_MENU_STREAM_NORMAL_X1		10024		//1���ٲ���
#define POP_MENU_STREAM_SLOW_X2			10025		// 2/1���ٲ���
#define POP_MENU_STREAM_SLOW_X4			10026		// 4/1���ٲ���
#define POP_MENU_STREAM_SLOW_X8			10027		// 8/1���ٲ���
#define POP_MENU_STREAM_SLOW_X16		10028		// 16/1���ٲ���
#define POP_MENU_STREAM_SINGLE_FRAME	10029		//��֡


#define POP_MENU_VA_WARNING_AREA		10031		//������

#define POP_MENU_ELECTORIC_ZOOM			10060
#define POP_MENU_VIDEO_FLIP				10062		//��Ƶ��ת
#define POP_MENU_SET_OVERLAY_TEXT		10100		//���õ�������
#define POP_MENU_CLEAR_OVERLAY_TEXT		10101		//�����������

#define POP_MENU_SHOW_TOOLBAR			10200		//��ʾ������

#define POP_MENU_MEDIA_INFO				10500		//????

#define POP_MENU_EXIT_FULLSCREEN		10600		//????

void CDlgRender::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClosePopupMenu();

	//Player_SetRenderRect(mChannelId, NULL);
	scaleMultiple = 1;




	if (libVA_GetRenderMode(playerHandle,mChannelId) !=RENDER_MODE_VIDEO  && channelStatus.drag == 0x01)
	{
		libVA_EndCustomZoneNode(playerHandle, mChannelId, 0x00);
		channelStatus.drag = 0x00;

		channelStatus.zoneId ++;
	}
	else
	{
		if (mChannelId > 0)
		{
			hMenu = CreatePopupMenu();
			if (NULL != hMenu)
			{
				//AppendMenu(hMenu, MF_STRING, POP_MENU_OPEN_FILE, TEXT("????"));
				

				//????
				channelStatus.audio = (libEasyPlayerPro_SoundPlaying(playerHandle, mChannelId) == 0x00?0x01:0x00);
				AppendMenu(hMenu, MF_STRING|(channelStatus.audio==0x01?MF_CHECKED:MF_UNCHECKED), POP_MENU_AUDIO, TEXT("��������"));

				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));

				//¼��
				AppendMenu(hMenu, MF_STRING|(channelStatus.recording==0x01?MF_CHECKED:MF_UNCHECKED), POP_MENU_RECORDING, TEXT("�ֶ�¼��"));

				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));

				//��Ƶ��ת
				AppendMenu(hMenu, MF_STRING|(channelStatus.flip==0x01?MF_CHECKED:MF_UNCHECKED), POP_MENU_VIDEO_FLIP, TEXT("��Ƶ��ת"));

				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));

				//ץͼ
				AppendMenu(hMenu, MF_STRING, POP_MENU_SNAPSHOT_BMP, TEXT("ץͼ(BMP)"));
				AppendMenu(hMenu, MF_STRING, POP_MENU_SNAPSHOT_JPG, TEXT("ץͼ(JPG)"));

				//���ӷŴ�
				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				AppendMenu(hMenu, MF_STRING|(channelStatus.digitalZoom==0x01?MF_CHECKED:MF_UNCHECKED), POP_MENU_ELECTORIC_ZOOM, TEXT("���ӷŴ�"));

				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				AppendMenu(hMenu, MF_STRING|(channelStatus.decodeKeyframeOnly==0x01?MF_CHECKED:MF_UNCHECKED), POP_MENU_DECODE_KEYFRAME_ONLY, TEXT("������ؼ�֡"));
				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));


				if (EASY_CHANNEL_SOURCE_TYPE_FILE == mSourceType)
				{
					AppendMenu(hMenu, MF_STRING, POP_MENU_STREAM_PAUSE, TEXT("��ͣ"));
					AppendMenu(hMenu, MF_STRING, POP_MENU_STREAM_RESUME, TEXT("�ָ�"));
				}
				AppendMenu(hMenu, MF_STRING|(channelStatus.instantReplay==0x01?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_INSTANT_REPLAY, TEXT("��ʱ�ط�"));	//��ʱ�ط�
		

				//AppendMenu(hMenu, MF_STRING, POP_MENU_STREAM_PREVIOUS_FRAME, TEXT("Previous Frame"));
				//AppendMenu(hMenu, MF_STRING, POP_MENU_STREAM_NEXT_FRAME, TEXT("Next Frame"));

				if (channelStatus.instantReplay == 0x01)
				{
					AppendMenu(hMenu, MF_STRING|(channelStatus.instantReplaySave==0x01?MF_CHECKED:MF_UNCHECKED), 
						POP_MENU_STREAM_INSTANT_REPLAY_RECORDING, TEXT("��ʱ�ط����Ϊ"));	//��ʱ�طű���
				}

				if (EASY_CHANNEL_SOURCE_TYPE_FILE == mSourceType)
				{
					AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
					AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));

					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed==PLAY_SPEED_FAST_X2?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_FAST_X2, TEXT("���(x2)"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed==PLAY_SPEED_FAST_X4?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_FAST_X4, TEXT("���(x4)"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed==PLAY_SPEED_FAST_X8?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_FAST_X8, TEXT("���(x8)"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed==PLAY_SPEED_FAST_X16?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_FAST_X16, TEXT("���(x16)"));

					AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed==PLAY_SPEED_NORMAL?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_NORMAL_X1, TEXT("����(x1)"));
		
					AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));

					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed==PLAY_SPEED_SLOW_X2?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_SLOW_X2, TEXT("����(1/2x)"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed==PLAY_SPEED_SLOW_X4?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_SLOW_X4, TEXT("����(1/4x)"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed==PLAY_SPEED_SLOW_X8?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_SLOW_X8, TEXT("����(1/8x)"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed==PLAY_SPEED_SLOW_X16?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_SLOW_X16, TEXT("����(1/16x)"));

					AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
					AppendMenu(hMenu, MF_STRING|(channelStatus.playSpeed==POP_MENU_STREAM_SINGLE_FRAME?MF_CHECKED:MF_UNCHECKED), POP_MENU_STREAM_SINGLE_FRAME, TEXT("��֡"));
				}

				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				//AppendMenu(hMenu, MF_STRING|(channelStatus.videoAnalysis==0x01?MF_CHECKED:MF_UNCHECKED), POP_MENU_VA_ENABLE, TEXT("Video Analysis Settings"));
				//if (channelStatus.videoAnalysis == 0x01)
				{
					RENDER_MODE_ENUM	renderMode = libVA_GetRenderMode(playerHandle,mChannelId);
					AppendMenu(hMenu, MF_STRING|(renderMode==RENDER_MODE_ZONE?MF_CHECKED:MF_UNCHECKED), POP_MENU_VA_WARNING_AREA, TEXT("������"));
				}


				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				AppendMenu(hMenu, MF_STRING, POP_MENU_SET_OVERLAY_TEXT, TEXT("���õ�������"));
				AppendMenu(hMenu, MF_STRING, POP_MENU_CLEAR_OVERLAY_TEXT, TEXT("�����������"));

				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				AppendMenu(hMenu, MF_STRING|(channelStatus.bShowToolbar?MF_CHECKED:MF_UNCHECKED), POP_MENU_SHOW_TOOLBAR, TEXT("������"));
			
				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
				AppendMenu(hMenu, MF_STRING, POP_MENU_MEDIA_INFO, TEXT("ý����Ϣ"));

				if (proConfig.fullScreen == 0x01)
				{
					AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
					AppendMenu(hMenu, MF_STRING, POP_MENU_EXIT_FULLSCREEN, TEXT("�˳�ȫ��"));
				}
			
				CPoint	pMousePosition;
				GetCursorPos(&pMousePosition);
				SetForegroundWindow();
				TrackPopupMenu(hMenu, TPM_LEFTALIGN, pMousePosition.x, pMousePosition.y, 0, GetSafeHwnd(), NULL);
			}
		}
		else
		{
			hMenu = CreatePopupMenu();
			if (NULL != hMenu)
			{
				AppendMenu(hMenu, MF_STRING, POP_MENU_OPEN_FILE, TEXT("���ļ�"));

				if (proConfig.fullScreen == 0x01)
				{
					AppendMenu(hMenu, MF_SEPARATOR, POP_MENU_SEPARATOR, TEXT("-"));
					AppendMenu(hMenu, MF_STRING, POP_MENU_EXIT_FULLSCREEN, TEXT("�˳�ȫ��"));
				}

				CPoint	pMousePosition;
				GetCursorPos(&pMousePosition);
				SetForegroundWindow();
				TrackPopupMenu(hMenu, TPM_LEFTALIGN, pMousePosition.x, pMousePosition.y, 0, GetSafeHwnd(), NULL);
			}

		}
	}

	CDialogEx::OnRButtonUp(nFlags, point);
}


BOOL CDlgRender::OnCommand(WPARAM wParam, LPARAM lParam)
{
	WORD	wID = (WORD)wParam;
	switch (wID)
	{
	case POP_MENU_OPEN_FILE:
		{
			CWnd *pWnd = GetParent();
			if (NULL != pWnd)
			{
				pWnd->PostMessageW(WM_OPEN_FILE);
			}
		}
		break;
	case POP_MENU_AUDIO:
		{
			if (mChannelId > 0)
			{
				channelStatus.audio = (channelStatus.audio==0x00?0x01:0x00);
				
				if (channelStatus.audio == 0x01)
				{
					int ret = libEasyPlayerPro_StartPlaySound(playerHandle, mChannelId);
					if (ret < 0)	channelStatus.audio = 0x00;
				}
				else
				{
					libEasyPlayerPro_StopPlaySound(playerHandle, mChannelId);
				}
			}
		}
		break;
	case POP_MENU_RECORDING:
		{
			//channelStatus.recording = (channelStatus.recording==0x00?0x01:0x00);
			if (mChannelId > 0)
			{
				channelStatus.recording = (channelStatus.recording==0x00?0x01:0x00);

				char sztmp[36] = {0};
				time_t tt = time(NULL);
				struct tm *_time = localtime(&tt);
				memset(sztmp, 0x00, sizeof(sztmp));
				strftime(sztmp, 32, "%Y%m%d_%H%M%S", _time);
				
				char szFilename[MAX_PATH] = {0};
				sprintf(szFilename, "ch%d_%s.mpg", mChannelId, sztmp);


				if (channelStatus.recording == 0x01)
				{
					int ret = libEasyPlayerPro_StartRecording(playerHandle, mChannelId, "", szFilename, 
								proConfig.recordingFileSize, 
								proConfig.recordingDuration, 
								0x01, 
								proConfig.recordingFileAutoSegmentation);
					if (ret < 0)	channelStatus.recording = 0x00;
				}
				else											libEasyPlayerPro_StopRecording(playerHandle, mChannelId);
			}
		}
		break;
	case POP_MENU_VIDEO_FLIP:
		{
			if (mChannelId > 0)
			{
				channelStatus.flip = (channelStatus.flip==0x00?0x01:0x00);

				libEasyPlayerPro_SetVideoFlip(playerHandle, mChannelId, channelStatus.flip);
			}
		}
		break;
	case POP_MENU_DECODE_KEYFRAME_ONLY:
		{
			if (mChannelId > 0)
			{
				channelStatus.decodeKeyframeOnly = (channelStatus.decodeKeyframeOnly==0x00?0x01:0x00);

				libEasyPlayerPro_SetDecodeType(playerHandle, mChannelId, channelStatus.decodeKeyframeOnly);
			}
		}
		break;
	case POP_MENU_SNAPSHOT_BMP:
	case POP_MENU_SNAPSHOT_JPG:
		{
			char sztmp[128] ={0};
			static int iSnapshotTally = 0;
			for (int i=0; i<1; i++)
			{
				memset(sztmp, 0x00, sizeof(sztmp));
				sprintf(sztmp, "Snapshot/%d.%s", ++iSnapshotTally, wID==POP_MENU_SNAPSHOT_BMP?"bmp":"jpg");
				while (0 != libEasyPlayerPro_SnapshotToFile(playerHandle, mChannelId, wID==POP_MENU_SNAPSHOT_BMP?0:1, sztmp, 0,1))
				{
					Sleep(1);
				}
			}
		}
		break;
	case POP_MENU_STREAM_PAUSE:
		{
			if (channelStatus.instantReplay == 0x00)
			{
				libEasyPlayerPro_SetPlaySpeed(playerHandle, mChannelId, PLAY_SPEED_PAUSED);	//��ͣԶ�̻ط�
				channelStatus.playSpeed = PLAY_SPEED_PAUSED;
			}
			else
			{
				libEasyPlayerPro_InstantReplay_Pause(playerHandle, mChannelId);			//��ͣ��ʱ�ط�
			}
		}
		break;
	case POP_MENU_STREAM_RESUME:
		{
			if (channelStatus.instantReplay == 0x00)
			{
				libEasyPlayerPro_SetPlaySpeed(playerHandle, mChannelId, PLAY_SPEED_NORMAL);	//�ָ�Զ�̻ط�
				channelStatus.playSpeed = PLAY_SPEED_NORMAL;
			}
			else
			{
				libEasyPlayerPro_InstantReplay_Resume(playerHandle, mChannelId);			//�ָ���ʱ�ط�
			}
		}
		break;
	case POP_MENU_STREAM_INSTANT_REPLAY:
		{
			channelStatus.instantReplay = (channelStatus.instantReplay==0x00?0x01:0x00);

			if (channelStatus.instantReplay == 0x01)
			{
				libEasyPlayerPro_InstantReplay_Start(playerHandle, mChannelId);		//��ʼ��ʱ�ط�

				int frameno=0, framenum=0;
				libEasyPlayerPro_InstantReplay_GetFrameNum(playerHandle, mChannelId, &frameno, &framenum);
				TRACE("video frame num: %d  / %d\n", frameno, framenum);
			}
			else
			{
				libEasyPlayerPro_InstantReplay_Stop(playerHandle, mChannelId);			//ֹͣ��ʱ�ط�
			}
		}
		break;
	case POP_MENU_STREAM_INSTANT_REPLAY_RECORDING:
		{
			libEasyPlayerPro_InstantReplay_Save(playerHandle, mChannelId, "E:\\recording\\123.mpg");
		}
		break;
	case POP_MENU_STREAM_PREVIOUS_FRAME:
		{
		}
		break;
	case POP_MENU_STREAM_NEXT_FRAME:
		{
		}
		break;

	case POP_MENU_STREAM_FAST_X2:
		{
			channelStatus.playSpeed = PLAY_SPEED_FAST_X2;
			libEasyPlayerPro_SetPlaySpeed(playerHandle, mChannelId, (PLAY_SPEED_ENUM)channelStatus.playSpeed);
		}
		break;
	case POP_MENU_STREAM_FAST_X4:
		{
			channelStatus.playSpeed = PLAY_SPEED_FAST_X4;
			libEasyPlayerPro_SetPlaySpeed(playerHandle, mChannelId, (PLAY_SPEED_ENUM)channelStatus.playSpeed);
		}
		break;
	case POP_MENU_STREAM_FAST_X8:
		{
			channelStatus.playSpeed = PLAY_SPEED_FAST_X8;
			libEasyPlayerPro_SetPlaySpeed(playerHandle, mChannelId, (PLAY_SPEED_ENUM)channelStatus.playSpeed);
		}
		break;
	case POP_MENU_STREAM_FAST_X16:
		{
			channelStatus.playSpeed = PLAY_SPEED_FAST_X16;
			libEasyPlayerPro_SetPlaySpeed(playerHandle, mChannelId, (PLAY_SPEED_ENUM)channelStatus.playSpeed);
		}
		break;
	case POP_MENU_STREAM_NORMAL_X1:
		{
			channelStatus.playSpeed = PLAY_SPEED_NORMAL;
			libEasyPlayerPro_SetPlaySpeed(playerHandle, mChannelId, (PLAY_SPEED_ENUM)channelStatus.playSpeed);
		}
		break;
	case POP_MENU_STREAM_SLOW_X2:
		{
			channelStatus.playSpeed = PLAY_SPEED_SLOW_X2;
			libEasyPlayerPro_SetPlaySpeed(playerHandle, mChannelId, (PLAY_SPEED_ENUM)channelStatus.playSpeed);
		}
		break;
	case POP_MENU_STREAM_SLOW_X4:
		{
			channelStatus.playSpeed = PLAY_SPEED_SLOW_X4;
			libEasyPlayerPro_SetPlaySpeed(playerHandle, mChannelId, (PLAY_SPEED_ENUM)channelStatus.playSpeed);
		}
		break;
	case POP_MENU_STREAM_SLOW_X8:
		{
			channelStatus.playSpeed = PLAY_SPEED_SLOW_X8;
			libEasyPlayerPro_SetPlaySpeed(playerHandle, mChannelId, (PLAY_SPEED_ENUM)channelStatus.playSpeed);
		}
		break;
	case POP_MENU_STREAM_SLOW_X16:
		{
			channelStatus.playSpeed = PLAY_SPEED_SLOW_X16;
			libEasyPlayerPro_SetPlaySpeed(playerHandle, mChannelId, (PLAY_SPEED_ENUM)channelStatus.playSpeed);
		}
		break;
	case POP_MENU_STREAM_SINGLE_FRAME:
		{
			channelStatus.playSpeed = PLAY_SPEED_SINGLE_FRAME;
			libEasyPlayerPro_SetPlaySpeed(playerHandle, mChannelId, (PLAY_SPEED_ENUM)channelStatus.playSpeed);
		}
		break;
	case POP_MENU_VA_WARNING_AREA:
		{
			RENDER_MODE_ENUM	oldRenderMode = libVA_GetRenderMode(playerHandle, mChannelId);
			RENDER_MODE_ENUM	renderMode = RENDER_MODE_VIDEO;
			if (wID == POP_MENU_VA_WARNING_AREA)				renderMode = RENDER_MODE_ZONE;
			if (oldRenderMode == renderMode)
			{
				libVA_SetRenderMode(playerHandle, mChannelId, RENDER_MODE_VIDEO);
			}
			else
			{
				libVA_SetRenderMode(playerHandle, mChannelId, renderMode);

				if (libVA_GetRenderMode(playerHandle,mChannelId) == RENDER_MODE_LANE)
					libVA_SetWarningGrade(playerHandle, mChannelId, VA_WARN_GRADE_LOW);
				else
				{
					libVA_SetWarningGrade(playerHandle, mChannelId, VA_WARN_GRADE_HIGH);
				}
				libVA_SetWarningType(playerHandle, mChannelId, VA_WARN_TYPE_ON);
				libVA_ShowAllWarningArea(playerHandle, mChannelId, 0x01);
			}
		}
		break;
	case POP_MENU_ELECTORIC_ZOOM:
		{
			channelStatus.digitalZoom = (channelStatus.digitalZoom==0x00?0x01:0x00);

			if (channelStatus.digitalZoom == 0x01)
			{
				//��ʼ���ӷŴ�
			}
			else
			{
				libEasyPlayerPro_SetElectronicZoom(playerHandle, mChannelId, 0);			//�ָ����ӷŴ�
				libEasyPlayerPro_ResetElectronicZoom(playerHandle, mChannelId);
			}
		}
		break;
	case POP_MENU_SET_OVERLAY_TEXT:
		{
			libEasyPlayerPro_SetOverlayText(playerHandle, mChannelId, "���Ե�������");
		}
		break;
	case POP_MENU_CLEAR_OVERLAY_TEXT:
		{
			libEasyPlayerPro_ClearOverlayText(playerHandle, mChannelId);

			//libEasyPlayerPro_SeekFile(playerHandle, mChannelId, 20);
		}
		break;
	case POP_MENU_SHOW_TOOLBAR:
		{
			CWnd *pWnd = GetParent();
			if (NULL != pWnd)
			{
				pWnd->PostMessageW(WM_SHOW_TOOLBAR);
			}
		}
		break;
	case POP_MENU_MEDIA_INFO:
		{
			EASY_MEDIA_INFO_T	mediaInfo;
			libEasyPlayerPro_GetStreamInfo(playerHandle, mChannelId, &mediaInfo);
			printf("mediainfo.\n");

			CDlgMediaInfo dlgMediaInfo(&mediaInfo);
			dlgMediaInfo.DoModal();
		}
		break;
	case POP_MENU_EXIT_FULLSCREEN:
		{
			CWnd *pWnd = ::AfxGetMainWnd();
			if (NULL != pWnd)
			{
				pWnd->PostMessageW(WM_EXIT_FULLSCREEN);
			}
		}
		break;
	default:
		break;
	}


	return CDialogEx::OnCommand(wParam, lParam);
}


void CDlgRender::OnLButtonDown(UINT nFlags, CPoint point)
{
	mDrag = true;

	startPoint.x = point.x;
	startPoint.y = point.y;

	CRect rcClient;
	GetClientRect(&rcClient);
	int nLeftPercent = (int)((float)startPoint.x / (float)rcClient.Width()*100.0f);
	int nTopPercent  = (int)((float)startPoint.y / (float)rcClient.Height()*100.0f);

	POINT pt;
	pt.x = nLeftPercent;
	pt.y = nTopPercent;

	//Player_SetDragStartPoint(mChannelId, pt);

	if (channelStatus.digitalZoom == 0x01)		//���ӷŴ�
	{
		channelStatus.drag = 0x01;

		float fXPercent = 0.0f, fYPercent=0.0f;

		CRect rcClient;
		GetClientRect(&rcClient);
		fXPercent = ((float)point.x / (float)rcClient.Width()*100.0f);
		fYPercent  = ((float)point.y / (float)rcClient.Height()*100.0f);
		libEasyPlayerPro_SetElectronicZoomStartPoint(playerHandle, mChannelId, fXPercent, fYPercent, 0x01);
	}
	else if (libVA_GetRenderMode(playerHandle,mChannelId) != RENDER_MODE_VIDEO)
	{
		VA_DETECT_POINT_T	p;
		memset(&p, 0x00, sizeof(VA_DETECT_POINT_T));
		p.x = point.x;
		p.y = point.y;
		p.xPercent = (float)(point.x) / (float)(rcClient.Width()) * 100.0f;
		p.yPercent = (float)(point.y) / (float)(rcClient.Height()) * 100.0f;

		//libVA_AddWarningAreaNode(playerHandle, mChannelId, &p);

		libVA_AddCustomZoneNode(playerHandle, mChannelId, channelStatus.zoneId, "", &p, 0x01, 1, 4, 40, 0x00, 
			RGB(0xff,0x00,0x00), RGB(0x80,0xff,0x00), RGB(0x00,0x00,0x00), 20, 100, 180);

		channelStatus.drag = 0x01;
	}


	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDlgRender::OnLButtonUp(UINT nFlags, CPoint point)
{

	if (mDrag)
	{
		if (channelStatus.digitalZoom == 0x01)
		{
			libEasyPlayerPro_SetElectronicZoom(playerHandle, mChannelId, 1);
			//libEasyPlayerPro_ResetDragPoint(playerHandle, mChannelId);
		}
		else
		{
			CRect rcClient;
			GetClientRect(&rcClient);

			VA_DETECT_POINT_T	p;
			memset(&p, 0x00, sizeof(VA_DETECT_POINT_T));
			p.x = point.x;
			p.y = point.y;
			p.xPercent = (float)(point.x) / (float)(rcClient.Width()) * 100.0f;
			p.yPercent = (float)(point.y) / (float)(rcClient.Height()) * 100.0f;

			libVA_MoveCustomZoneNode(playerHandle, mChannelId, &p, 0x01, 0x00);
			//libVA_EndCustomZoneNode(playerHandle, mChannelId, 0x00);

			channelStatus.drag = 0x01;
		}
	}


	mDrag = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CDlgRender::OnMouseMove(UINT nFlags, CPoint point)
{
	if (mDrag)
	{
		CRect rcClient;
		GetClientRect(&rcClient);



		if (channelStatus.digitalZoom == 0x01)		//���ӷŴ�
		{
			float fXPercent = 0.0f, fYPercent=0.0f;

			CRect rcClient;
			GetClientRect(&rcClient);
			fXPercent = ((float)point.x / (float)rcClient.Width()*100.0f);
			fYPercent  = ((float)point.y / (float)rcClient.Height()*100.0f);
			libEasyPlayerPro_SetElectronicZoomEndPoint(playerHandle, mChannelId, fXPercent, fYPercent);
		}
		else
		{
			int nLeftPercent = (int)((float)startPoint.x / (float)rcClient.Width()*100.0f);
			int nTopPercent  = (int)((float)startPoint.y / (float)rcClient.Height()*100.0f);
			int nRightPercent = (int)((float)point.x / (float)rcClient.Width()*100.0f);
			int nBottomPercent  = (int)((float)point.y / (float)rcClient.Height()*100.0f);

			VA_DETECT_POINT_T	p;
			memset(&p, 0x00, sizeof(VA_DETECT_POINT_T));
			p.x = point.x;
			p.y = point.y;
			p.xPercent = (float)(point.x) / (float)(rcClient.Width()) * 100.0f;
			p.yPercent = (float)(point.y) / (float)(rcClient.Height()) * 100.0f;

			

			//Player_SetDragEndPoint(mChannelId, pt);
		}
	}

	if (libVA_GetRenderMode(playerHandle,mChannelId) != RENDER_MODE_VIDEO && channelStatus.drag == 0x01)
	{
		CRect rcClient;
		GetClientRect(&rcClient);

		VA_DETECT_POINT_T	p;
		memset(&p, 0x00, sizeof(VA_DETECT_POINT_T));
		p.x = point.x;
		p.y = point.y;
		p.xPercent = (float)(point.x) / (float)(rcClient.Width()) * 100.0f;
		p.yPercent = (float)(point.y) / (float)(rcClient.Height()) * 100.0f;

		//libVA_UpdateWarningAreaNode(playerHandle, mChannelId, &p);
		libVA_MoveCustomZoneNode(playerHandle, mChannelId, &p, 0x00, 0x00);
	}


	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CDlgRender::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
void CDlgRender::OnMouseWheel(short zDelta, CPoint pt)
{
}

void	CDlgRender::SetRecordingFlag(int flag)
{
	channelStatus.recording = flag;
}


void CDlgRender::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (libVA_GetRenderMode(playerHandle,mChannelId) != RENDER_MODE_VIDEO)
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		libVA_UpdateWarningAreaPosition(playerHandle, mChannelId, rcClient);

		libVA_UpdateCustomZonePosition(playerHandle, mChannelId, rcClient);
	}

}
