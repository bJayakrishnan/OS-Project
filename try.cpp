#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include<bits/stdc++.h>

using namespace std;

int main()
{
    vector<vector<double>> values;
    ifstream stream1("project_file.csv");
    for (string line; getline(stream1, line); )
    {
        replace(line.begin(), line.end(), ',', ' ');
        istringstream in(line);
        values.push_back(
            vector<double>(istream_iterator<double>(in),
                                istream_iterator<double>()));
    }

    for(auto i=values.begin(); i != values.end(); i++)
    {
        
        for(auto j=(*i).begin(); j!= (*i).end(); j++)
        {
            *j = log10(*j);
            

        }

    }


    for (vector<vector<double> >::const_iterator
             it(values.begin()), end(values.end()); it != end; ++it) {

        copy(it->begin(), it->end(),
                  ostream_iterator<double>(cout, ", "));
        cout << "\n";
    }

    for(auto i=values.begin(); i != values.end(); i++)
    {
        
        cout<<*max_element((*i).begin(), (*i).end())<<endl;
    }
    return 0;
}