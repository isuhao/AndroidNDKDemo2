//----------------------------------------------------------------
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
//----------------------------------------------------------------
#include "SoAudioFileWave.h"
#include "SoFileHelp.h"
//----------------------------------------------------------------
#define SoAudioFileWave_Format_PCM 1
#define SoAudioFileWave_Format_Extensible 0xFFFE
//----------------------------------------------------------------
SoAudioFileWave::SoAudioFileWave()
:m_pFile(NULL)
{
	memset(&m_stChunkDataFormat, 0, sizeof(stChunkData_FormatExtensible));
	memset(&m_stChunkDataAudioData, 0, sizeof(stChunkData_AudioData));
}
//----------------------------------------------------------------
SoAudioFileWave::~SoAudioFileWave()
{
	CloseFileWave();
}
//----------------------------------------------------------------
bool SoAudioFileWave::OpenFileWave(const char* szFile)
{
	if (szFile == 0 || szFile[0] == 0)
	{
		return false;
	}

	m_pFile = SoFileHelp::CreateFile(szFile, "rb");
	if (m_pFile == 0)
	{
		return false;
	}

	if (ReadHeader() == false)
	{
		CloseFileWave();
		return false;
	}

	if (ReadChunk() == false)
	{
		CloseFileWave();
		return false;
	}

	//�ر��ļ���
    SoFileHelp::DeleteFile(m_pFile);

	return true;
}
//----------------------------------------------------------------
void SoAudioFileWave::CloseFileWave()
{
	if (m_pFile)
	{
        SoFileHelp::DeleteFile(m_pFile);
	}
	if (m_stChunkDataAudioData.pData)
	{
		delete [] m_stChunkDataAudioData.pData;
		m_stChunkDataAudioData.pData = 0;
	}
	memset(&m_stChunkDataFormat, 0, sizeof(stChunkData_FormatExtensible));
	memset(&m_stChunkDataAudioData, 0, sizeof(stChunkData_AudioData));
}
//----------------------------------------------------------------
unsigned char* SoAudioFileWave::GetAudioData() const
{
	return m_stChunkDataAudioData.pData;
}
//----------------------------------------------------------------
unsigned int SoAudioFileWave::GetAudioDataSize() const
{
	return m_stChunkDataAudioData.uiSize;
}
//----------------------------------------------------------------
unsigned int SoAudioFileWave::GetFrequency() const
{
	return m_stChunkDataFormat.kFormatPCM.uiSampleRate;
}
//----------------------------------------------------------------
unsigned int SoAudioFileWave::GetChannelCount() const
{
	return m_stChunkDataFormat.kFormatPCM.wChannelCount;
}
//----------------------------------------------------------------
unsigned int SoAudioFileWave::GetChannelMask() const
{
	return m_stChunkDataFormat.uiChannelMask;
}
//----------------------------------------------------------------
unsigned int SoAudioFileWave::GetBitsPerSample() const
{
	return m_stChunkDataFormat.kFormatPCM.wBitsPerSample;
}
//----------------------------------------------------------------
bool SoAudioFileWave::IsFormatPCM() const
{
	return (m_stChunkDataFormat.kFormatPCM.wFormatTag == SoAudioFileWave_Format_PCM);
}
//----------------------------------------------------------------
bool SoAudioFileWave::IsFormatExtensible() const
{
	return (m_stChunkDataFormat.kFormatPCM.wFormatTag == SoAudioFileWave_Format_Extensible);
}
//----------------------------------------------------------------
bool SoAudioFileWave::ReadHeader()
{
	stFileHeader kHeader;
	memset(&kHeader, 0, sizeof(stFileHeader));
    m_pFile->Read(&kHeader, 1, sizeof(stFileHeader));
	if (kHeader.RIFF[0] == 'R'
		&& kHeader.RIFF[1] == 'I' 
		&& kHeader.RIFF[2] == 'F' 
		&& kHeader.RIFF[3] == 'F'
		&& kHeader.WAVE[0] == 'W'
		&& kHeader.WAVE[1] == 'A' 
		&& kHeader.WAVE[2] == 'V'
		&& kHeader.WAVE[3] == 'E')
	{
		return true;
	}
	else
	{
		return false;
	}
}
//----------------------------------------------------------------
bool SoAudioFileWave::ReadChunk()
{
	bool br = true;
	stChunkHeader kHeader;
	memset(&kHeader, 0, sizeof(stChunkHeader));
	while (m_pFile->Read(&kHeader, 1, sizeof(stChunkHeader)) == sizeof(stChunkHeader))
	{
		if (kHeader.Flag[0] == 'f'
			&& kHeader.Flag[1] == 'm'
			&& kHeader.Flag[2] == 't'
			&& kHeader.Flag[3] == ' ')
		{
			if (kHeader.uiChunkSize <= sizeof(stChunkData_FormatExtensible))
			{
                m_pFile->Read(&m_stChunkDataFormat, 1, kHeader.uiChunkSize);
				if (m_stChunkDataFormat.kFormatPCM.wFormatTag != SoAudioFileWave_Format_PCM
					&& m_stChunkDataFormat.kFormatPCM.wFormatTag != SoAudioFileWave_Format_Extensible)
				{
					br = false;
					break;
				}
			}
			else
			{
				//���ﲻҪ����ѭ���������������Chunk������ѭ����
                m_pFile->Seek(kHeader.uiChunkSize, SEEK_CUR);
			}
		}
		else if (kHeader.Flag[0] == 'd'
			&& kHeader.Flag[1] == 'a'
			&& kHeader.Flag[2] == 't'
			&& kHeader.Flag[3] == 'a')
		{
			m_stChunkDataAudioData.pData = new unsigned char[kHeader.uiChunkSize];
			if (m_stChunkDataAudioData.pData)
			{
                m_pFile->Read(m_stChunkDataAudioData.pData, 1, kHeader.uiChunkSize);
				m_stChunkDataAudioData.uiSize = kHeader.uiChunkSize;
			}
			else
			{
				br = false;
				break;
			}
		}
		else
		{
			//����Chunk
            m_pFile->Seek(kHeader.uiChunkSize, SEEK_CUR);
		}
		//���ļ��ṹ�У�ÿ��Chunk��size����2����������
		//���kHeader.uiChunkSize����2��������������Ҫʹ�ļ�ָ�����һ���ֽڡ�
		if (kHeader.uiChunkSize & 1)
		{
            m_pFile->Seek(1, SEEK_CUR);
		}
	}
	//
	return br;
}
//----------------------------------------------------------------
