//----------------------------------------------------------------
#ifndef _GGUIImageset_h_
#define _GGUIImageset_h_
//----------------------------------------------------------------
#include "GGUIImagesetBase.h"
//----------------------------------------------------------------
class GLTexture;
//----------------------------------------------------------------
class GGUIImageset : public GGUIImagesetBase
{
public:
	void AddRect(const SoTinyString& kName, const stImageRect& kRect);
	int GetRectID(const SoTinyString& kName) const;
	const stImageRect* GetRectByID(int nID) const;
	const stImageRect* GetRectByName(const SoTinyString& kName) const;

	souint32 GetTexResourceID() const;
	float GetTextureWidth() const;
	float GetTextureHeight() const;

protected:
	friend class GGUIImagesetManager;
	GGUIImageset();
	~GGUIImageset();
	//��ʼ��������
	//--nInitRectCount Ԥ������ٸ�GGUIRect��
	bool InitImageset(int nInitRectCount);
	void ClearImageset();
	void SetTexture(GLTexture* pTexture);

private:
	typedef std::map<SoTinyString, int> mapName2ID;

private:
	//���飬�洢��Ԫ����GGUIRect��
	SoArrayUID m_kRectArray;
	//GGUIRect���ֵ�GGUIRect��ŵ�ӳ�䡣
	mapName2ID m_kName2IDMap;
	//��ͼ����ָ�롣
	GLTexture* m_pTexture;
};
//----------------------------------------------------------------
#endif //_GGUIImageset_h_
//----------------------------------------------------------------
