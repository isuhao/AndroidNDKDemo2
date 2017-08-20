//----------------------------------------------------------------
#include "GGUIWindowScrollBar.h"
#include "GGUIWindowFactory.h"
#include "GGUIWindowButton.h"
#include "GGUIEvent.h"
//----------------------------------------------------------------
GGUIWindowScrollBar::GGUIWindowScrollBar()
:m_pBtnLeft(0)
,m_pBtnRight(0)
,m_pBtnCenter(0)
,m_fCenterBtn_FullRectDeltaY(0.0f)
,m_fRangeMaxValue(100.0f)
,m_fRangeMinValue(0.0f)
,m_fRangeStep(1.0f)
,m_fRangePosDeltaPerStep(1.0f)
,m_fRangeValueDeltaPerPixel(1.0f)
,m_fRangeCurValue(0.0f)
{
	m_eType = GGUIWindow_ScrollBar;
	InitScrollBar();
}
//----------------------------------------------------------------
GGUIWindowScrollBar::~GGUIWindowScrollBar()
{
	//ֻҪ��ָ�����óɿռ��ɡ�
	m_pBtnLeft = 0;
	m_pBtnRight = 0;
	m_pBtnCenter = 0;
}
//----------------------------------------------------------------
void GGUIWindowScrollBar::ClearWindow()
{
	GGUIWindowContainer::ClearWindow();
	//m_pBtnLeft�ȴ���ָ�뱣�ֲ��䡣
	m_fCenterBtn_FullRectDeltaY = 0.0f;
	m_fRangeMaxValue = 100.0f;
	m_fRangeMinValue = 0.0f;
	m_fRangeStep = 1.0f;
	m_fRangePosDeltaPerStep = 1.0f;
	m_fRangeValueDeltaPerPixel = 1.0f;
	m_fRangeCurValue = 0.0f;
}
//----------------------------------------------------------------
void GGUIWindowScrollBar::ProcessUIEvent(int nEventType, void* pParam)
{
	switch (nEventType)
	{
	case GGUIEvent_Button_Clicked:
		{
			GGUIEventParam_Button_Clicked* myParam = (GGUIEventParam_Button_Clicked*)pParam;
			if (m_pBtnLeft->GetID() == myParam->nWindowID)
			{
				m_pBtnCenter->MoveDelta(-m_fRangePosDeltaPerStep, 0.0f);
				AdjustCenterBtnPos();
			}
			else if (m_pBtnRight->GetID() == myParam->nWindowID)
			{
				m_pBtnCenter->MoveDelta(m_fRangePosDeltaPerStep, 0.0f);
				AdjustCenterBtnPos();
			}
		} break;
	case GGUIEvent_PosChangedByDrag:
		{
			AdjustCenterBtnPos();
		} break;
	}
}
//----------------------------------------------------------------
void GGUIWindowScrollBar::SetUIEventHandler(GGUIWindowBase* pHandler)
{
	//ע�⣬���ﲻ��ִ�� GGUIWindowContainer::SetUIEventHandler ������ִ�� GGUIWindowBase::SetUIEventHandler ��
	GGUIWindowBase::SetUIEventHandler(pHandler);
	//����Ҫ����ÿ���Ӵ��ڵ�UIEvent��
	m_pBtnLeft->SetUIEventHandler(this);
	m_pBtnRight->SetUIEventHandler(this);
	m_pBtnCenter->SetUIEventHandler(this);
}
//----------------------------------------------------------------
void GGUIWindowScrollBar::InitScrollBar()
{
	GGUIFullRect kFullRect;
	GGUIWindowButton* pUIButton = 0;
	//
	kFullRect.fScaleX = 0.0f;
	kFullRect.fDeltaX = 0.0f;
	kFullRect.fScaleY = 0.0f;
	kFullRect.fDeltaY = 0.0f;
	kFullRect.fScaleW = 0.0f;
	kFullRect.fDeltaW = 50.0f;
	kFullRect.fScaleH = 1.0f;
	kFullRect.fDeltaH = 0.0f;
	pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
	pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_GGUI_ScrollBar_LeftBG);
	pUIButton->SetDragEnable(false);
	AddChild(pUIButton);
	m_pBtnLeft = pUIButton;
	//
	kFullRect.fScaleX = 1.0f;
	kFullRect.fDeltaX = -20.0f;
	kFullRect.fScaleY = 0.0f;
	kFullRect.fDeltaY = 0.0f;
	kFullRect.fScaleW = 0.0f;
	kFullRect.fDeltaW = 50.0f;
	kFullRect.fScaleH = 1.0f;
	kFullRect.fDeltaH = 0.0f;
	pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
	pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_GGUI_ScrollBar_RightBG);
	pUIButton->SetDragEnable(false);
	AddChild(pUIButton);
	m_pBtnRight = pUIButton;
	//
	kFullRect.fScaleX = 0.0f;
	kFullRect.fDeltaX = 40.0f;
	kFullRect.fScaleY = 0.0f;
	kFullRect.fDeltaY = 0.0f;
	kFullRect.fScaleW = 0.0f;
	kFullRect.fDeltaW = 50.0f;
	kFullRect.fScaleH = 1.0f;
	kFullRect.fDeltaH = 0.0f;
	pUIButton = (GGUIWindowButton*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Button);
	pUIButton->SetFullRect(kFullRect);
    pUIButton->SetImage(g_GGUI_ScrollBar_CenterBG);
	pUIButton->SetDragEnable(true);
	AddChild(pUIButton);
	m_pBtnCenter = pUIButton;
	m_fCenterBtn_FullRectDeltaY = kFullRect.fDeltaY;
}
//----------------------------------------------------------------
void GGUIWindowScrollBar::AdjustCenterBtnPos()
{
	//������ˮƽ�����ϣ�����λ���Ƿ񳬳��˱߽硣
	//fDeltaX��ֵΪ0��ʾû�г����߽硣
	float fDeltaX = 0.0f;
	const GGUIRect& kLeftRect = m_pBtnLeft->GetRectInAbsCoord();
	const GGUIRect& kRightRect = m_pBtnRight->GetRectInAbsCoord();
	const GGUIRect& kCenterRect = m_pBtnCenter->GetRectInAbsCoord();
	if (kCenterRect.x < kLeftRect.x + kLeftRect.w)
	{
		fDeltaX = kLeftRect.x + kLeftRect.w - kCenterRect.x;
	}
	else if (kCenterRect.x > kRightRect.x - kCenterRect.w)
	{
		fDeltaX = kRightRect.x - kCenterRect.w - kCenterRect.x;
	}
	//�����ڴ�ֱ�����ϣ�����λ���Ƿ񳬳��˱߽硣
	//fDeltaY��ֵΪ0��ʾû�г����߽硣
	float fDeltaY = 0.0f;
	//ע�⣬������ʹ�þɵ��Լ����µ��Լ����Ƚϣ����Բ���ʹ�þ������꣬Ӧ��ʹ��������ꡣ
	const GGUIFullRect& kCenterFullRect = m_pBtnCenter->GetFullRect();
	fDeltaY = m_fCenterBtn_FullRectDeltaY - kCenterFullRect.fDeltaY;
	//�淶�����λ�á�
	if (SoMath_IsFloatZero(fDeltaX) == false || SoMath_IsFloatZero(fDeltaY) == false)
	{
		m_pBtnCenter->MoveDelta(fDeltaX, fDeltaY);
	}
	//��������ֵ��
	float fCurValue = 0.0f;
	if (fDeltaX > 0.01f)
	{
		fCurValue = m_fRangeMinValue;
	}
	else if (fDeltaX < -0.01f)
	{
		fCurValue = m_fRangeMaxValue;
	}
	else
	{
		float fDelta = kCenterRect.x - (kLeftRect.x + kLeftRect.w);
		fCurValue = m_fRangeMinValue + fDelta * m_fRangeValueDeltaPerPixel;
	}
	m_fRangeCurValue = fCurValue;
    const char* szText = SoStrFmt("%.2f", fCurValue);
	m_pBtnCenter->SetText(szText);

	//�׳���Ϣ��
	GGUIEventParam_ScrollBar_PosChanged kParam;
	kParam.szWindowName = GetName().GetValue();
	kParam.nWindowID = GetID();
	kParam.fNewValue = fCurValue;
	m_pUIEventHandler->ProcessUIEvent(GGUIEvent_ScrollBar_PosChanged, &kParam);
}
//----------------------------------------------------------------
void GGUIWindowScrollBar::SetRange(float fMin, float fMax, float fStep)
{
	//(fMax-fMin)��ֵ������0����Ϊ��Ҫ��������
	if (fMin >= fMax)
	{
		fMin = fMax - 1.0f;
		GGUILogErrorf("GGUIWindowScrollBar::SetRange : Invalid Param; fMin[%.2f] fMax[%.2f]", fMin, fMax);
	}
	m_fRangeMinValue = fMin;
	m_fRangeMaxValue = fMax;
	m_fRangeStep = fStep;
	//
	const GGUIRect& kLeftRect = m_pBtnLeft->GetRectInAbsCoord();
	const GGUIRect& kRightRect = m_pBtnRight->GetRectInAbsCoord();
	const GGUIRect& kCenterRect = m_pBtnCenter->GetRectInAbsCoord();
	float fPosLength = (kRightRect.x - kCenterRect.w) - (kLeftRect.x + kLeftRect.w);
	if (fPosLength <= 0.0f)
	{
		//����������0
		fPosLength = 1.0f;
		//�����������Ӵ��ڵ�λ�ô�С�����������޷�����
		GGUILogError("GGUIWindowScrollBar::SetRange : wrong pos");
	}
	m_fRangePosDeltaPerStep = fPosLength / (fMax - fMin) * fStep;
	m_fRangeValueDeltaPerPixel = (fMax - fMin) / fPosLength;
}
//----------------------------------------------------------------
void GGUIWindowScrollBar::SetValue(float fValue)
{
	if (fValue < m_fRangeMinValue)
	{
		fValue = m_fRangeMinValue;
	}
	if (fValue > m_fRangeMaxValue)
	{
		fValue = m_fRangeMaxValue;
	}
	m_fRangeCurValue = fValue;
	//
	const GGUIRect& kLeftRect = m_pBtnLeft->GetRectInAbsCoord();
	const GGUIRect& kCenterRect = m_pBtnCenter->GetRectInAbsCoord();
	float fDestPosX = (fValue - m_fRangeMinValue) / m_fRangeValueDeltaPerPixel;
	float fAbsPosX = (kLeftRect.x + kLeftRect.w) + fDestPosX;
	m_pBtnCenter->MoveDelta(fAbsPosX - kCenterRect.x, 0.0f);
	//
	AdjustCenterBtnPos();
}
//----------------------------------------------------------------
