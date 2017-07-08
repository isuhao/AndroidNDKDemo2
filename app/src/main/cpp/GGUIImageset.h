//----------------------------------------------------------------
#ifndef _GGUIImageset_h_
#define _GGUIImageset_h_
//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
//----------------------------------------------------------------
class GLTexture;
//----------------------------------------------------------------
class GGUIImageset
{
public:
	void AddRect(const SoTinyString& kName, const GGUIRect& kRect);
	int GetRectID(const SoTinyString& kName) const;
	const GGUIRect& GetRect(int nID) const;
	int GetRectCount() const;
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
	void SetD3DTexture(GLTexture* pD3DTexture);

private:
	typedef std::map<SoTinyString, int> mapName2ID;

private:
	//���飬�洢��Ԫ����GGUIRect��
	SoArrayUID m_kRectArray;
	//GGUIRect���ֵ�GGUIRect��ŵ�ӳ�䡣
	mapName2ID m_kName2IDMap;
	//��ͼ����ָ�롣
	GLTexture* m_pD3DTexture;
};
//----------------------------------------------------------------
#endif //_GGUIImageset_h_
//----------------------------------------------------------------
