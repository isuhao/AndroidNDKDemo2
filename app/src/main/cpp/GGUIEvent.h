//------------------------------------------------------------
#ifndef _GGUIEvent_h_
#define _GGUIEvent_h_
//------------------------------------------------------------
enum GGUIEventType
{
	GGUIEvent_Invalid = -1,
	GGUIEvent_WindowRectEnter,
	GGUIEvent_WindowRectLeave,
	GGUIEvent_PosChangedByDrag, //���������ק���µ�λ���ƶ�
	GGUIEvent_Button_Clicked, //��ť������
	GGUIEvent_ScrollBar_PosChanged, //�������Ļ��鷢����λ���ƶ�
};
//------------------------------------------------------------
struct GGUIEventParam_WindowRectEnter
{
	const char* szWindowName;
	int nWindowID;
};
//------------------------------------------------------------
struct GGUIEventParam_WindowRectLeave
{
	const char* szWindowName;
	int nWindowID;
};
//------------------------------------------------------------
struct GGUIEventParam_ButtonClick
{
	const char* szWindowName;
	int nWindowID;
};
//------------------------------------------------------------
struct GGUIEventParam_PosChangedByDrag
{
	const char* szWindowName;
	int nWindowID;
};
//------------------------------------------------------------
struct GGUIEventParam_ScrollBar_PosChanged
{
	const char* szWindowName;
	int nWindowID;
	float fNewValue;
};
//------------------------------------------------------------
#endif //_GGUIEvent_h_
//------------------------------------------------------------
