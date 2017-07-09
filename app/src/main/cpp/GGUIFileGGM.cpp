//----------------------------------------------------------------
#include "GGUIFileGGM.h"
//----------------------------------------------------------------
GGUIFileGGM::GGUIFileGGM()
:m_pFile(0)
,m_pFileBuff(0)
,m_nFileSize(0)
,m_nReadPointer(0)
{

}
//----------------------------------------------------------------
GGUIFileGGM::~GGUIFileGGM()
{
	CloseFcfFile();
}
//----------------------------------------------------------------
bool GGUIFileGGM::ReadFcfFile(const char* szFileName)
{
	if (szFileName == 0 || szFileName[0] == 0)
	{
		return false;
	}
	m_pFile = SoFileHelp::CreateFile(szFileName, "rt");
	if (m_pFile == 0)
	{
		return false;
	}
	//
	m_pFileBuff = (char*)m_pFile->GetFileData();
	m_nFileSize = m_pFile->GetFileSize();
	m_nReadPointer = 0;
	return true;
}
//----------------------------------------------------------------
bool GGUIFileGGM::GetTextureName(std::string& strTextureName)
{
	m_nReadPointer = 0;
	const char* szFirstLine = ReadNextFileLine();
	if (szFirstLine)
	{
		strTextureName = SoCmdLineHelp::GetValueByKey(szFirstLine, -1, "Texture");
		return true;
	}
	else
	{
		return false;
	}
}
//----------------------------------------------------------------
bool GGUIFileGGM::GetNextImageRect(SoTinyString& kName, GGUIRect& kRect)
{
	char* szLine = ReadNextFileLine();
	if (szLine == 0)
	{
		return false;
	}

	const int nSplitIndex = SoStrChr(szLine, '=');
	if (nSplitIndex == -1)
	{
		return false;
	}

	szLine[nSplitIndex] = 0;
	const char* szRectName = szLine;
	const char* szRectData = szLine + nSplitIndex + 1;
	//
	kName = SoStrSlim(szRectName);
	kRect.x = SoCmdLineHelp::GetFloatByKey(szRectData, -1, "x", 0.0f);
	kRect.y = SoCmdLineHelp::GetFloatByKey(szRectData, -1, "y", 0.0f);
	kRect.w = SoCmdLineHelp::GetFloatByKey(szRectData, -1, "w", 0.0f);
	kRect.h = SoCmdLineHelp::GetFloatByKey(szRectData, -1, "h", 0.0f);
	return true;
}
//----------------------------------------------------------------
int GGUIFileGGM::GetImageRectCount()
{
	if (m_pFileBuff == 0)
	{
		return 0;
	}

	int nRectCount = 0;
	for (int i = 0; i < m_nFileSize; ++i)
	{
		if (m_pFileBuff[i] == '{')
		{
			++nRectCount;
		}
	}
	return nRectCount;
}
//----------------------------------------------------------------
void GGUIFileGGM::CloseFcfFile()
{
    SoFileHelp::DeleteFile(m_pFile);
    m_pFileBuff = 0;
	m_nFileSize = 0;
	m_nReadPointer = 0;
}
//----------------------------------------------------------------
char* GGUIFileGGM::ReadNextFileLine()
{
	if (m_pFileBuff == 0)
	{
		return 0;
	}
	if (m_nReadPointer >= m_nFileSize)
	{
		return 0;
	}
	//
	const int nOldPointer = m_nReadPointer;
	for (int i = m_nReadPointer; i < m_nFileSize; ++i)
	{
		if (m_pFileBuff[i] == '\n')
		{
			m_pFileBuff[i] = 0;
			m_nReadPointer = i + 1;
			break;
		}
	}
	return (m_pFileBuff+nOldPointer);
}
//----------------------------------------------------------------
