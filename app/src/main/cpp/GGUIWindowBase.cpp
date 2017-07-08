//----------------------------------------------------------------
#include "GGUIWindowBase.h"
#include "GGUIWindowFactory.h"
#include "WinInputMsg.h"
#include "GGUIEvent.h"
//----------------------------------------------------------------
GGUIWindowBase::GGUIWindowBase()
:m_nID(-1)
,m_nParentID(-1)
,m_eType(GGUIWindow_Invalid)
,m_pUIEventHandler(0)
,m_bDragEnable(false)
,m_bCursorIsInside(false)
{
	
}
//----------------------------------------------------------------
GGUIWindowBase::~GGUIWindowBase()
{

}
//----------------------------------------------------------------
void GGUIWindowBase::ClearWindow()
{
	//��Factory���յ�Window����ParentID����-1��
	//ֻҪParentIDΪ-1�����Window���ڱ����մ�����״̬��
	//
	//m_nID = -1;
	//m_eType = GGUIWindow_Invalid;
	m_nParentID = -1;
	m_kName.Clear();
	m_pUIEventHandler = 0;
	m_kFullRect = GGUIFullRect_Empty;
	m_kRectInAbsCoord = GGUIRect_Empty;
	m_kParentRectInAbsCoord = GGUIRect_Empty;
	m_kUnvisibleReason.Clear();
	m_kInputDisableReason.Clear();
	m_bCursorIsInside = false;
}
//----------------------------------------------------------------
void GGUIWindowBase::UpdateWindow(float fDeltaTime)
{
	//do nothing
}
//----------------------------------------------------------------
void GGUIWindowBase::RenderWindow()
{
	//do nothing
}
//----------------------------------------------------------------
bool GGUIWindowBase::InputWindow(stInputEvent* pInputEvent)
{
	if (GetVisible() == false)
	{
		//�����಻Ҫ�ٴ���input��
		return true;
	}
	if (GetInputEnable() == false)
	{
		//�����಻Ҫ�ٴ���input��
		return true;
	}
	if (m_pUIEventHandler == 0)
	{
		//�����಻Ҫ�ٴ���input��
		return true;
	}
	if (GGUIInputState::m_nWindoeID_CursorDrag != -1 && GGUIInputState::m_nWindoeID_CursorDrag != m_nID)
	{
		//�д������ڴ�����ק�У����Ҹô��ڲ��Ǳ����ڡ�
		//�����಻Ҫ�ٴ���input��
		return true;
	}
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//�ж�����Ƿ�λ�ڴ��ڷ�Χ�ڡ�
	bool bIsInside = false;
	if (m_nID == GGUIInputState::m_nWindoeID_CursorDrag)
	{
		//���������ק�����ڣ�����Ϊ�������λ�ڴ��ڷ�Χ�ڡ�
		//����Ϊ�˷�ֹ�������������
		//�����ק�����У����˲�们��̫�죬��ǰ֡������Ƴ��˱����ڷ�Χ��
		//�����жϳ��ˡ�����뿪���ڷ�Χ������ק�жϡ�
		bIsInside = true;
	}
	else
	{
		bIsInside = m_kRectInAbsCoord.IsInside((float)pInputEvent->nParam1, (float)pInputEvent->nParam2);
	}
	if (bIsInside)
	{
		//���λ�ڴ��ڷ�Χ�ڡ�
		if (m_eType == GGUIWindow_Panel)
		{
			//��������һ��Panel�����ܰ����е���Ϣ�����ɵ���
			//���磬��������һ��ȫ�����ڣ���������е���Ϣ�����ɵ�����ô����ģ����Զ������Ӧ��Ϣ�ˡ�
			//Panel����ֻ������ɴ�����ק����Ϣ��
		}
		else
		{
			pInputEvent->Swallow();
		}
	}
	m_bCursorIsInside = bIsInside;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//��ⴰ����ק�߼���
	if (GetDragEnable())
	{
		if (InputDragLogic(pInputEvent))
		{
			//������ק�С�
			//ֻ������ק�������������¼���ֱ���˳���
			//�����಻Ҫ�ٴ���input��
			return true;
		}
	}
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//����Ƿ�Ҫ�׳��������봰�����򡱻��ߡ�����뿪���������¼���
	if (InputWindowRectLogic())
	{
		//�׳����¼��������������¼���ֱ���˳���
		//�����಻Ҫ�ٴ���input��
		return true;
	}
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	return false;
}
//----------------------------------------------------------------
void GGUIWindowBase::ProcessUIEvent(int nEventType, void* pParam)
{
	//do nothing
}
//----------------------------------------------------------------
void GGUIWindowBase::SetFullRect(const GGUIFullRect& kRect)
{
	m_kFullRect = kRect;
	CalculateRectInAbsCoord();
}
//----------------------------------------------------------------
void GGUIWindowBase::SetFullRectScalePos(float fScaleX, float fScaleY)
{
	m_kFullRect.fScaleX = fScaleX;
	m_kFullRect.fScaleY = fScaleY;
	CalculateRectInAbsCoord();
}
//----------------------------------------------------------------
void GGUIWindowBase::SetFullRectDeltaPos(float fDeltaX, float fDeltaY)
{
	m_kFullRect.fDeltaX = fDeltaX;
	m_kFullRect.fDeltaY = fDeltaY;
	CalculateRectInAbsCoord();
}
//----------------------------------------------------------------
void GGUIWindowBase::MoveDelta(float fDeltaX, float fDeltaY)
{
	m_kFullRect.fDeltaX += fDeltaX;
	m_kFullRect.fDeltaY += fDeltaY;
	CalculateRectInAbsCoord();
}
//----------------------------------------------------------------
void GGUIWindowBase::OnParentRectChanged(const GGUIRect& kParentRectInAbsCoord)
{
	m_kParentRectInAbsCoord = kParentRectInAbsCoord;
	CalculateRectInAbsCoord();
}
//----------------------------------------------------------------
void GGUIWindowBase::SetVisibleByReason(souint32 uiReason, bool bVisible)
{
	if (bVisible)
	{
		m_kUnvisibleReason.RemoveFlag(uiReason);
	}
	else
	{
		m_kUnvisibleReason.AddFlag(uiReason);
	}
}
//----------------------------------------------------------------
void GGUIWindowBase::SetInputEnableByReason(souint32 uiReason, bool bEnable)
{
	if (bEnable)
	{
		m_kInputDisableReason.RemoveFlag(uiReason);
	}
	else
	{
		m_kInputDisableReason.AddFlag(uiReason);
	}
}
//----------------------------------------------------------------
void GGUIWindowBase::CalculateRectInAbsCoord()
{
	m_kRectInAbsCoord.x = m_kParentRectInAbsCoord.x + m_kParentRectInAbsCoord.w * m_kFullRect.fScaleX + m_kFullRect.fDeltaX;
	m_kRectInAbsCoord.y = m_kParentRectInAbsCoord.y + m_kParentRectInAbsCoord.h * m_kFullRect.fScaleY + m_kFullRect.fDeltaY;
	m_kRectInAbsCoord.w = m_kParentRectInAbsCoord.w * m_kFullRect.fScaleW + m_kFullRect.fDeltaW;
	m_kRectInAbsCoord.h = m_kParentRectInAbsCoord.h * m_kFullRect.fScaleH + m_kFullRect.fDeltaH;
}
//----------------------------------------------------------------
bool GGUIWindowBase::InputDragLogic(stInputEvent* pInputEvent)
{
	bool bDrag = false;
	if (m_nID != GGUIInputState::m_nWindoeID_CursorDrag)
	{
		//�ж�����Ƿ�ʼ��ק���ڡ�
		if (m_bCursorIsInside && m_nID == GGUIInputState::m_nWindoeID_CursorInWindowRect)
		{
			//���һֱλ�ڱ����ھ��η�Χ�ڡ�
			if (pInputEvent->theEvent == InputEvent_Down && pInputEvent->theKey == InputKey_LMouse)
			{
				//�����������ˣ���ʼ��ק��
				GGUIInputState::m_nWindoeID_CursorDrag = m_nID;
				GGUIInputState::m_nLastCursorPosX = pInputEvent->nParam1;
				GGUIInputState::m_nLastCursorPosY = pInputEvent->nParam2;
				//ע�⣬���ﲻ�ܰ�bDrag���ó�true�����򴰿��޷���Ӧ�����¼���
				//��Ϣ�������ˣ���Ϣ�����ɡ�
				pInputEvent->Swallow();
			}
		}
	}
	else
	{
		//���������ק�����ڡ�
		//������ֻ��Ӧ����ƶ���������̧�������¼���
		if (pInputEvent->theEvent == InputEvent_MouseMove)
		{
			//�����ƶ���
			int nDeltaX = pInputEvent->nParam1 - GGUIInputState::m_nLastCursorPosX;
			int nDeltaY = pInputEvent->nParam2 - GGUIInputState::m_nLastCursorPosY;
			MoveDelta((float)nDeltaX, (float)nDeltaY);
			GGUIInputState::m_nLastCursorPosX = pInputEvent->nParam1;
			GGUIInputState::m_nLastCursorPosY = pInputEvent->nParam2;
			bDrag = true;
			//�׳��¼�
			GGUIEventParam_PosChangedByDrag kParam;
			kParam.szWindowName = m_kName.GetValue();
			kParam.nWindowID = m_nID;
			m_pUIEventHandler->ProcessUIEvent(GGUIEvent_PosChangedByDrag, &kParam);
			//��Ϣ�������ˣ���Ϣ�����ɡ�
			pInputEvent->Swallow();
		}
		else if (pInputEvent->theEvent == InputEvent_Up && pInputEvent->theKey == InputKey_LMouse)
		{
			//ֹͣ��ק��
			GGUIInputState::m_nWindoeID_CursorDrag = -1;
			//��Ϣ�������ˣ���Ϣ�����ɡ�
			pInputEvent->Swallow();
		}
	}
	return bDrag;
}
//----------------------------------------------------------------
bool GGUIWindowBase::InputWindowRectLogic()
{
	bool bShouldSendEvent_WindowRect = false;
	const int oldWindoeID_CursorInWindowRect = GGUIInputState::m_nWindoeID_CursorInWindowRect;
	if (m_nID == GGUIInputState::m_nWindoeID_CursorInWindowRect)
	{
		if (m_bCursorIsInside == false)
		{
			//֮ǰ���λ�ڱ������ڲ������ڲ���λ�ڱ������ڲ���
			bShouldSendEvent_WindowRect = true;
			GGUIInputState::m_nWindoeID_CursorInWindowRect = -1;
			if (m_nID == GGUIInputState::m_nWindoeID_CursorDrag)
			{
				//��������������ק�У�ֹͣ��ק��
				//��������ξͻ�������������
				//�����ק�����ڹ����У�����������ϲ㴰�ڵľ��η�Χ��
				//�ϲ㴰�ڵ�input���ȼ��ȱ�����Ҫ��,
				//�򱾴���ֹͣ��ק���������׳����Ƴ����ڷ�Χ�����¼���
				//�ϲ㴰���׳������봰�ڷ�Χ�����¼���
				GGUIInputState::m_nWindoeID_CursorDrag = -1;
			}
		}
	}
	else
	{
		if (m_bCursorIsInside == true)
		{
			//֮ǰ��겻λ�ڱ������ڲ�������λ�ڱ������ڲ���
			bShouldSendEvent_WindowRect = true;
			GGUIInputState::m_nWindoeID_CursorInWindowRect = m_nID;
			//�����ڿ϶�������ק�У��������ĸ����ڴ�����ק�У���Ҫֹͣ��
			GGUIInputState::m_nWindoeID_CursorDrag = -1;
		}
	}
	//
	if (bShouldSendEvent_WindowRect)
	{
		if (m_bCursorIsInside)
		{
			if (oldWindoeID_CursorInWindowRect != -1)
			{
				//�ɴ���Ҫ�׳��뿪���ڵ��¼���
				//δ�������������һ�������Ƶ��߼����ɴ���һ��������g_pCurrentPanel��
				//���ǲ�һ����
				//����ɴ��ڲ�������g_pCurrentPanel����ô��Ҫ�ҳ��������ڵ��Ǹ�Panel����PanelҪ���ȼ�¼��������
				//���ڣ�������Ϊ�ɴ���������g_pCurrentPanel��
				GGUIWindowBase* pOldWindow = GGUIWindowFactory::Get()->GetUIWindow(oldWindoeID_CursorInWindowRect);
				if (pOldWindow)
				{
					GGUIEventParam_WindowRectLeave kParam;
					kParam.szWindowName = pOldWindow->GetName().GetValue();
					kParam.nWindowID = pOldWindow->GetID();
					m_pUIEventHandler->ProcessUIEvent(GGUIEvent_WindowRectLeave, &kParam);
				}
			}
			//
			GGUIEventParam_WindowRectEnter kParam;
			kParam.szWindowName = m_kName.GetValue();
			kParam.nWindowID = m_nID;
			m_pUIEventHandler->ProcessUIEvent(GGUIEvent_WindowRectEnter, &kParam);
		}
		else
		{
			GGUIEventParam_WindowRectLeave kParam;
			kParam.szWindowName = m_kName.GetValue();
			kParam.nWindowID = m_nID;
			m_pUIEventHandler->ProcessUIEvent(GGUIEvent_WindowRectLeave, &kParam);
		}
	}
	return bShouldSendEvent_WindowRect;
}
//----------------------------------------------------------------
