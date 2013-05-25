#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
using namespace std;
//////////////////////////////////////////////////////////////
// Prototypes
//////////////////////////////////////////////////////////////
string getTime (void);
void logMsgT (string function_name, string msg_data, int msg_code, string logfile);


//////////////////////////////////////////////////////////////
// NodeQP Class definition
//////////////////////////////////////////////////////////////
class NodeQP
{
	public:
	int nodeId, nodeType;
	string children, definition;
	void addChildren (int);
	void addPredicate (int);
	vector<int> getChildren (void);
	vector<string>	getPredicates (void);
	NodeQP (int, int);
};

//////////////////////////////////////////////////////////////
// Predicate Class definition
//////////////////////////////////////////////////////////////
class PredicateData
{
        public:
        class PredicateStruct
        {
                public:
                int predLoc, predDef;
                string predKey;
                int    getPredLoc () const {return predLoc;}
                string getPredKey () const {return predKey;}
                int    getPredDef () const {return predDef;}
        };
	string key;
	map<int,PredicateStruct> registry;
        void addPredicate (int, string, int);
	string checkPredicate (int);
        void showFullRegistry (void);
};

//////////////////////////////////////////////////////////////
// PredicateList Class definition
//////////////////////////////////////////////////////////////
class PredicateList
{
        public:
        //int predID;
        //string predDef;
        map<int,string> pList;
        //string getPredDef (void) {return predDef;}
        void addPredicate (string predicate);
        void showFullRegistry(void);
};
