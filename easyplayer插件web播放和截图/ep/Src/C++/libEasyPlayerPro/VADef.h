#ifndef __VADEF_H__
#define __VADEF_H__

#include <stdlib.h>
#include <string.h>



//���ܷ������
#ifdef _DEBUG
#define		MAX_DETECT_POINT_NUM			100		//
#define		MAX_DETECT_ZONE_NUM				100
#define		MAX_DETECT_LINE_NUM				16
#define		MAX_DETECT_DIRECT_ZONE_NUM		4
#else
#define		MAX_DETECT_POINT_NUM			100		//
#define		MAX_DETECT_ZONE_NUM				100
#define		MAX_DETECT_LINE_NUM				16
#define		MAX_DETECT_DIRECT_ZONE_NUM		4
#endif



//��Ⱦģʽ
typedef enum __RENDER_MODE_ENUM
{
	RENDER_MODE_VIDEO			=	0x00,						//��Ⱦ��Ƶ
	RENDER_MODE_ZONE			=	0x00000001,					//�����
	RENDER_MODE_LINE			=	0x00000002,					//�����
	RENDER_MODE_DIRECT_ZONE		=	0x00000004,					//��������
	RENDER_MODE_LANE			=	0x00000008					//����

}RENDER_MODE_ENUM;

//��������
typedef enum __VA_WARN_TYPE_ENUM
{
	VA_WARN_TYPE_OFF		=	0x00,
	VA_WARN_TYPE_ON			=	0x01
}VA_WARN_TYPE_ENUM;

//����ȼ�
typedef enum __VA_WARN_GRADE_ENUM
{
	VA_WARN_GRADE_HIGH	=	0x01,
	VA_WARN_GRADE_MIDDLE,
	VA_WARN_GRADE_LOW
}VA_WARN_GRADE_ENUM;


typedef struct __VA_DETECT_POINT_T
{
	int			id;
	char		name[36];
	int			x;
	int			y;
	float		xPercent;
	float		yPercent;
}VA_DETECT_POINT_T;

//�����
typedef struct __VA_DETECT_ZONE_T
{
	int			id;
	char		name[36];
	VA_WARN_TYPE_ENUM	warnType;			//��������
	VA_WARN_GRADE_ENUM	warnGrade;			//����ȼ�

	unsigned char	show;					//�Ƿ���ʾ
	unsigned char	hasArrow;				//�Ƿ��м�ͷ
	unsigned char	fill;					//�Ƿ���Ҫ�����ɫ
	unsigned char	selected;				//�Ƿ�ѡ��
	unsigned char	complete;				//����������
	unsigned char	movePoint;				//�ƶ�����
	unsigned char	moveArrow;				//�ƶ���ͷ����
	unsigned char	moveZone;				//�ƶ�����
	COLORREF		borderColor;
	COLORREF		textColor;
	COLORREF		color;
	int			alpha_normal;				//����͸����
	int			alpha_selected;				//��ѡ��ʱ͸����

	int			min_point_num;				//��С������
	int			max_point_num;				//�����Ƶ���󶥵���, ���ܴ���MAX_DETECT_POINT_NUM
	int			point_num;
	VA_DETECT_POINT_T	point[MAX_DETECT_POINT_NUM];

	VA_DETECT_POINT_T	ptCenter;			//��ͷ���ĵ�
	VA_DETECT_POINT_T	ptArrow;			//��ͷλ��
	VA_DETECT_POINT_T	ptMove;
}VA_DETECT_ZONE_T;


typedef enum __VA_DIRECTION_ENUM
{
	VA_DIRECTION_LEFT2RIGHT		=	0x00,		//������
	VA_DIRECTION_RIGHT2LEFT,					//���ҵ���
	VA_DIRECTION_TWO_WAY						//˫��
}VA_DIRECTION_ENUM;

//�����
typedef struct __VA_DETECT_LINE_T
{
	int			id;
	char		name[36];
	int			selected;
	int			complete;				//
	VA_DIRECTION_ENUM	direction;			//�����߷���0Ϊ�����ң�����ˮƽ�ߣ���1Ϊ���ҵ���2Ϊ˫��
	int			point_num;
	VA_DETECT_POINT_T	point[2];
}VA_DETECT_LINE_T;

//������б�
typedef struct __VA_DETECT_ZONE_LIST_T
{
	VA_DETECT_ZONE_T			zone;
	__VA_DETECT_ZONE_LIST_T	*next;
}VA_DETECT_ZONE_LIST_T;

//������б�
typedef struct __VA_DETECT_LINE_LIST_T
{
	VA_DETECT_LINE_T			line;
	__VA_DETECT_LINE_LIST_T	*next;
}VA_DETECT_LINE_LIST_T;


#endif
