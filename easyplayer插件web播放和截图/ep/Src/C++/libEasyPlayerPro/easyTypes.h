
#ifndef __EASY_TYPES_H__
#define __EASY_TYPES_H__

#ifdef _WIN32
#define LIB_EASYPLAYER_PRO_API  __declspec(dllexport)
#ifndef LIB_APICALL
#define LIB_APICALL  __stdcall
#endif
#define WIN32_LEAN_AND_MEAN
#else
#define LIB_EASYPLAYER_PRO_API
#define LIB_APICALL 
#endif

#ifdef _WIN32
#define Easy_API  __declspec(dllexport)
#define Easy_APICALL  __stdcall
#define WIN32_LEAN_AND_MEAN
#else
#define Easy_API
#define Easy_APICALL 
#endif

// Handle Type
#define Easy_RTSP_Handle void*
#define Easy_Pusher_Handle void*
#define Easy_HLS_Handle void*

typedef int						Easy_I32;

typedef unsigned char           Easy_U8;
typedef unsigned char           Easy_UChar;
typedef unsigned short          Easy_U16;
typedef unsigned int            Easy_U32;
typedef unsigned char			Easy_Bool;

enum
{
	Easy_NoErr = 0,
	Easy_RequestFailed = -1,
	Easy_Unimplemented = -2,
	Easy_RequestArrived = -3,
	Easy_OutOfState = -4,
	Easy_NotAModule = -5,
	Easy_WrongVersion = -6,
	Easy_IllegalService = -7,
	Easy_BadIndex = -8,
	Easy_ValueNotFound = -9,
	Easy_BadArgument = -10,
	Easy_ReadOnly = -11,
	Easy_NotPreemptiveSafe = -12,
	Easy_NotEnoughSpace = -13,
	Easy_WouldBlock = -14,
	Easy_NotConnected = -15,
	Easy_FileNotFound = -16,
	Easy_NoMoreData = -17,
	Easy_AttrDoesntExist = -18,
	Easy_AttrNameExists = -19,
	Easy_InstanceAttrsNotAllowed = -20,
	Easy_InvalidSocket = -21,
	Easy_MallocError = -22,
	Easy_ConnectError = -23,
	Easy_SendError = -24
};
typedef int Easy_Error;


typedef enum __EASY_ACTIVATE_ERR_CODE_ENUM
{
	EASY_ACTIVATE_INVALID_KEY = -1,			/* ��ЧKey */
	EASY_ACTIVATE_TIME_ERR = -2,			/* ʱ����� */
	EASY_ACTIVATE_PROCESS_NAME_LEN_ERR = -3,			/* �������Ƴ��Ȳ�ƥ�� */
	EASY_ACTIVATE_PROCESS_NAME_ERR = -4,			/* �������Ʋ�ƥ�� */
	EASY_ACTIVATE_VALIDITY_PERIOD_ERR = -5,			/* ��Ч��У�鲻һ�� */
	EASY_ACTIVATE_PLATFORM_ERR = -6,			/* ƽ̨��ƥ�� */
	EASY_ACTIVATE_COMPANY_ID_LEN_ERR = -7,			/* ��Ȩʹ���̲�ƥ�� */
	EASY_ACTIVATE_SUCCESS = 0,			/* ����ɹ� */

}EASY_ACTIVATE_ERR_CODE_ENUM;


//ý������
#ifndef MEDIA_TYPE_VIDEO
#define MEDIA_TYPE_VIDEO		0x00000001
#endif
#ifndef MEDIA_TYPE_AUDIO
#define MEDIA_TYPE_AUDIO		0x00000002
#endif
#ifndef MEDIA_TYPE_EVENT
#define MEDIA_TYPE_EVENT		0x00000004
#endif
#ifndef MEDIA_TYPE_RTP
#define MEDIA_TYPE_RTP			0x00000008
#endif
#ifndef MEDIA_TYPE_SDP
#define MEDIA_TYPE_SDP			0x00000010
#endif
#ifndef MEDIA_TYPE_CODEC_INFO
#define	MEDIA_TYPE_CODEC_INFO	0x00000020
#endif


typedef enum __RTSP_SERVER_ERROR_CODE_ENUM
{
	RTSP_SERVER_ERR_NoErr			=	0,
	RTSP_SERVER_ERR_NotInitialized	=	-1,			//û�г�ʼ��
	RTSP_SERVER_ERR_BadArgument		=	-2,			//��������
	RTSP_SERVER_ERR_ALLOC_MEMORY	=	-3,			//�ڴ����ʧ��
	RTSP_SERVER_ERR_OPERATE			=	-4,			//����ʧ��
}RTSP_SERVER_ERROR_CODE_ENUM;


//video codec
#define	VIDEO_CODEC_H264	0x1C
#define VIDEO_CODEC_H265	0xAE	/* 174 */
#define	VIDEO_CODEC_MJPEG	0x08
#define	VIDEO_CODEC_MPEG4	0x0D
//audio codec
#define AUDIO_CODEC_MP3		0x15001		//86017
#define AUDIO_CODEC_MP4A	0x15002		//86018
#define AUDIO_CODEC_PCMU	0x10006		//65542	g711 ulaw
#define AUDIO_CODEC_PCMA	0x10007		//g711 alaw
#define AUDIO_CODEC_G726	0x1100B		//69643	g726
//event codec
#define	EVENT_CODEC_ERROR	0x63657272	//cerr
#define EVENT_CODEC_RECONN	0x7265636F	//reco
#define	EVENT_CODEC_EXIT	0x65786974	//exit
#define	EVENT_CODEC_FILE_INFO	0x696E666F	//info


//��Ƶ�ؼ��ֱ�ʶ
//#define RTSP_VIDEO_FRAME_I		0x01		//I֡
#define FRAME_TYPE_I		0x01		//I֡
#define FRAME_TYPE_P		0x02		//P֡
#define FRAME_TYPE_B		0x03		//B֡
#define FRAME_TYPE_J		0x04		//JPEG



//��������
typedef enum __RTP_CONNECT_TYPE_ENUM
{
	RTP_OVER_TCP	=	0x01,
	RTP_OVER_UDP
}RTP_CONNECT_TYPE_ENUM;

// �����ٶ�
typedef enum __PLAY_SPEED_ENUM
{	
	PLAY_SPEED_UNKNOWN	=	-1,
	PLAY_SPEED_NORMAL	=	0x00,		// ��������
	PLAY_SPEED_PAUSED,					// ��ͣ
	PLAY_SPEED_SLOW_X2,					// 1/2
	PLAY_SPEED_SLOW_X4,					// 1/4
	PLAY_SPEED_SLOW_X8,					// 1/8
	PLAY_SPEED_SLOW_X16,				// 1/16
	PLAY_SPEED_FAST_X2,					// x2
	PLAY_SPEED_FAST_X4,					// x4
	PLAY_SPEED_FAST_X8,					// x8
	PLAY_SPEED_FAST_X16,				// x16
	PLAY_SPEED_REWIND_X2,				// -2x
	PLAY_SPEED_REWIND_X4,				// -4x
	PLAY_SPEED_REWIND_X8,				// -8x	
	PLAY_SPEED_REWIND_X16,				// -16x

	PLAY_SPEED_SINGLE_FRAME,			//��֡����,�ֶ�����
}PLAY_SPEED_ENUM;


//ý����Ϣ
typedef struct __EASY_MEDIA_INFO_T
{
	unsigned int videoCodec;			//��Ƶ��������
	unsigned int videoFps;				//��Ƶ֡��
	int			 videoWidth;
	int			 videoHeight;
	float		 videoBitrate;

	unsigned int audioCodec;			//��Ƶ��������
	unsigned int audioSampleRate;		//��Ƶ������
	unsigned int audioChannel;			//��Ƶͨ����
	unsigned int audioBitsPerSample;	//��Ƶ��������

	unsigned int metadataCodec;			//Metadata����

	unsigned int vpsLength;				//��Ƶvps֡����
	unsigned int spsLength;				//��Ƶsps֡����
	unsigned int ppsLength;				//��Ƶpps֡����
	unsigned int seiLength;				//��Ƶsei֡����
	unsigned char	 vps[255];			//��Ƶvps֡����
	unsigned char	 sps[255];			//��Ƶsps֡����
	unsigned char	 pps[128];			//��Ƶsps֡����
	unsigned char	 sei[128];			//��Ƶsei֡����
}EASY_MEDIA_INFO_T;

/* ý����Ϣ */
typedef struct __EASY_IPC_MEDIA_INFO_T
{
	Easy_U32 u32VideoCodec;				/* ��Ƶ�������� */
	Easy_U32 u32VideoFps;				/* ��Ƶ֡�� */

	Easy_U32 u32AudioCodec;				/* ��Ƶ�������� */
	Easy_U32 u32AudioSamplerate;		/* ��Ƶ������ */
	Easy_U32 u32AudioChannel;			/* ��Ƶͨ���� */
	Easy_U32 u32AudioBitsPerSample;		/* ��Ƶ�������� */

	Easy_U32 u32VpsLength;			/* ��Ƶvps֡���� */
	Easy_U32 u32SpsLength;			/* ��Ƶsps֡���� */
	Easy_U32 u32PpsLength;			/* ��Ƶpps֡���� */
	Easy_U32 u32SeiLength;			/* ��Ƶsei֡���� */
	Easy_U8	 u8Vps[255];			/* ��Ƶvps֡���� */
	Easy_U8	 u8Sps[255];			/* ��Ƶsps֡���� */
	Easy_U8	 u8Pps[128];				/* ��Ƶsps֡���� */
	Easy_U8	 u8Sei[128];				/* ��Ƶsei֡���� */
}EASY_IPC_MEDIA_INFO_T;

/* ֡��Ϣ */
typedef struct
{
	unsigned int	codec;				/* ����Ƶ��ʽ */

	unsigned int	type;				/* ��Ƶ֡���� */
	unsigned char	fps;				/* ��Ƶ֡�� */
	unsigned short	width;				/* ��Ƶ�� */
	unsigned short  height;				/* ��Ƶ�� */

	unsigned int	reserved1;			/* ��������1 */
	unsigned int	reserved2;			/* ��������2 */

	unsigned int	sample_rate;		/* ��Ƶ������ */
	unsigned int	channels;			/* ��Ƶ������ */
	unsigned int	bits_per_sample;	/* ��Ƶ�������� */

	unsigned int	length;				/* ����Ƶ֡��С */
	unsigned int    timestamp_usec;		/* ʱ���,΢�� */
	unsigned int	timestamp_sec;		/* ʱ��� �� */

	float			bitrate;			/* ������ */
	float			losspacket;			/* ������ */
}RTSP_FRAME_INFO;


#endif
