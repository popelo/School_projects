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
#include <deque>
#include <string>
#include <sstream> 
#include <cstdlib>
#include <fstream>

const unsigned long PRINT_LINES = 10;

using namespace std;

void tail(istream &stream, unsigned long print_lines)
	{
		deque<string> buffer;
		string line;
		for (unsigned long i = 0; getline(stream, line ); i++)
			{
				buffer.push_front(line);
				if (i >= print_lines)
					buffer.pop_back();
			}
		while (!buffer.empty())
			{
				cout << buffer.back() << endl;
				buffer.pop_back();
			}
	}

int main(int argc, char *argv[])
	{
		fstream file;
		istream  *stream = &cin ;
		unsigned long print_lines = PRINT_LINES;
		string param;
		if(argc == 1)
			{
				tail(*stream, print_lines);
				return 0;
			}
		file.close();
		return 0;
	}


