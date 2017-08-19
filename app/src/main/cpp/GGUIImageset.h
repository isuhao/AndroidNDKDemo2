//----------------------------------------------------------------
#ifndef _GGUIImageset_h_
#define _GGUIImageset_h_
//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
//----------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)
class SoD3DTexture;
#elif (SoTargetPlatform == SoPlatform_Android)
class GLTexture;
#endif
//----------------------------------------------------------------
struct stImagesetParam
{
	//Imageset�����֡�
	SoTinyString kName;
	//��ͼ����
	void* pTexture;
	//Ԥ������ٸ�Rect��
	int nInitRectCount;
	float fFontSize;
	float fFontHeight;

    stImagesetParam() : pTexture(NULL), nInitRectCount(4), fFontSize(24.0f), fFontHeight(32.0f)
	{

	}
};
//----------------------------------------------------------------
class GGUIImageset
{
public:
	void AddRect(const SoTinyString& kName, const stImageRect& kRect);
	int GetRectID(const SoTinyString& kName) const;
	const stImageRect* GetRectByID(int nID) const;
	const stImageRect* GetRectByName(const SoTinyString& kName) const;

    void AddFontRect(const char* szChar, const stImageRect& kRect);
    const stImageRect* GetFontRect(const char* szChar) const;
    void CalculateStringGlyphSize(const char* szString, int nCharCount, float* pStringWidth, float* pStringHeight) const;

	souint64 GetTexResource() const;
	float GetTextureWidth() const;
	float GetTextureHeight() const;

protected:
	friend class GGUIImagesetManager;
	GGUIImageset();
	~GGUIImageset();
	bool InitImageset(const stImagesetParam* pParam);
	void ClearImageset();
    souint32 GenerateCharNumber(const souint8* szChar) const;
    int GetRectIDByCharNumber(souint32 Number) const;

private:
	typedef std::map<SoTinyString, int> mapName2ID;
    typedef std::map<souint32, int> mapCharNumber2ID;

private:
	//���飬�洢��Ԫ���� stImageRect ��
	SoArrayUID m_kRectArray;
	//Rect���ֵ�Rect��ŵ�ӳ�䡣
    //���������洢����һ���Imageset����map��Ч��
	mapName2ID m_kName2IDMap;
    //�ַ����ֵ�Rect��ŵ�ӳ�䡣
    //���������洢�����������͵�Imageset����map��Ч��
    mapCharNumber2ID m_kIDMap;
	//��ͼ����ָ�롣
#if (SoTargetPlatform == SoPlatform_Windows)
    SoD3DTexture* m_pTexture;
#elif (SoTargetPlatform == SoPlatform_Android)
    GLTexture* m_pTexture;
#endif
    float m_fFontSize;
    float m_fFontHeight;
};
//----------------------------------------------------------------
#endif //_GGUIImageset_h_
//----------------------------------------------------------------
