/*
 * Profiler.h
 *
 *  Created on: 2013-6-8
 *      Author: wangjiay
 */

#pragma once

#include <map>
#include <string>
using namespace std;


//////////////////////////////////////////////////////////////////////////
// Sample
// void Foo()
// {
//    PROFILER_HERE;
//
//    ....
// }

class StopWatch
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
	double mStartTick;
	double mTicks;
	bool  mIsStopped;
	int   mHitCount;
    int   mIsTicksValid;
};

class Profiler
{
public:
	static int AcquireWatch(string name, string file = "", int line= 0);
	static int QueryOrAcquireWatch(string name, string file = "", int line= 0);

	static StopWatch* QueryWatch(int count);

	static void ReportResult(string title, string filePath);
};

#define DECLARE_WATCH(id) static int id = Profiler::AcquireWatch(__FUNCTION__, __FILE__, __LINE__);

class StopWatchHelper
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
#define PROFILER_HERE2(name) StopWatchHelper PROFILER_IT2(stopWatchHelper, __LINE__)(name, __FILE__, __LINE__)

