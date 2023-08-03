#include <stdint.h>
#include<ctime>
#include <chrono>
using namespace std;

struct uint128_t {
	uint64_t Delim1;
	uint64_t Delim2;
};

struct MetaHeader {
	uint128_t Delimit;                  //16 till here
	uint64_t  Creation_time;            //24 till here | diff8
	uint64_t  Last_access_time;         //32 till here | diff8
	uint64_t  Available_space;          //40 till here | diff8
	uint64_t  CRC;                      //48 till here | diff8
	uint8_t   no_of_files;              //56 till here | diff8 
	uint8_t   Max_size;                 //56 till here | diff0 || padding of 6 bytes added 
	char	  left_over_space[456];		//512 till here

	MetaHeader();
}; 





