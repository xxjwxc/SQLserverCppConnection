# SQLserver-Connection-for-cpp
SQLserver Connection for cpp

DatabaseDLL使用说明文档
加载步骤
1，打开Include文件夹
LightCom
TypGuid
DefineFile.h
IDatabaseIO.h
PocoDBIO.cpp
PocoDBIO.h

看到有以上文件，其中TypGuid是工程文件LightCom是公共文件
2，打开你自己的工程，选择添加文件，将IDatabaseIO.h，DefineFile.h，\LightCom\LightCom.cpp, \LightCom \ TypShell.cpp 文件导入到自己工程中。
3，添加现有工程将TypGuid导入到工程，并作为你自己工程的引用依赖项设置（工程->属性->通用属性->框架和引用->添加新引用->选择TypGuid）
4，使用IDatabaseIO.h中函数构造对象。示例代码如下

IDataBaseModule * lpiDataBaseSql = NULL;
if(CreatIDataBaseSql("./DatabaseDLL.dll",lpiDataBaseSql))//创建com
{
	lpiDataBaseSql->OnInit(L"LENOVO-PC",L"./stu.mdb",DATABASE_TYPE::ACCESS,L"",L"123";//初始化
				… …
	lpiDataBaseSql->GetTableCount("sa");//调用
				CString s;
				s.Format("SELECT * from sa");
				_RecordsetPtr m_RecordSetPtr;
				lpiDataBaseSql->MyQuarty(s,m_RecordSetPtr);//调用
}
		
ReleaseIDataBaseSql(lpiDataBaseSql);//释放
5. 特别说明：debug 请使用DatabaseDLLD.dll 。release 请使用DatabaseDLL.dll

6. PocoDBIO 类使用说明
      将：PocoDBIO.h, PocoDBIO.cpp, DefineFile.h, IDatabaseIO.h, LightCom置于同一目录
按照以上步骤完成工程及文件配置
修改PocoDBIO.h中__DLL_PATH宏参数（DatabaseDLLD .dll 路径，注意debug与release 配置说明（5中详细说明））
到此结束，如有疑问，请及时联系
