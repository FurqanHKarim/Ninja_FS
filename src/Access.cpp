#include "Access.h"



bool Access::OpenDevice(string dev_name) {
    dev_name.insert(0,"\\\\.\\");
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
    if (!DeviceIoControl(Disk_101,                     // handle to device
        IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS,          // dwIoControlCode
        NULL,                                          // lpInBuffer
        0,                                             // nInBufferSize
        &hello,                                        // output buffer
        sizeof(hello),                                 // size of output buffer
        &status,                                       // number of bytes returned
        NULL                                           // OVERLAPPED structure   
        ))
        cout << "Device Credentials not extracted: Error" << GetLastError() << endl;

    inter = "\\\\.\\PhysicalDrive";
    inter.append(to_string(hello.Extents[0].DiskNumber));


    /////////////////closing that instance of the data device
    if (!CloseHandle(Disk_101))
        cout << "Handle not closed: Error" << GetLastError() << endl;
    
    
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
        return(1);
    }

    /////////////////Locking the device from other processes
    if (!DeviceIoControl(Disk_101, 
        FSCTL_LOCK_VOLUME,
        NULL, 0, NULL, 0, &status, NULL))
        {
        printf("Failed to lock volume (err = %d).\n", GetLastError());
        return(1);
    }


    /////////////////Dismounting the drive 
    if (!DeviceIoControl(Disk_101,
        FSCTL_DISMOUNT_VOLUME,
        NULL, 0, NULL, 0, &status, NULL)) 
        {
        printf("Failed to dismount volume (err = %d).\n", GetLastError());
        return(1);
    }

    return 0;

}

bool Access:: Write_on_device(char* note,int byte_offset,size_t size){

    //////Setting the pointer to where to write the file
    error_code = SetFilePointer(Disk_101, (byte_offset), 0, FILE_BEGIN);
    if (error_code == INVALID_SET_FILE_POINTER)
    {
        std::cerr << "Error: failed to seek to the beginning of the disk device" << GetLastError() <<std::endl;
        CloseHandle(Disk_101);
        return 1;
    }

    int meh =sizeof(*note);
    meh =sizeof(note);

    ///////Actually writing the file
    if (!WriteFile(Disk_101, note, size, &status, NULL))
    {
        std::cerr << "Error: failed to write data to disk device" <<  GetLastError() << std::endl;
        CloseHandle(Disk_101);
        error_code = GetLastError();
        return 1;
    }
    std::cout << "Data was successfully written to disk device"<< std::endl;
    return 0;

}


bool Access:: Read_from_device(char* note,int byte_offset,size_t size){
    // Read the data back from the disk device
    //////Setting the pointer to where to start reading the file
    error_code = SetFilePointer(Disk_101, byte_offset, 0, FILE_BEGIN);
    if (error_code == INVALID_SET_FILE_POINTER)
    {
        std::cerr << "Error: failed to seek to the beginning of the disk device" << std::endl;
        CloseHandle(Disk_101);
        return 1;
    }


    if (!ReadFile(Disk_101, note, size, &status, NULL))
    {
        error_code = GetLastError();
        std::cerr << "Failed to read file on USB drive. Error code: " << error_code << std::endl;

        std::cerr << "Error: failed to read data from disk device" << std::endl;
        CloseHandle(Disk_101);
        return 1;
    }
    return 0;
}


bool Access:: Close_device(){
    // Close the disk device
    if(Disk_101 == INVALID_HANDLE_VALUE){
        cout<<"Disk is not Open:   "<<endl;
        return 1;
    }else{
        CloseHandle(Disk_101);
        return 0;
    }
}