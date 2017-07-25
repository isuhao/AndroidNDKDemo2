//----------------------------------------------------------------
#ifndef _GGUIImagesetManager_h_
#define _GGUIImagesetManager_h_
//----------------------------------------------------------------
#include "GGUIImageset.h"
#include "GGUIImagesetFont.h"
//----------------------------------------------------------------
class GLTexture;
//----------------------------------------------------------------
struct stImagesetParam
{
	//Imageset�����֡�
	SoTinyString kName;
	//Ԥ������ٸ�GGUIRect��
	int nInitRectCount;
	//��ͼ����
	GLTexture* pTexture;
};
//----------------------------------------------------------------
struct stImagesetFontParam
{
	//Imageset�����֡�
	SoTinyString kName;
	//Ԥ������ٸ�Rect��
	int nInitRectCount;
	//��ͼ����
	GLTexture* pTexture;
};
//----------------------------------------------------------------
class GGUIImagesetManager
{
public:
	static bool CreateUIImagesetManager();
	static void ReleaseUIImagesetManager();
	static GGUIImagesetManager* Get();

	//����һ���µ�Imageset����
    GGUIImageset* CreateImageset(const stImagesetParam& kParam);
	//����һ���µ�ImagesetFont����
    GGUIImagesetFont* CreateImagesetFont(const stImagesetFontParam& kParam);

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
