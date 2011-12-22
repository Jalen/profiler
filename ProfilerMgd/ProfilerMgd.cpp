// ProfilerMgd.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ProfilerMgd.h"

#include "..\Profiler\Profiler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}


namespace DevTools
{
	public ref class ProfilerMgd
	{
	public:
		static void ReportResult(System::String^ title, System::String^ filePath)
		{
			CString strTitle = title;

			Profiler::ReportResult(strTitle.GetBuffer(), CString(filePath).GetBuffer());
		}

		static int AcquireWatch(System::String^ name)
		{
			//string currentFile=new System.Diagnostics.StackTrace(true).GetFrame(0).GetFileName(); 
			//int currentLine = new System.Diagnostics.StackTrace(true).GetFrame(0).GetFileLineNumber();  

			CString strName = name;

			return Profiler::AcquireWatch(strName.GetBuffer());
		}
	};

	public ref struct StopWatchMgd
	{
	public:
		StopWatchMgd(int id)
		{
			StopWatch* sw = Profiler::QueryWatch(id);
			if(sw != NULL)
				sw->Start();

			mID = id;

			mStopped = false;
		}

		~StopWatchMgd()
		{
			Stop();
		}

		void Stop()
		{
			if(mStopped)
				return ;

			StopWatch* sw = Profiler::QueryWatch(mID);
			if(sw != NULL)
				sw->Stop();

			mStopped = true;
		}

	private:
		int mID;
		bool mStopped;
	};
}