#include <algorithm>
#include <fstream>
#include <chrono>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include<bits/stdc++.h>

using namespace std;
using namespace std::chrono;
std::mutex m;
std::condition_variable cv1, cv2, cv3;
vector<vector<double>> values;
int counter = 0, counter2 = 0, counter3 = 0;

void read_csv()
{
    lock_guard<mutex> lock(m);
    ifstream stream1("project_file.csv");
    for (string line; getline(stream1, line); )
    {
        replace(line.begin(), line.end(), ',', ' ');
        istringstream in(line);
        values.push_back(
            vector<double>(istream_iterator<double>(in),
                                istream_iterator<double>()));
    }
    counter+=1;
    cv1.notify_one();
}

void cal_log()
{
    unique_lock<mutex> lock(m);
    cv1.wait(lock, []{return (counter==1) ? true : false; });
    for(auto i=values.begin(); i != values.end(); i++)
    {
        
        for(auto j=(*i).begin(); j!= (*i).end(); j++)
        {
            *j = log10(*j);
        }
    }
    counter2+=1;
    counter3+=1;
    cv2.notify_one();
    cv3.notify_one();
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
    unique_lock<mutex> lock(m);
    cv2.wait(lock, []{ return (counter2==1) ? true : false; });
    for(auto i=values.begin(); i != values.end(); i++)
    {
        cout<<"maximum: "<<*max_element((*i).begin(), (*i).end())<<", minimum: "<<*min_element((*i).begin(), (*i).end())<<endl;
    }
    
}

void mean_sd()
{
    unique_lock<mutex> lock(m);
    cv3.wait(lock, []{ return (counter3==1) ? true : false; });
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

    thread t1(read_csv);

    thread t2(cal_log);

    thread t3(min_and_max);

    thread t4(mean_sd);

    t1.join();
    t2.join();
    t3.join();
    t4.join();



    auto fin_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(fin_time - start_time);

    cout << "Runtime : " << duration.count()<<endl;

    return 0;
}