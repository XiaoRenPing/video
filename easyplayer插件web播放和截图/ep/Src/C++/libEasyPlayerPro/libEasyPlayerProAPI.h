#ifndef __LIB_EASY_PLAYER_PRO_API_H__
#define __LIB_EASY_PLAYER_PRO_API_H__


#include <winsock2.h>
#include "easyTypes.h"

typedef enum __RENDER_FORMAT
{
	RENDER_FORMAT_YV12		=		842094169,
	RENDER_FORMAT_YUY2		=		844715353,
	RENDER_FORMAT_UYVY		=		1498831189,
	RENDER_FORMAT_A8R8G8B8	=		21,
	RENDER_FORMAT_X8R8G8B8	=		22,
	RENDER_FORMAT_RGB565	=		23,
	RENDER_FORMAT_RGB555	=		25,

	RENDER_FORMAT_RGB24_GDI=		26
}RENDER_FORMAT;

//ͨ��Դ���� (ָ��Դ����)
typedef enum __EASY_CHANNEL_SOURCE_TYPE_ENUM
{
	EASY_CHANNEL_SOURCE_TYPE_RTSP	=	0,		//ԴΪRTSP(����)
	EASY_CHANNEL_SOURCE_TYPE_RTMP,				//ԴΪRTMP(����)
	EASY_CHANNEL_SOURCE_TYPE_HLS,				//ԴΪHLS(����)
	EASY_CHANNEL_SOURCE_TYPE_FILE,				//ԴΪ�����ļ�(����)
	EASY_CHANNEL_SOURCE_TYPE_ENCODE_DATA,		//ԴΪ�ⲿ�ı�������
	EASY_CHANNEL_SOURCE_TYPE_DECODE_DATA,		//ԴΪ�ⲿ�Ľ�������
}EASY_CHANNEL_SOURCE_TYPE_ENUM;





//�����豸��Ϣ
#define		MAX_MIXER_DEVICE_NUM		16
typedef struct __MIXER_DEVICE_INFO_T
{
	int		id;
	char	name[128];
	char	version[16];
}MIXER_DEVICE_INFO_T;

//֡��Ϣ
typedef struct 
{
	unsigned int	codec;			//�����ʽ
	unsigned char	type;			//֡����
	unsigned char	fps;			//֡��
	unsigned char	reserved1;
	unsigned char	reserved2;

	unsigned short	width;			//��
	unsigned short  height;			//��
	unsigned int	sample_rate;	//������
	unsigned int	channels;		//����
	unsigned int	bitsPerSample;	//��������
	unsigned int	length;			//֡��С
	unsigned int    rtptimestamp_sec;	//rtp timestamp	sec
	unsigned int    rtptimestamp_usec;	//rtp timestamp	usec
	unsigned int	timestamp_sec;	//��
	
	float			bitrate;		//Kbps
	float			losspacket;
	//float			currentPlayTime;//��ǰ����ʱ��
}EASY_FRAME_INFO;


//��Ƶ�ɼ��豸��Ϣ
typedef struct __EASY_AUDIO_CAPTURE_DEVICE_INFO
{
	int			id;
	//LPGUID		lpGuid;
	//LPTSTR		lpstrDescription;
	//LPTSTR		lpstrModule;

	char		description[128];
	char		module[128];
}EASY_AUDIO_CAPTURE_DEVICE_INFO;
//��Ƶ�ɼ���ʽ
typedef struct __EASY_AUDIO_WAVE_FORMAT_INFO
{
    WORD        wFormatTag;         /* format type */
    WORD        nChannels;          /* number of channels (i.e. mono, stereo...) */
    DWORD       nSamplesPerSec;     /* sample rate */
    DWORD       nAvgBytesPerSec;    /* for buffer estimation */
    WORD        nBlockAlign;        /* block size of data */
    WORD        wBitsPerSample;     /* number of bits per sample of mono data */
    WORD        cbSize;             /* the count in bytes of the size of */
                                    /* extra information (after cbSize) */
}EASY_AUDIO_WAVE_FORMAT_INFO;


typedef enum __EASY_CALLBACK_TYPE_ENUM
{
	EASY_TYPE_CONNECTING		=	100,			//��ǰͨ��������
	EASY_TYPE_CONNECTED,							//��ǰͨ��������
	EASY_TYPE_RECONNECT,							//��ǰͨ�������ѶϿ�,��������
	EASY_TYPE_DISCONNECT,							//��ǰͨ����������ֹ(�ڲ������߳����˳�),ָ�������Ӵ���������»�ص���ֵ

	EASY_TYPE_CODEC_DATA,							//��������
	EASY_TYPE_DECODE_DATA,							//��������
	EASY_TYPE_SNAPSHOT,								//ץ��
	EASY_TYPE_RECORDING,							//¼��
	EASY_TYPE_INSTANT_REPLAY_RECORDING,				//��ʱ�ط�¼�����

	EASY_TYPE_START_PLAY_AUDIO,						//��ʼ��������
	EASY_TYPE_STOP_PLAY_AUDIO,						//ֹͣ��������
	EASY_TYPE_CAPTURE_AUDIO_DATA,					//���زɼ�����Ƶ����

	EASY_TYPE_FILE_DURATION							//�ļ�ʱ��
}EASY_CALLBACK_TYPE_ENUM;
typedef int (CALLBACK *EasyPlayerProCallBack)(EASY_CALLBACK_TYPE_ENUM callbackType, int channelId, void *userPtr, int mediaType, char *pbuf, EASY_FRAME_INFO *frameInfo);


//���������
typedef void *PLAYER_HANDLE;

#ifdef __cplusplus
extern "C"
{
#endif

    //����SDK ȫ��ֻ�����һ��
    LIB_EASYPLAYER_PRO_API EASY_ACTIVATE_ERR_CODE_ENUM LIB_APICALL	libEasyPlayerPro_Activate(const char* license);

	/*
	libEasyPlayerPro ��Ϊ���ֵ��÷�ʽ:
								1. ʹ��libEasyPlayerPro_Initialize��ʼ��,  �ں�������е�����, PLAYER_HANDLEΪNULL, ��������libEasyPlayerPro_Deinitialize
								2. ʹ��libEasyPlayerPro_Create ����һ��PLAYER_HANDLE���, �ں�������е�����, ���ϴ����ľ��, ��������libEasyPlayerPro_Release
	*/

	//=====================================================================================
	//=====================================================================================
	//��ʼ��
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_Initialize(int supportMaxChannel/*����ָ�����ͨ����, ����ܳ����궨��MAX_CHANNEL_NUM*/);
	//����ʼ��
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_Deinitialize();

	//=====================================================================================
	//=====================================================================================
	//����
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_Create(PLAYER_HANDLE *handle, int supportMaxChannel/*����ָ�����ͨ����, ����ܳ����궨��MAX_CHANNEL_NUM*/);
	//�ͷ�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_Release(PLAYER_HANDLE *handle);

	//=====================================================================================
	//=====================================================================================

	//����, ����һ��channelId, �������в����������ڸ�channelId
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_OpenStream(PLAYER_HANDLE handle, 
											EASY_CHANNEL_SOURCE_TYPE_ENUM channelType/*ͨ��Դ����*/, 
											const char *url, unsigned char rtpOverTcp/*1Ϊtcp, 0Ϊudp*/, 
											unsigned int mediaType, //ý������ MEDIA_TYPE_VIDEO | MEDIA_TYPE_AUDIO | MEDIA_TYPE_EVENT
											EasyPlayerProCallBack callback, void *userPtr, //�ص��������Զ���ָ��
											unsigned int reconnection/*1��ʾ���޴�����,0��ʾ������,����1��ʾָ����������(��С��1000)*/, 
											unsigned int heartbeatType/*0*/, 
											unsigned int queueSize/*������д�С,�����1024*512 */, 
											unsigned char multiplex/*0x01:����Դ,����ͬһ��urlʱ����ǰ�˵�����ֻ��һ��  0x00:�򿪶��ٸ�url,���ж��ٸ�����*/);
	//�ر���
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_CloseStream(PLAYER_HANDLE handle, int channelId);


	//��ʼ����     ��ͬһ����,��󲥷Ÿ������ܴ���5��, ���ֻ���� libEasyPlayerPro_OpenStream �������� libEasyPlayerPro_StartPlayStream ���޴�����
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_StartPlayStream(PLAYER_HANDLE handle, int channelId, HWND hWnd, 
													RENDER_FORMAT renderFormat, unsigned char decodeType=0/*0:��� 1:Ӳ��*/);
	//�ͱ�������ָ��ͨ��, �����libEasyPlayerPro_OpenStream�е�channelType==EASY_CHANNEL_SOURCE_TYPE_ENCODE_DATA��EASY_CHANNEL_SOURCE_TYPE_DECODE_DATA
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_PutFrameData(PLAYER_HANDLE handle, int channelId, int mediaType, EASY_FRAME_INFO *frameInfo, unsigned char *pbuf);
	//���֡����, ������һ���յ��Ĺؼ�֡��ʼ����
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_ResetFrameQueue(PLAYER_HANDLE handle, int channelId);
	//ֹͣ����
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_StopPlayStream(PLAYER_HANDLE handle, int channelId);

	//��ȡָ��ͨ����ý����Ϣ
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_GetStreamInfo(PLAYER_HANDLE handle, int channelId, EASY_MEDIA_INFO_T *pMediaInfo);

	//���ò���֡����, 1 - 10   ֡��ԽС��ʾ��ʱԽС
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SetPlayFrameCache(PLAYER_HANDLE handle, int channelId, int cache/*�����С  1 - 10*/);
	//��ȡ����֡����
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_GetPlayFrameCache(PLAYER_HANDLE handle, int channelId);



	//��ʾͳ����Ϣ
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_ShowStatisticalInfo(PLAYER_HANDLE handle, int channelId, unsigned char show);
	//�����Ƿ��������ʾ�ؼ�֡
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SetDecodeType(PLAYER_HANDLE handle, int channelId, unsigned char decodeKeyframeOnly);
	//������Ƶ��ת
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SetVideoFlip(PLAYER_HANDLE handle, int channelId, unsigned char flip);
	//������ʾ����
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SetRenderRect(PLAYER_HANDLE handle, int channelId, LPRECT lpRect);	//RECTΪ�ֱ��������
	//��������ʾ
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SetScaleDisplay(PLAYER_HANDLE handle, int channelId, 
														unsigned char scaleDisplay/*0x00:�������� 0x01:��������ʾ*/,
														COLORREF bkColor/*����ɫ*/);
	//���õ�������
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SetOverlayText(PLAYER_HANDLE handle, int channelId, const char *text);
	//��յ�������
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_ClearOverlayText(PLAYER_HANDLE handle, int channelId);


	//���ò����ٶ�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SetPlaySpeed(PLAYER_HANDLE handle, int channelId, PLAY_SPEED_ENUM speed);
	//��ȡ��ǰ�����ٶ�
	LIB_EASYPLAYER_PRO_API PLAY_SPEED_ENUM LIB_APICALL	libEasyPlayerPro_GetPlaySpeed(PLAYER_HANDLE handle, int channelId);

	//��֡����, �ɵ���libEasyPlayerPro_SetPlaySpeed�л�����������ģʽ
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_PlaySingleFrame(PLAYER_HANDLE handle, int channelId);
	//��ת��ָ��ʱ�䲥��
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_ChangePlayTime(PLAYER_HANDLE handle, int channelId, const char *playTime/*YYYYMMDDTHHMMSSZ  ��: 20170208T092700Z*/);
	//��ת��ָ��ʱ�䲥��(�ļ�)
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SeekFile(PLAYER_HANDLE handle, int channelId, const unsigned int playTimeSecs/*��*/);

	//============================================================
	//��ʼ�ֶ�¼��  ���ָ����¼���ļ���С,��¼��ʱ����Ч����filesizeΪ0, ��duration��Ч
	//���preRecording����Ϊ1, ����Ӧ���ļ���С���ļ�ʱ����������Ԥ¼�Ĵ�С��ʱ��, ��: ָ��filesizeΪ100MB,ͬʱpreRecording����Ϊ1, ��ʵ��¼���ļ���СΪ100MB+Ԥ¼��С
	//Ԥ¼��С��ʱ�������ڲ�ָ��Ϊ10��,����Ӧ�ڴ����libEasyPlayerPro_OpenStream�е�queueSizeָ��, ��:�ڴ�����㹻�����Ԥ¼ʱ��Ϊ10��, �ڴ����С,Ԥ¼ʱ������10��
	//   ע:   ��������ʱ�ط�ʱ���������ֶ�¼��, ���᷵��-3
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_StartRecording(PLAYER_HANDLE handle, int channelId, const char *foldername, const char *filename, 
														unsigned int filesize/*¼���ļ���С MB*/, int duration/*¼��ʱ��(second)*/,  
														unsigned char preRecording/*0x01:Ԥ¼  0x00:��Ԥ¼*/,
														unsigned char autoSegmentation/*�Զ��ָ��ļ�  0x01:¼��ָ����С��ʱ����,������һ���ļ�����¼��  0x00:¼��ָ����С��ʱ����,ֹͣ¼��*/);
	//ֹͣ�ֶ�¼��
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_StopRecording(PLAYER_HANDLE handle, int channelId);

	//ץͼ���ļ�, ֻ�����첽ץͼģʽ�£�����ʹ�ö���,�����ڴ�Ϊ31104000bytes(��ԼΪ32MB)
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SnapshotToFile(PLAYER_HANDLE handle, int channelId, unsigned char imageFormat/*0:bmp 1:jpg*/, 
														char *filename, unsigned char sync=0/*0:�첽: 1:ͬ��*/, 
														unsigned char useQueue=0/*1:ʹ�ö��� 0:��ʹ�ö���*/);



	//==============================================================================
	//==============================================================================
	//================���ӷŴ����==================================================
	//==============================================================================
	//==============================================================================
	//���÷Ŵ���ʼ��   fXPercent �� fYPercent Ϊ��굥���ĵ�����ڴ��ڵİٷֱ�   showBoxΪ�Ƿ���ʾ�����Ŀ�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SetElectronicZoomStartPoint(PLAYER_HANDLE handle, int channelId, float fXPercent, float fYPercent, unsigned char showBox);
	//���÷Ŵ������
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SetElectronicZoomEndPoint(PLAYER_HANDLE handle, int channelId, float fXPercent, float fYPercent);
	//�����Ƿ�Ŵ�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SetElectronicZoom(PLAYER_HANDLE handle, int channelId, int zoomIn/*1:�Ŵ�  0:���Ŵ�*/);
	//����Ŵ����
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_ResetElectronicZoom(PLAYER_HANDLE handle, int channelId);

	
	//==============================================================================
	//==============================================================================
	//================��ʱ�طż�����================================================
	//==============================================================================
	//==============================================================================
	//��ʼ��ʱ�ط�    �����ǰ�����ֶ�¼����, ���ܿ�����ʱ�ط�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_InstantReplay_Start(PLAYER_HANDLE handle, int channelId);
	//��ͣ��ʱ�ط�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_InstantReplay_Pause(PLAYER_HANDLE handle, int channelId);
	//�ָ���ʱ�ط�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_InstantReplay_Resume(PLAYER_HANDLE handle, int channelId);
	//ֹͣ��ʱ�ط�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_InstantReplay_Stop(PLAYER_HANDLE handle, int channelId);
	//���漴ʱ�ط�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_InstantReplay_Save(PLAYER_HANDLE handle, int channelId, char *filename/*�����ļ���������·��*/);
	//��һ֡
	//LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_InstantReplay_PreviousFrame(PLAYER_HANDLE handle, int channelId);
	//��һ֡
	//LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_InstantReplay_NextFrame(PLAYER_HANDLE handle, int channelId);
	//��ȡ��ʱ�ط��е�֡��
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_InstantReplay_GetFrameNum(PLAYER_HANDLE handle, int channelId, int *currentFrameNo, int *totalFrameNum);



	//==============================================================================
	//==============================================================================
	//==========����Ϊ�������ż�����================================================
	//==============================================================================
	//==============================================================================
	//��������
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_StartPlaySound(PLAYER_HANDLE handle, int channelId);
	//ֹͣ��������
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_StopPlaySound(PLAYER_HANDLE handle, int channelId);
	//��ȡ��������״̬: �Ƿ��ڲ�����		0:������, <0:�ǲ�����
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SoundPlaying(PLAYER_HANDLE handle, int channelId);


	//��ȡ��Ƶ�豸�б�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_GetAudioOutputDeviceList(PLAYER_HANDLE handle, MIXER_DEVICE_INFO_T	**devicelist, int *deviceNum);
	//���õ�ǰ��Ƶ�豸ID
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SetAudioOutputDeviceId(PLAYER_HANDLE handle, int deviceId);
	//���õ�ǰ��Ƶ�豸����
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SetAudioOutputDeviceName(PLAYER_HANDLE handle, char *deviceName);

	//�������� ( 0 ~ 100 )
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_SetAudioVolume(PLAYER_HANDLE handle, int volume);
	//��ȡ����
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_GetAudioVolume(PLAYER_HANDLE handle);





	//==============================================================================
	//==============================================================================
	//==========����Ϊ�����ɼ�����==================================================
	//==============================================================================
	//==============================================================================
	//��ȡ��ǰ��Ƶ�ɼ��豸
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_GetAudioCaptureDeviceList(PLAYER_HANDLE handle, int *deviceNum, EASY_AUDIO_CAPTURE_DEVICE_INFO **pDeviceInfo);
	//����Ƶ�ɼ��豸 && ��ȡ֧�ֵĸ�ʽ�б�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_OpenAudioCaptureDevice(PLAYER_HANDLE handle, int captureDeviceIndex, 
																			int *waveFormatNum, EASY_AUDIO_WAVE_FORMAT_INFO **ppWaveFormatEx);
	//��ʼ��Ƶ�ɼ�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_StartAudioCaptureById(PLAYER_HANDLE handle, int waveFormatExIndex, unsigned int codec, int frameSize, 
																			EasyPlayerProCallBack callback, void *userptr);
	//��ʼ��Ƶ�ɼ�  �Զ���ɼ���ʽ
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_StartAudioCaptureByParam(PLAYER_HANDLE handle, 
																			unsigned int codec/*��������: RTSP_AUDIO_CODEC_G711A  RTSP_AUDIO_CODEC_G711U RTSP_AUDIO_CODEC_AAC*/, 
																			int frameSize/*֡��С, g711ʱΪ160,320, aacʱΪ1024��2048*/, 
																			int samplerate/*������*/, int bitsPerSample/*��������*/, int channels/*ͨ��*/, 
																			EasyPlayerProCallBack callback, void *userptr);
	//ֹͣ��Ƶ�ɼ�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_StopAudioCapture(PLAYER_HANDLE handle);
	//�ر���Ƶ�ɼ��豸
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libEasyPlayerPro_CloseAudioCaptureDevice(PLAYER_HANDLE handle);

#ifdef __cplusplus
}
#endif


#if 0

//�ص�����ʾ������:

int CALLBACK __EasyPlayerProCallBack(EASY_CALLBACK_TYPE_ENUM callbackType, int channelId, void *userPtr, int mediaType, char *pbuf, EASY_FRAME_INFO *frameInfo)
{
	LIVE_VIDEO_T	*pLiveVideo = (LIVE_VIDEO_T *)userPtr;

	if (callbackType == EASY_TYPE_CODEC_DATA)	//��������
	{
		_TRACE(TRACE_LOG_DEBUG, "��������[ch%d]type[%d] channelId[%d] mediaType[%d] [%d x %d] framesize[%d]\n",  pLiveVideo->channelId,
			callbackType, channelId, mediaType, frameInfo->width, frameInfo->height, frameInfo->length);
	}
	else if (callbackType == EASY_TYPE_DECODE_DATA)
	{
		_TRACE(TRACE_LOG_DEBUG, "��������[ch%d]type[%d] channelId[%d] mediaType[%d] [%d x %d] framesize[%d]\n",  pLiveVideo->channelId,
			callbackType, channelId, mediaType, frameInfo->width, frameInfo->height, frameInfo->length);
	}
	else if (callbackType == EASY_TYPE_SNAPSHOT)
	{
		//ץ��ʱ, �ص���frameInfoΪNULL
		//mediaTypeΪMEDIA_TYPE_VIDEOʱ��ʾ�ɹ���ΪMEDIA_TYPE_EVENTʱ��ʾʧ��
		//pbufΪץ�ĵ��ļ���

		if (mediaType == MEDIA_TYPE_VIDEO)		//ץͼ�ɹ�
			_TRACE(TRACE_LOG_DEBUG, "ץ��ͼƬ�ɹ�[ch%d] %s. filename:%s\n",  channelId, mediaType==MEDIA_TYPE_VIDEO?"�ɹ�":"ʧ��", pbuf);
		else  if (mediaType == MEDIA_TYPE_EVENT)	//ץͼʧ��
			_TRACE(TRACE_LOG_DEBUG, "ץ��ͼƬʧ��[ch%d] %s. filename:%s\n",  channelId, mediaType==MEDIA_TYPE_VIDEO?"�ɹ�":"ʧ��", pbuf);
	}
	else if (callbackType == EASY_TYPE_RECORDING)
	{
		if (mediaType == MEDIA_TYPE_VIDEO)		//¼��ɹ�
			_TRACE(TRACE_LOG_DEBUG, "�ֶ�¼��ɹ�[ch%d] %s. filename:%s\n",  channelId, mediaType==MEDIA_TYPE_VIDEO?"�ɹ�":"ʧ��", pbuf);
		else  if (mediaType == MEDIA_TYPE_EVENT)	//¼��ʧ��
			_TRACE(TRACE_LOG_DEBUG, "�ֶ�¼��ʧ��[ch%d] %s. filename:%s\n",  channelId, mediaType==MEDIA_TYPE_VIDEO?"�ɹ�":"ʧ��", pbuf);
	}


	return 0;
}





#endif



#endif
