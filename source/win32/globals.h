#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <map>
#include <vector>
#include <set>
#include <mutex>
#include <condition_variable>

#include "../openwl.h"

extern HINSTANCE hInstance; // set by DllMain
extern const WCHAR *szWindowClass;

enum Win32MessageEnum {
    Nothing = WM_USER,
    WM_MainThreadExecMsg,
};

// globals
extern std::map<int, wlAction> actionMap;
extern std::vector<ACCEL> acceleratorList;
extern std::set<unsigned char> suppressedScanCodes;

// timer stuff
extern LARGE_INTEGER perfCounterTicksPerSecond;

// direct2D stuff
extern bool useDirect2D;
extern ID2D1Factory1 *d2dFactory;
extern IDWriteFactory *writeFactory;
void d2dCreateTarget(wlWindow wlw);

// fwd decls for wlExecuteOnMainThread
struct MainThreadExecItem {

    wlVoidCallback callback;
    void *data;
    std::condition_variable& execCond;
};
void ExecuteMainItem(MainThreadExecItem *item);

// client-supplied callback
extern wlEventCallback eventCallback;

// custom messages
#define OPENWL_TIMER_MESSAGE WM_USER+0



