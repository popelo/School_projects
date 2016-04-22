/* Project 1(TEXT READING) - Filip Bednár - 1BIA - sk.10  */


/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define maxstr 100 /*max amount of char*/

/*Function to calculate the number of symbols in the word (also with '\0')*/
int length_function(char word[maxstr]) 
  {
	int lngth=0;
	for(int i=0;word[i] != '\0'; i++)
		{
        lngth++;
		}

	return(lngth);
  }

/*Function to validate the input - if the symbols are printable*/
int input_control(char word[maxstr])
  {
  	int flag = 0;
        int length=length_function(word);
        for(int i=0; (length)>i; i++)
                {
                        char c=word[i];
                        int ch=c;
                        if(ch< ' ')
                                flag=1;
                }

  	return(flag);
  }

/*Function to differ if word is text or number*/
int soi(char word[maxstr])
{
int flag=0;
int wlength=length_function(word);
        for(int i=0; i < wlength; i++)
                {
                int ch=word[i];
                if(ch < '0' || ch > '9')
                        {
                                flag=1;
                        }
                }
        return(flag);
	
}
/*function to find out if word is <= int max*/
void imax(char word[maxstr])
  {
                                                if(word[0] > '2')
                                                                {
                                                                printf("number: %s\n", word);
                                                                }
                                                 if(word[0] >= '2' && word[1] > '1')
                                                                {
                                                                printf("number: %s\n", word);
                                                                }
                                                if(word[0] >= '2' && word[1] >= '1' && word[2] > '4')
                                                                {
                                                                printf("number: %s\n",word);
                                                                }
                                                if(word[0] >= '2' && word[1] >= '1' && word[2] >= '4' && word[3] > '7')
                                                                {
                                                                printf("number: %s\n",word);
                                                                }
                                                if(word[0] >= '2' && word[1] >= '1' && word[2] >= '4' && word[3] >= '7' && word[4] > '4')
                                                                {
                                                                printf("number: %s\n",word);
                                                                }
                                                if(word[0] > '2' && word[1] >= '1' && word[2] >= '4' && word[3] >= '7' && word[4] >= '4' && word[5] > '8')
                                                                {
                                                                printf("number: %s\n",word);
                                                                }
                                                if(word[0] >= '2' && word[1] >= '1' && word[2] >= '4' && word[3] >= '7' && word[4] >= '4' && word[5] >= '8' && word[6] > '3')
                                                                {
                                                                printf("number: %s\n",word);
                                                                }
                                                if(word[0] >= '2' && word[1] >= '1' && word[2] >= '4' && word[3] >= '7' && word[4] >= '4' && word[5] >= '8' && word[6] >= '3' && word[7] > '6')
                                                                {
                                                                printf("number: %s\n",word);
                                                                }
                                                if(word[0] >= '2' && word[1] >= '1' && word[2] >= '4' && word[3] >= '7' && word[4] >= '4' && word[5] >= '8' && word[6] >= '3' && word[7] >= '6' && word[8] > '4')
                                                                {
                                                                printf("number: %s\n",word);
                                                                }
                                                if(word[0] >= '2' && word[1] >= '1' && word[2] >= '4' && word[3] >= '7' && word[4] >= '4' && word[5] >= '8' && word[6] >= '3' && word[7] >= '6' && word[8] >= '4' && word[9] > '7')
                                                                {
                                                                printf("number: %s\n",word);
                                                                }
  }

/*Function to transform text to number(long int)*/
int transform(char word[maxstr]) 
  {
	char *ptr;
	long number;
	number=strtol(word, &ptr, 0);
	return(number);
  }
/*Function to validate if the word is date*/
int date_control(char word[maxstr])
  {
 	char word2[maxstr];
	int flag=3;
 	if(word[0] != '-' && word[1] != '-' && word[2] != '-' && word[3] != '-' && word[5] != '-' &&  word[6] != '-' &&  word[8] != '-' &&  word[9] != '-') /*45 in ASCII = "-"*/
        	{
        		int length=length_function(word);
        		for(int i=0; i<= length; i++ )
                		{
                        		word2[i]=word[i];
                		}
        		word2[4]='0';
        		word2[7]='0';
        		int boolen=soi(word2);
        		if(boolen==0)
                	flag=2;
        	}
        else
                flag=1;
	
	return(flag); 
  }

/*Struct for mktime to find out which day of week is the date*/
  struct tm time_str;
  char daybuf[20];

/*Function to find out which day of week is the date*/
void date(char word[maxstr])
  {
  	char ayear[3]; /*Array of symbols of the year*/
  	char aday[2]; /*Array of symbols of the day*/
  	char amonth[2]; /*Array of symbols of the month*/
  	long year,month,day; 

        for(int i=0; i<2; i++)
                {
                        amonth[i]=word[i+5];
                        aday[i]=word[i+8];
                }
        for(int i=0; i<4;i++)
                {
                        ayear[i]=word[i];
                }
	
	/*text to int for calculation*/
	year=transform(ayear);
        month=transform(amonth);
        day=transform(aday);
	
	/*Permission against invalid mktime values*/
        if(day <=31 && month <=12 && year>1900)
                {
			/*mktime structure*/
                        time_str.tm_year = year - 1900;
                        time_str.tm_mon = month-1;
                        time_str.tm_mday = day;
                        time_str.tm_hour = 0;
                        time_str.tm_min = 0;
                        time_str.tm_sec = 1;
                        time_str.tm_isdst = -1;
			
                        if (mktime(&time_str) == -1)
                                printf("word: %s\n",word);
                        else
                                {
                                        (void)strftime(daybuf, sizeof(daybuf), "%a", &time_str);
                                        printf("date: %s %s\n", daybuf, word);
                                }
                }
        else
        printf("word: %s\n", word);

  }  

/*Function for prime check*/
int prime_detect(long n) 
  {
        int flag;
	if(n>1)
		{
			if(n==2)
				flag=0;
			else	       
	      			for(int i=2; i<=n-1;i++)
                			{
                        		if(n%i==0)
                                		{
                                			flag=1;
                                			break;
                                		}
					else
							flag=0;
                		}
		}
	else
			flag=1;
	return(flag);  /*1 means false ; 0 means true*/
  }

/*Function to check if word is palindrome*/
int palindrom_check(char word[maxstr])
  {
        
        int type;
	int flag=0;
        
        int word_length=length_function(word)-1;
        for( int i=0;i<(word_length);i++)
                {
                        if(word[i] != word[word_length])
                                {
                                        flag=1;
                                        break;
			        }
			word_length--;
		}
	if(flag == 1 )
		type=0;

	if(flag != 1)
		type=1;

	return(type); 
  }


/********************************************************* MAIN FUNCTION ****************************************************************************************/
int main(int argc, char *argv[])
  {
	/*Program doesn't support arguments*/
	(void) argv;
		if(argc != 1)
			{
		 		printf("Error:The word is too long(max 100 symbols)\n Autor:Filip Bednár (xbedna63)\n Program for type detection(date,int,text)\n");
		 		return 0;
			}



	/*variables*/
	char word[maxstr]; /*Scanned word*/
	char word2[maxstr];
	int flag; /*Type of word*/
	int palindrom; /*palindrom flag*/
	long number; /*for transformation*/
	int length; 
	int zero=0; /*to count how many '0' are before the number*/
	/*Reading from stdi*/
	while(scanf("%s", word) != EOF)
 		{
    			/*Validation of length of the word*/
			length=length_function(word);
    			if(length>100)
				{
					printf("Error: Out of range (Input must be max 100 symbols)\n");
					return 0;	
				}
	/*Control of valid symbols*/
	int hflag=input_control(word);
    	if(hflag == 1)
		{    
	    		printf("Error: Unprintable symbol");
    		}
    	else
		{
   			if(word[4] == '-' && word[7] ==  '-' && word[10] == '\0')	/*One of the permissions to check if word is date; ASCII 45 = '-'*/
     				{
					flag=date_control(word);	
     				}
    			else	
    					flag=soi(word); /*If word isn't date the function will find out if it is text or number*/
		}
    
   	switch(flag)
   		{
			case 0:  /*word is number*/
				
			       	/*to control the numbers*/
				
				/*delete the zeroes before number*/ 
        			length=length_function(word);
				if(word[0] == '0')
                                 	{
                                		for(int i = 0; i<length;i++)
                                        		{
                                                		if(word[i] == '0')
                                                        		zero++;
                                        		}
                                if(zero != length)
                                	{
                               			for(int i = 0; i <= length;i++)
                                        		{
                                                		word2[i]=word[i+zero];
								word[i]=word2[i];
								
                                        		}
                                
                                	}	
                                }
				/*if the number <= int max*/
                                length=length_function(word);
                                if(length >10)
                                        {
                                                printf("number: %s\n", word);
                                                break;
                                        }
                                if(length == 10)
                                        {
                                        	imax(word);        
						break;
                                        }
				/*will change text to numer(long)*/
				number=transform(word);
				if(number<=INT_MAX && number>=0) 
		 			{ 
						int prime=prime_detect(number);
							if(prime == 1)
								{
				  					printf("number: %ld\n", number);
								}
		  					if(prime == 0)
								{
				  					printf("number: %ld (prime)\n", number);
								}
					}
				else
						printf("number: %ld\n", number);
						
						break;
   					
			case 1: /*word is text*/
				palindrom=palindrom_check(word);
					if(palindrom == 1)
						{
			 				printf("word: %s (palindrome)\n", word);
						}
					if(palindrom == 0)
						{
			 				printf("word: %s\n", word);
						}
		 		break;	
		
			case 2:	/*word is date*/
				(void) date(word);
				break;
		
   		}
		 
		 
	}
	return 0;
  }
