//----------------------------------------------------------------
#ifndef _SoAudioFileWave_h_
#define _SoAudioFileWave_h_
//----------------------------------------------------------------
#include "SoCodeBaseInclude.h"
//----------------------------------------------------------------
class SoFile;
//----------------------------------------------------------------
class SoAudioFileWave
{
public:
	SoAudioFileWave();
	~SoAudioFileWave();

	bool OpenFileWave(const char* szFile);
	void CloseFileWave();

    unsigned char* GetAudioData() const;
	unsigned int GetAudioDataSize() const;
	unsigned int GetFrequency() const;
	unsigned int GetChannelCount() const;
	unsigned int GetChannelMask() const;
	unsigned int GetBitsPerSample() const;
	bool IsFormatPCM() const;
	bool IsFormatExtensible() const;

public:
	struct stFileHeader
	{
		//���ĸ��ַ���ֵ������'R''I''F''F'��
		char RIFF[4];
		//���ֵ����8�͵����ļ���size��
		unsigned int uiFileLength;
		//���ĸ��ַ���ֵ������'W''A''V''E'��
		char WAVE[4];
	};
	//һ��Wave�ļ���һ��stFileHeader�����ɸ�Chunk��ɡ�
	//ÿ��Chunk��һ��stChunkHeader��һ��stChunkData��ɡ�
	struct stChunkHeader
	{
		char Flag[4];
		unsigned int uiChunkSize;
	};
	struct stChunkData_FormatPCM
	{
		//ֵΪSoAudioFileWave_Format_PCM����ʾPCM��ʽ������δѹ���ĸ�ʽ��
		//ֵΪSoAudioFileWave_Format_Extensible����ʾ��չ��ʽ������δѹ���ĸ�ʽ��
		//����ֵ����ʾĳ��ѹ����ʽ����֧������ֵ��
		unsigned short wFormatTag;
		//�м���������
		unsigned short wChannelCount;
		//Ƶ�ʡ�
		unsigned int uiSampleRate;
		//��ֵ����(uiSampleRate * wChannelCount * wBitsPerSample / 8)��
		unsigned int uiBytePerSecond;
		//��ֵ����(wChannelCount * wBitsPerSample / 8)��
		unsigned short wBlockAlign;
		//λ�һ��ֵΪ8��16��32��
		unsigned short wBitsPerSample;
	};
	struct stChunkData_FormatExtensible
	{
		stChunkData_FormatPCM kFormatPCM;
		unsigned short wSize;
		unsigned short wReserved;
		unsigned int uiChannelMask;
		unsigned int GUID_Data1;
		unsigned short GUID_Data2;
		unsigned short GUID_Data3;
		unsigned char GUID_Data4[8];
	};
	struct stChunkData_AudioData
	{
		unsigned char* pData;
		unsigned int uiSize;
	};
	
private:
	bool ReadHeader();
	bool ReadChunk(const char* szFile);

private:
    SoFile* m_pFile;
	stChunkData_FormatExtensible m_stChunkDataFormat;
	stChunkData_AudioData m_stChunkDataAudioData;
};
//----------------------------------------------------------------
#endif //_SoAudioFileWave_h_
//----------------------------------------------------------------
