// read and successfully done log .....

#include<bits/stdc++.h>
#include<pthread.h>
#include<unistd.h>

using namespace std;

std::vector<string> column;

// Declaration of thread condition variable 
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;  
  
// declaring mutex 
pthread_mutex_t locker = PTHREAD_MUTEX_INITIALIZER; 

double counter = 0;
bool decision = false;


// void *average(void *m)
// {

// 	// cout << "Inside Average.." << endl;
// 	double a[15];
	
// 	for(int i = 0; i < 15; i++)
// 	{
// 		a[i] = 0;
// 	}	

// 	long long int j = 0, i = 0, c = 1;
// 	double holder;

// 	while(i < column.size()-1)
// 	{
// 		if(column[i] != "\n") 
// 		{
			
// 			holder = stod(column[i]);
// 			a[j] = a[j] + holder;
// 			j++;
// 		}
// 		else if (column[i] == "\n")
// 		{
// 			j = 0;
// 			c++;
// 		}
// 		i++;
// 	}

// 	cout << "Outside : " << c << endl;

// 	double result;

// 	for(int k = 0; k < j; k++)
// 	{	
// 		result = a[k]/c;
// 		cout << "column : " << (k+1) << " : " << result << endl;
// 	}	

// 	pthread_exit(NULL);

// }

void *logger(void *l)
{
	cout << "Inside logger :\n";
	long long int i = 0;
	double holder;
	
	pthread_mutex_lock(&locker);
	cout << "waiting inside Logger.." << endl;
	pthread_cond_wait(&cond2, &locker);
	cout << "waiting done.." << endl;
	while(i < column.size())
	{
		if(counter == 10000 && decision == false)
		{
			counter = 0;
			cout << "Signalling Reader" << endl;
			pthread_cond_signal(&cond1);
			cout << "waiting again in Logger" << endl;
			pthread_cond_wait(&cond2,&locker);	
		}
		else
		{
			if(column[i] != "\n")
			{
				holder = stod(column[i]);
				holder = log10(holder);
				column[i] = to_string(holder);
			}
			i++;
			counter++;		
		}	
		
		pthread_mutex_unlock(&locker);
	}
	 cout << " logger done ... : " << i << "\n"; 


}

void *file_reader(void *t)
{
	
	cout << "inside Reader..\n";
	fstream fin;
	fin.open("project_file.csv", ios::in);
	string line, word, temp;

	pthread_mutex_lock(&locker);
	
	while(fin >> temp)
	{
		
		stringstream s(temp);
	
		if(counter > 10000)
		{
			counter = 0;
			cout << "Signalling logger" << endl;
			pthread_cond_signal(&cond2);
			cout << "waiting inside Reader.." << endl;
			pthread_cond_wait(&cond1, &locker);
		}	
		
		while(getline(s, word, ','))
		{
			column.push_back(word);
			counter++;
		}
		
		column.push_back("\n");
			
		
		pthread_mutex_unlock(&locker);
	}


	cout << "\n done reading.... : " << column.size() << "\n";
	cout << "Signalling logger Last time" << endl;
	decision = true;
	pthread_cond_signal(&cond2);	
}

int main()
{

	int rR, rL, rM;
	pthread_t threads;
	pthread_t log;
	pthread_t mean;
	void *status;
	int i = 0;
	time_t start, end;

	time(&start);
	
	cout<<"calling function 1:\n";
	rR = pthread_create(&threads, NULL, file_reader, NULL);
	
	//sleep(1);			//just ot make sure read starts execution first.

	cout<<"calling function 2:\n";
	rL = pthread_create(&log, NULL, logger, NULL);
	
	// cout<<"calling function 3:\n";
	// rM = pthread_create(&mean, NULL, average, NULL);
	
	pthread_join(threads, NULL);	
	pthread_join(log, NULL);	
	// pthread_join(mean, NULL);
	
	time(&end);

	double runtime = double(end - start);
	cout << "\n The runtime : " << runtime << endl;
	return 0;	
}