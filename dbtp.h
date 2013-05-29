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
	char nodeType;
	int nodeParent;
	vector<int> nodeChildren;
	string nodeDefinition;
	void addPredicate (int);
	map<int,NodeQP> nodeList;
	string getChildren (void) const;
	vector<string>	getPredicates (void);
	void addNode (int, char);
        void initialize (void);
        void showNodeList (void);
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
