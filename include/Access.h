#ifndef _Access
#define _Access


#include <windows.h>
#include <WinIoCtl.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "tchar.h"
using namespace std;


class Access {
private:
    
    DWORD error_code = GetLastError();
    bool u_Good = 0;
    DWORD status = { 0 };
    VOLUME_DISK_EXTENTS hello;
    string inter = "\\\\.\\E:";
    HANDLE Disk_101;



public:
    bool OpenDevice(string);
    bool Write_on_device(char*,int,int);
    bool Read_from_device(char*,int,int);
    bool Close_device();

};




#endif // !_Access
