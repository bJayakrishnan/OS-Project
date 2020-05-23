#include <algorithm>
#include <fstream>
#include <chrono>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include<bits/stdc++.h>

using namespace std;
using namespace std::chrono;
vector<vector<double>> values;

void read_csv()
{
	ifstream stream1("project_file.csv");
    for (string line; getline(stream1, line); )
    {
        replace(line.begin(), line.end(), ',', ' ');
        istringstream in(line);
        values.push_back(
            vector<double>(istream_iterator<double>(in),
                                istream_iterator<double>()));
    }
}

void cal_log()
{
    for(auto i=values.begin(); i != values.end(); i++)
    {
        
        for(auto j=(*i).begin(); j!= (*i).end(); j++)
        {
            *j = log10(*j);
        }
    }
}

void display()
{
    for (vector<vector<double> >::const_iterator
             it(values.begin()), end(values.end()); it != end; ++it) {

        copy(it->begin(), it->end(),
                  ostream_iterator<double>(cout, ", "));
        cout << "\n";
    }
}

void min_and_max()
{
    for(auto i=values.begin(); i != values.end(); i++)
    {
        cout<<"maximum: "<<*max_element((*i).begin(), (*i).end())<<", minimum: "<<*min_element((*i).begin(), (*i).end())<<endl;
    }
}

void mean_sd()
{
	double temp, temp2, temp3;
	vector<double> mean_value, std_dev_value;
	for(auto i=values.begin(); i!=values.end(); i++)
	{
		temp = 0;
		temp3 = 0;
		for(auto j = (*i).begin(); j != (*i).end(); j++)
		{
			temp = temp + *j;
		}
		temp2 = temp/(*i).size();
		mean_value.push_back(temp2);
		for(auto j = (*i).begin(); j != (*i).end(); j++)
		{
			double t = pow(temp2 - (*j), 2);
			temp3 = temp3 + t;
		}
		temp3 = temp3/(*i).size(); 
		std_dev_value.push_back(sqrt(temp3));
	}

	for(auto i = std_dev_value.begin(), j = mean_value.begin(); i != std_dev_value.end(), j != mean_value.end(); i++, j++)
	{
		cout<<"mean: "<<*j<<" std: "<<*i<<endl;
	}
}

int main()
{
    

    auto start_time = high_resolution_clock::now();
    
   	read_csv();

   	cal_log();

    min_and_max();

    mean_sd();



    auto fin_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(fin_time - start_time);

    cout<<duration.count()<<endl;
    
    return 0;
}