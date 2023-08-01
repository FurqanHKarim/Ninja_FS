#include "Data.h"
#include "functions.h"



MetaHeader::MetaHeader() {
	//Delimit = 0xDEADBEEFBEEFFEED;
	auto temp = std::chrono::system_clock::now();
	Creation_time = get_time();

}
