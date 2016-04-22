// Filip Bednár
// xbedna63
// VUT FIT
// príklad (a2 
// 14.4.2016

#include <iostream>
#include <queue>
#include <string>
#include <sstream> 
#include <istream>
#include <fstream>

#define PRINT_LINES  10

  using namespace std;

  bool isnum( const std::string &str )
	{
		return  str.find_first_not_of( "0123456789" ) == std::string::npos;
	}

  void tail( istream &stream, unsigned long print_lines )
	{
		queue<string> buffer;
		string line;
		for ( unsigned long i = 0; getline( stream, line ); i++ )
			{
				buffer.push( line );
				if ( i >= print_lines )
					buffer.pop();
			}
		while ( !buffer.empty() )
			{
				cout << buffer.front() << endl;
				buffer.pop();
			}
	}

  int main( int argc, char *argv[] )
	{
		std::ios::sync_with_stdio(false);
		
		bool read_file = false;
		fstream file;
		istream  *stream = &cin ;
		unsigned long print_lines = PRINT_LINES;
		stringstream st;
		
		if ( argc > 4 )
			{
				fprintf( stderr, "%s\n", "Error: Too many arguments" );
				return 1;
			}

		if ( argc == 1 )
			{
				tail( *stream, print_lines );
				return 0;
			}
		
		if ( argc == 2 )
			{
				st.str( argv[1] );
				if ( st.str() != "-" )
					{
						file.open( argv[1] );
						if ( !file.is_open() )
							{
								fprintf( stderr, "%s\n", "Invalid argument" );
								return 1;
							}
						
						read_file = true;
					}
				
			}
		if ( argc == 3 || argc == 4 )
			{
				st.str( argv[1] );
				if ( st.str() == "-n" )
					{
						if ( isnum( argv[2] ) )
							{
								st.str( argv[2] );
								st >> print_lines;
								if ( argc == 4 )
									{
										file.open( argv[3] );
										if ( !file.is_open() )
											{
												fprintf( stderr, "%s\n", "ERROR OPENING FILE" );
												return 1;	
											}
										else
											{
												read_file = true;
											}
									}
							}
						else
							{
			                               	      fprintf( stderr, "%s\n", "Invalid argument" );
                                                              return 1;
							}
					}			
				else
                        		{
	                                         fprintf( stderr, "%s\n", "Invalid argument" );
                                                 return 1;
                         		}

			}
				if ( read_file == true )
					stream = &file;
				
				tail( *stream, print_lines );
				if ( read_file == true )
					file.close();
			 	
				return 0;
	}


