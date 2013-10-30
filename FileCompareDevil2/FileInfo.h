#pragma once
#include <vector>

class CFileInfo
{
public:
	CFileInfo(void);
	~CFileInfo(void);
	CFileInfo* pParent;
	std::vector<CFileInfo*> children;
	int Release(void);
	int Serialize(CArchive& ar);

	int nIndex;//���������
	BOOL bReadOnly;//�Ƿ���ֻ��
	BOOL bSystem;//�Ƿ�ϵͳ��
	BOOL bHidden;//�Ƿ����أ�
	DWORD dwFileAttributes; //�ļ�����
	FILETIME ftCreationTime; // �ļ�����ʱ��
	FILETIME ftLastAccessTime; // �ļ����һ�η���ʱ��
	FILETIME ftLastWriteTime; // �ļ����һ���޸�ʱ��
	ULONGLONG nFileSize; // �ļ�����
	CString szFileType; //��չ��
	CString szFilename; //�ļ���

	int nFilesCur;//�ļ���������������Ŀ¼
	int nDirsCur;//Ŀ¼��������������Ŀ¼
	int nFilesAll;//��ǰ��Ŀ¼���ļ�����
	int nDirsAll;//��ǰ��Ŀ¼��Ŀ¼����

	BOOL bVisible;//�Ƿ�ɼ����۵���
	BOOL bDeleted;//�Ƿ���ɾ��
	BOOL bIgnored;//�Ƿ��Ѻ��ԣ�������
	int nSate;//״̬��0-������1-������2-�����ƣ�3-�����У�4-��ɾ����5-�Ѹ��ƣ�6-�Ѽ���/��ɾ����7-����������8-���ų���
	int nChecked;//0-unchecked,1-checked,2-greychecked
	BOOL bExpand;//TRUE-չ����FALSE-�۵�
	//CString sFullPath;
	
	CFileInfo* Copy(void);//��������ṹ�Ŀ���
	int nlayers;//��Ŀ¼������0Ϊroot
};
