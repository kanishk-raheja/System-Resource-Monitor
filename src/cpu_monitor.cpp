#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <iostream>

#include "../include/cpu_monitor.h"

static ULONGLONG fileTimeToULL(const FILETIME& ft) {
    return (static_cast<ULONGLONG>(ft.dwHighDateTime) << 32) |
            ft.dwLowDateTime;
}

void showCPUUsage() {
    static FILETIME prevIdle, prevKernel, prevUser;
    static bool firstCall = true;

    FILETIME idleTime, kernelTime, userTime;

    if (!GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
        std::cout << "CPU Usage: unavailable\n";
        return;
    }

    if (firstCall) {
        prevIdle = idleTime;
        prevKernel = kernelTime;
        prevUser = userTime;
        firstCall = false;
        std::cout << "CPU Usage: calculating...\n";
        return;
    }

    ULONGLONG idleDiff =
        fileTimeToULL(idleTime) - fileTimeToULL(prevIdle);
    ULONGLONG kernelDiff =
        fileTimeToULL(kernelTime) - fileTimeToULL(prevKernel);
    ULONGLONG userDiff =
        fileTimeToULL(userTime) - fileTimeToULL(prevUser);

    ULONGLONG total = kernelDiff + userDiff;
    double cpuUsage = (total - idleDiff) * 100.0 / total;

    std::cout << "CPU Usage: " << cpuUsage << " %\n";

    prevIdle = idleTime;
    prevKernel = kernelTime;
    prevUser = userTime;
}
