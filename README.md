▶️ How to Compile and Run (Step-by-Step)

1️⃣ Open PowerShell in Project Folder

Navigate to the project root directory:

cd "C:\Users\User\OneDrive\Desktop\System Resource Monitor"

Make sure you see src and include folders:

dir

2️⃣ Compile the Project

Run the following command from the project root:

g++ src\*.cpp -o monitor -lpsapi

src\*.cpp → compiles all source files

-o monitor → creates executable named monitor

-lpsapi → links Windows Process Status API

3️⃣ Run the Executable
.\monitor

✅ Sample Output
=== System Resource Monitor ===

CPU Usage: 31.25 %
Memory Usage: 87.15 %

PID     Memory(MB)     Process Name
--------------------------------------
1234    210.45         chrome.exe
4321    95.12          explorer.exe
5678    60.88          Code.exe

Refreshing in 1 second...

📈 Notes

CPU and memory usage update every second

Memory usage may appear high depending on system load

Some system processes may not show memory values due to permission restrictions

🚀 Future Enhancements (Optional)

Sort processes by memory or CPU usage

Add per-process CPU usage

Export logs to a file

Build a GUI using Win32 or Qt

👨‍💻 Author

Kanishk
C++ | Operating Systems | System Programming
