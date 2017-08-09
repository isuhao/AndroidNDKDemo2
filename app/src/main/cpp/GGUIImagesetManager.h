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

	//创建一个新的Imageset对象。
    GGUIImageset* CreateImageset(const stImagesetParam* pParam);
	//创建一个新的ImagesetFont对象。
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
	//数组，存储的元素是GGUIImagesetBase*。
	SoArrayUID m_kImagesetArray;
	//Imageset名字到Imageset序号的映射。
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
