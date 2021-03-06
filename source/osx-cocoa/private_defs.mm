//
//  private_defs.cpp
//  openwl
//
//  Created by Daniel X on 2/12/18.
//  Copyright (c) 2018 OpenWL Developers. All rights reserved.
//

#include "private_defs.h"
#include "globals.h"

#import "WLWindowObject.h"

// wlAction
@implementation WLActionObject
@synthesize _id;
@synthesize label;
@synthesize icon;
@synthesize accel;
@end


// wlTimer
#define ONE_BILLION 1000000000
inline double timespecDiff(mach_timespec_t newer, mach_timespec_t older) {
    if (newer.tv_nsec < older.tv_nsec) {
        newer.tv_nsec += ONE_BILLION;
        newer.tv_sec -= 1;
    }
    auto diff = (newer.tv_sec - older.tv_sec) * ONE_BILLION + (newer.tv_nsec - older.tv_nsec);
    return (double) diff / ONE_BILLION;
}

@implementation WLTimerObject
@synthesize timer;
@synthesize forWindow;
@synthesize _id;
- (void)timerFired:(id)sender {
    WLEvent event;
    event.handled = false;
    event.eventType = WLEventType_Timer;
    event.timerEvent.timerID = _id;
    event.timerEvent.timer = (wlTimer)self;
    event.timerEvent.stopTimer = false;
    
    mach_timespec_t now;
    clock_get_time(systemClock, &now);
    event.timerEvent.secondsSinceLast = timespecDiff(now, self->lastTime);
    
    eventCallback((wlWindow)forWindow, &event, forWindow.userData);
    
    self->lastTime = now;
    
    if (event.handled && event.timerEvent.stopTimer) {
        [self stopTimer];
    }
}
- (void)stopTimer {
    printf("stopping timer %d\n", _id);
    [timer invalidate];
}
@end
