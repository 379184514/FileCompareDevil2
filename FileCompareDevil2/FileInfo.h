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

	int nIndex;//数组中序号
	BOOL bReadOnly;//是否是只读
	BOOL bSystem;//是否系统；
	BOOL bHidden;//是否隐藏；
	DWORD dwFileAttributes; //文件属性
	FILETIME ftCreationTime; // 文件创建时间
	FILETIME ftLastAccessTime; // 文件最后一次访问时间
	FILETIME ftLastWriteTime; // 文件最后一次修改时间
	ULONGLONG nFileSize; // 文件长度
	CString szFileType; //扩展名
	CString szFilename; //文件名

	int nFilesCur;//文件总数，不包括子目录
	int nDirsCur;//目录总数，不包括子目录
	int nFilesAll;//当前子目录下文件总数
	int nDirsAll;//当前子目录下目录总数

	BOOL bVisible;//是否可见，折叠用
	BOOL bDeleted;//是否已删除
	BOOL bIgnored;//是否已忽略，过滤用
	int nSate;//状态：0-正常，1-新增，2-待复制，3-待剪切，4-待删除，5-已复制，6-已剪切/已删除，7-重命名过，8-已排除；
	int nChecked;//0-unchecked,1-checked,2-greychecked
	BOOL bExpand;//TRUE-展开，FALSE-折叠
	//CString sFullPath;
	
	CFileInfo* Copy(void);//生成自身结构的拷贝
	int nlayers;//父目录层数，0为root
};
