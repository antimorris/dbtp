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
#include <String.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

struct table {
  vector <string> fields;
  vector< vector<string> > tuples;
} ;

void loadTable(const char *path, table *table);

table JOIN (table A, table B, string field);

table SELECT (table A, vector<string> fields);


