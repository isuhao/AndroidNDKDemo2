//----------------------------------------------------------------
#ifndef _GGUIRenderManagerDX_h_
#define _GGUIRenderManagerDX_h_
//----------------------------------------------------------------
#include "SoCodeBaseInclude.h"
//----------------------------------------------------------------
#if (SoTargetPlatform == SoPlatform_Windows)
//----------------------------------------------------------------
#include "SoD3DInclude.h"
#include "GGUIRenderDefine.h"
//----------------------------------------------------------------
class SoD3DShaderBase;
//----------------------------------------------------------------
class GGUIRenderManagerDX
{
public:
	static bool CreateUIRenderManagerDX();
	static void ReleaseUIRenderManagerDX();
	static GGUIRenderManagerDX* Get();

	void AddRnederUnit(const stUIRenderUnit* pUIRenderUnit);
	void RenderUIRenderManagerDX();

private:
	GGUIRenderManagerDX();
	~GGUIRenderManagerDX();
	bool InitUIRenderManagerDX();
	void ClearUIRenderManagerDX();
	//
	bool CreateVertexList();
	void ReleaseVertexList();
	bool CreateVertexBuffer();
	void ReleaseVertexBuffer();
	bool CreateIndexBuffer();
	void ReleaseIndexBuffer();
	bool CreateSRVList();
	void ReleaseSRVList();

private:
	struct stVertexType
	{
		XMFLOAT3 kPosition;
		XMFLOAT3 kTexCoordAndTexIndex;
		XMFLOAT4 kColorRGBA;
	};

private:
	static GGUIRenderManagerDX* ms_pInstance;
	stVertexType* m_pVertexList;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;
	ID3D11ShaderResourceView** m_pSRVList;
	SoD3DShaderBase* m_pShader;
	//��¼ m_pVertexList �е�Ԫ�ظ���
	int m_nMaxWindowCount;
	int m_nCurWindowCount;
	//��¼ m_pSRVList �е�Ԫ�ظ���
	int m_nMaxSRVCount;
	int m_nCurSRVCount;
	//���һ��ִ��AddRnederUnitʱ����ͼ����Ƕ��١�
	//����ִ��AddRnederUnitʱ����ͼ��ż��п������ϴε���ͼ�����ͬ��
	//��������Ŀ������������ʣ����ٱ�����
	int m_nLastTextureIndex;
	//���Ƶ�ǰ�� stUIRenderUnit ʱ��ʹ�õ�ZValue��ֵ�Ƕ��١�
	float m_fCurrentRenderOrder;
};
//----------------------------------------------------------------
inline GGUIRenderManagerDX* GGUIRenderManagerDX::Get()
{
	return ms_pInstance;
}
//----------------------------------------------------------------
#endif //(SoTargetPlatform == SoPlatform_Windows)
//----------------------------------------------------------------
#endif //_GGUIRenderManagerDX_h_
//----------------------------------------------------------------
