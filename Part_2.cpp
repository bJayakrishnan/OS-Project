// read and successfully done log .....

#include<bits/stdc++.h>


using namespace std;

std::vector<string> column;

void average()
{

	cout << "Inside Average.." << endl;
	double a[15];
	
	for(int i = 0; i < 15; i++)
	{
		a[i] = 0;
	}	

	long long int j = 0, i = 0, c = 1;
	double holder;
	cout << column.size() << endl; 

	while(i < column.size()-1)
	{
		if(column[i] != "\n")
		{
			holder = stod(column[i]);
			a[j] = a[j] + holder;
			j++;
		//	cout << "j : " << j << " : " << " holder : " << holder << " : " << a[j] << endl;
		}
		else if (column[i] == "\n")
		{
			j = 0;
			c++;
		}
		i++;
	}

	//cout << "Outside\n";

	for(int k = 0; k < j; k++)
	{
		cout << "column : " << (k+1) << " : " << (a[k]/c) << endl;
	}	

}

void logger()
{
	cout << "printing from LOg :\n";
	long long int i = 0;
	double holder;
	cout << "From logger : " <<column.size() << endl;
	while(i < column.size())
	{
		if(column[i] != "\n")
		{
			holder = stod(column[i]);
			holder = log10(holder);
			column[i] = to_string(holder);
			//cout << column[i] << "h ,  ";
		}

		i++;
		
	}


}

void file_reader()
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
			cout << column[i] << " ";
		else
			cout << endl;
		
	}	

}

int main()
{

	int rR, rL, rM;
	int i = 0;
	time_t start, end;

	time(&start);

	cout<<"calling function 1:\n";
	file_reader();	
	cout<<"calling function 2:\n";
	logger();
	cout<<"calling function 3:\n";
	average();

	time(&end);
	cout << "S : " << double(start);
	cout << "E : " << double(end);
	double runtime = double(end - start);
	cout << "\n The runtime : " << runtime << endl;
	return 0;	
}