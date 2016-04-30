#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <semaphore.h>


#include <unistd.h>

#include <sys/wait.h>
#include <sys/mman.h>


//ošetriť pretečenie

#define unmap_var \
	do {\
		munmap(N, sizeof(int)); \
		munmap(A, sizeof(int));  \
		munmap(I, sizeof(int)); \
	} while(0);

#define unmap_sem \
     			do { \
				sem_destroy(sem_printer);		\
				sem_destroy(sem_boarding);		\
				sem_destroy(sem_unboarding);	\
				sem_destroy(sem_lastboarded);	\
				sem_destroy(sem_lastunboarded);	\
				sem_destroy(sem_allfinished);	\
				sem_destroy(sem_mainfinished);	\
			} while (0)


#define sem_rm \
			do{ \
				sem_destroy(sem_printer); \
				sem_destroy(sem_boarding); \
				sem_destroy(sem_unboarding); \
				sem_destroy(sem_lastboarded);\
				sem_destroy(sem_lastunboarded);\
				sem_destroy(sem_allfinished);	\
				sem_destroy(sem_mainfinished);	\
			} while(0)

  int isnum( char *str )
	{
		int i = 0;
		while ( str[i] != '\0')	
				i++;

		for ( int k = 0; k<i; k++ ) 
			{
				if ( str[k] < 48 || str[k] > 57 )
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



		FILE *file = fopen("proj2.out", "wb");
		if (file == NULL)
			{
				fprintf(stderr, "%s\n", "ERROR while opening file\n");
				exit(2);
			}
		
		setbuf(stderr, NULL);
		setbuf(file, NULL);
		
		if (argc == 5)
			{
				if(!isnum(argv[1]) && !isnum(argv[2]) && !isnum(argv[3]) && !isnum(argv[4]))
					{
						P = atoi(argv[1]);
						C = atoi(argv[2]);
						PT = atoi(argv[3]);
						RT = atoi(argv[4]);
			
						if ( C > 0 && P > 0 && ( P % C == 0) )
							{
								if ( 0 > PT || PT >= 5001 || 0 > RT || RT >= 5001)
									{
											if (fclose(file) == EOF)	
												{	
													fprintf(stderr, "%s\n", "ERROR while closing file");	
												}
								
											fprintf(stderr, "%s\n", "ERROR: invalid value of parameter PT or RT");
											exit(1);
									}
							}
						else
							{
								if (fclose(file) == EOF)   
                                                                	{
                                                                        	fprintf(stderr, "%s\n", "ERROR while closing file");
                                                                        }       
                                                                
                                                                fprintf(stderr, "%s\n", "ERROR: invalid value of parameter P or C");
                                                                                        exit(1);

							}
					}
				else
					{
                                     	  	if (fclose(file) == EOF)   
                                               		{
                                                        	fprintf(stderr, "%s\n", "ERROR while closing file");
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

	sem_t *sem_printer;
	sem_t *sem_boarding;
	sem_t *sem_unboarding;
	sem_t *sem_lastboarded;
	sem_t *sem_lastunboarded;
	sem_t *sem_allfinished;
	sem_t *sem_mainfinished;

	sem_printer = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_boarding = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_unboarding = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_lastboarded = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_lastunboarded = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_allfinished = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem_mainfinished = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	sem_init(sem_printer, 1, 1);
	sem_init(sem_boarding, 1, 0);
	sem_init(sem_unboarding, 1, 0);
	sem_init(sem_lastboarded, 1, 0);
	sem_init(sem_lastunboarded, 1, 0);
	sem_init(sem_allfinished, 1, 0);
	sem_init(sem_mainfinished, 1, 0);		
			
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
				sem_wait(sem_printer);
				fprintf(file, "%d %s %d %s\n", *A, ": P ", id, ": started");
				*A += 1;
				sem_post(sem_printer);

				sem_wait(sem_boarding);		//post CAR

				//Zacatie nastupovania na vozik
				sem_wait(sem_printer);
				fprintf(file, "%d %s %d %s\n", *A, ": P ", id, ": board");
				*A += 1;
				//sem_post(sem_printer);

				//Vypis uspesneho nastupenia na vozik
				if (*N == C)
				{
					//sem_wait(sem_printer);
					fprintf(file, "%d %s %d %s\n", *A, ": P ", id, ": board last");
					*A += 1;
					*N = 1;
					sem_post(sem_printer);

					//Semafor pre vozik, ze je vozik plny a moze ist na cestu
					sem_post(sem_lastboarded);
				} else
				{
					//sem_wait(sem_printer);
					fprintf(file, "%d %s %d %s %d\n", *A, ": P ", id, ": board order ", *N);
					*A += 1;
					*N += 1;
					sem_post(sem_printer);
				}

				//Cakanie pasazierov na vystupovanie z vozika 
				//Caka kym vozik urobi jazdu
				sem_wait(sem_unboarding);

				//Zaciatok vystupovanie z vozika
				sem_wait(sem_printer);
				fprintf(file, "%d %s %d %s\n", *A, ": P ", id, ": unboard");
				*A += 1;
				//sem_post(sem_printer);

				if (*N == C)
				{
					//sem_wait(sem_printer);
					fprintf(file, "%d %s %d %s\n", *A, ": P ", id, ": unboard last");
					*A += 1;
					*N = 1;
					sem_post(sem_printer);

					//Semafor pre vozik, vsetci pasazieri vystupili von
					sem_post(sem_lastunboarded);
				} else
				{
					//sem_wait(sem_printer);
					fprintf(file, "%d %s %d %s %d\n", *A, ": P ", id, ": unboard order ", *N);
					*A += 1;
					*N += 1;
					sem_post(sem_printer);
				}

				//Kazdy pasazier caka kym sa vsetci "povozia" a mozu sa ukoncit
				sem_wait(sem_allfinished);

				sem_wait(sem_printer);
				fprintf(file, "%d %s %d %s\n", *A, ": P ", id, ": finished");
				*A += 1;
				sem_post(sem_printer);

				//Semafor pre hlavny proces, aby sa ukoncil ako posledny
				sem_post(sem_mainfinished);

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
		sem_wait(sem_printer);
		fprintf(file, "%d %s\n", *A, ": C  1 : started");
		*A += 1;
		sem_post(sem_printer);

		//Cyklus pre "vozenie" pasazierov po trati
		for (int k = 0; k < P/C; k++)
		{	
			//Zaciatok nastupovanie pasazierov
			sem_wait(sem_printer);
			fprintf(file, "%d %s\n", *A, ": C  1 : load");
			*A += 1;
			sem_post(sem_printer);

			//Povolenie pasazierom nastupovat
			for (int j = 0; j < C; j++)
				sem_post(sem_boarding);

			//Vozik caka, kym sa vsetci nastupia
			sem_wait(sem_lastboarded);

			//Vozik sa pusta na jazdu
			sem_wait(sem_printer);
			fprintf(file, "%d %s\n", *A, ": C  1 : run");
			*A += 1;
			sem_post(sem_printer);
			
			//Sleep -> jazda vozikom
			if (RT != 0)
				usleep(rand() % RT);

			//Vozik dojazdil, zacina vystupovanie posazierov
			sem_wait(sem_printer);
			fprintf(file, "%d %s\n", *A, ": C  1 : unload");
			*A += 1;
			sem_post(sem_printer);

			//Vozik povoluje pasazierom vystupovat
			for (int j = 0; j < C; j++)
				sem_post(sem_unboarding);

			//Vozik caka kym vystupia vsetci pasazieri
			sem_wait(sem_lastunboarded);
		}

		//Vsetci pasazieri sa povozili, ukonceniev vsetkych procesov na koniec (okrem hlavne procesu)
		for (int j = 0; j < P; j++)
		{
			sem_post(sem_allfinished);
		}

		sem_wait(sem_printer);
		fprintf(file, "%d %s\n", *A, ": C  1 : finished");
		*A += 1;
		sem_post(sem_printer);
		
		//Semafor pre hlavny proces, aby sa ukoncil ako posledny
		sem_post(sem_mainfinished);

		exit(0);
	}

	//Hlavny proces caka na ukoncenie vsetkych pasazierov + vozika
	for (int k = 0; k < P + 1; k++)
		sem_wait(sem_mainfinished);

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
	
