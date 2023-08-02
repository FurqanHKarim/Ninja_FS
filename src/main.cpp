#include <iostream>
#include <cstring>
#include <ctime>
#include <chrono>    /* time_t, struct tm, difftime, time, mktime */
#include <stdio.h>      /* printf */
#include <sstream> // stringstream
#include <iomanip> // put_time

#include "Data.h"
#include "functions.h"
#include "Access.h"
#include "File_Header.h"
using namespace std;



void bharlo(char* leh) {
    for (int i = 0; i < 512; i++)
    {
        leh[i] = (char)i;
    }
}



int main()
{
    //Access testing;
    //// Open the disk device
    //char buf[512] = {0};
    //char leh[512] = {0};
    //bharlo(leh);
    //string inter="E:";
    //testing.OpenDevice(inter);
    //testing.Write_on_device(leh,0x0000,sizeof(leh));
    //testing.Read_from_device(buf,0x000,sizeof(buf));
    //testing.Close_device();
    Sysstem n;
    cout << sizeof(n.Ninja) << endl;
    cout << sizeof(n);
    // Close the disk device
    return 0;
}

/*    removed cuz moved into class Access.h left here cuz it could prove useful for the time being
    /// accessing the Disk using its given disk letter;
    HANDLE Disk_101 = 
    CreateFileA(
            inter.c_str(),                        //[in]           LPCSTR   lpFileName,
            GENERIC_WRITE | GENERIC_READ,       //[in]           DWORD    dwDesiredAccess,
            FILE_SHARE_READ|FILE_SHARE_WRITE,   //[in]           DWORD    dwShareMode,
            NULL,                               //[in, opt]      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
            OPEN_EXISTING,                      //[in]           DWORD                 dwCreationDisposition,
            0,                                  //[in]           DWORD                 dwFlagsAndAttributes,
            NULL                                //[in, opt]      HANDLE                hTemplateFile
    );error_code = GetLastError();
    if (Disk_101 == INVALID_HANDLE_VALUE) {
        cout << "File not created. Error Code: " << GetLastError() << endl;
        return(-1);
    }
    error_code = GetLastError();
    // getting the device's physical device no
    if (!DeviceIoControl(
                Disk_101,                     // handle to device
        IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS, // dwIoControlCode
             NULL,                                 // lpInBuffer
          0,                                    // nInBufferSize
            &hello,                 // output buffer
         sizeof(hello),               // size of output buffer
        &status,            // number of bytes returned
           NULL           // OVERLAPPED structure
    ))
    {
        cout<< "Device Credentials not extracted: Error"<<GetLastError()<<endl;
    }
    error_code = GetLastError();
    if (!CloseHandle(Disk_101))//closing that instance of the data device
    {
        cout<<"Handle not closed: Error"<<GetLastError()<<endl;
    }

    inter = "\\\\.\\PhysicalDrive";
    inter.append(to_string(hello.Extents[0].DiskNumber));

    /////////////////Reopening the instance of the device using its physical address no
    Disk_101 = CreateFileA(inter.c_str(),                              // Drive to open
                          GENERIC_READ | GENERIC_WRITE,          // Access to the drive
                          FILE_SHARE_READ | FILE_SHARE_WRITE,    // Share mode
                          NULL,                                  // Security
                          OPEN_EXISTING,                         // Disposition
                          0,                                     // no file attributes
                          NULL);

    if (Disk_101 == INVALID_HANDLE_VALUE) {
        cout << "File not created. Error Code: " << GetLastError() << endl;
        return(-1);
    }

        u_Good = DeviceIoControl(Disk_101, FSCTL_LOCK_VOLUME, 
                               NULL, 0, NULL, 0, &status, NULL);
     if (!u_Good) {
         printf("Failed to lock volume (err = %d).\n", GetLastError());
         return(-1);
     }
    
     u_Good = DeviceIoControl(Disk_101, FSCTL_DISMOUNT_VOLUME, 
                               NULL, 0, NULL, 0, &status, NULL);
     if (!u_Good) {
         printf("Failed to dismount volume (err = %d).\n", GetLastError());
         return(-1);
     }*/

/*
int main11()
{
    printf("hello world\n");
    DWORD nRead;
    char buf[512];
    char leh[512];
    bharlo(leh);

  

    HANDLE hDisk = CreateFileA(
        "\\\\.\\E:",                    //[in]           LPCSTR   lpFileName,
        GENERIC_WRITE | GENERIC_READ,   //[in]           DWORD    dwDesiredAccess,
        0,                              //[in]           DWORD    dwShareMode,
        NULL,                           //[in, opt]      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        OPEN_EXISTING,                  //[in]           DWORD                 dwCreationDisposition,
        0,                              //[in]           DWORD                 dwFlagsAndAttributes,
        NULL                            //[in, opt]      HANDLE                hTemplateFile
    );
    DWORD error_code = GetLastError();
    std::cerr << "Failed to read file on USB drive. Error code: " << error_code << std::endl;
    if (hDisk == INVALID_HANDLE_VALUE) {
        cout << "stuff not workin" << endl;
    }

    SetFilePointer(hDisk, 0x000, 0, FILE_BEGIN);
    error_code = GetLastError();
    std::cerr << "Failed to read file on USB drive. Error code: " << error_code << std::endl;


    DWORD num_bytes_written;
    if (!WriteFile(hDisk, leh, strlen(leh), &num_bytes_written, NULL))
    {
        std::cerr << "Error: failed to write data to disk device" << std::endl;
        CloseHandle(hDisk);
        return 1;
    }
    cout << strlen(leh);
    //WriteFile(hDisk, leh, 512,NULL,NULL);
    error_code = GetLastError();
    std::cerr << "Failed to read file on USB drive. Error code: " << error_code << std::endl;
    printf("hDisk %i\n", hDisk);

    printf("hDisk %i\n", hDisk);

    SetFilePointer(hDisk, 0x000, 0, FILE_BEGIN);
    error_code = GetLastError();
    std::cerr << "Failed to read file on USB drive. Error code: " << error_code << std::endl;

    ReadFile(hDisk, buf, strlen(buf), &num_bytes_written, NULL);
     error_code = GetLastError();
    std::cerr << "Failed to read file on USB drive. Error code: " << error_code << std::endl;
    for (int currentpos = 0; currentpos < 512; currentpos++) {
        std::cout << buf[currentpos];
    }
    CloseHandle(hDisk);


    return 0;
}*/