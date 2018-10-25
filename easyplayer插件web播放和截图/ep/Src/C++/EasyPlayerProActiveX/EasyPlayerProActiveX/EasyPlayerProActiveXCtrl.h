#pragma once

#include "MainVideoWnd.h"
#include "EasyPlayerProManager.h"

// EasyPlayerProActiveXCtrl.h : CEasyPlayerProActiveXCtrl ActiveX �ؼ����������

// CEasyPlayerProActiveXCtrl : �й�ʵ�ֵ���Ϣ������� EasyPlayerProActiveXCtrl.cpp��

class CEasyPlayerProActiveXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CEasyPlayerProActiveXCtrl)

// ���캯��
public:
	CEasyPlayerProActiveXCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual void OnSetClientSite();

// ʵ��
protected:
	~CEasyPlayerProActiveXCtrl();

	BEGIN_OLEFACTORY(CEasyPlayerProActiveXCtrl)        // �๤���� guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR *);
	END_OLEFACTORY(CEasyPlayerProActiveXCtrl)

	DECLARE_OLETYPELIB(CEasyPlayerProActiveXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CEasyPlayerProActiveXCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CEasyPlayerProActiveXCtrl)		// �������ƺ�����״̬

// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();

// ����ӳ��
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
		dispiSeekFile = 12L,
		dispiPlaySingleFrame = 11L,
		dispiSetPlaySpeed = 10L,
		dispiGetAudioVolume = 9L,
		dispiSetAudioVolume = 8L,
		dispiPlaySound = 7L,
		dispiSnapshot = 6L,
		dispiStopRecord = 5L,
		dispiStartRecord = 4L,
		dispiSetOSD = 3L,
		dispidClose = 2L,
		dispidStart = 1L
	};

	//�ӿں���
public:
	//����
// 	int Start(char* szURL, HWND hShowWnd, RENDER_FORMAT renderFormat,  int nRTPOverTCP, int nCache, 
// 		BOOL bShownToScale, BOOL bPlaySound, BOOL bStatisticalInfo);
// 	//�ر���
// 	int Close(void);
// 	int InRunning();
// 
// 	//����OSD
// 	int SetOSD(int show, const char* osd);
// 
// 	//¼��
// 	int StartRecord(const char *foldername, 
// 		const char *filename, 
// 		unsigned int filesize/*¼���ļ���С MB*/, int duration/*¼��ʱ��(second)*/,  
// 		unsigned char preRecording/*0x01:Ԥ¼  0x00:��Ԥ¼*/);
// 	int StopRecord();
// 
// 	//ץͼ
// 	int Snapshot( 
// 		char *filename, unsigned char sync=0/*0:�첽: 1:ͬ��*/, 
// 		unsigned char useQueue=0/*1:ʹ�ö��� 0:��ʹ�ö���*/);
// 
// 	//�������źͿ���
// 	int PlaySound(BOOL bPlay);
// 	int SetAudioVolume( int volume);
// 	int GetAudioVolume();
// 
// 	//���ſ���
// 	// ���ò����ٶ�(�ļ�)
// 	int SetPlaySpeed(PLAY_SPEED_ENUM speed);
// 	//��֡����, �ɵ���libEasyPlayerPro_SetPlaySpeed�л�����������ģʽ
// 	int PlaySingleFrame();
// 	//��ת��ָ��ʱ�䲥��(�ļ�)
// 	int SeekFile( unsigned int playTimeSecs/*��*/ );

	LONG Start(LPCTSTR sURL, LPCTSTR sRenderFormat, LPCTSTR sRTPOverTCP, LPCTSTR sCache, 
		LPCTSTR sShownToScale, LPCTSTR sPlaySound, LPCTSTR sStatisticalInfo);
	void Close(void);
	void SetOSD(LPCTSTR show, LPCTSTR osd);

	//¼��
	LONG StartRecord(LPCTSTR sFoldername, LPCTSTR sFilename, 
		LPCTSTR sFilesize/*¼���ļ���С MB*/, LPCTSTR sDuration/*¼��ʱ��(second)*/,  
		LPCTSTR sPreRecording/*0x01:Ԥ¼  0x00:��Ԥ¼*/);
	LONG StopRecord();

	//ץͼ
	LONG Snapshot( LPCTSTR sFilename);

	//�������źͿ���
	LONG PlaySound(LPCTSTR sbPlay);
	LONG SetAudioVolume( LPCTSTR sVolume);
	LONG GetAudioVolume();

	//���ſ���
	// ���ò����ٶ�(�ļ�)
	LONG SetPlaySpeed(LPCTSTR sSpeed);
	//��֡����, �ɵ���libEasyPlayerPro_SetPlaySpeed�л�����������ģʽ
	LONG PlaySingleFrame();
	//��ת��ָ��ʱ�䲥��(�ļ�)
	LONG SeekFile( LPCTSTR sPlayTimeSecs/*��*/ );
private:
	CMainVideoWnd m_pActiveDlg; 
	EasyPlayerProManager m_player;

	//���ò���
	char m_szURL[512] ;
	RENDER_FORMAT m_eRenderFormat;
	int  m_nRTPOverTCP ;
	int	   m_nFrameCache ;
	BOOL m_bPlaySound ;
	BOOL m_bShowToScale ;
	BOOL m_bShowStatisticInfo ;

};

