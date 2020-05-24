// read and successfully done log .....

#include<bits/stdc++.h>
#include<pthread.h>
#include<unistd.h>

using namespace std;

std::vector<string> column;
 

void *average(void *m)
{

	cout << "Inside Average.." << endl;
	double a[15];
	
	for(int i = 0; i < 15; i++)
	{
		a[i] = 0;
	}	

	long long int j = 0, i = 0, c = 1;
	double holder;

	while(i < column.size()-1)
	{
		if(column[i] != "\n") 
		{
			
			holder = stod(column[i]);
			a[j] = a[j] + holder;
			j++;
		}
		else if (column[i] == "\n")
		{
			j = 0;
			c++;
		}
		i++;
	}

	cout << "Outside : " << c << endl;

	double result;

	for(int k = 0; k < j; k++)
	{	
		result = a[k]/c;
		cout << "column : " << (k+1) << " : " << result << endl;
	}	

}

void *logger(void *l)
{
	cout << "Inside logger :\n";
	long long int i = 0;
	double holder;
	
	while(i < column.size())
	{
		if(column[i] != "\n")
		{
			holder = stod(column[i]);
			holder = log10(holder);
			column[i] = to_string(holder);
		}
		i++;
		
	}
	 cout << " logger done ..\n"; 


}

void *file_reader(void *t)
{
	cout << "inside Reader..\n";
	fstream fin;
	fin.open("project_file.csv", ios::in);
	std::vector<string> row;
	string line, word, temp;

	while(fin >> temp)
	{
		row.clear();
		stringstream s(temp);

		while(getline(s, word, ','))
		{
			row.push_back(word);
			column.push_back(word);
		}
		column.push_back("\n");

	}
	cout << "\n done reading....\n";

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
	
	sleep(2);			//just ot make sure read starts execution first.

	cout<<"calling function 2:\n";
	rL = pthread_create(&log, NULL, logger, NULL);
	
	sleep(2);

	cout<<"calling function 3:\n";
	rM = pthread_create(&mean, NULL, average, NULL);
	
	pthread_join(threads, NULL);	
	pthread_join(log, NULL);	
	pthread_join(mean, NULL);
	
	time(&end);

	double runtime = double(end - start);
	cout << "\n The runtime : " << runtime << endl;
	return 0;	
}