//----------------------------------------------------------------
#ifndef _GGUIImagesetManager_h_
#define _GGUIImagesetManager_h_
//----------------------------------------------------------------
#include "GGUIImageset.h"
#include "GGUIImagesetFont.h"
//----------------------------------------------------------------
class GGUIImagesetManager
{
public:
	static bool CreateUIImagesetManager();
	static void ReleaseUIImagesetManager();
	static GGUIImagesetManager* Get();

	//����һ���µ�Imageset����
    GGUIImageset* CreateImageset(const stImagesetParam* pParam);
	//����һ���µ�ImagesetFont����
    GGUIImagesetFont* CreateImagesetFont(const stImagesetFontParam* pParam);

	int GetImagesetIDByName(const SoTinyString &kName);
	GGUIImagesetBase* GetImagesetByID(int nImagesetID);
	GGUIImagesetBase* GetImagesetByName(const SoTinyString& kName);

private:
	GGUIImagesetManager();
	~GGUIImagesetManager();
	bool InitUIImagesetManager();
	void ClearUIImagesetManager();

private:
	typedef std::map<SoTinyString, int> mapName2Index;

private:
	static GGUIImagesetManager* ms_pInstance;
	//���飬�洢��Ԫ����GGUIImagesetBase*��
	SoArrayUID m_kImagesetArray;
	//Imageset���ֵ�Imageset��ŵ�ӳ�䡣
	mapName2Index m_kName2IndexMap;
};
//----------------------------------------------------------------
inline GGUIImagesetManager* GGUIImagesetManager::Get()
{
	return ms_pInstance;
}
//----------------------------------------------------------------
#endif //_GGUIImagesetManager_h_
//----------------------------------------------------------------
