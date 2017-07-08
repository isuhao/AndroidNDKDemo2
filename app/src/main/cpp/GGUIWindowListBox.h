//------------------------------------------------------------
#ifndef _GGUIWindowListBox_h_
#define _GGUIWindowListBox_h_
//------------------------------------------------------------
#include "GGUIWindowContainer.h"
//------------------------------------------------------------
class GGUIWindowImage;
class GGUIWindowScrollBar;
class GGUIWindowText;
//------------------------------------------------------------
class GGUIWindowListBox : public GGUIWindowContainer
{
public:
	void AddItem(const char* szText, void* pUserData);
	void InsertItem(int nItemIndex, const char* szText, void* pUserData);
	void RemoveItem(int nItemIndex);
	

protected:
	friend class GGUIWindowFactory;
	GGUIWindowListBox();
	virtual ~GGUIWindowListBox();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void ClearWindow();
	virtual void ProcessUIEvent(int nEventType, void* pParam);
	virtual void SetUIEventHandler(GGUIWindowBase* pHandler);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	void InitListBox();

private:
	//�洢�û����Զ������ݡ�
	//Item�����UserData���һһ��Ӧ��
	SoArray m_kUserDataArray;
	GGUIWindowImage* m_pImgBG;
	GGUIWindowScrollBar* m_pScrollBar;
};
//------------------------------------------------------------
#endif _GGUIWindowListBox_h_
//------------------------------------------------------------
