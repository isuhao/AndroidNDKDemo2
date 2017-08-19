//----------------------------------------------------------------
#ifndef _GGUIFileGGM_h_
#define _GGUIFileGGM_h_
//----------------------------------------------------------------
#include "GGUIBaseInclude.h"
//----------------------------------------------------------------
class GGUIFileGGM
{
public:
	GGUIFileGGM();
	~GGUIFileGGM();

	bool ReadGgmFile(const char *szFileName);
	bool GetTextureName(std::string& strTextureName);
	bool GetNextImageRect(SoTinyString& kName, stImageRect& kRect);
	bool GetNextImageFontRect(SoTinyString& kName, stImageRect& kRect);
	int GetImageRectCount();

    float GetFontSize();
    float GetFontHeight();

private:
	char* ReadNextFileLine();
    void CloseGgmFile();

private:
	SoFile* m_pFile;
	//�洢�����ļ������ݡ�
	char* m_pFileBuff;
	int m_nFileSize;
	//�������Ĺ��λ�á�
	int m_nReadPointer;
    //
	float m_fTexWidth;
	float m_fTexHeight;
	float m_fFontSize;
	float m_fFontHeight;
};
//----------------------------------------------------------------
#endif //_GGUIFileGGM_h_
//----------------------------------------------------------------
