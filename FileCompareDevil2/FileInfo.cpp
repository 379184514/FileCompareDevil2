#include "StdAfx.h"
#include "FileInfo.h"

CFileInfo::CFileInfo(void)
: nlayers(0)
{
	pParent = NULL;
	nIndex = 0;//���������
	szFilename = "";  //�ļ���
	szFileType = ""; //��չ��
	nFileSize = 0; // �ļ�����
	ftCreationTime.dwHighDateTime = 0; // �ļ�����ʱ��
	ftCreationTime.dwLowDateTime = 0;
	ftLastAccessTime.dwHighDateTime = 0; // �ļ����һ�η���ʱ��
	ftLastAccessTime.dwLowDateTime = 0;
	ftLastWriteTime.dwHighDateTime = 0; // �ļ����һ���޸�ʱ��
	ftLastWriteTime.dwLowDateTime = 0;
	bReadOnly = FALSE;//�Ƿ���ֻ��
	bSystem = FALSE;//�Ƿ�ϵͳ��
	bHidden = FALSE;//�Ƿ����أ�
	dwFileAttributes = 0; //�ļ�����
	nFilesCur = 0;//�ļ���������������Ŀ¼
	nDirsCur = 0;//Ŀ¼��������������Ŀ¼
	nFilesAll = 0;//��ǰ��Ŀ¼���ļ�����
	nDirsAll = 0;//��ǰ��Ŀ¼��Ŀ¼����
	bVisible = TRUE;//�Ƿ�ɼ����۵���
	bDeleted = FALSE;//�Ƿ���ɾ��
	bIgnored = FALSE;//�Ƿ��Ѻ��ԣ������ã�δ����
	nSate = 0;//״̬������
	nChecked = 0;//0-unchecked,1-checked,2-greychecked
	nlayers = 0;
	bExpand = TRUE;
}

CFileInfo::~CFileInfo(void)
{
	Release();
}

int CFileInfo::Release(void)
{
	for(int i=0;i<children.size();i++)
	{
		delete children[i];
	}
	children.clear();
	return 0;
}

int CFileInfo::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		ar << szFilename;
		ar << szFileType;
		ar << nFileSize;
		ar << ftCreationTime.dwHighDateTime;
		ar << ftCreationTime.dwLowDateTime;
		ar << ftLastAccessTime.dwHighDateTime;
		ar << ftLastAccessTime.dwLowDateTime;
		ar << ftLastWriteTime.dwHighDateTime;
		ar << ftLastWriteTime.dwLowDateTime;
		ar << bReadOnly;
		ar << bSystem;
		ar << bHidden;
		ar << dwFileAttributes;
		ar << nFilesCur;
		ar << nDirsCur;
		ar << nFilesAll;
		ar << nDirsAll; 
		ar << bVisible;
		ar << bDeleted; 
		ar << bIgnored;
		ar << nSate;
		ar << nChecked;
		ar << bExpand;
		ar << nlayers;
		ar << (int)children.size();

		for(int i=0;i<children.size();i++)
		{
			children[i]->Serialize(ar);
		}
	}
	else
	{
		Release();
		ar >> szFilename;
		ar >> szFileType;
		ar >> nFileSize;
		ar >> ftCreationTime.dwHighDateTime;
		ar >> ftCreationTime.dwLowDateTime;
		ar >> ftLastAccessTime.dwHighDateTime;
		ar >> ftLastAccessTime.dwLowDateTime;
		ar >> ftLastWriteTime.dwHighDateTime;
		ar >> ftLastWriteTime.dwLowDateTime;
		ar >> bReadOnly;
		ar >> bSystem;
		ar >> bHidden;
		ar >> dwFileAttributes;
		ar >> nFilesCur;
		ar >> nDirsCur;
		ar >> nFilesAll;
		ar >> nDirsAll; 
		ar >> bVisible;
		ar >> bDeleted; 
		ar >> bIgnored;
		ar >> nSate;
		ar >> nChecked;
		ar >> bExpand;
		ar >> nlayers;
		int siz;
		ar >> siz;
		children.resize(siz);

		for(int i=0;i<siz;i++)
		{
			children[i]=new CFileInfo;
			children[i]->pParent=this;
			children[i]->Serialize(ar);
		}
	}
	return 0;
}

CFileInfo* CFileInfo::Copy(void)
{
	CFileInfo* ret = new CFileInfo;
	ret->pParent = NULL;
	ret->nIndex = nIndex;
	ret->szFilename = szFilename;
	ret->szFileType = szFileType;
	ret->nFileSize = nFileSize;
	ret->ftCreationTime.dwHighDateTime = ftCreationTime.dwHighDateTime;
	ret->ftCreationTime.dwLowDateTime = ftCreationTime.dwLowDateTime;
	ret->ftLastAccessTime.dwHighDateTime = ftLastAccessTime.dwHighDateTime;
	ret->ftLastAccessTime.dwLowDateTime = ftLastAccessTime.dwLowDateTime;
	ret->ftLastWriteTime.dwHighDateTime = ftLastWriteTime.dwHighDateTime;
	ret->ftLastWriteTime.dwLowDateTime = ftLastWriteTime.dwLowDateTime;
	ret->bReadOnly = bReadOnly;
	ret->bSystem = bSystem;
	ret->bHidden = bHidden;
	ret->dwFileAttributes = dwFileAttributes;
	ret->nFilesCur = nFilesCur;
	ret->nDirsCur = nDirsCur;
	ret->nFilesAll = nFilesAll;
	ret->nDirsAll = nDirsAll;
	ret->bVisible = bVisible;
	ret->bDeleted = bDeleted;
	ret->bIgnored = bIgnored;
	ret->nSate = nSate;//��ĳ�����
	ret->nChecked = nChecked;
	ret->nlayers = nlayers;
	ret->bExpand = bExpand;
	CFileInfo* child = NULL;
	for(int i=0;i<children.size();i++)
	{
		child = children[i]->Copy();
		child->pParent = ret;
		if (child->nSate == 2)
		{
			children[i]->nSate = 5;
			child->nSate = 1;
			ret->children.push_back(child);
		}
		else if (child->nSate == 3)
		{
			children[i]->nSate = 6;
			child->nSate = 1;
			ret->children.push_back(child);
		}
	}
	return ret;
}
