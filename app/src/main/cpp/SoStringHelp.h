//--------------------------------------------------------------------
#ifndef _SoStringHelp_h_
#define _SoStringHelp_h_
//--------------------------------------------------------------------
#include "SoCodeBaseInclude.h"
//--------------------------------------------------------------------
#define SoStringHelp_GlobalBuffSize 2048
//--------------------------------------------------------------------
//��ȡ�����ַ������档
char* SoStrGetBuff();

//�����ַ������ȡ�
//�ַ������Ȳ��ܴ���0x3FFFFFFF��1G�ࣩ��
//�����������ֵ��Ŀ���ǣ���ֹ�û�������һ��û����0��β���ַ�����������ѭ����
int SoStrLen(const char* szString);
int SoWStrLen(const wchar_t* szString);

//�ַ���������
//�����ַ������ȡ�
int SoStrCpy(char* DestBuff, const int nDestBuffSize, const char* szSourceString);
int SoWStrCpy(wchar_t* DestBuff, const int nDestBuffSize, const wchar_t* szSourceString);


//2017-08-08���ڰ�׿ƽ̨��ʹ�� char* SoStrFmt(const char* szFormat, ...); ���������
//�ַ�����ʧ�����⣬���磬��Ԥ�ڵõ��Ľ���ַ�����"�м�2"��ʵ���ϵõ��Ŀ����ǿ��ַ�����������"��"�Ȳ�ȱ���ַ�����
//�������ԣ�����ʹ�� __VA_ARGS__ ��ȴ�������ģ��������ַ�����ʧ�����⡣
//������Բ�ͬƽ̨��ʹ�ò�ͬʵ�֡�
#if (SoTargetPlatform == SoPlatform_Windows)

//�ַ�����ʽ����ʹ�ñ�ģ���ṩ���ַ������档
//����ֵ����const char*���ǿ����޸ĵ��ַ������棬�����������Զ��ַ�����һЩ�޸ġ�
char* SoStrFmt(const char* szFormat, ...);
//�ַ�����ʽ����ʹ��ָ�����ַ�������
void SoStrFmtSelf(char* Buff, const int nBuffSize, const char* szFormat, ...);
char* SoStrFmtByVaList(const char* szFormat, const void* pValist);
void SoStrFmtSelfByVaList(char* Buff, const int nBuffSize, const char* szFormat, const void* pValist);

#elif (SoTargetPlatform == SoPlatform_Android)

//�ڰ�׿ƽ̨����ȷ��ʹ�÷����� const char* szResult = SoStrFmt();
//��������ʹ�� pWindow->SetText(SoStrFmt());
#define SoStrFmt(...)  SoStrGetBuff(); snprintf(SoStrGetBuff(), SoStringHelp_GlobalBuffSize, __VA_ARGS__);
#define SoStrFmtSelf(Buff, nBuffSize, ...)  SoStrGetBuff(); snprintf(Buff, nBuffSize, __VA_ARGS__);

#endif


//�Ƚ������ַ���
int SoStrCmp(const char* s1, const char* s2);
int SoWStrCmp(const wchar_t* s1, const wchar_t* s2);
//�Ƚ������ַ����������Ǵ�Сд����
int SoStrCmpNoCase(const char* s1, const char* s2);
int SoWStrCmpNoCase(const wchar_t* s1, const wchar_t* s2);

//�����ַ�c���ַ���str���״γ��ֵ�λ����š�
//�����Դ����ַ���str�ĳ��ȣ����������Ļ��������ڲ�������ַ������ȡ�
//����ҵĵ�������ֵ��Χ[0, SoStrLen(str))��
//����Ҳ���������ֵΪ-1��
int SoStrChr(const char* str, const char c, int nStrLen = -1);
int SoWStrChr(const wchar_t* str, const wchar_t c, int nStrLen = -1);
//�����ַ�c���ַ���str��ĩ�γ��ֵ�λ����š�
//�����Դ����ַ���str�ĳ��ȣ����������Ļ��������ڲ�������ַ������ȡ�
//����ҵĵ�������ֵ��Χ[0, SoStrLen(str))��
//����Ҳ���������ֵΪ-1��
int SoStrRChr(const char* str, const char c, int nStrLen = -1);
int SoWStrRChr(const wchar_t* str, const wchar_t c, int nStrLen = -1);

//��str�л�ȡһ�����ַ�����
//���ַ��������������ǣ�λ���������[nStartIndex, nEndIndex]�ڵ��ַ���
char* SoSubStr(const char* str, int nStartIndex, int nEndIndex);

//�ַ���������ͷ����β���Ŀո��tab�ַ�ȥ����
char* SoStrSlim(const char* str, int nStrLen = -1);

//���ַ����е��ַ��滻�ɴ�д��ĸ
char* SoStrToUpper(const char* szString);
void SoStrToUpperSelf(char* szString);

//���ַ����е��ַ��滻��Сд��ĸ
char* SoStrToLower(const char* szString);
void SoStrToLowerSelf(char* szString);

//·���ַ�����׼��
//�Ѵ����·���ַ����޸ĳ����¸�ʽ��
//1��ȥ��·��ͷ����'.'��'/'��'\\'���ո�tab�ַ���
//   ȥ��·��β����'.'���ո�tab�ַ���
//2����'\\'�޸ĳ�'/'��
//3���Ѵ�д��ĸ�޸ĳ�Сд��ĸ��
//--bXieGang ֵΪtrue����ʾ�ַ���ĩβ������'/'��ֵΪfalse��ʾ����Ҫ��
//����ֵ��һ��ȫ�ֵ��ַ������飬���Ҫ���콫����ֵȡ�ߡ�
char* SoPathNormalize(const char* szPath, bool bXieGang);
//����Ҫȥ��ͷ���ַ�����ĩβ����ַ������Բ���ֱ�Ӷ�Դ�ַ������޸ģ����Բ��ṩ�������������
//void SoPathNormalizeSelf(char* szString);


//��ȡutf8�ַ����е�һ���ַ���
//--pByteCountOfTheCharacter ���Ϊ��Чֵ�������˳���Я�����ַ����ֽڸ�����
char* SoGetOneCharacterFromUtf8String(const char* pszUtf8Str, const int nUtf8StrLen, const int nStartIndex, int* pByteCountOfTheCharacter);
//�ж�utf8�ַ����Ƿ���Ϲ淶��
bool SoCheckUtf8WellFormed(const unsigned char *str, int len);

// Same to ::atof, but strip the string, remain 7 numbers after '.' before call atof.
// Why we need this? Because in android c++_static, atof ( and std::atof ) is unsupported for numbers
// have long decimal part and contain several numbers can approximate to 1 ( like 90.099998474121094 ), 
// it will return inf. This function is used to fix this bug.
double Soatof(const char* szString);
#if (SoTargetPlatform == SoPlatform_Windows)
double SoWatof(const wchar_t* szString);
#endif
// Same to atoi
#define Soatoi atoi
#define SoWatoi _wtoi
#define Sostrtol strtol
#define SoWstrtol wcstol
#define Sostrtoul strtoul
#define SoWstrtoul wcstoul
//--------------------------------------------------------------------
#endif //_SoStringHelp_h_
//--------------------------------------------------------------------
