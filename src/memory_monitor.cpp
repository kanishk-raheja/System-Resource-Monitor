#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <iostream>

#include "../include/memory_monitor.h"

void showMemoryUsage() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);

    if (!GlobalMemoryStatusEx(&memInfo)) {
        std::cout << "Memory Usage: unavailable\n";
        return;
    }

    DWORDLONG totalPhys = memInfo.ullTotalPhys;
    DWORDLONG availPhys = memInfo.ullAvailPhys;

    double usedPercent =
        ((double)(totalPhys - availPhys) / totalPhys) * 100.0;

    std::cout << "Memory Usage: " << usedPercent << " %\n";
}
