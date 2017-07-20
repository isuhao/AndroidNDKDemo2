//----------------------------------------------------------------
#include "GGUIWindowBase.h"
#include "GGUIWindowFactory.h"
#include "GGUIEvent.h"
#include "GGUIActionGroup.h"
//----------------------------------------------------------------
GGUIWindowBase::GGUIWindowBase()
:m_nID(-1)
,m_nParentID(-1)
,m_eType(GGUIWindow_Invalid)
,m_pUIEventHandler(0)
,m_pActionGroup(NULL)
,m_fScaleX(1.0f)
,m_fScaleY(1.0f)
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
	m_nParentID = -1;
	m_kName.Clear();
	m_pUIEventHandler = 0;
	m_kFullRect = GGUIFullRect_Empty;
	m_kParentRectInAbsCoord = GGUIRect_Empty;
	m_kOriginalRectInAbsCoord = GGUIRect_Empty;
	m_kRectInAbsCoord = GGUIRect_Empty;
    m_fScaleX = 1.0f;
    m_fScaleY = 1.0f;
	m_kUnvisibleReason.Clear();
	m_kInputDisableReason.Clear();
	m_bCursorIsInside = false;
	DeleteActionGroup();
}
//----------------------------------------------------------------
void GGUIWindowBase::UpdateWindow(float fDeltaTime)
{
	if (m_pActionGroup)
	{
		m_pActionGroup->UpdateActionGroup(fDeltaTime);
	}
}
//----------------------------------------------------------------
void GGUIWindowBase::RenderWindow()
{
	//do nothing
}
//----------------------------------------------------------------
bool GGUIWindowBase::InputWindow(GGUIInputMsg* pInputMsg)
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
		bIsInside = m_kRectInAbsCoord.IsInside(pInputMsg->fPosX, pInputMsg->fPosY);
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
			pInputMsg->bSwallowed = true;
		}
	}
	m_bCursorIsInside = bIsInside;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//��ⴰ����ק�߼���
	if (GetDragEnable())
	{
		if (InputDragLogic(pInputMsg))
		{
			//������ק�С�
			//ֻ������ק�������������¼���ֱ���˳���
			//�����಻Ҫ�ٴ���input��
			return true;
		}
	}
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#if (SoTargetPlatform == SoPlatform_Windows)
    //����Ƿ�Ҫ�׳��������봰�����򡱻��ߡ�����뿪���������¼���
	if (InputWindowRectLogic())
	{
		//�׳����¼��������������¼���ֱ���˳���
		//�����಻Ҫ�ٴ���input��
		return true;
	}
#elif (SoTargetPlatform == SoPlatform_Android)
    //�ƶ��豸û�й�꣬����û��hover״̬��
#endif
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	return false;
}
//----------------------------------------------------------------
void GGUIWindowBase::ProcessUIEvent(int nEventType, void* pParam)
{
	//do nothing
}
//----------------------------------------------------------------
void GGUIWindowBase::ProcessActionEvent(int nEventId)
{
    //do nothing
}
//----------------------------------------------------------------
void GGUIWindowBase::SetFullRect(const GGUIFullRect& kRect)
{
	m_kFullRect = kRect;
	CalculateRectInAbsCoord(false);
}
//----------------------------------------------------------------
void GGUIWindowBase::SetFullRectScalePos(float fScaleX, float fScaleY)
{
	m_kFullRect.fScaleX = fScaleX;
	m_kFullRect.fScaleY = fScaleY;
	CalculateRectInAbsCoord(false);
}
//----------------------------------------------------------------
void GGUIWindowBase::SetFullRectDeltaPos(float fDeltaX, float fDeltaY)
{
	m_kFullRect.fDeltaX = fDeltaX;
	m_kFullRect.fDeltaY = fDeltaY;
	CalculateRectInAbsCoord(false);
}
//----------------------------------------------------------------
void GGUIWindowBase::SetFullRectScaleWH(float fScaleW, float fScaleH)
{
	m_kFullRect.fScaleW = fScaleW;
	m_kFullRect.fScaleH = fScaleH;
	CalculateRectInAbsCoord(false);
}
//----------------------------------------------------------------
void GGUIWindowBase::MoveDelta(float fDeltaX, float fDeltaY)
{
	m_kFullRect.fDeltaX += fDeltaX;
	m_kFullRect.fDeltaY += fDeltaY;
	CalculateRectInAbsCoord(false);
}
//----------------------------------------------------------------
void GGUIWindowBase::SetScale(float fScaleX, float fScaleY)
{
    m_fScaleX = fScaleX;
    m_fScaleY = fScaleY;
    CalculateRectInAbsCoord(true);
}
//----------------------------------------------------------------
void GGUIWindowBase::ScaleDelta(float fDeltaX, float fDeltaY)
{
    m_fScaleX += fDeltaX;
    m_fScaleY += fDeltaY;
    CalculateRectInAbsCoord(true);
}
//----------------------------------------------------------------
void GGUIWindowBase::OnParentRectChanged(const GGUIRect& kParentRectInAbsCoord)
{
	m_kParentRectInAbsCoord = kParentRectInAbsCoord;
	CalculateRectInAbsCoord(false);
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
GGUIActionGroup* GGUIWindowBase::CreateActionGroup()
{
	if (m_pActionGroup == NULL)
	{
		m_pActionGroup = SoNew GGUIActionGroup(this);
	}
	return m_pActionGroup;
}
//----------------------------------------------------------------
void GGUIWindowBase::DeleteActionGroup()
{
	if (m_pActionGroup)
	{
		SoDelete m_pActionGroup;
		m_pActionGroup = NULL;
	}
}
//----------------------------------------------------------------
void GGUIWindowBase::CalculateRectInAbsCoord(bool bOnlyScaleChanged)
{
    if (bOnlyScaleChanged == false)
    {
        m_kOriginalRectInAbsCoord.x = m_kParentRectInAbsCoord.x + m_kParentRectInAbsCoord.w * m_kFullRect.fScaleX + m_kFullRect.fDeltaX;
        m_kOriginalRectInAbsCoord.y = m_kParentRectInAbsCoord.y + m_kParentRectInAbsCoord.h * m_kFullRect.fScaleY + m_kFullRect.fDeltaY;
        m_kOriginalRectInAbsCoord.w = m_kParentRectInAbsCoord.w * m_kFullRect.fScaleW + m_kFullRect.fDeltaW;
        m_kOriginalRectInAbsCoord.h = m_kParentRectInAbsCoord.h * m_kFullRect.fScaleH + m_kFullRect.fDeltaH;
    }
    m_kRectInAbsCoord.x = m_kOriginalRectInAbsCoord.x;
    m_kRectInAbsCoord.y = m_kOriginalRectInAbsCoord.y;
    m_kRectInAbsCoord.w = m_kOriginalRectInAbsCoord.w * m_fScaleX;
    m_kRectInAbsCoord.h = m_kOriginalRectInAbsCoord.h * m_fScaleY;
}
//----------------------------------------------------------------
bool GGUIWindowBase::InputDragLogic(GGUIInputMsg* pInputMsg)
{
	bool bDrag = false;
	if (m_nID != GGUIInputState::m_nWindoeID_CursorDrag)
	{
		//�ж�����Ƿ�ʼ��ק���ڡ�
		if (m_bCursorIsInside
#if (SoTargetPlatform == SoPlatform_Windows)
			&& m_nID == GGUIInputState::m_nWindoeID_CursorInWindowRect
#elif (SoTargetPlatform == SoPlatform_Android)
            //�ƶ��豸û�й�꣬����û��hover״̬��
#endif
				)
		{
			//���һֱλ�ڱ����ھ��η�Χ�ڡ�
#if (SoTargetPlatform == SoPlatform_Windows)
			if (pInputEvent->theEvent == InputEvent_Down && pInputEvent->theKey == InputKey_LMouse)
#elif (SoTargetPlatform == SoPlatform_Android)
			if (pInputMsg->theType == GGUIInputMsg_TouchDown)
#endif
			{
				//�����������ˣ���ʼ��ק��
				GGUIInputState::m_nWindoeID_CursorDrag = m_nID;
				GGUIInputState::m_fLastCursorPosX = pInputMsg->fPosX;
				GGUIInputState::m_fLastCursorPosY = pInputMsg->fPosY;
				//ע�⣬���ﲻ�ܰ�bDrag���ó�true�����򴰿��޷���Ӧ�����¼���
				//��Ϣ�������ˣ���Ϣ�����ɡ�
                pInputMsg->bSwallowed = true;
			}
		}
	}
	else
	{
		//���������ק�����ڡ�
		//������ֻ��Ӧ����ƶ���������̧�������¼���
#if (SoTargetPlatform == SoPlatform_Windows)
		if (pInputEvent->theEvent == InputEvent_MouseMove)
#elif (SoTargetPlatform == SoPlatform_Android)
        if (pInputMsg->theType == GGUIInputMsg_TouchMove)
#endif
		{
			//�����ƶ���
			float fDeltaX = pInputMsg->fPosX - GGUIInputState::m_fLastCursorPosX;
			float fDeltaY = pInputMsg->fPosY - GGUIInputState::m_fLastCursorPosY;
			MoveDelta(fDeltaX, fDeltaY);
			GGUIInputState::m_fLastCursorPosX = pInputMsg->fPosX;
			GGUIInputState::m_fLastCursorPosY = pInputMsg->fPosY;
			bDrag = true;
			//�׳��¼�
			GGUIEventParam_PosChangedByDrag kParam;
			kParam.szWindowName = m_kName.GetValue();
			kParam.nWindowID = m_nID;
			m_pUIEventHandler->ProcessUIEvent(GGUIEvent_PosChangedByDrag, &kParam);
			//��Ϣ�������ˣ���Ϣ�����ɡ�
            pInputMsg->bSwallowed = true;
		}
#if (SoTargetPlatform == SoPlatform_Windows)
		else if (pInputEvent->theEvent == InputEvent_Up && pInputEvent->theKey == InputKey_LMouse)
#elif (SoTargetPlatform == SoPlatform_Android)
        else if (pInputMsg->theType == GGUIInputMsg_TouchUp)
#endif
		{
			//ֹͣ��ק��
			GGUIInputState::m_nWindoeID_CursorDrag = -1;
			//��Ϣ�������ˣ���Ϣ�����ɡ�
            pInputMsg->bSwallowed = true;
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
