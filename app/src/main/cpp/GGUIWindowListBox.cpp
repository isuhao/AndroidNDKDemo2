//------------------------------------------------------------
//1�����ؼ����Ӵ��ڵĴ洢�ṹ��
//   ���Ϊ0���Ӵ��ڱض��Ǳ����ؼ�GGUIWindowImage��
//   ���Ϊ1���Ӵ��ڱض��ǹ������ؼ�GGUIWindowScrollBar��
//   �����2��ʼ������Ŀ��Item���ؼ�GGUIWindowText��
//2�����ΪN��Item���Ǳ��ؼ������Ϊ(GGUIWindowListBox_ItemStartIndex+N)���Ӵ��ڡ�
//------------------------------------------------------------
#include "GGUIWindowListBox.h"
#include "GGUIWindowFactory.h"
#include "GGUIWindowImage.h"
#include "GGUIWindowScrollBar.h"
#include "GGUIWindowText.h"
#include "GGUIEvent.h"
//------------------------------------------------------------
#define GGUIWindowListBox_ItemStartIndex 2
//------------------------------------------------------------
GGUIWindowListBox::GGUIWindowListBox()
:m_pImgBG(0)
,m_pScrollBar(0)
{
	m_eType = GGUIWindow_ListBox;
	InitListBox();
}
//------------------------------------------------------------
GGUIWindowListBox::~GGUIWindowListBox()
{
	//ֻҪ��ָ�����óɿռ��ɡ�
	m_pImgBG = 0;
	m_pScrollBar = 0;
}
//----------------------------------------------------------------
void GGUIWindowListBox::ClearWindow()
{
    GGUIWindowContainer::ClearWindow();
}
//----------------------------------------------------------------
void GGUIWindowListBox::ProcessUIEvent(int nEventType, void* pParam)
{
	//switch (nEventType)
	//{
	//case GGUIEvent_Button_Clicked:
	//	{
	//		GGUIEventParam_ButtonClick* myParam = (GGUIEventParam_ButtonClick*)pParam;
	//		if (m_pBtnLeft->GetID() == myParam->nWindowID)
	//		{
	//			m_pBtnCenter->MoveDelta(-m_fRangePosDeltaPerStep, 0.0f);
	//			AdjustCenterBtnPos();
	//		}
	//		else if (m_pBtnRight->GetID() == myParam->nWindowID)
	//		{
	//			m_pBtnCenter->MoveDelta(m_fRangePosDeltaPerStep, 0.0f);
	//			AdjustCenterBtnPos();
	//		}
	//	} break;
	//case GGUIEvent_PosChangedByDrag:
	//	{
	//		AdjustCenterBtnPos();
	//	} break;
	//}
}
//----------------------------------------------------------------
void GGUIWindowListBox::SetUIEventHandler(GGUIWindowBase* pHandler)
{
	//ע�⣬���ﲻ��ִ�� GGUIWindowContainer::SetUIEventHandler ������ִ�� GGUIWindowBase::SetUIEventHandler ��
	GGUIWindowBase::SetUIEventHandler(pHandler);
	////����Ҫ����ÿ���Ӵ��ڵ�UIEvent��
	//m_pBtnLeft->SetUIEventHandler(this);
	//m_pBtnRight->SetUIEventHandler(this);
	//m_pBtnCenter->SetUIEventHandler(this);
}
//----------------------------------------------------------------
void GGUIWindowListBox::InitListBox()
{
	GGUIFullRect kFullRect;
	//
	kFullRect.fScaleX = 0.0f;
	kFullRect.fDeltaX = 0.0f;
	kFullRect.fScaleY = 0.0f;
	kFullRect.fDeltaY = 0.0f;
	kFullRect.fScaleW = 1.0f;
	kFullRect.fDeltaW = 0.0f;
	kFullRect.fScaleH = 1.0f;
	kFullRect.fDeltaH = 0.0f;
	GGUIWindowImage* pUIImage = (GGUIWindowImage*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_Image);
	pUIImage->SetFullRect(kFullRect);
	pUIImage->SetTexture("texture/mm2:Name1");
	pUIImage->SetDragEnable(true);
	AddChild(pUIImage);
	m_pImgBG = pUIImage;
	//
	//kFullRect.fScaleX = 1.0f;
	//kFullRect.fDeltaX = -10.0f;
	//kFullRect.fScaleY = 0.0f;
	//kFullRect.fDeltaY = 0.0f;
	//kFullRect.fScaleW = 0.0f;
	//kFullRect.fDeltaW = 10.0f;
	//kFullRect.fScaleH = 1.0f;
	//kFullRect.fDeltaH = 0.0f;
	//GGUIWindowScrollBar* pUIScrollBar = (GGUIWindowScrollBar*)GGUIWindowFactory::Get()->CreateUIWindow(GGUIWindow_ScrollBar);
	//pUIScrollBar->SetFullRect(kFullRect);
	//pUIScrollBar->SetDragEnable(false);
	//AddChild(pUIScrollBar);
	//m_pScrollBar = pUIScrollBar;
}
//----------------------------------------------------------------
void GGUIWindowListBox::AddItem(const char* szText, void* pUserData)
{

}
//----------------------------------------------------------------
void GGUIWindowListBox::InsertItem(int nItemIndex, const char* szText, void* pUserData)
{

}
//----------------------------------------------------------------
void GGUIWindowListBox::RemoveItem(int nItemIndex)
{

}
//------------------------------------------------------------
