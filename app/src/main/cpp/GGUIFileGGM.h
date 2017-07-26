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

	bool ReadFcfFile(const char* szFileName);
	bool GetTextureName(std::string& strTextureName);
	bool GetNextImageRect(SoTinyString& kName, stImageRect& kRect);
	bool GetNextImageFontRect(SoTinyString& kName, stImageFontRect& kRect);
	int GetImageRectCount();

	void CloseFcfFile();

private:
	char* ReadNextFileLine();

private:
	SoFile* m_pFile;
	//�洢�����ļ������ݡ�
	char* m_pFileBuff;
	int m_nFileSize;
	//�������Ĺ��λ�á�
	int m_nReadPointer;
};
//----------------------------------------------------------------
#endif //_GGUIFileGGM_h_
//----------------------------------------------------------------
