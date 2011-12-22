#pragma  once

#include <map>
#include <string>
using namespace std;

#ifdef PROFILER
#define EXPORT_PROFILER __declspec(dllexport) 
#else
#define EXPORT_PROFILER __declspec(dllimport)
#endif


//////////////////////////////////////////////////////////////////////////
// Sample
// void Foo()
// {
//    static int id = Profiler::AcquireWatch("Foo");
//    StopWatchHelper swh(id);
//    ....
// }

#pragma warning(disable:4251) 

class EXPORT_PROFILER StopWatch
{
public:
	StopWatch(string reportName, string file, int line, bool start = true);

	~StopWatch();

	void Stop();

	void Start();

	void Report(fstream& out, bool bReset = false);

	bool isEqual(string reportName, string file, int line);
private:
	string mReportName;
	string mFile;
	int   mLine;
	ULONG mStartTick;
	ULONG mTicks;
	bool  mIsStopped;
	int   mHitCount;
};

class EXPORT_PROFILER Profiler
{
public:
	static int AcquireWatch(string name, string file = "", int line= 0);
	static int QueryOrAcquireWatch(string name, string file = "", int line= 0);

	static StopWatch* QueryWatch(int count);

	static void ReportResult(string title, string filePath);
};

#define DECLARE_WATCH(id) static int id = Profiler::AcquireWatch(__FUNCTION__, __FILE__, __LINE__);

class EXPORT_PROFILER StopWatchHelper
{
public:
	StopWatchHelper(int id);
	StopWatchHelper(string name, string file = "", int line= 0);

	~StopWatchHelper();

	void Stop();

private:
	int mID;
	bool mStopped;
};


#define PROFILER_HERE(id) StopWatchHelper stopWatchHelper_##id(__FUNCTION__, __FILE__, __LINE__);
