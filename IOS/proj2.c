#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define unmap_var \
	do {\
		munmap(N, sizeof(int));\
		munmap(A, sizeof(int));\
		munmap(I, sizeof(int));\
	} while(0)

#define unmap_sem \
     			do {\
				sem_destroy(sem_print);\
				sem_destroy(sem_board);\
				sem_destroy(sem_unboard);\
				sem_destroy(sem_last_board);\
				sem_destroy(sem_last_unboard);\
				sem_destroy(sem_all_finished);\
				sem_destroy(sem_main_finished);\
			} while (0)

#define sem_rm \
			do{\
				sem_destroy( sem_print );\
				sem_destroy (sem_board) ;\
				sem_destroy( sem_unboard );\
				sem_destroy( sem_last_board );\
				sem_destroy( sem_last_unboard );\
				sem_destroy( sem_all_finished );\
				sem_destroy( sem_main_finished );\
			} while(0)

  int isnum( char *str )
	{
		int i = 0;
		while ( str[i] != '\0')	
				i++;

		for ( int j = 0; j<i; j++ ) 
			{
				if ( str[j] < 48 || str[j] > 57 )
					return 1;
			}
		
		return 0;
	}
  
  int main( int argc, char *argv[] )
	{		
		int P;
		int C;
		int PT;
		int RT;

		int *N;
		int *A;
		int *I;

		int main_p;
		int car_p;
		int pas_p;

		FILE *file = fopen( "proj2.out", "wb");
		
		if ( file == NULL )
			{
				fprintf( stderr, "%s\n", "ERROR while opening file\n");
				exit(2);
			}
		
		setbuf( stderr, NULL );
		setbuf( file, NULL );
		
		if ( argc == 5 )
			{
				if( !isnum( argv[1]) && !isnum(argv[2]) && !isnum(argv[3]) && !isnum( argv[4]) )
					{
						P = atoi( argv[1] );
						C = atoi( argv[2] );
						PT = atoi( argv[3] );
						RT = atoi( argv[4] );
			
						if ( P > 0 && C > 0 && ( P % C == 0) )
							{
								if ( 0 > RT || RT >= 5001 || 0 > PT || PT >= 5001 )
									{
											if ( fclose(file) == EOF )	
												{	
													fprintf( stderr, "%s\n", "ERROR while closing file" );	
												}
								
											fprintf( stderr, "%s\n", "ERROR: invalid value of parameter PT or RT" );
											exit(1);
									}
							}
						else
							{
								if ( fclose(file) == EOF )   
                                                                	{
                                                                        	fprintf( stderr, "%s\n", "ERROR while closing file" );
                                                                        }       
                                                                
                                                                fprintf(stderr, "%s\n", "ERROR: invalid value of parameter P or C" );
                                                                                        exit(1);

							}
					}
				else
					{
                                     	  	if ( fclose(file) == EOF )   
                                               		{
                                                        	fprintf( stderr, "%s\n", "ERROR while closing file" );
                                                        }       
                                                             
                                                fprintf(stderr, "%s\n", "ERROR: invalid argument");
                                                exit(1);
					}
						
			}
		else
			{
                	        if (fclose(file) == EOF)   
                        		{
                                        	fprintf(stderr, "%s\n", "ERROR while closing file");
                                        }       
                                                             
                                fprintf(stderr, "%s\n", "ERROR: wrong number of arguments");
                                exit(1);

			}
/********************************************PROGRAM****************************************************************/

	sem_t *sem_print;
	sem_t *sem_board;
	sem_t *sem_unboard;
	sem_t *sem_last_board;
	sem_t *sem_last_unboard;
	sem_t *sem_all_finished;
	sem_t *sem_main_finished;

	sem_print = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_board = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_unboard = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_last_board = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_last_unboard = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_all_finished = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_main_finished = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	sem_init(sem_print, 1, 1);
	sem_init(sem_board, 1, 0);
	sem_init(sem_unboard, 1, 0);
	sem_init(sem_last_board, 1, 0);
	sem_init(sem_last_unboard, 1, 0);
	sem_init(sem_all_finished, 1, 0);
	sem_init(sem_main_finished, 1, 0);		
			
	N = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	I = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	A = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	
	*A = 1;
	*N = 1;
	*I = 0;
	if ((main_p = fork()) < 0)
	{
		//Unmap pamate
		unmap_var;

		//Znicenie semaforov
		sem_rm;

		//Unmapnutie semaforov z pamate
		unmap_sem;

		//Zavretie vystupneho suboru
		        if (fclose(file) == EOF)    
                {
                        fprintf(stderr, "%s\n", "Error: Closing file"); 
                }


		fprintf(stderr, "%s\n", "Error: fork main process");
		exit(2);
	}

	if (main_p == 0)	//Subprocess pre generovanie pasazierov
	{
		for (int k = 0; k < P; k++)
		{	
			//Sleep pre pasaziera
			if (PT != 0)
				usleep(rand() % PT);

			//Vytvorenie pasaziera a osetrenie error-u
			if ((pas_p = fork()) < 0)
			{
				//Unmap pamate
				unmap_var;

				//Znicenie semaforov
				sem_rm;

				//Unmapnutie semaforov z pamate
				unmap_sem;

				//Zavretie vystupneho suboru
        		if (fclose(file) == EOF)    
                		{
                        		fprintf(stderr, "%s\n", "Error: Closing file"); 
                		}	


				fprintf(stderr, "%s\n", "Error: fork subprocess for passengers");
				exit(2);
			}
			
			//Ak je child == pasazier
			if (pas_p == 0)
			{
				//ID kazdeho pasaziera
				*I = *I + 1;
				int id = *I;

				//Start pasaziera a cakanie na vozik
				sem_wait(sem_print);
				fprintf(file, "%d %s %d %s\n", *A, ": P ", id, ": started");
				*A += 1;
				sem_post(sem_print);

				sem_wait(sem_board);		//post CAR

				//Zacatie nastupovania na vozik
				sem_wait(sem_print);
				fprintf(file, "%d %s %d %s\n", *A, ": P ", id, ": board");
				*A += 1;
				//sem_post(sem_print);

				//Vypis uspesneho nastupenia na vozik
				if (*N == C)
				{
					//sem_wait(sem_print);
					fprintf(file, "%d %s %d %s\n", *A, ": P ", id, ": board last");
					*A += 1;
					*N = 1;
					sem_post(sem_print);

					//Semafor pre vozik, ze je vozik plny a moze ist na cestu
					sem_post(sem_last_board);
				} else
				{
					//sem_wait(sem_print);
					fprintf(file, "%d %s %d %s %d\n", *A, ": P ", id, ": board order ", *N);
					*A += 1;
					*N += 1;
					sem_post(sem_print);
				}

				//Cakanie pasazierov na vystupovanie z vozika 
				//Caka kym vozik urobi jazdu
				sem_wait(sem_unboard);

				//Zaciatok vystupovanie z vozika
				sem_wait(sem_print);
				fprintf(file, "%d %s %d %s\n", *A, ": P ", id, ": unboard");
				*A += 1;
				//sem_post(sem_print);

				if (*N == C)
				{
					//sem_wait(sem_print);
					fprintf(file, "%d %s %d %s\n", *A, ": P ", id, ": unboard last");
					*A += 1;
					*N = 1;
					sem_post(sem_print);

					//Semafor pre vozik, vsetci pasazieri vystupili von
					sem_post(sem_last_unboard);
				} else
				{
					//sem_wait(sem_print);
					fprintf(file, "%d %s %d %s %d\n", *A, ": P ", id, ": unboard order ", *N);
					*A += 1;
					*N += 1;
					sem_post(sem_print);
				}

				//Kazdy pasazier caka kym sa vsetci "povozia" a mozu sa ukoncit
				sem_wait(sem_all_finished);

				sem_wait(sem_print);
				fprintf(file, "%d %s %d %s\n", *A, ": P ", id, ": finished");
				*A += 1;
				sem_post(sem_print);

				//Semafor pre hlavny proces, aby sa ukoncil ako posledny
				sem_post(sem_main_finished);

				exit(0);
			}
		}

		exit(0);
	}

	//Fork main procesu pre vytvorenie vozika
	if ((car_p = fork()) < 0)
	{
		//Unmap pamate
		unmap_var;

		//Znicenie semaforov
		sem_rm;

		//Unmapnutie semaforov z pamate
		unmap_sem;

		//Zavretie vystupneho suboru
        if (fclose(file) == EOF)    
                {
                        fprintf(stderr, "%s\n", "Error: Closing file"); 
                }


		fprintf(stderr, "%s\n", "Error: fork main process");
		exit(2);
	}

	//Subprocess pre vozik
	if (car_p == 0)
	{	
		//Inicializacia vozika
		sem_wait(sem_print);
		fprintf(file, "%d %s\n", *A, ": C  1 : started");
		*A += 1;
		sem_post(sem_print);

		//Cyklus pre "vozenie" pasazierov po trati
		for (int k = 0; k < P/C; k++)
		{	
			//Zaciatok nastupovanie pasazierov
			sem_wait(sem_print);
			fprintf(file, "%d %s\n", *A, ": C  1 : load");
			*A += 1;
			sem_post(sem_print);

			//Povolenie pasazierom nastupovat
			for (int j = 0; j < C; j++)
				sem_post(sem_board);

			//Vozik caka, kym sa vsetci nastupia
			sem_wait(sem_last_board);

			//Vozik sa pusta na jazdu
			sem_wait(sem_print);
			fprintf(file, "%d %s\n", *A, ": C  1 : run");
			*A += 1;
			sem_post(sem_print);
			
			//Sleep -> jazda vozikom
			if (RT != 0)
				usleep(rand() % RT);

			//Vozik dojazdil, zacina vystupovanie posazierov
			sem_wait(sem_print);
			fprintf(file, "%d %s\n", *A, ": C  1 : unload");
			*A += 1;
			sem_post(sem_print);

			//Vozik povoluje pasazierom vystupovat
			for (int j = 0; j < C; j++)
				sem_post(sem_unboard);

			//Vozik caka kym vystupia vsetci pasazieri
			sem_wait(sem_last_unboard);
		}

		//Vsetci pasazieri sa povozili, ukonceniev vsetkych procesov na koniec (okrem hlavne procesu)
		for (int j = 0; j < P; j++)
		{
			sem_post(sem_all_finished);
		}

		sem_wait(sem_print);
		fprintf(file, "%d %s\n", *A, ": C  1 : finished");
		*A += 1;
		sem_post(sem_print);
		
		//Semafor pre hlavny proces, aby sa ukoncil ako posledny
		sem_post(sem_main_finished);

		exit(0);
	}

	//Hlavny proces caka na ukoncenie vsetkych pasazierov + vozika
	for (int k = 0; k < P + 1; k++)
		sem_wait(sem_main_finished);

	//Ukoncenie hlavneho procesu + cistenie pamati
	//Unmap pamate
	unmap_var;

	//Znicenie semaforov
	sem_rm;

	//Unmapnutie semaforov z pamate
	unmap_sem;

	//Zavretie vystupneho suboru
	if (fclose(file) == EOF)	
		{	
			fprintf(stderr, "%s\n", "Error: Closing file");	
		}

	//Koniec procesu
	exit(0);
}
	
