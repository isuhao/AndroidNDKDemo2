//----------------------------------------------------------------
#ifndef _GGUIPanelManager_h_
#define _GGUIPanelManager_h_
//----------------------------------------------------------------
#include "GGUIWindowPanel.h"
//----------------------------------------------------------------
class GGUIPanelManager
{
public:
	static bool CreateUIPanelManager();
	static void ReleaseUIPanelManager();
	static GGUIPanelManager* Get();

	void UpdateUIPanelManager(float fDeltaTime);
	void RenderUIPanelManager();
	void InputUIPanelManager(GGUIInputMsg* kInputMsg);
	//��Ϸ�ֱ��ʷ����˱仯����������Panel������Ϳ�ߡ�
	void ResolutionChanged(float newWidth, float newHeight);

	void AddUIPanel(GGUIWindowPanel* pPanel, int eSpaceType);
	void RemoveUIPanel(GGUIWindowPanel* pPanel, int eSpaceType);
	GGUIWindowPanel* GetUIPanel(int eSpaceType, int nIndex);
	//��Panel���õ����ϲ㡣
	//�������ϲ��Panel������������ϲ㣬���ȴ���input��
	void MakeTopUIPanel(GGUIWindowPanel* pPanel);

	void UISpace_SetVisible(int eSpaceType, bool bVisible);
	bool UISpace_GetVisible(int eSpaceType);
	int UISpace_GetPanelCount(int eSpaceType);

private:
	GGUIPanelManager();
	~GGUIPanelManager();
	bool InitUIPanelManager();
	void ClearUIPanelManager();

private:
	static GGUIPanelManager* ms_pInstance;
	//����ֻά��GGUIWindowPanel�����ָ�룬����縺�𴴽���ɾ��GGUIWindowPanel����
	//Panel���Խ��Խ������Ļ��Խ�������ϲ㣬Խ���ȴ���input��
	SoArray m_kUISpaceArray[GGUIPanelSpace_Max];
	bool m_bUISpaceVisible[GGUIPanelSpace_Max];
};
//----------------------------------------------------------------
inline GGUIPanelManager* GGUIPanelManager::Get()
{
	return ms_pInstance;
}
//----------------------------------------------------------------
#endif //_GGUIPanelManager_h_
//----------------------------------------------------------------
