// read and succesfully done log .....

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include<fstream>
#include<vector>
#include<bits/stdc++.h>
#include<string>
#include<sstream>

using namespace std;

std::vector<string> column;

void *logger(void *l)
{
	cout << "printing from LOg :\n";
	cout << "column size : " << column.size() << endl;
	int i = 0;
	double holder;
	sleep(0.1);
	while(i < column.size())
	{
		cout << "Column size : " << column.size() << endl;
		if(column[i] != "\n")
		{
			holder = stod(column[i]);
			holder = log10(holder);
			column[i] = to_string(holder);
			cout << column[i] << "  ";
		}
		else
		{
			cout << endl;
		}
		
		i++;
		
	}
	//cout << "column size1 : " << column.size() << endl;
	cout << endl;

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
	for(int i = 0; i < column.size(); i++)
	{
		if(column[i] != "\n")
			cout << " R : " << column[i];
		else
			cout << endl;
		
	}	

}

int main()
{

	int rR, rL;
	pthread_t threads;
	pthread_t log;
	void *status;
	int i = 0;
	cout<<"calling function 1:\n";
	rR, rR = pthread_create(&threads, NULL, file_reader, NULL);
	if (rR) {
         cout << "Error:unable to join," << rR << endl;
         exit(-1);
      }
	cout<<"calling function 2:\n";
	rL = pthread_create(&log, NULL, logger, NULL);
	if (rL) {
         cout << "Error:unable to join," << rL << endl;
         exit(-1);
      }

	pthread_join(threads, NULL);
	pthread_join(log, NULL);
	sleep(1);
	return 0;	
}