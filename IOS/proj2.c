//Filip Bednár
//xbedna63
//IOS proj2

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

  int isnum( char *str ) //či je string číslo
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

//PREMENNÉ
		int P; //počet procesov reprezentujúcich pasažierov 
		int C; //kapacita vozíku
		int PT; //maximálna doba(milisekundy) pre ktoré je generovaný nový proces pasažiera 
		int RT; //maximálna doba(milisekundy) pre prejazd traťou

		int *N; //poradie
		int *A; //poradové číslo akcie
		int *I;	//interný identifikátor procesu

		//premenné pre procesy
		int main_p; 
		int car_p;
		int pas_p;
		int id_p;

		//premenné (semafory)
		sem_t *sem_print;
		sem_t *sem_board;
		sem_t *sem_unboard;
		sem_t *sem_last_board;
		sem_t *sem_last_unboard;
		sem_t *sem_all_finished;
		sem_t *sem_main_finished;

//SPRÁVA ARGUMENTOV

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
								
											fprintf( stderr, "%s\n", "ERROR: invalid_p value of parameter PT or RT" );
											exit(1);
									}
							}
						else
							{
								if ( fclose(file) == EOF )   
                                                                	{
                                                                        	fprintf( stderr, "%s\n", "ERROR while closing file" );
                                                                        }       
                                                                
                                                                fprintf(stderr, "%s\n", "ERROR: invalid_p value of parameter P or C" );
                                                                                        exit(1);

							}
					}
				else
					{
                                     	  	if ( fclose(file) == EOF )   
                                               		{
                                                        	fprintf( stderr, "%s\n", "ERROR while closing file" );
                                                        }       
                                                             
                                                fprintf(stderr, "%s\n", "ERROR: invalid_p argument");
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
//PRÁCA S PROCESMI

	sem_print = mmap( NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
	sem_board = mmap( NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
	sem_unboard = mmap( NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );

	sem_last_board = mmap( NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
	sem_last_unboard = mmap( NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );

	sem_all_finished = mmap( NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
	sem_main_finished = mmap( NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );

	sem_init( sem_print, 1, 1 );
	sem_init( sem_board, 1, 0 );
	sem_init( sem_unboard, 1, 0 );

	sem_init( sem_last_board, 1, 0 );
	sem_init( sem_last_unboard, 1, 0 );

	sem_init( sem_all_finished, 1, 0 );
	sem_init( sem_main_finished, 1, 0 );		
			
	N = (int*)mmap( NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
	A = (int*)mmap( NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
	I = (int*)mmap( NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
	
	*N = 1;
	*A = 1;	
	*I = 0;
	if ( (main_p = fork()) < 0 )
		{
			unmap_var; //unmapovanie pamäte
			sem_rm; //odstránenie semaforov
			unmap_sem; //unmapovanie semaforov
		        if (fclose(file) == EOF) //zatvorenie súboru   
                		fprintf(stderr, "%s\n", "ERROR: while closing file"); 
                
			fprintf(stderr, "%s\n", "ERROR: forking main process");
			exit(2);
	}

	if ( main_p == 0 )	//Subprocess pre vytáranie pasažierov
		{
			for (int i = 0; i < P; i++)
				{
					if (PT != 0) 
						usleep(rand() % PT); //sleep pre pasažiera

					if ( (pas_p = fork()) < 0 )//pasažier
						{
							unmap_var; //unmapovanie pamäte
							sem_rm; //odstránenie semaforov
							unmap_sem; //unmapovanie semaforov
		        				if (fclose(file) == EOF) //zatvorenie súboru   
                						fprintf(stderr, "%s\n", "ERROR: while closing file"); 
                
							fprintf(stderr, "%s\n", "ERROR: forking main process");
							exit(2);
						}
			
					if ( pas_p == 0 )
						{
							*I = *I + 1;
							id_p = *I; //id pasažiera
							
							sem_wait(sem_print); //štart a čakanie na vozík
							fprintf(file, "%d %s %d %s\n", *A, ": P ", id_p, ": started");
							*A += 1;
							sem_post(sem_print);
							sem_wait(sem_board);		

							sem_wait(sem_print); //nastupovanie
							fprintf(file, "%d %s %d %s\n", *A, ": P ", id_p, ": board");
							*A += 1;

							if (*N == C) //výpis nastúpenia
								{
									fprintf(file, "%d %s %d %s\n", *A, ": P ", id_p, ": board last");
									*N = 1;
									*A += 1;
									sem_post(sem_print);
									sem_post(sem_last_board); //vozík je pripravený vyraziť
								} 
							else
								{
									fprintf(file, "%d %s %d %s %d\n", *A, ": P ", id_p, ": board order ", *N);
									*N += 1;
									*A += 1;
									sem_post(sem_print);
								}

							sem_wait(sem_unboard); //vystupovanie z vozíka
							sem_wait(sem_print);
							fprintf(file, "%d %s %d %s\n", *A, ": P ", id_p, ": unboard");
							*A += 1;
							if (*N == C)
								{
									fprintf(file, "%d %s %d %s\n", *A, ": P ", id_p, ": unboard last");
									*A += 1;
									*N = 1;
									sem_post(sem_print);
									sem_post(sem_last_unboard); // vystúpenie pasažierov z vozíka
								}
				 			else
								{
									fprintf(file, "%d %s %d %s %d\n", *A, ": P ", id_p, ": unboard order ", *N);
									*N += 1;
									*A += 1;
									sem_post(sem_print);
								}

							sem_wait(sem_all_finished); //všetcia čakajú, ukončenie
							sem_wait(sem_print);
							fprintf(file, "%d %s %d %s\n", *A, ": P ", id_p, ": finished");
							*A += 1;
				
							sem_post(sem_print);
							sem_post(sem_main_finished); //posledný proces

							exit(0);
						}
				}

		exit(0);

	}

	if ( (car_p = fork()) < 0 ) //vytvorenie vozíka
		{
			unmap_var; //unmapovanie pamäte
			sem_rm; //odstránenie semaforov
			unmap_sem; //unmapovanie semaforov
 			if (fclose(file) == EOF) //zatvorenie súboru   
                		fprintf(stderr, "%s\n", "ERROR: while closing file"); 
                
			fprintf(stderr, "%s\n", "ERROR: forking main process");
			exit(2);
		}

	if (car_p == 0) 
		{	
			sem_wait(sem_print); //inicializácia vozíka
			fprintf(file, "%d %s\n", *A, ": C  1 : started");
			*A += 1;
			sem_post(sem_print);
	
			for (int j = 0; j < P/C; j++) //vozenie pasažierov
				{
					sem_wait(sem_print);
					fprintf(file, "%d %s\n", *A, ": C  1 : load"); //nastupovanie
					*A += 1;
					sem_post(sem_print);
					for (int k = 0; k < C; k++)
						sem_post(sem_board);
					
					sem_wait(sem_last_board); //čakanie pre nastúpenie všetkých pasažierov
					sem_wait(sem_print);
					fprintf(file, "%d %s\n", *A, ": C  1 : run");
					*A += 1;
					sem_post(sem_print);
					
					if (RT != 0)
						usleep(rand() % RT); //jazda vozíkom
		
					sem_wait(sem_print); //vystupovanie
					fprintf(file, "%d %s\n", *A, ": C  1 : unload");
					*A += 1;
					sem_post(sem_print);
					for (int l = 0; l < C; l++) 
						sem_post(sem_unboard);
					sem_wait(sem_last_unboard); //čakanie na všetkých pasažierov
				}
	
			for (int m = 0; m < P; m++) //všetci dojazdili
					sem_post(sem_all_finished);
			
			sem_wait(sem_print);
			fprintf(file, "%d %s\n", *A, ": C  1 : finished");
			*A += 1;
			sem_post(sem_print);
			sem_post(sem_main_finished);

			exit(0);
		}

	for (int n = 0; n < P + 1; n++) //ukončenie hlavného procesu
		sem_wait(sem_main_finished);

	unmap_var; //unmapovanie pamäte
	sem_rm; //odstránenie semaforov
	unmap_sem; //unmapovanie semaforov
	if (fclose(file) == EOF) //zatvorenie súboru   
         	fprintf(stderr, "%s\n", "ERROR: while closing file"); 
                
	exit(0);
}
	
