//----------------------------------------------------------------
#ifndef _GGUIInputState_h_
#define _GGUIInputState_h_
//----------------------------------------------------------------
class GGUIInputState
{
public:
	//�����λ���ĸ����ڷ�Χ�ڡ�
	static int m_nWindoeID_CursorInWindowRect;
	//��������϶��ĸ����ڡ�
	//�������������ڣ��ͻᴥ������꿪ʼ��ק�ô��ڡ����߼���
	//ͬʱҲ�ᴥ��Click�߼�������GGUIEvent_ButtonClick����
	//������ק�͵�����ͬʱ������
	static int m_nWindoeID_CursorDrag;
	//����������Ա�ṩ�������ã�����ק�߼��л��õ���
	static int m_nLastCursorPosX;
	static int m_nLastCursorPosY;
};
//----------------------------------------------------------------
#endif //_GGUIInputState_h_
//----------------------------------------------------------------
