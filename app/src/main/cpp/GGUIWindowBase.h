//----------------------------------------------------------------
#ifndef _GGUIWindowBase_h_
#define _GGUIWindowBase_h_
//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
//----------------------------------------------------------------
struct stInputEvent;
//----------------------------------------------------------------
class GGUIWindowBase
{
public:
	//���¡�
	virtual void UpdateWindow(float fDeltaTime);
	//���ơ�
	virtual void RenderWindow();
	//����Input�¼���
	//����true����ʾ���������Ѿ��������¼��������಻��Ҫ�ٴ���input��
	//����false����ʾ��������Դ����Լ�����Ȥ��input��
	virtual bool InputWindow(stInputEvent* pInputEvent);
	//����UI�¼���
	//һ������£������ڵĴ����׳��¼�������Button�׳�GGUIEvent_ButtonClick�¼������� GGUIWindowPanel ����Ӧ�¼���
	virtual void ProcessUIEvent(int nEventType, void* pParam);

	//��ȡ����ID��
	int GetID() const;
	//��ȡ�������͡�
	GGUIWindowType GetType() const;

	//���ø�����ID��
	void SetParentID(int nID);
	//��ȡ������ID��
	int GetParentID() const;

	//���ô������֡�
	void SetName(const char* szName);
	//��ȡ�������֡�
	const SoTinyString& GetName() const;

	virtual void SetFullRect(const GGUIFullRect& kRect);
	virtual void SetFullRectScalePos(float fScaleX, float fScaleY);
	virtual void SetFullRectDeltaPos(float fDeltaX, float fDeltaY);
	virtual void MoveDelta(float fDeltaX, float fDeltaY);
	virtual void OnParentRectChanged(const GGUIRect& kParentRectInAbsCoord);
	virtual void SetUIEventHandler(GGUIWindowBase* pHandler);

	const GGUIFullRect& GetFullRect() const;
	const GGUIRect& GetRectInAbsCoord() const;
	const GGUIRect& GetParentRectInAbsCoord() const;

	void SetVisible(bool bVisible);
	virtual void SetVisibleByReason(souint32 uiReason, bool bVisible);
	bool GetVisible() const;

	void SetInputEnable(bool bEnable);
	void SetInputEnableByReason(souint32 uiReason, bool bEnable);
	bool GetInputEnable() const;

	void SetDragEnable(bool bDrag);
	bool GetDragEnable() const;

protected:
	friend class GGUIWindowFactory;
	GGUIWindowBase();
	virtual ~GGUIWindowBase();
	virtual void ClearWindow();
	void SetID(int nID);
	void CalculateRectInAbsCoord();
	//����ֵΪtrue����ʾ���������ק�����ڡ�
	bool InputDragLogic(stInputEvent* pInputEvent);
	//����ֵΪtrue����ʾ�׳��ˡ������봰�����򡱻��ߡ�����뿪���������¼���
	bool InputWindowRectLogic();

protected:
	int m_nID;
	int m_nParentID;
	GGUIWindowType m_eType;
	SoTinyString m_kName;
	//�����ڻ��׳�UIEvent����m_pUIEventHandler������Ӧ��UIEvent�Ĵ��ڡ�
	//һ������£�GGUIWindowPanel ��䵱 m_pUIEventHandler ��
	GGUIWindowBase* m_pUIEventHandler;
	GGUIFullRect m_kFullRect;
	GGUIRect m_kRectInAbsCoord;
	GGUIRect m_kParentRectInAbsCoord;
	SoBitFlag m_kUnvisibleReason;
	SoBitFlag m_kInputDisableReason;
	bool m_bDragEnable;
	bool m_bCursorIsInside;
};
//----------------------------------------------------------------
inline void GGUIWindowBase::SetID(int nID)
{
	m_nID = nID;
}
//----------------------------------------------------------------
inline int GGUIWindowBase::GetID() const
{
	return m_nID;
}
//----------------------------------------------------------------
inline void GGUIWindowBase::SetParentID(int nID)
{
	m_nParentID = nID;
}
//----------------------------------------------------------------
inline int GGUIWindowBase::GetParentID() const
{
	return m_nParentID;
}
//----------------------------------------------------------------
inline GGUIWindowType GGUIWindowBase::GetType() const
{
	return m_eType;
}
//----------------------------------------------------------------
inline void GGUIWindowBase::SetName(const char* szName)
{
	m_kName = szName;
}
//----------------------------------------------------------------
inline const SoTinyString& GGUIWindowBase::GetName() const
{
	return m_kName;
}
//----------------------------------------------------------------
inline const GGUIFullRect& GGUIWindowBase::GetFullRect() const
{
	return m_kFullRect;
}
//----------------------------------------------------------------
inline const GGUIRect& GGUIWindowBase::GetRectInAbsCoord() const
{
	return m_kRectInAbsCoord;
}
//----------------------------------------------------------------
inline const GGUIRect& GGUIWindowBase::GetParentRectInAbsCoord() const
{
	return m_kParentRectInAbsCoord;
}
//----------------------------------------------------------------
inline void GGUIWindowBase::SetVisible(bool bVisible)
{
	SetVisibleByReason(GGUIReasonUnvisible_Self, bVisible);
}
//----------------------------------------------------------------
inline bool GGUIWindowBase::GetVisible() const
{
	return m_kUnvisibleReason.IsZero();
}
//----------------------------------------------------------------
inline void GGUIWindowBase::SetInputEnable(bool bEnable)
{
	SetInputEnableByReason(GGUIReasonInputDisable_Self, bEnable);
}
//----------------------------------------------------------------
inline bool GGUIWindowBase::GetInputEnable() const
{
	return m_kInputDisableReason.IsZero();
}
//----------------------------------------------------------------
inline void GGUIWindowBase::SetDragEnable(bool bDrag)
{
	m_bDragEnable = bDrag;
}
//----------------------------------------------------------------
inline bool GGUIWindowBase::GetDragEnable() const
{
	return m_bDragEnable;
}
//----------------------------------------------------------------
inline void GGUIWindowBase::SetUIEventHandler(GGUIWindowBase* pHandler)
{
	m_pUIEventHandler = pHandler;
}
//----------------------------------------------------------------
#endif //_GGUIWindowBase_h_
//----------------------------------------------------------------
