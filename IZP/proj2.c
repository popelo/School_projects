/************************************************************/
/************************Filip Bednár************************/
/**************************xbedna63**************************/
/**************************projekt2**************************/
/************************************************************/

/* Program starts --log X(number) n(number of iterations) or --iter MIN(smaller number from interval) MAX(larger number from interval) EPS(difference)*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define maxstr 300


//length of string function
int length_function(char word[maxstr])
  {
        int lngth=0;
        
	for(int i=0;word[i] != '\0'; i++)
                {
        lngth++;
                }
	return(lngth);
  }

//string or number function
int soi(char word[maxstr])
  {
	int flag=0;
	int wlength=length_function(word);
        
	for(int i=0; i < wlength; i++)
                {
                	int ch=word[i];
                	if(ch < '0' || ch > '9')
                        	{
                                	if(ch != '.' && ch != '-')
                                		flag=1;
                        	}
                }
        return(flag);
  }

//input control function
int control(char x[maxstr])
  {
	int flag=0;

	if(strcmp(x,"INFINITY")!=0)
        	{
                	if(strcmp(x,"-INFINITY")!=0)
                        	{
                                	if(strcmp(x,"NAN")!=0)
                                        	{
                                                	flag=soi(x);
						}
                        	}
        	}
	return(flag);
  }

//function to make absolut value from number
double absv(double x)
  	{
		if(x<0)
			x*=-1;
		return(x);
	}

//function to calculate log with taylor polynomial
double taylor_log(double x, unsigned int n)
  	{
 		double result=0;
		double last;
		
		if(x == INFINITY)
			return(INFINITY);
		if(x == -INFINITY)
			return(NAN);
		if(x < 0)
			return(NAN);
			
		if(x>1)
        		{
                		for(unsigned int i=1; i<=n;i++)
                        		{
                                		if(i == 1)
						last=(((x-1)/x)/i);
						else
						last=(last*(i-1)*((x-1)/x))/i;
						result+=last;				
		                        }
        			return(result);
        		}
		if(x>0 && x<=1)
       			{
                		x=1-x;
				for(unsigned int i=1; i<=n; i++)
                        		{
                                		if(i==1)
							last=(x/i);							
						else
							last=((last*x*(i-1))/i);     
							result-=last;	
					}
					
                		return(result);
       			}
		return(NAN);
  }

//function to calculate log with continued fraction
double cfrac_log(double x, unsigned int n)
 	{
		double suma=0.0;
		double z=(x-1)/(x+1);
        	double a0=2*z; 
		unsigned int i=n;
		
		if(x == INFINITY)
                        return(INFINITY);
                if(x == -INFINITY)
                        return(NAN);
                if(x < 0) 
                        return(NAN);
		if(x == NAN)
			return(NAN);        	
		
		for(;n>=1;n--)
			{	
				if(n==i)
					{
						suma=((n*2-1)-(z*z*n*n)/((n+1)*((((n+1)*2)-1)-(n+1)*z*z)));
					}
				else
					{
						suma=((n*2-1)-((z*z*n*n))/suma);
					}	
  			}
		return(a0/suma);
	}
//function to calculate number of iteration for taylor polynomial
unsigned int taylor_iter(double MIN,double MAX,double EPS)
  	{
		double realvalue_min=log(MIN);//value of log(MIN) from math.h
        	double realvalue_max=log(MAX);//value of log(MAX) from math.h
		double diff,result;
		unsigned int min_iter,max_iter;

		//to calculate from min 
		diff=1+EPS; //for first iteration 
        	for(unsigned int i = 1; diff>EPS;i++)
           		{
                		result=taylor_log(MIN,i);
                       		diff=absv(realvalue_min-result);
                   		min_iter=i;
				if(i== UINT_MAX)
					{
						printf("Too many iterations\n");
						return(0);                             
					}                        
                	}
		//to calculate from max	
      		diff=1+EPS; //for first iteration
        	for(unsigned int i = 1; diff>EPS;i++)
         	 	{
                		result=taylor_log(MAX,i);
                        	diff=absv(realvalue_max-result);
                        	max_iter=i;
				if(i== UINT_MAX)
                                        {
                                                printf("Too many iterations\n");
                                                return(0);
                                        }                     
                	}
		//comparation of iteration from min and max
		if(max_iter>min_iter)
			return(max_iter);
		else
			return(min_iter);
  	}

//function to calculate number of iteration for continued fraction
unsigned int cf_iter(double MIN,double MAX,double EPS)
  	{
        	double realvalue_min=log(MIN); //value of log(MIN) from math.h
        	double realvalue_max=log(MAX); //value of log(MAX) from math.h
        	double diff,result;
        	unsigned int min_iter,max_iter;

        	diff=1+EPS; //for first iteration, condition must be true
        	for(unsigned int i = 1; diff>EPS;i++)
                	{
                        	result=cfrac_log(MIN,i);
                        	diff=absv(result-realvalue_min);
                        	min_iter=i;
		                if(i== UINT_MAX)
                                        {
                                                printf("Too many iterations\n");
                                                return(0);
                                        }                     
                	}
		diff=1+EPS;//for first iteration, condition must be true
        	for(unsigned int i = 1; diff>EPS;i++)
                	{
                        	result=cfrac_log(MAX,i);
                        	diff=absv(result-realvalue_max);
                 	       	max_iter=i;
                 		if(i== UINT_MAX)
                                        {
                                                printf("Too many iterations\n");
                                                return(0);
                                        }                     
			}
		//comparation of iterations from MIN and MAX
        	if(max_iter>min_iter)
                	return(max_iter);
        	else
                	return(min_iter);
  	}

int main(int argc, char *argv[])
  	{
		int flag;//for switch 0 == --log &  == --iter
		long int test;//variable to test input (number of iterations from --log)
		double x,MAX,MIN,EPS;//input values 
		double taylor_result,cf_result;//result values --log
		unsigned int n;//input value for number of iteration
		unsigned int it_cf_result,it_taylor_result;//result values --iter
		char *ptr;//pointer for strtod functio	
		//input verification if --log, if true flag=0 ;

		int bool=0;
		if((strcmp(argv[1], "--log") == 0))
			{
				if(argc == 4) //validation number of arguments
					{
     					  	flag=0;
                                        	bool=control(argv[2]);
						if(bool != 0)
						{
							printf("Wrong input\n");
							return(1);
						}
						x=strtod(argv[2], &ptr); //string to double                   				
						sscanf(argv[3], "%ld", &test); //test value from string
						bool=control(argv[3]);
						if(bool != 0 )
							{
								printf("Wrong input\n");
								return(1);
						}	
						if(test>UINT_MAX) //if number isn't bigger than unsigned int
							{
								printf("Wrong input\n");
								return(1);
							}
						if(test<=0)
							{
								printf("Wrong input\n");
									return(1);
							}
						sscanf(argv[3], "%u", &n);//string to number
					}
				else	
					{
						printf("Invalid arguments\n");
						return 1;
					}	 
			}
		//input verification if --iter, if true flag=1
		if((strcmp(argv[1], "--iter") == 0))	
			{         
				if(argc == 5 )//validation number of arguments
					{
						flag=1;	
						//converting from string to double
        					MIN=strtod(argv[2], &ptr);
						 bool=control(argv[2]);
                                                if(bool != 0)
                                                {
                                                        printf("Wrong input\n");
                                                        return(1);
                                                }

        					MAX=strtod(argv[3], &ptr);
						 bool=control(argv[3]);
                                                if(bool != 0)
                                                {
                                                        printf("Wrong input\n");
                                                        return(1);
                                                }

        					EPS=strtod(argv[4], &ptr);
						if(EPS<=0)
							{
							printf("Wrong input\n");
							return(1);
							}
					}
			}
		if(flag != 1 && flag != 0)
			{	
				printf("Invalid arguments\n");
				return(1);
			}
			
        
		//Output
		switch(flag) 	{
					case 0: //--log
						taylor_result=taylor_log(x,n);
						cf_result=cfrac_log(x,n);
						printf("log(%.12g) = %.12g\n", x, log(x));				
	                      			printf("cf_log(%.12g) = %.12g\n", x, cf_result);
						printf("taylor_log(%.12g) = %.12g\n", x, taylor_result);
						break;
				
					case 1: //--iter
						if(EPS<1e-12)
						{
							printf("Wrong input\n");
							return(1);
						}
						it_taylor_result=taylor_iter(MIN,MAX,EPS);
						if(it_taylor_result == 0)
							return(1);	
						it_cf_result=cf_iter(MIN,MAX,EPS);
						if(it_cf_result== 0)
							return(1);
						printf("log(%.12g) = %.12g\n", MIN, log(MIN));
                                		printf("log(%.12g) = %.12g\n", MAX, log(MAX));
						printf("continued fraction iterations = %u\n", it_cf_result);
						printf("cf_log(%s) = %.12g\n", argv[2], cfrac_log(MIN,it_cf_result));
						printf("cf_log(%s) = %.12g\n", argv[3], cfrac_log(MAX,it_cf_result));
						printf("taylor polynomial iteration = %u\n", it_taylor_result);
						printf("taylor_log(%s) = %.12g\n", argv[2], taylor_log(MIN,it_taylor_result));
                                		printf("taylor_log(%s) = %.12g\n", argv[3], taylor_log(MAX,it_taylor_result));
						break;
		    		}	


		return 0;
  	}

