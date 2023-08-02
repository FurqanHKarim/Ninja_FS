#ifndef _FILEHEADER
#define _FILEHEADER



#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <chrono>

#include "Data.h";

using namespace std;
using namespace chrono;


struct FileHeader
{
	char File_name[16];
	uint64_t Delimit;
	uint64_t Create_time;
	uint64_t Last_modified;
	uint64_t Access_time;
	uint64_t File_size;
	uint64_t offset;
	uint8_t File_identity;
	uint8_t Read_permission;
	uint8_t Write_permission;
	char padding1[438];
};

struct RAW_USB
{
	static const uint32_t Total_size = 64;
	static const uint32_t Meta_size = 512;
	MetaHeader Fs;
	FileHeader Meta[Total_size];
	char padding2[512 * 15];
};

class Sysstem
{
	private:
		int File_index;
		uint64_t Disk_size;
		
	public:
		RAW_USB Ninja;
		void Update_Header();
		void File_meta(char* file);
		unsigned int Free_space_available();
		void File_check(char* filename);
		bool Validity(char* filename);
};

#endif