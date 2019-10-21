/*
	Hamza Amjad
	Homework 6 - Derby
*/

/* buffer.h */
typedef int buffer_item;
#define BUFFER_SIZE 5

/* main.c */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
//#include "buffer.h"

// Defining some basics
#define RAND_DIVISOR 100000000
#define TRUE 1
#define THREAD_COUNT 20
#define _XOPEN_SOURCE 600 // Required to use the barriers

 

pthread_mutex_t mutex;


// Declaring global variables to be used in this project
int x = 0;
int y = 0;
int numOfrows = 20;
int numOfcolumns = 1250;
int **horse_pos;
int number = 0;


void array()
{
	int i = 0;
	
	horse_pos = malloc(numOfrows * sizeof(int *));
	
	for(i = 0; i < numOfrows; i++)
	{
		horse_pos[i] = malloc(numOfcolumns * sizeof(int));
		
	}
		
	int a = 0;
	int k=0;
	
	for(a=0; a < 20; a++)
	{
		for(k=0; k < 1250; k++)
		{
			horse_pos[a][k]= 0;
		}
	}
	
	for(a=0; a<20; a++)
	{
		
		horse_pos[a][0]= a;
		
	}
	
}

// ----------------- Get Horse postions info --------------------------
void getInfo (int i, int k, int lap, int thread_id, int y, int wait_sec, int lap1)
{
		int l = 0;	 
		 
	for (l=0 ; l<20; l++)
	{		
		 
		for(k = 0; k<1250; k++)
		{
		
			
			number = rand() % 2 + 1;
				
				
			if (number == 1) // Forward Movement 
			{
			
				if (horse_pos[l][k+2] == 0)
				{
					
					horse_pos[l][k+2] = horse_pos[l][k];
					
					horse_pos[l][k] = 0;
					
					if(k+1 == 1250)
					{
						lap = 1;
					}
					
					printf("Horse: %d, Lane: %d, Position: %d, Lap: %d\n", y, l, k+2, lap);
							
					sleep(0.1);
				}
				
				else
				{
					pthread_mutex_lock(&mutex);
					horse_pos[l][k+2] = horse_pos[l][k];
					horse_pos[l][k] = 0;
					
					if(k+1 == 1250)
					{
						lap = 1;
					}
					
					printf("Horse: %d, Lane: %d, Position: %d, Lap: %d\n", y,l,k+2,lap);
						
						
					sleep(0.1);
					
					
					pthread_mutex_unlock(&mutex);
					
				}
				
			
			}
	
			else if (number == 2) // Left Movement 
			{
				if (l==0)
				{
					
					
					if (horse_pos[l][k+1] == 0)
				  {
					
					horse_pos[l][k+1] = horse_pos[l][k];
					horse_pos[l][k] = 0;
					
					
					if(k+1 == 1250)
					{
						lap = 1;
					}
					
					printf("Horse: %d, Lane: %d, Position: %d, Lap: %d\n", y, l, k+1, lap);
					
					sleep(0.1);
				  }
				  
				  
				else
				{
					pthread_mutex_lock(&mutex);
					horse_pos[l][k+1] = horse_pos[l][k];
					horse_pos[l][k] = 0;
					
					if(k+1 == 1250)
					{
						lap = 1;
					}
					
					printf("Horse: %d, Lane: %d, Position: %d, Lap: %d\n", y, l, k+1, lap);
						
						
					sleep(0.1);
					
					pthread_mutex_unlock(&mutex);
					
				}
					
						
			}
				
			
				else if (horse_pos[l-1][k+1] == 0)
				{
					
					horse_pos[l-1][k+1] = horse_pos[l][k];
					horse_pos[l][k] = 0;
					
					if(k+1 == 1250)
					{
						lap = 1;
					}
					
					printf("Horse: %d, Lane: %d, Position: %d, Lap: %d\n", y,l ,k+1 , lap);
										
					sleep(0.1);
				}
						
				else
				{
					pthread_mutex_lock(&mutex);
					horse_pos[l-1][k+1] = horse_pos[l][k];
					horse_pos[l][k] = 0;
					
					if(k+1 == 1250)
					{
						lap = 1;
					}
					
					printf("Horse: %d, Lane: %d, Position: %d, Lap: %d\n", y, l-1, k+1, lap);
					pthread_mutex_unlock(&mutex);
					sleep(0.1);
					
				}

		
			}
	
			else if (number == 3) // Right Movement
			{
				if (l==19)
				{
					
					if (horse_pos[l][k+1] == 0)
				  {
					  
						horse_pos[l][k+1] = horse_pos[l][k];
						horse_pos[l][k] = 0;
						
						if(k+1 == 1250)
						{
							lap = 1;
						}
						
						printf("Horse: %d, Lane: %d, Position: %d, Lap: %d\n", y, l, k+1, lap);
											
						sleep(0.1);
				  }
				  
				  else
					{
						pthread_mutex_lock(&mutex);
						horse_pos[l][k+1] = horse_pos[l][k];
						horse_pos[l][k] = 0;
						
						if(k+1 == 1250)
						{
							lap = 1;
						}
						
						printf("Horse: %d, Lane: %d, Position: %d, Lap: %d\n", y,l,k+1,lap);
					
						pthread_mutex_unlock(&mutex);
						sleep(0.1);
					
					}
				
						
				}
				
				else if (horse_pos[l+1][k+1] == 0)
				{
					//pthread_mutex_lock(&mutex);
					horse_pos[l+1][k+1] = horse_pos[l][k];
					horse_pos[l][k] = 0;
					
					if(k+1 == 1250)
					{
						lap = 1;
					}
					
					printf("Horse: %d, Lane: %d, Position: %d, Lap: %d\n", y,l,k+1,lap);
					 
					 sleep(0.1);
				}
				
				else
				{
					pthread_mutex_lock(&mutex);
					horse_pos[l+1][k+1] = horse_pos[l][k];
					horse_pos[l][k] = 0;
					
					if(k+1 == 1250)
					{
						lap = 1;
					}
					
					printf("Horse: %d, Lane: %d, Position: %d, Lap: %d\n", y,l+1,k+1,lap);
				
					pthread_mutex_unlock(&mutex);
					sleep(0.1);
					
				}
			
			}	                                   
			
		}		
			
	}

}


// -------------- Waiting for 1 second ------------------
void *setInfo(void *h_ptr){
	
	
	int i = 0;
	int k = 0;
	int lap = 0;
	int lap1 = 1;
	int thread_id = *(int *)h_ptr;
	int y = thread_id;
	int wait_sec = 1;
	
	

	sleep(wait_sec);
	printf("Horse %d starts\n", thread_id);
	sleep(0.5);

	getInfo(i, k, lap, thread_id, y, wait_sec, lap1);

		 	
  return NULL;
		 
}



// --------------------- main function -------------------
int main(int argc, char *argv[]) {

    /* Create threads */
	
	int i,k;
	pthread_t parent;
	pthread_t ids[THREAD_COUNT];
	int IdShort[THREAD_COUNT];
	
	srand(time(NULL));
	

	for (i=0; i < THREAD_COUNT; i++) 
	{
		IdShort[i] = i;
		pthread_create(&ids[i], NULL, setInfo, &IdShort[i]);
	}
	
	array();

// Printing Statemtns	

	printf("3, 2, 1 .. GO!\n");
	sleep(1);
	
		
	
	for (i=0; i < THREAD_COUNT; i++) {
		pthread_join(ids[i], NULL);
	}

    printf("The race finishes!\n");
   
    exit(0);
}// end main
