#include <iostream>
#include <cstring>
#include <ctime>
#include <chrono>    /* time_t, struct tm, difftime, time, mktime */
#include <stdio.h>      /* printf */
#include <sstream> // stringstream
#include <iomanip> // put_time
#include "Data.h"
#include "functions.h"
using namespace std;

#include <windows.h>
#include <WinIoCtl.h>
#include <stdio.h>
#include <iostream>
#include "tchar.h"

void bharlo(char* leh) {
    for (int i = 0; i < 512; i++)
    {
        leh[i] = (char)i;
    }
}

int main(int argc, _TCHAR* argv[])
{
    printf("hello world\n");
    DWORD nRead;
    char buf[512];
    char leh[512];
    bharlo(leh);

    HANDLE hDisk = CreateFileA("\\\\.\\E:",
        NULL, FILE_SHARE_WRITE | FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD error_code = GetLastError();
    std::cerr << "Failed to read file on USB drive. Error code: " << error_code << std::endl;
    if (hDisk == INVALID_HANDLE_VALUE) {
        cout << "stuff not workin" << endl;
    }

    SetFilePointer(hDisk, 0x000, 0, FILE_BEGIN);
    error_code = GetLastError();
    std::cerr << "Failed to read file on USB drive. Error code: " << error_code << std::endl;
    WriteFile(hDisk, leh, 512, &nRead, NULL);
    error_code = GetLastError();
    std::cerr << "Failed to read file on USB drive. Error code: " << error_code << std::endl;
    printf("hDisk %i\n", hDisk);

    printf("hDisk %i\n", hDisk);

    SetFilePointer(hDisk, 0x000, 0, FILE_BEGIN);
    error_code = GetLastError();
    std::cerr << "Failed to read file on USB drive. Error code: " << error_code << std::endl;

    ReadFile(hDisk, buf,512, &nRead, NULL);
     error_code = GetLastError();
    std::cerr << "Failed to read file on USB drive. Error code: " << error_code << std::endl;
    for (int currentpos = 0; currentpos < 512; currentpos++) {
        std::cout << buf[currentpos];
    }
    CloseHandle(hDisk);


    return 0;
}










/////////////////////////////////////////////////////////////////////////////////////
//#include <Windows.h>
//#include <iostream>
//#include <string>
//
//int main() {
//    // Specify the path of the USB drive
//    std::string drive_path = "\\\\.\\E:";
//
//    // Open the USB drive
//    HANDLE drive_handle = CreateFileA(
//        drive_path.c_str(),
//        GENERIC_WRITE,
//        FILE_SHARE_WRITE,
//        NULL,
//        OPEN_EXISTING,
//        FILE_ATTRIBUTE_NORMAL,
//        NULL
//    );
//
//    if (drive_handle == INVALID_HANDLE_VALUE) {
//        // Failed to open USB drive
//        std::cerr << "Failed to open USB drive." << std::endl;
//        return 1;
//    }
//
//    // Write data to the USB drive
//    const char* data = "Hello, world!";
//    DWORD bytes_written = 0;
//
//    if (!WriteFile(
//        drive_handle,
//        data,
//        strlen(data),
//        &bytes_written,
//        NULL
//    )) {
//        // Failed to write to USB drive
//        std::cerr << "Failed to write to USB drive." << std::endl;
//        CloseHandle(drive_handle);
//        return 1;
//    }
//
//    // Close the USB drive handle
//    CloseHandle(drive_handle);
//
//    return 0;
//}