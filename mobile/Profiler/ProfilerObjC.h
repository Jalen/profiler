
#import <Foundation/Foundation.h>

@interface ObjCStopWatchHelper : NSObject

- (instancetype)initWithFunctionName:(char*)functionName file:(char*)file line:(int)lineNo;

@end

#ifdef DEBUG
#   define DLog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#   define DLog(...)
#endif

// ALog always displays output regardless of the DEBUG setting
#define ALog(fmt, ...) NSLog((@"%s [Line %d] " fmt), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__)

#define PROFILER_HERE_OBJC ObjCStopWatchHelper* stopWatchHelper = [[ObjCStopWatchHelper alloc] initWithFunctionName:__PRETTY_FUNCTION__ file:__FILE__ line:__LINE__]
