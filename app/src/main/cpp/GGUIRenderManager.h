//----------------------------------------------------------------
#ifndef _GGUIRenderManager_h_
#define _GGUIRenderManager_h_
//----------------------------------------------------------------
#include "GLBaseInclude.h"
//----------------------------------------------------------------
class GLShaderBase;
//----------------------------------------------------------------
struct stUIRenderUnit
{
	float fRectLeft;
	float fRectRight;
	float fRectTop;
	float fRectBottom;
	float fTexCoordLeft;
	float fTexCoordRight;
	float fTexCoordTop;
	float fTexCoordBottom;
	float fColorR;
	float fColorG;
	float fColorB;
	float fColorA;
    GLuint uiTexResourceId;
};
//----------------------------------------------------------------
class GGUIRenderManager
{
public:
	static bool CreateUIRenderManager();
	static void ReleaseUIRenderManager();
	static GGUIRenderManager* Get();

	void AddRnederUnit(const stUIRenderUnit* pUIRenderUnit);
	void RenderUIRenderManager();

private:
	GGUIRenderManager();
	~GGUIRenderManager();
	bool InitUIRenderManager();
	void ClearUIRenderManager();
	//
	bool CreateVertexList();
	void ReleaseVertexList();
	bool CreateIndexList();
	void ReleaseIndexList();
	bool CreateSRVList();
	void ReleaseSRVList();

private:
	struct stVertexType
	{
		SoMathFloat3 kPosition;
        SoMathFloat3 kTexCoordAndTexIndex;
        SoMathFloat4 kColorRGBA;
	};

private:
	static GGUIRenderManager* ms_pInstance;
	stVertexType* m_pVertexList;
    unsigned short* m_pIndexList;
    GLuint* m_pSRVList;
	const GLShaderBase* m_pShader;
	//��¼ m_pVertexList �е�Ԫ�ظ���
	int m_nMaxWindowCount;
	int m_nCurWindowCount;
	//��¼ m_pTexResourceList �е�Ԫ�ظ���
	int m_nMaxSRVCount;
	int m_nCurSRVCount;
	//���һ��ִ��AddRnederUnitʱ����ͼ����Ƕ��١�
	//����ִ��AddRnederUnitʱ����ͼ��ż��п������ϴε���ͼ�����ͬ��
	//��������Ŀ������������ʣ����ٱ�����
	int m_nLastTextureIndex;
	//���Ƶ�ǰ�� stUIRenderUnit ʱ��ʹ�õ�ZValue��ֵ�Ƕ��١�
	float m_fCurrentRenderOrder;
    float m_fScreenHeight;
};
//----------------------------------------------------------------
inline GGUIRenderManager* GGUIRenderManager::Get()
{
	return ms_pInstance;
}
//----------------------------------------------------------------
#endif //_GGUIRenderManager_h_
//----------------------------------------------------------------
