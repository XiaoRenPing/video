#ifndef __SYS_COMMON_H__
#define __SYS_COMMON_H__


#include <winsock2.h>

typedef struct __SYS_PARAM_T
{
	unsigned char	showVideoTitlebar;	//��ʾ��Ƶ���ڱ�����

	unsigned int	renderFormat;
	int				frameCache;		//��Ƶ֡����
	int				queueSize;		//���Ӷ���
	unsigned char	renderMetadata;
	int				patrolTime;		//��Ѳ���ʱ��

	int				record_filesize;	//�ļ���С
	int				record_times;		//�ļ�ʱ��
	char			szRecordingPath[MAX_PATH];
	char			szSnapshotPath[MAX_PATH];
}SYS_PARAM_T;


int		InitialSysParams();
SYS_PARAM_T *GetSysParams();
int		SaveSysParams();

#endif
