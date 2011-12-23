// ProfilerMgd.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "..\Profiler\Profiler.h"

namespace DevTools
{
	public ref class ProfilerMgd
	{
	public:
		static std::string ConvertToString(System::String^ str)
		{
			int q=(int)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str);
			char* p=(char*)q;
			return std::string(p);
		}

		static void ReportResult(System::String^ title, System::String^ filePath)
		{
			Profiler::ReportResult(ConvertToString(title), ConvertToString(filePath));
		}

		static int QueryOrAcquireWatch(System::String^ name)
		{
			//string currentFile=new System.Diagnostics.StackTrace(true).GetFrame(0).GetFileName(); 
			//int currentLine = new System.Diagnostics.StackTrace(true).GetFrame(0).GetFileLineNumber();

			return Profiler::QueryOrAcquireWatch(ConvertToString(name));
		}
	};

	public ref struct StopWatchMgd
	{
	public:
		StopWatchMgd(System::String^ name)
		{
			int id = ProfilerMgd::QueryOrAcquireWatch(name);

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