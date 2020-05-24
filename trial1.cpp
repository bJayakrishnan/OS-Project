#include <pthread.h>
#include<bits/stdc++.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

#define NUM_THREADS 3
#define TCOUNT 10
#define COUNT_LIMIT 12

int counter = 0;
int thread_ids[3] = {0,1,2};
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;

void *inc_count(void *t)
{
	long my_id = (long)t;
	for (int i=0; i<TCOUNT; i++) 
	{
		pthread_mutex_lock(&count_mutex);
		counter++;
		cout << "1  ";
		if (counter == COUNT_LIMIT)
		{ 
			cout << "2  ";														// 6  6 
			pthread_cond_signal(&count_threshold_cv); 							
			cout << "3  ";																			
		}
		cout << "4  ";														
		pthread_mutex_unlock(&count_mutex);
		cout << "5  ";
		//sleep(1);
	}
	cout << "6  ";
	pthread_exit(NULL);
}
void *watch_count(void *t)
{
	long my_id = (long)t;
	
	pthread_mutex_lock(&count_mutex);
	
	cout << "7  ";
	if (counter < COUNT_LIMIT) 
	{
		cout << "8  ";
		pthread_cond_wait(&count_threshold_cv, &count_mutex);
		cout << "9  ";																
		counter += 125;
		cout << "10  ";
	}
	cout << "11  ";
	pthread_mutex_unlock(&count_mutex);
	cout << "12  ";
	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	int I;
	long t1=1, t2=2, t3=3;
	pthread_t threads[3];
	pthread_attr_t attr;
	pthread_mutex_init(&count_mutex, NULL);
	pthread_cond_init (&count_threshold_cv, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_create(&threads[0], &attr, watch_count, (void *)t1);
	pthread_create(&threads[1], &attr, inc_count, (void *)t2);
	pthread_create(&threads[2], &attr, inc_count, (void *)t3);
	
	for (int i=0; i<NUM_THREADS; i++) 
	{ /* Wait for all threads */
		pthread_join(threads[i], NULL);
	}
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&count_mutex);
	pthread_cond_destroy(&count_threshold_cv);
	pthread_exit(NULL);
}