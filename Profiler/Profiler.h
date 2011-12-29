#pragma  once

#include <map>
#include <string>
using namespace std;

#ifdef PROFILER
#define EXPORT_PROFILER __declspec(dllexport) 
#else
#define EXPORT_PROFILER __declspec(dllimport)
#ifdef DEBUG
#pragma comment(lib,"../Debug/Profiler.lib")
#else
#pragma comment(lib,"../Release/Profiler.lib")
#endif
#endif


//////////////////////////////////////////////////////////////////////////
// Sample
// void Foo()
// {
//    PROFILER_HERE;
//    
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
    int   mIsTicksValid;
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


// Indirect macro expansion
// See http://stackoverflow.com/questions/1597007/creating-c-macro-with-and-line-token-concatenation-with-positioning-macr for more information
#define PROFILER_IT(x, y) x ## y
#define PROFILER_IT2(x, y) PROFILER_IT(x, y)
#define PROFILER_HERE StopWatchHelper PROFILER_IT2(stopWatchHelper, __LINE__)(__FUNCTION__, __FILE__, __LINE__)
