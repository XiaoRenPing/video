// EasyPlayerProActiveXPropPage.cpp : CEasyPlayerProActiveXPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "EasyPlayerProActiveX.h"
#include "EasyPlayerProActiveXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CEasyPlayerProActiveXPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CEasyPlayerProActiveXPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CEasyPlayerProActiveXPropPage, "EASYPLAYERPROA.EasyPlayerProAPropPage.1",
	0x7e6e2fe0, 0xde0e, 0x4191, 0x84, 0x32, 0xfa, 0x80, 0xef, 0x21, 0x52, 0x72)



// CEasyPlayerProActiveXPropPage::CEasyPlayerProActiveXPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CEasyPlayerProActiveXPropPage ��ϵͳע�����

BOOL CEasyPlayerProActiveXPropPage::CEasyPlayerProActiveXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_EASYPLAYERPROACTIVEX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CEasyPlayerProActiveXPropPage::CEasyPlayerProActiveXPropPage - ���캯��

CEasyPlayerProActiveXPropPage::CEasyPlayerProActiveXPropPage() :
	COlePropertyPage(IDD, IDS_EASYPLAYERPROACTIVEX_PPG_CAPTION)
{
}



// CEasyPlayerProActiveXPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CEasyPlayerProActiveXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CEasyPlayerProActiveXPropPage ��Ϣ�������
