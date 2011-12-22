// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PROFILERMGD_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PROFILERMGD_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef PROFILERMGD_EXPORTS
#define PROFILERMGD_API __declspec(dllexport)
#else
#define PROFILERMGD_API __declspec(dllimport)
#endif

// This class is exported from the ProfilerMgd.dll
class PROFILERMGD_API CProfilerMgd {
public:
	CProfilerMgd(void);
	// TODO: add your methods here.
};

extern PROFILERMGD_API int nProfilerMgd;

PROFILERMGD_API int fnProfilerMgd(void);
