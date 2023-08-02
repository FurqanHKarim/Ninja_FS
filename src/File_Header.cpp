#include "File_Header.h";
#include "functions.h";

/*TIME FUNCTIONS HAVE TO USE print_time() FUNCTION TO DISPLAY THEM*/

bool Sysstem::Validity(char* filename)
{
	//Query the file in the directory
	uint16_t i = 0;
	while (i < RAW_USB::Total_size)
	{
		//Find file in the meta data for the file
		if (!(strcmp(filename, Ninja.Meta[i].File_name)))  //If file has been found 
		{
			cout << Ninja.Meta[i].File_name << " : File found in the File Metadata Header File" << endl;
			File_index = i;
			return true;
		}
		i++;
	}

	return false;
}

void Sysstem::Update_Header()
{
	Ninja.Meta[File_index].Last_modified = get_time();
	Ninja.Meta[File_index].Access_time = get_time();
}

void Sysstem::File_meta(char* file)
{
	unsigned int i = 0;
	while (i < RAW_USB::Total_size)
	{
		if (!(Ninja.Meta[i].File_identity))
		{
			strcpy(Ninja.Meta[i].File_name, file);
			Ninja.Meta[i].Delimit = 0xfeeddeadbeeffeed;
			Ninja.Meta[i].File_size = 0;
			Ninja.Meta[i].Create_time = get_time();
			Ninja.Meta[i].File_identity = 1;
			File_index = i;
			Update_Header();
			break;
		}
		i++;
	}
}

unsigned int Sysstem::Free_space_available()
{
	unsigned int i = 0;
	Disk_size = sizeof(Sysstem);
	while (i < RAW_USB::Total_size)
	{
		if ((Ninja.Meta[i].File_identity))
		{
			Disk_size += Ninja.Meta[i].File_size;
			i++;
		}
		else
		{
			break;
		}

	}
	return Disk_size;
}

void Sysstem::File_check(char* filename)
{
	bool status = Validity(filename);
	if (status)
	{
		Update_Header();
		cout << "File has successfully opened" << endl;
	}
	else
	{
		File_meta(filename);
	}

}

	//size_t i = get_time();
	//print_time(i);