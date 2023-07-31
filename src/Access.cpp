#include "Access.h"




bool Access::OpenDevice(string dev_name) {

    //////////OPENING Device in first instance
    Disk_101 = CreateFileA(
        inter.c_str(),                        //[in]           LPCSTR   lpFileName,
        GENERIC_WRITE | GENERIC_READ,       //[in]           DWORD    dwDesiredAccess,
        FILE_SHARE_READ | FILE_SHARE_WRITE,   //[in]           DWORD    dwShareMode,
        NULL,                               //[in, opt]      LPSECURITY_ATTRIBUTES lpSecurityAttributes,
        OPEN_EXISTING,                      //[in]           DWORD                 dwCreationDisposition,
        0,                                  //[in]           DWORD                 dwFlagsAndAttributes,
        NULL                                //[in, opt]      HANDLE                hTemplateFile
    );

    if (Disk_101 == INVALID_HANDLE_VALUE) {
        cout << "File not created. Error Code: " << GetLastError() << endl;
        return(1);
    }

    ///Extracting Physical Device No////////
    u_Good = DeviceIoControl(
        Disk_101,                     // handle to device
        IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS, // dwIoControlCode
        NULL,                                 // lpInBuffer
        0,                                    // nInBufferSize
        &hello,                 // output buffer
        sizeof(hello),               // size of output buffer
        &status,            // number of bytes returned
        NULL           // OVERLAPPED structure
    );

    if (!u_Good)
        cout << "Device Credentials not extracted: Error" << GetLastError() << endl;
     
    /////////////////closing that instance of the data device
    if (!CloseHandle(Disk_101))
        cout << "Handle not closed: Error" << GetLastError() << endl;
    
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
    /////////////////Locking the device from other processes
    u_Good = DeviceIoControl(Disk_101, FSCTL_LOCK_VOLUME,
        NULL, 0, NULL, 0, &status, NULL);
    if (!u_Good) {
        printf("Failed to lock volume (err = %d).\n", GetLastError());
        return(1);
    }


    /////////////////Dismounting the drive 
    u_Good = DeviceIoControl(Disk_101, FSCTL_DISMOUNT_VOLUME,
        NULL, 0, NULL, 0, &status, NULL);
    if (!u_Good) {
        printf("Failed to dismount volume (err = %d).\n", GetLastError());
        return(1);
    }

    return 0;
 




}
