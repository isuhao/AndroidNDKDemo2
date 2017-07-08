//------------------------------------------------------------
#ifndef _GGUIWindowContainer_h_
#define _GGUIWindowContainer_h_
//------------------------------------------------------------
#include "GGUIWindowBase.h"
//----------------------------------------------------------------
struct stInputEvent;
//------------------------------------------------------------
class GGUIWindowContainer : public GGUIWindowBase
{
public:
	void AddChild(GGUIWindowBase* pChild);
	void RemoveChildByIndex(int nIndex);
	void RemoveChildByID(int nWindowID);
	void RemoveAllChild();
	void SwapChild(int nIndexA, int nIndexB);

	int GetChildCount() const;
	GGUIWindowBase* GetChildByIndex(int nIndex) const;
	GGUIWindowBase* GetChildByID(int nWindowID) const;
	GGUIWindowBase* GetChildByName(const char* szName) const;
	int GetIndexByID(int nWindowID) const;
	//�ݹ����
	GGUIWindowBase* FindWindowByID(int nWindowID) const;
	//�ݹ����
	GGUIWindowBase* FindWindowByName(const char* szName) const;

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void UpdateWindow(float fDeltaTime);
	virtual void RenderWindow();
	//����true����ʾ���������Ѿ��������¼��������಻��Ҫ�ٴ���input��
	//����false����ʾ��������Դ����Լ�����Ȥ��input��
	virtual bool InputWindow(stInputEvent* pInputEvent);
	virtual bool InputWindow2(AnInputMsgInfo* kMsgInfo);
	virtual void SetFullRect(const GGUIFullRect& kRect);
	virtual void SetFullRectScalePos(float fScaleX, float fScaleY);
	virtual void SetFullRectDeltaPos(float fDeltaX, float fDeltaY);
	virtual void MoveDelta(float fDeltaX, float fDeltaY);
	virtual void OnParentRectChanged(const GGUIRect& kParentRectInAbsCoord);
	virtual void SetUIEventHandler(GGUIWindowBase* pHandler);
	virtual void SetVisibleByReason(souint32 uiReason, bool bVisible);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

protected:
	friend class GGUIWindowFactory;
	GGUIWindowContainer();
	virtual ~GGUIWindowContainer();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void ClearWindow();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	void DoRemoveChild(GGUIWindowBase* pChild);
	void Notify_ParentRectChanged() const;
	void Notify_ParentVisibleChanged() const;

private:
	SoArray m_kWindowArray;
};
//----------------------------------------------------------------
inline int GGUIWindowContainer::GetChildCount() const
{
	return m_kWindowArray.GetSize();
}
//------------------------------------------------------------
#endif //_GGUIWindowContainer_h_
//------------------------------------------------------------
