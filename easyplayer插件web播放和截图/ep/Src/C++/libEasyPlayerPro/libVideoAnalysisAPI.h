#ifndef __LIB_VIDEO_ANALYSIS_API_H__
#define __LIB_VIDEO_ANALYSIS_API_H__

#include "libEasyPlayerProAPI.h"
#include "VADef.h"

	//==============================================================================
	//==============================================================================
	//==========����Ϊ��Ƶ��������==================================================
	//==============================================================================
	//==============================================================================

#ifdef __cplusplus
extern "C"
{
#endif

	//������Ⱦģʽ  ��mode����ΪRENDER_MODE_ZONEANDRULEʱ, ��ʾ�ֱ����Զ�����Ϊ SCALE_RESOLUTION_WIDTH x SCALE_RESOLUTION_HEIGHT
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetRenderMode(PLAYER_HANDLE handle, int channelId, RENDER_MODE_ENUM mode);
	//��ȡ��Ⱦģʽ
	LIB_EASYPLAYER_PRO_API RENDER_MODE_ENUM LIB_APICALL	libVA_GetRenderMode(PLAYER_HANDLE handle, int channelId);


	//���þ�������������  1Ϊ������ 0Ϊ������
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetWarningType(PLAYER_HANDLE handle, int channelId, VA_WARN_TYPE_ENUM type);
	//����ȫ������
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetFullWarning(int channelId);

	//���þ������ȼ�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetWarningGrade(PLAYER_HANDLE handle, int channelId, VA_WARN_GRADE_ENUM grade);

	//��ʾ���о�������
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_ShowAllWarningArea(PLAYER_HANDLE handle, int channelId, unsigned char show);

	//��Ӿ�������ڵ�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_AddWarningAreaNode(PLAYER_HANDLE handle, int channelId, VA_DETECT_POINT_T *p);
	//���¾�������ڵ�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_UpdateWarningAreaNode(PLAYER_HANDLE handle, int channelId, VA_DETECT_POINT_T *p);
	//����������������ڵ�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_EndWarningAreaNode(PLAYER_HANDLE handle, int channelId);

	//ɾ���������, //modeΪSetWarningMode�е�mode,��Ϊ�����������ߡ���������������
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_DeleteWarningAreaAndLine(PLAYER_HANDLE handle, int channelId, int mode, int delete_all, int areaOrLineId);

	//��������ʱ�İٷֱ�, ���յ�ǰ��rect,����λ�õ�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_UpdateWarningAreaPosition(PLAYER_HANDLE handle, int channelId, LPRECT lpRect);

	//��ȡ�������б�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_GetWarningAreaList(PLAYER_HANDLE handle, int channelId, VA_DETECT_ZONE_LIST_T **list);
	//���þ������б�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetWarningAreaList(PLAYER_HANDLE handle, int channelId, VA_DETECT_ZONE_LIST_T *list, int num);
	//���þ����߷���
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetWarningLineDirection(PLAYER_HANDLE handle, int channelId, VA_DIRECTION_ENUM _direction);
	//���ݾ�����id �޸ľ����߷���
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetWarningLineDirectionById(PLAYER_HANDLE handle, int channelId, int lineId, VA_DIRECTION_ENUM _direction);
	//��ȡ�������б�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_GetWarningLineList(PLAYER_HANDLE handle, int channelId, VA_DETECT_LINE_LIST_T **list);
	//���þ������б�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetWarningLineList(PLAYER_HANDLE handle, int channelId, VA_DETECT_LINE_LIST_T *list, int num);



	//����Զ�������
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_AddCustomZoneNode(PLAYER_HANDLE handle, int channelId, int id, char *name, 
															VA_DETECT_POINT_T *p, unsigned char hasArrow, unsigned char fill, int minPointNum,int maxPointNum, 
															unsigned char checkOverlap, 
															COLORREF zoneColor, COLORREF borderColor, COLORREF textColor, 
															int maxZoneNum, int alphaNormal, int alphaSelected);
	//�ƶ��Զ�������ڵ�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_MoveCustomZoneNode(PLAYER_HANDLE handle, int channelId, VA_DETECT_POINT_T *p, 
															unsigned char keyRelease/*LButtonUp�¼�ʱ��ֵΪ1*/, unsigned char checkOverlap);
	//�������Ƶ�ǰ�Զ�������
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_EndCustomZoneNode(PLAYER_HANDLE handle, int channelId, unsigned char checkOverlap);	//�������Ƶ�ǰ����

	//ɾ���Զ�������
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_DeleteCustomZone(PLAYER_HANDLE handle, int channelId, 
																unsigned char deleteAll, char *name, int zoneId, unsigned char updateId);	//ɾ������

	//��ʾָ��ID���Զ����������ʾȫ������
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_ShowCustomZoneById(PLAYER_HANDLE handle, int channelId, int id);				//��ʾȫ��  or ��ʾָ��ID������

	//��������ʱ�İٷֱ�, ���յ�ǰ��rect,����λ�õ�
	LIB_EASYPLAYER_PRO_API void LIB_APICALL	libVA_UpdateCustomZonePosition(PLAYER_HANDLE handle, int channelId, LPRECT lpRect);

	//��ȡ�����Զ�������
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_GetCusromZone(PLAYER_HANDLE handle, int channelId, VA_DETECT_ZONE_LIST_T **list, int *num);

	//�����Զ��������б�
	LIB_EASYPLAYER_PRO_API int LIB_APICALL	libVA_SetCustomZone(PLAYER_HANDLE handle, int channelId, VA_DETECT_ZONE_LIST_T *list, int num);

#ifdef __cplusplus
}
#endif


#endif
