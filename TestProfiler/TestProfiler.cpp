// TestProfiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <map>
#include <sstream>
#include <algorithm>

#include "../Profiler/Profiler.h"
#pragma comment(lib,"../Debug/Profiler.lib")

void TestPerformanceOfMap()
{
	DECLARE_WATCH(id);
	StopWatchHelper watch1(id);

	std::map<string, string> data;

	for (int i = 0; i < 1000; i++)
	{
		std::stringstream ss;
		ss << i;
		data[ss.str()] == ss.str();
	}

	DECLARE_WATCH(id2);
	StopWatchHelper watch2(id2);

	for (int i = 0; i < 1000; i++)
	{
		data.find("888");
		std::map<string, string>::iterator it = data.find("888");
		if(it != data.end())
		{
			// Got it
		}
	}
}

void TestPerformanceOfMap1()
{
	PROFILER_HERE(0);

	std::map<string, string> data;

	for (int i = 0; i < 1000; i++)
	{
		std::stringstream ss;
		ss << i;
		data[ss.str()] == ss.str();
	}

	PROFILER_HERE(1);

	for (int i = 0; i < 1000; i++)
	{
		data.find("888");
		std::map<string, string>::iterator it = data.find("888");
		if(it != data.end())
		{
			// Got it
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	DECLARE_WATCH(id);
	StopWatchHelper watch1(id);

	TestPerformanceOfMap();
	TestPerformanceOfMap1();
	TestPerformanceOfMap1();
	watch1.Stop();

	Profiler::ReportResult("Title", "c:\\result.xml");

	return 0;
}

