// magicbox2.cpp : main source file for magicbox2.exe
//

#include "stdafx.h"
#include "DuiSystem.h" 
#include "DuiDefaultLogger.h"
 

#include "MainDlg.h"
 
CAppModule _Module;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	HRESULT hRes = CoInitialize(NULL);
	DUIASSERT(SUCCEEDED(hRes));

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	AtlAxWinInit();

	char szCurrentDir[MAX_PATH]; memset( szCurrentDir, 0, sizeof(szCurrentDir) );
	GetModuleFileNameA( NULL, szCurrentDir, sizeof(szCurrentDir) );
	LPSTR lpInsertPos = strrchr( szCurrentDir, L'\\' );
	*lpInsertPos = '\0';   

	DuiSystem duiSystem(hInstance);
	DefaultLogger loger;
	loger.setLogFilename(CStringA(szCurrentDir)+"\\dui-demo.log");
	duiSystem.SetLogger(&loger);

	duiSystem.logEvent("demo started");
	duiSystem.InitName2ID(IDR_NAME2ID,"XML2");//����ID���ƶ��ձ�,����Դ����APP��������Ƥ��Ӧ�ù��������ֱ������ֱ����Ǵӳ�����Դ����
#ifdef __DUIFILE_RC 
	//���ļ��м���Ƥ��,ָ��Ƥ��λ��
    lstrcatA( szCurrentDir, "\\..\\template.wtl\\skin" );
	DuiResProviderFiles *pResFiles=new DuiResProviderFiles;
	if(!pResFiles->Init(szCurrentDir))
	{
		DUIASSERT(0);
		return 1;
	}
	duiSystem.SetResProvider(pResFiles);
#else 
	//����Դ����Ƥ��
	duiSystem.SetResProvider(new DuiResProviderPE(hInstance));
#endif 
	// ���� Load xx ������Ǳ���ģ�����Ƥ����������ʾ���ⲿ����Դ����Ƥ�����𣬲�ͬ��Ƥ�������в�ͬ�Ķ���
	DuiString::getSingleton().Init(IDR_DUI_STRING_DEF); // �����ַ���
	DuiFontPool::getSingleton().SetDefaultFont(_T("����"), -12); // ��������
	DuiSkinPool::getSingleton().Init(IDR_DUI_SKIN_DEF); // ����Ƥ��
	DuiStylePool::getSingleton().Init(IDR_DUI_STYLE_DEF); // ���ط��
	DuiCSS::getSingleton().Init(IDR_DUI_OBJATTR_DEF);//������Ĭ������

	int nRet = 0; 
	// BLOCK: Run application
	{
		CMainDlg dlgMain;  
		nRet = dlgMain.DoModal();  
	}

	duiSystem.logEvent("demo end");

	delete duiSystem.GetResProvider();

	CoUninitialize();
	return nRet;
}