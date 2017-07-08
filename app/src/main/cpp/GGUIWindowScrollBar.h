//------------------------------------------------------------
#ifndef _GGUIWindowScrollBar_h_
#define _GGUIWindowScrollBar_h_
//------------------------------------------------------------
#include "GGUIWindowContainer.h"
//------------------------------------------------------------
class GGUIWindowButton;
//------------------------------------------------------------
class GGUIWindowScrollBar : public GGUIWindowContainer
{
public:
	void SetRange(float fMin, float fMax, float fStep);
	void SetValue(float fValue);
	float GetValue() const;

protected:
	friend class GGUIWindowFactory;
	GGUIWindowScrollBar();
	virtual ~GGUIWindowScrollBar();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void ClearWindow();
	virtual void ProcessUIEvent(int nEventType, void* pParam);
	virtual void SetUIEventHandler(GGUIWindowBase* pHandler);
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	void InitScrollBar();
	//�������λ�÷����˱仯����Ҫ���ñ��������淶�����λ�ã������㵱ǰֵ��
	void AdjustCenterBtnPos();

private:
	GGUIWindowButton* m_pBtnLeft;
	GGUIWindowButton* m_pBtnRight;
	GGUIWindowButton* m_pBtnCenter;
	//��¼����Ļ����λ�ã��������ƶ��������淶�����λ�á�
	float m_fCenterBtn_FullRectDeltaY;
	//<<<<<<<<<<<<<<<<<<<<<<<<<<
	//ȡֵ��Χ�����ֵ��
	float m_fRangeMaxValue;
	//ȡֵ��Χ����Сֵ��
	float m_fRangeMinValue;
	//������ఴťʱ����ǰֵ�ı仯����
	//ע�⣬�ǵ�ǰֵ�ı仯�����ǻ����λ�ñ仯��
	float m_fRangeStep;
	//������ఴťʱ�������λ�ñ仯��
	float m_fRangePosDeltaPerStep;
	//�����ƶ�ʱ��ÿ�����ػᵼ��ֵ�仯���١�
	float m_fRangeValueDeltaPerPixel;
	//��ǰֵ��ȡֵ��Χ��[m_fRangeMinValue, m_fRangeMaxValue]��
	float m_fRangeCurValue;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>
};
//------------------------------------------------------------
inline float GGUIWindowScrollBar::GetValue() const
{
	return m_fRangeCurValue;
}
//------------------------------------------------------------
#endif //_GGUIWindowScrollBar_h_
//------------------------------------------------------------
