#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "Tables.h"
using namespace std;


void loadTable(const char *path, table *table)
{
    std::string line;
	std::ifstream backstory (path);
	if (backstory.is_open())
	{
	        string rec;
	        getline(backstory,line);
	        std::istringstream ln( line );
	        while (ln.good())
            {
	        getline(ln,rec,',');
	        table->fields.push_back(rec);
            }
            while (backstory.good())
            {
                vector<string> tup;
                getline(backstory,line);
                std::istringstream ln( line );
                while (ln.good())
                {
                    getline(ln,rec,',');
                    tup.push_back(rec);
                }
                table->tuples.push_back(tup);
            }
        cout<<path<<" loaded"<<endl;
		backstory.close();
	}
	else
	{
		std::cout <<path << " Unable to open file" << std::endl << std::endl;
	}
	table->tuples.pop_back();
}

table JOIN (table A, table B, string field)
{
    table result;
    int pointa;
    int pointb;
    result.fields.push_back(field);
    for(int i=0; i<A.fields.size(); i++)
    {
        if (field == A.fields[i]) pointa = i;
        else
        result.fields.push_back(A.fields[i]);
    }
    for(int i=0; i<B.fields.size(); i++)
    {
        if (field == B.fields[i]) pointb = i;
        else
        result.fields.push_back(B.fields[i]);
    }
    for(int i=0; i<A.tuples.size(); i++){
        string buff = A.tuples[i][pointa];
        for(int j=0; j<B.tuples.size(); j++){
            if(buff == B.tuples[j][pointb]){
            vector<string> buff2;
            buff2.push_back(buff);
            for(int k=0; k<A.fields.size(); k++)
                if (buff != A.fields[k]) buff2.push_back(A.fields[k]);
            for(int l=0; l<B.fields.size(); l++)
                if (buff != B.fields[l]) buff2.push_back(B.fields[l]);
            result.tuples.push_back(buff2);
            }
        }
    }
    return result;
}

table SELECT (table A, vector<string> fields)
{
    table result;
    result.fields = fields;
    vector <int> fi;

    for(int i=0; i<fields.size(); i++)
        for (int j=0; j<A.fields.size(); j++)
            if (fields[i]==A.fields[j]) fi.push_back(j);
    for(int i=0; i<A.tuples.size();i++)
    {
        vector <string> buff;
        for (int j=0; j<fi.size(); j++)
        {
            buff.push_back(A.tuples[i][fi[j]]);
        }
        result.tuples.push_back(buff);
    }
    return result;
}
