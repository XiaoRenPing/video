#pragma once

// EasyPlayerProActiveXPropPage.h : CEasyPlayerProActiveXPropPage ����ҳ���������


// CEasyPlayerProActiveXPropPage : �й�ʵ�ֵ���Ϣ������� EasyPlayerProActiveXPropPage.cpp��

class CEasyPlayerProActiveXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CEasyPlayerProActiveXPropPage)
	DECLARE_OLECREATE_EX(CEasyPlayerProActiveXPropPage)

// ���캯��
public:
	CEasyPlayerProActiveXPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_EASYPLAYERPROACTIVEX };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};

