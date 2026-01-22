#include <iostream>
#include <windows.h>

#include "../include/cpu_monitor.h"
#include "../include/memory_monitor.h"
#include "../include/process_monitor.h"

int main() {
    while (true) {
        system("cls");

        std::cout << "=== System Resource Monitor ===\n\n";

        showCPUUsage();
        showMemoryUsage();
        showTopProcesses();

        std::cout << "\nRefreshing in 1 second...\n";
        Sleep(1000);
    }

    return 0;
}
