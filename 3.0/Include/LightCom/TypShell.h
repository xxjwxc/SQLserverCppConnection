//////////////////////////////////////////////////////////////////////////
//
//	TypShell.h
//
//	Windows 外壳常用功能
//
//-------------------------------------------------------------
//	2006-11-3
//	Ver 1.1
//	Typhone 最后修改
//-------------------------------------------------------------
//
//////////////////////////////////////////////////////////////////////////

#ifndef _TYPSHELL_H
#define _TYPSHELL_H

//	无效的数组索引
#define INVALID_ARRAY_INDEX				-1
//	数组第二个元素的索引
#define SECOND_ARRAY_INDEX				1
//	数组最后一个元素索引
#define LAST_ARRAY_INDEX(nArraySize)	((nArraySize)-1)

// 中文中数字的位基数
#define NUMBER_BASE_DIGIT			4
//	数字基数1万
#define NUMBER_BASE_1WAN			10000
//	数字万的位数
#define NUMBER_1WAN_DIGIT			5
//	数字基数1亿
#define NUMBER_BASE_1YI				100000000
//	数字亿的位数
#define NUMBER_1YI_DIGIT			9

//-------------------------------------------------------------
//	禁止多开程序配置项
#define	MUTEX_FILENAME			"mt.cfg"
#define CFG_SECT_MUTEX			"mt"
#define CFG_MUTEX_ID_NAME		"mtname"
#define MUTEX_COMMON			"TypGame"
#define DEFAULT_MUTEX			"invlalid"
//-------------------------------------------------------------

//-------------------------------------------------------------
//	TypMutex 最多支持互斥量数
#define MAX_MUTEXCOUNT			0xFF
//-------------------------------------------------------------

//-------------------------------------------------------------
//	阻止多开程序的规则
//		程序启动后将创建两个互斥量
//		第一个为通用互斥量 CFG_MUTEX_COMMON
//		第二个为通过配置文件（主程序下的 mt.fak）来获取的互斥量
//			（符合TypMutex规则）
//		如果第一个互斥量不存在，则正常启动
//			否则
//		如果第二个互斥量名字为 CFG_MUTEX_NOMUTEX，则也正常启动
//		如果第二个互斥量符合规则，且没有先例，则正常启动
//		如果第二个互斥量不符合规则，或者已有先例，则禁止
//		如果第二互斥量为指定的禁止互斥标志，则正常启动
//		
//-------------------------------------------------------------

//-------------------------------------------------------------
//		圆周率
#define PI		3.1415926535897932384626
//-------------------------------------------------------------

//-------------------------------------------------------------
//	UINT代码中是否包逻辑含某个值
//		UINT uCode：UINT代码
//		const UINT uId：值
//		返回：如果 uCode 中包含 uId，则返回 TRUE，否则返回 FALSE
BOOL	IsContain( UINT uCode, const UINT uId );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	UINT 代码是否等于某个值
//		UINT uCode：UINT代码
//		const UINT uId：值
//		返回：如果 uCode 等于 uId，则返回 TRUE，否则返回 FALSE
BOOL	IsEqual( UINT uCode, const UINT uId );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	显示数码型数字
//		例如：05  008  0001
//		DWORD Value：数字
//		BYTE Digital：位数
//		返回：显示数码型数字的字符串
CString ShowDigitalInt(DWORD Value, BYTE Digital);
//-------------------------------------------------------------

//-------------------------------------------------------------
//		小写
#define CHI_LIT			0
//		大写
#define CHI_CAP			1
//	单个数字转换为字符串
//		BYTE nValue：数字
//		UINT uType：类型
//		返回：显示数字的字符串
CString ChSInt( BYTE nValue, UINT uType = CHI_LIT );
//	数字转换为字符串
//		int nValue：数字
//		UINT uType：类型
//		返回：显示数字的字符串
CString ChInt( int Value, UINT uType = CHI_LIT );
//-------------------------------------------------------------

//-------------------------------------------------------------
//		星期
#define SSTM_WEEK	0x00000001
//		时间
#define SSTM_TIME	0x00000010
//		日期
#define SSTM_DATE	0x00000100
//		中文显示
#define SSTM_CHN	0x10000000
//		简单显示
#define SSTM_SIMPLE 0x01000000
//	显示系统时间
//		SYSTEMTIME TimeValue：时间
//		UINT uType：类型
//		返回：显示时间的字符串
CString ShowSystemTime( SYSTEMTIME TimeValue, UINT uType = SSTM_WEEK|SSTM_TIME|SSTM_DATE);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	从路径中获取安全的目录字符串
//		LPCSTR lpszPath：路径
//		BOOL bWithLSeparator：是否带 \ 结尾
//		返回：目录字符串
CString GetSafeFolder( LPCSTR lpszPath, BOOL bWithLSeparator = TRUE );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	从路径中获取文件名
//		LPCSTR lpszPath：路径
//		返回：文件名字符串
CString GetFileName( LPCSTR lpszPath );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	从路径中获取目录名
//		LPCSTR lpszPath：路径
//		返回：目录字符串
CString GetFolderName( LPCSTR lpszPath );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	从全文件名获取纯文件名（不带扩展名）
//		LPCSTR lpszFile：文件名
//		返回：纯文件名
CString GetPureName( LPCSTR lpszFile );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	从全文件名获取扩展名
//		LPCSTR lpszFile：文件名
//		返回：扩展名
CString GetFileExt( LPCSTR lpszFile );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	选择目录
//		HWND hWnd：窗口句柄
//		CString strCaption：标题文字
//		CString &strPath：输入时作为默认目录，返回时为实际浏览的目录名
//		返回：选择了目录返回 TRUE，取消了则返回 FALSE
BOOL	BrowseFolder( HWND hWnd, CString strCaption, CString &strPath );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	修改文件名
//		HWND hWnd：窗口句柄
//		CString strFrom：修改前的文件
//		CString strTo：修改为某文件名
//		返回：修改成功则返回 TRUE，否则返回 FALSE
BOOL	RenameFile( HWND hWnd, CString strFrom, CString strTo );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	创建多级目录
//		CString strDir：目录名（多级）
//		返回：创建目录成功，返回 TRUE，否则返回 FALSE
BOOL	CreateMDir( CString strDir );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	删除目录树以及其中的文件
//		CString strDir：待删除的目录名称
//		返回：删除成功，返回 TRUE，否则返回 FALSE
BOOL    DeleteTree( CString strDir );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取文件尺寸
//		CString strFileName：文件名
//		__int64 *pfSize：返回文件尺寸
//		返回：如果文件存在，且取尺寸成功则返回 TRUE，否则返回 FALSE
BOOL	GetFileSize( CString strFileName, __int64 *pfSize ); 
//-------------------------------------------------------------

//-------------------------------------------------------------
//	显示尺寸（空间）
//		__int64 space：空间尺寸
//		返回：表示空间尺寸的字符串
CString ShowSpace( __int64 space );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取模块的文件名
//		HMODULE hModule：模块句柄
//		返回：文件名字符串
CString GetModuleFile( HMODULE hModule );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取模块的路径
//		HMODULE hModule：模块句柄
//		返回：路径字符串
CString GetModulePath( HMODULE hModule );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取模块的目录
//		HMODULE hModule：模块句柄
//		返回：目录名符串
CString GetModuleFolder( HMODULE hModule );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取 GUID 字符串
//		GUID &guid：待转换 guid
//		CString &strAll：完整字符串
//		CString &strApp：App 部分
//		CString &strModule：Module 部分
void GetGuidString( GUID& guid, CString& strAll, CString& strApp, CString& strModule );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	GUID 转换为字符串
//		GUID &guid：待转换 guid
//		CString &str：返回字符串
void GuidToStr( GUID &guid, CString &str );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	选择排序
//		int *pnSrc：待排序数字
//		int nCount：待排序数字数目
//		BOOL bSmallFirst：是否从小到大排列
void SelectSort( int *pnSrc, int nCount, BOOL bSmallFirst );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	折半查找（只能查找已排序数列）
//		int *pnSrc：待查找数字
//		int nCount：数字数目
//		int nValue：待查找的值
//		返回：查找到的位置的索引号，如果没找到则返回 -1
int DichotomyFind( int *pnSrc, int nCount, int nValue );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	裁剪区域
//		RECT &rt：输入待裁剪区域，返回裁剪后区域
//		int &nDstX，&nDstY：目标位置
//		int &nWidth，&nHeight：目标尺寸
//		int &nSrcX，&nSrcY：源位置
void ClipBoard( RECT &rt, int &nDstX, int &nDstY, int &nWidth, int &nHeight, int &nSrcX, int &nSrcY );
//-------------------------------------------------------------

//-------------------------------------------------------------
//	初始化随机种子
void Randomize(__int64 nSeed);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	取随机值
unsigned long Random(long nMax);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	取随机值
//		__int64 &nSeed：随机种子
//		long nMax：最大值
//		返回：产生的随机值
unsigned long RandomEx(__int64 &nSeed, long nMax);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	锁定/解锁时钟（防止重入）
#define LOCKTIMER(bLock)	if (bLock) return; bLock = TRUE;
#define LOCKTIMER_(bLock, val)	if (bLock) return val; bLock = TRUE;
#define UNLOCKTIMER(bLock)	bLock = FALSE;
//-------------------------------------------------------------

//-------------------------------------------------------------
//	括号类型
typedef enum enumBRACKETTYPE{
	//	小括号
	BT_SMALL		= (UINT)0,
	//	中括号
	BT_MID			= (UINT)1,
	//	大括号
	BT_BIG			= (UINT)2,
}BRACKETTYPE;
//-------------------------------------------------------------

//-------------------------------------------------------------
//	查找第一个括号
//		CString str：待查找字符串
//		CString &strDst：返回查找到的字符串
//		CString &strRest：返回剩余的字符串
//		BRACKETTYPE type：查找的括号类型
//		返回：找到的字符串的位置
int FindFirstBracket(CString str, CString &strDst, CString &strRest, BRACKETTYPE type = BT_SMALL);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	查找第一个分号
//		CString str：待查找字符串
//		CString &strDst：返回查找到的字符串
//		CString &strRest：返回剩余的字符串
//		返回：找到的字符串的位置
int FindFirstComma(CString str, CString &strDst, CString &strRest);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	查找第一个空格
//		CString str：待查找字符串
//		CString &strDst：返回查找到的字符串
//		CString &strRest：返回剩余的字符串
//		返回：找到的字符串的位置
int FindFirstBlank(CString str, CString &strDst, CString &strRest);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	查找括号前的字符串
//		CString str：待查找字符串
//		CString &strDst：返回查找到的字符串
//		CString &strRest：返回剩余的字符串
//		BRACKETTYPE type：括号类型
//		返回：找到的字符串的位置
int StringBeforeBracket(CString str, CString &strDst, CString &strRest, BRACKETTYPE type = BT_SMALL);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	查找括号
//		CString str：待查找字符串
//		int nIndex：查找第nindex个括号
//		CString &strDst：返回找到的字符串
//		BRACKETTYPE type：括号类型
//		返回：找到了指定的括号则返回 TRUE，否则返回 FALSE
BOOL FindBracket(CString str, int nIndex, CString &strDst, BRACKETTYPE type = BT_SMALL);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	查找括号里的内容
//		CString str：待查找字符串
//		int nIndex：查找第nIndex个括号
//		CString &strDst：返回找到的括号内的字符串
//		BRACKETTYPE type：括号类型
//		返回：找到了指定括号则返回 TRUE，否则返回 FALSE
BOOL FindBracketContain(CString str, int nIndex, CString &strDst, BRACKETTYPE type = BT_SMALL);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	查找分号
BOOL FindComma(CString str, int nIndex, CString &strDst);
//	查找空格
BOOL FindBlank(CString str, int nIndex, CString &strDst);
//	查找分号数
int FindCommaCount(CString str);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	将字符串转换为整数
//		CString &str：待转换字符串
//		int *pInt, DWORD *pdw, __int64 *pInt64：返回转换完成的数字
//		返回：如果字符串是数字内容，则返回 TRUE，否则返回 FALSE
BOOL GetStrNum(CString &str, int *pInt);
BOOL GetStrNum(CString &str, DWORD *pdw);
BOOL GetStrNum64(CString &str, __int64 *pInt64);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	安全的按字数拆分字符串（不会把双字节拆两半）
//		LPCSTR lpsz：待拆分字符串
//		int nPart1Count：第一部分拆分的字数
//		CString &str1：返回第一部分字符串
//		CString &str2：返回第二部分字符串
//		返回：如果拆分成功则返回 TRUE，否则返回 FALSE
BOOL GetSafeStrPart(LPCSTR lpsz, int nPart1Count, CString &str1, CString &str2);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	安全的按字节数拆分字符串（不会把双字节拆两半）
//		LPCSTR lpsz：待拆分字符串
//		int nPart1Count：第一部分拆分的字节数
//		CString &str1：返回第一部分字符串
//		CString &str2：返回第二部分字符串
//		返回：如果拆分成功则返回 TRUE，否则返回 FALSE
BOOL GetSafeStrPartInCharCount(LPCSTR lpsz, int nPart1Count, CString &str1, CString &str2);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	截断显示字符串
CString CutString(LPCSTR lpsz, int nCount, BOOL bByCharCount);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	自动增加字符串末尾数字
//		如果字符串以数字结尾，则末尾数字自动增加1，否则末尾加0
//		CString &str：待处理字符串
//		返回：处理过的字符串
CString AutoIncStrNum(CString &str);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	链接文件打开方式到指定程序（修改注册表，文件打开方式）
//		HINSTANCE hInstance：程序实例句柄
//		LPCSTR lpszFileExt：待链接文件扩展名
//		int nIconIndex：使用程序中的第nIconIndex个图标显示
void LinkFile(HINSTANCE hInstance, LPCSTR lpszFileExt, int nIconIndex);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	链接多个文件打开方式到程序（修改注册表，文件打开方式）
//		HINSTANCE hInstance：程序实例句柄
//		CString *lpstrExt：待链接文件扩展名列表
//		int nExtCount：文件扩展名列表长度
//		int nIconIndex：使用程序中的第nIconIndex个图标显示
void LinkFileEx(HINSTANCE hInstance, CString *lpstrExt, int nExtCount, int nIconIndex);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	从程序运行参数中获取通过参数链接的文件名
//		LPSTR lpCmdLine：运行参数
//		CString &str：返回文件名
//		返回：有文件链接到此程序，并且获取到了此文件名，则返回 TRUE，否则返回 FALSE
BOOL LinkFileGetOpenFileName(LPSTR lpCmdLine, CString &str);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取角度
//		POINT &pntSrc：起点坐标
//		POINT &pntDst：终点坐标
//		返回：起点到终点的角度
//		注意：使用的是屏幕坐标系（左上角为原点）
float GetAngle(POINT &pntSrc, POINT &pntDst);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取金钱字符串（以逗号分隔）
//		例如：30,008,639
//		int nMoney：金钱数目
//		返回：表达金钱数目的字符串
CString GetMoneyStr(__int64 nMoney);
//-------------------------------------------------------------

// Typhone [6/5/2009] 获取缩略数字 int 数字只占7个字符
CString GetOmittedNum(__int64 nNum);

//-------------------------------------------------------------
//	链接文件打开方式的动态链接库文件名
#define LINKFILE_MODULE_FILENAME		"LinkFile.dll"
//	链接文件打开方式的函数名称
#define LINKFILE_PROC_NAME				"LinkFileToAppA"
//-------------------------------------------------------------

//-------------------------------------------------------------
//	数字限制最大最小值
#define minmax(minval, maxval, val)			val = max(minval, min(maxval, val))
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取当前时间(返回 100 纳秒精度)
//		返回：当前时间
__int64 GetNowFileTime();
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取桌面工作区域，不包括任务栏
RECT GetWorkArea();
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取窗口尺寸 —— 不论窗口当前正处于什么状态都可取到
//		HWND hWnd：待取区域的窗口
//		返回：窗口区域
RECT GetWindowRealRect(HWND hWnd);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取配置文件内容 - 字符串
//		LPCSTR lpszCfgFile：配置文件路径
//		LPCSTR lpszSect：配置区
//		LPCSTR lpszID：配置项
//		CString &strValue：输入默认字符串，返回获取到的字符串
//		返回：读取到的字符串长度
DWORD GetConfigStr(LPCSTR lpszCfgFile, LPCSTR lpszSect, LPCSTR lpszID, CString &strValue);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取配置文件内容 - 整数
//		LPCSTR lpszCfgFile：配置文件路径
//		LPCSTR lpszSect：配置区
//		LPCSTR lpszID：配置项
//		int nDefaultValue：默认值
//		返回：读取到的值（如果没有读到此配置项，则返回值等于输入的默认值）
int GetConfigInt(LPCSTR lpszCfgFile, LPCSTR lpszSect, LPCSTR lpszID, int nDefaultValue);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取配置文件内容 - 无符号整数
//		LPCSTR lpszCfgFile：配置文件路径
//		LPCSTR lpszSect：配置区
//		LPCSTR lpszID：配置项
//		DWORD dwDefaultValue：默认值
//		返回：读取到的值（如果没有读到此配置项，则返回值等于输入的默认值）
DWORD GetConfigDW(LPCSTR lpszCfgFile, LPCSTR lpszSect, LPCSTR lpszID, DWORD dwDefaultValue);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	写配置
//		LPCSTR lpszCfgFile：配置文件路径
//		LPCSTR lpszSect：配置区
//		LPCSTR lpszID：配置项
//		CString strValue：待写入字符串
BOOL SetConfigStr(LPCSTR lpszCfgFile, LPCSTR lpszSect, LPCSTR lpszID, CString strValue);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取配置文件内容 - 整数
//		LPCSTR lpszCfgFile：配置文件路径
//		LPCSTR lpszSect：配置区
//		LPCSTR lpszID：配置项
//		int nValue：待写入值
BOOL SetConfigInt(LPCSTR lpszCfgFile, LPCSTR lpszSect, LPCSTR lpszID, int nValue, BOOL bHex = FALSE);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取配置文件内容 - 无符号整数
//		LPCSTR lpszCfgFile：配置文件路径
//		LPCSTR lpszSect：配置区
//		LPCSTR lpszID：配置项
//		DWORD dwValue：待写入值
BOOL SetConfigDW(LPCSTR lpszCfgFile, LPCSTR lpszSect, LPCSTR lpszID, DWORD dwValue, BOOL bHex = TRUE);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	比较字符串大小
//		LPCSTR lpsz1：比较者
//		LPCSTR lpsz2：被比较者
//		BOOL bReverse：是否逆序比较
//		int &nSwitch：比较结果
//			如果 1 == 2，则返回 0， 
//			正常情况下，如果 1 比 2 大，则返回大于0；如果 1 比 2 小则返回小于0
//			逆序情况下，如果 1 比 2 大，则反回小于0；如果 1 比 2 小则返回大于0
void CompareStr(LPCSTR lpsz1, LPCSTR lpsz2, BOOL bReverse, int &nResult);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	比较BOOL值大小
//		BOOL b1：比较者
//		BOOL b2：被比较者
//		BOOL bReverse：是否逆序比较
//		int &nSwitch：比较结果
//			如果 1 == 2，则返回 0， 
//			正常情况下，如果 1 比 2 大，则返回大于0；如果 1 比 2 小则返回小于0
//			逆序情况下，如果 1 比 2 大，则反回小于0；如果 1 比 2 小则返回大于0
void CompareBOOL(BOOL b1, BOOL b2, BOOL bReverse, int &nResult);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	比较 int 值大小
//		int n1：比较者
//		int n2：被比较者
//		BOOL bReverse：是否逆序比较
//		int &nSwitch：比较结果
//			如果 1 == 2，则返回 0， 
//			正常情况下，如果 1 比 2 大，则返回大于0；如果 1 比 2 小则返回小于0
//			逆序情况下，如果 1 比 2 大，则反回小于0；如果 1 比 2 小则返回大于0
void CompareInt(int n1, int n2, BOOL bReverse, int &nResult);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	比较 DWORD 值大小
//		DWORD dw1：比较者
//		DWORD dw2：被比较者
//		BOOL bReverse：是否逆序比较
//		int &nSwitch：比较结果
//			如果 1 == 2，则返回 0， 
//			正常情况下，如果 1 比 2 大，则返回大于0；如果 1 比 2 小则返回小于0
//			逆序情况下，如果 1 比 2 大，则反回小于0；如果 1 比 2 小则返回大于0
void CompareDWORD(DWORD dw1, DWORD dw2, BOOL bReverse, int &nResult);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	比较 int64 值大小
//		__int64 n641：比较者
//		__int64 n642：被比较者
//		BOOL bReverse：是否逆序比较
//		int &nSwitch：比较结果
//			如果 1 == 2，则返回 0， 
//			正常情况下，如果 1 比 2 大，则返回大于0；如果 1 比 2 小则返回小于0
//			逆序情况下，如果 1 比 2 大，则反回小于0；如果 1 比 2 小则返回大于0
void CompareInt64(__int64 n641, __int64 n642, BOOL bReverse, int &nResult);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	创建 MutexName
CString MakeMutexName(int nSeed);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	互斥量名是否符合规则
//		LPCSTR lpszMutex：互斥量名称
//	返回：如果合法，则返回 TRUE，否则返回 FALSE
BOOL ValidMutexName(LPCSTR lpszMutex);
//-------------------------------------------------------------

typedef enum enumMUTEXCHECKRESULT
{
	MTCR_OK = (UINT)0,
	MTCR_ALREADY = (UINT)0x80000001,
	MTCR_ILLEGAL = (UINT)0x80000002,
}MUTEXCHECKRESULT;
//-------------------------------------------------------------
//	互斥检测
//		HINSTANCE hInstance：主程序实例句柄
//		HANDLE &hMutex1：互斥量1
//		HANDLE &hMutex2：互斥量2
//	返回：如果返回 TRUE，则可以进入程序，否则不能
MUTEXCHECKRESULT MutexCheck(HINSTANCE hInstance, HANDLE &hMutex, CString *pStrMutexName);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	查找互斥窗口
HWND FindMutexWnd(LPCSTR lpszMutexName);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	设置互斥窗口（只有设置了才能被查找到）
void SetMutexWnd(HWND hWnd, LPCSTR lpszMutexName);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	拷贝到剪帖板
BOOL CopyToClipboard(CString &strData);
//-------------------------------------------------------------

#define TILERECT_COUNT	9
#define TILERECT_LT		0
#define TILERECT_T		1
#define TILERECT_RT		2
#define TILERECT_L		3
#define TILERECT_C		4
#define TILERECT_R		5
#define TILERECT_LB		6
#define TILERECT_B		7
#define TILERECT_RB		8

//-------------------------------------------------------------
//	0	1	2
//	3	4	5
//	6	7	8
//	获取平铺信息（按九宫格切图）
//		RECT &rtDst：目标区域
//		RECT &rtSrc：源区域
//		RECT &rtSrcTile：除去边框外的平铺区域（4号）
//		CRect *pSrcRects：切割以后的源区域
//		CRect *pDstRects：切割后的目标区域
void GetTileInfo(const CRect &rtDst, const CRect &rtSrc, const CRect &rtSrcTile, CRect *pDstRects, CRect *pSrcRects);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	获取数字字符串
CString GetNumStr(int nNum);
CString GetNumStr(UINT uNum);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	将数字转换为字符串
//		BOOL bPlus：		如果是正数，前面是否带+号
//		BOOL bComma：		是否用逗号分隔数字（如果为TRUE，则后面的参数无效）
//		BOOL bLong：		长显示模式，#亿#万#（如果为TRUE，则后面的参数无效）
//		BOOL bShort：		简短显示模式（只显示 #亿，#.#亿，#万，#.#万）
//		int nMaxTailCount：	简短显示模式的小数位数
CString NumberToStr(__int64 nNumber, BOOL bPlus, BOOL bComma, BOOL bLong, BOOL bShort, int nMaxTailCount = 0);
//-------------------------------------------------------------

//	float小数位四舍五入变整数
long FloatRound(float fNumber);

#endif