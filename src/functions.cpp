#include "functions.h"
#include<ctime>
#include <chrono>
#include<iostream>

using namespace std;


void print_time(uint64_t a)// take epoch time in time_t as argument and prints out the time and date
{
    time_t inter = *(time_t*)&a;
    inter = inter / 10000000;// necessary conversion for struct time to work
    struct tm* time_in_struct;
    time_in_struct = localtime(&inter);
    cout << "Time: " << time_in_struct->tm_hour << ":"
        << time_in_struct->tm_min << ":"
        << time_in_struct->tm_sec << endl;
    cout << "Date: "
        << time_in_struct->tm_mday << "/"
        << time_in_struct->tm_mon + 1 << "/"
        << time_in_struct->tm_year + 1900 << endl;
}

uint64_t get_time() {

	std::chrono::system_clock::time_point hello;
	hello = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(hello);
	return hello.time_since_epoch().count();
}

void print_everything(char* arr,int size){
	for (int  i = 0; i < sizeof(arr); i++)
	{
		cout<<arr[i];
	}
	cout<<endl;
}
