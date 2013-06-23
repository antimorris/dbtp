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
using namespace std;

struct table {
  std::vector <std::string> fields;
  std::vector< vector<std::string> > tuples;
} ;


void loadTable(const char *path, table *table);
table JOIN (table A, table B, string field);
table SELECT (table A, vector<string> fields);


