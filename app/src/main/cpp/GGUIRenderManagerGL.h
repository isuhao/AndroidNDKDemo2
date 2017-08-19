//----------------------------------------------------------------
#ifndef _GGUIGLRenderManager_h_
#define _GGUIGLRenderManager_h_
//----------------------------------------------------------------
#include "GLBaseInclude.h"
#include "GGUIRenderDefine.h"
//----------------------------------------------------------------
class GLShaderBase;
//----------------------------------------------------------------
class GGUIRenderManagerGL
{
public:
	static bool CreateUIRenderManagerGL();
	static void ReleaseUIRenderManagerGL();
	static GGUIRenderManagerGL* Get();

	void AddRnederUnit(const stUIRenderUnit* pUIRenderUnit);
	void RenderUIRenderManager();

private:
	GGUIRenderManagerGL();
	~GGUIRenderManagerGL();
	bool InitUIRenderManagerGL();
	void ClearUIRenderManagerGL();
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
	static GGUIRenderManagerGL* ms_pInstance;
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
inline GGUIRenderManagerGL* GGUIRenderManagerGL::Get()
{
	return ms_pInstance;
}
//----------------------------------------------------------------
#endif //_GGUIGLRenderManager_h_
//----------------------------------------------------------------
