//----------------------------------------------------------------
#ifndef _GGUIAnimation_h_
#define _GGUIAnimation_h_
//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
//----------------------------------------------------------------
//������һ֡
struct GGUIAnimFrame
{
    int nImagesetId;
    int nImageRectId;

    static const GGUIAnimFrame ms_Empty;
    GGUIAnimFrame();
};
//----------------------------------------------------------------
//�������У�һ�������Ķ���
struct GGUIAnimFrameset
{
    //��������ID
    int nAnimId;
    //����洢����FrameID
    SoArray kFrameIDList;

	GGUIAnimFrameset();
    void SetAnimID(int nAnimId);
    int GetAnimID() const;
    void AddFrameID(int nFrameId);
    int GetFrameCount() const;
    int GetFrameID(int nIndex) const;
};
//----------------------------------------------------------------
class GGUIAnimation
{
public:
    void AddAnimFrame(const char* szImage);
    //�˺������᷵��NULL
    const GGUIAnimFrame* GetAnimFrameByID(int nFrameId);

    GGUIAnimFrameset* CreateFrameset(int nAnimId, int nInitFrameCount);
    GGUIAnimFrameset* GetFrameset(int nAnimId);

protected:
	friend class GGUIImagesetManager;
	GGUIAnimation();
	~GGUIAnimation();
	//��ʼ��������
	//--nInitFrameCount Ԥ������ٸ�GGUIAnimFrame��
    //--nInitFramesetCount Ԥ������ٸ�GGUIAnimFrameset��
	bool InitAnimation(int nInitFrameCount, int nInitFramesetCount);
	void ClearAnimation();

private:
    //�洢����֡ GGUIAnimFrame ���洢��ž��� FrameID ��
    SoArrayUID m_kFrameArray;
    SoArray m_kFramesetArray;
};
//----------------------------------------------------------------
#endif //_GGUIAnimation_h_
//----------------------------------------------------------------
