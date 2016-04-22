// Filip Bednár
// xbedna63
// VUT FIT
// príklad (a2 
// 14.4.2016
//POZNÁMKY--------------------------------------------------------------------------//
// 	                                                                           //
//					                                          //
//POZNÁMKY-----------------------------------------------------------------------//

#include <iostream>
#include <queue>
#include <string>
#include <sstream> 
#include <istream>
#include <fstream>

#define PRINT_LINES  10

using namespace std;

bool isnum(const std::string &str)
	{
		return  str.find_first_not_of("0123456789") == std::string::npos;
	}

void tail(istream &stream, unsigned long print_lines)
	{
		queue<string> buffer;
		string line;
		for (unsigned long i = 0; getline(stream, line ); i++)
			{
				buffer.push(line);
				if (i >= print_lines)
					buffer.pop();
			}
		while (!buffer.empty())
			{
				cout << buffer.front() << endl;
				buffer.pop();
			}
	}

int main(int argc, char *argv[])
	{
		std::ios::sync_with_stdio(false);

		bool read_file = false;
		fstream file;
		istream  *stream = &cin ;
		unsigned long print_lines = PRINT_LINES;
		if(argc == 1)
			{
				tail(*stream, print_lines);
				return 0;
			}
		if(argc == 2)
			{
				if (!(argv[2] == "-"))
					{
						file.open(argv[2]);
		
						if(!file.open())
							{
								fprintf(stderr, "%s\n", "Invalid argument");
								return 1;
							}
						read_file = true;
					}
			}
		if(argc)
		file.close(); //niaky ten ifik
		return 0;
	}


