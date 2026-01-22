#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <iostream>
#include <iomanip>

#include "../include/process_monitor.h"

void showTopProcesses() {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        std::cout << "Processes: unavailable\n";
        return;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(snapshot, &pe)) {
        CloseHandle(snapshot);
        std::cout << "Processes: unavailable\n";
        return;
    }

    std::cout << "\nPID\tMemory(MB)\tProcess Name\n";
    std::cout << "--------------------------------------\n";

    int count = 0;

    do {
        HANDLE hProcess = OpenProcess(
            PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
            FALSE,
            pe.th32ProcessID
        );

        if (hProcess) {
            PROCESS_MEMORY_COUNTERS pmc;
            if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
                std::cout << pe.th32ProcessID << "\t"
                          << std::fixed << std::setprecision(2)
                          << (pmc.WorkingSetSize / (1024.0 * 1024.0)) << "\t\t"
                          << pe.szExeFile << "\n";
                count++;
            }
            CloseHandle(hProcess);
        }

        if (count >= 5) break;   // limit output

    } while (Process32Next(snapshot, &pe));

    CloseHandle(snapshot);
}
