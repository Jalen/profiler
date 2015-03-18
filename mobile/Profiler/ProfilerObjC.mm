
#import "ProfilerObjC.h"

#include "Profiler.h"


@implementation ObjCStopWatchHelper {
    StopWatchHelper *stopWatchHelper;
}

- (instancetype)initWithFunctionName:(char *)functionName file:(char *)file line:(int)lineNo {
    if (self) {
        stopWatchHelper = new StopWatchHelper(functionName, file, lineNo);
    }
    
    return self;
}

- (void)dealloc {
    delete stopWatchHelper;
    stopWatchHelper = NULL;
}

@end