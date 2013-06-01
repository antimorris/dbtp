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
	int nodeParent;
	string nodeType;
	string nodeDefinition;
	vector<int> nodeChildren;
};

//////////////////////////////////////////////////////////////
// PredicateList Class definition
//////////////////////////////////////////////////////////////
class PredicateList
{
        public:
        map<int,string> pList;
        void addPredicate (string predicate);
        void showFullRegistry(void);
};

//////////////////////////////////////////////////////////////
// QP Class definition
//////////////////////////////////////////////////////////////
class QueryPlan
{
        public:
        map<int,NodeQP> nodeList;
        PredicateList conjPredicateList, generalPredicateList;
	string showChildren (int);
	string getPredicate (void) const;
	vector<string>	getAttributes (int);
	void addDefinition (int, string);
	void createPredLists (void);
	vector<string> getPredicatesNode(int);
	vector<string> getPredicatesOver(vector<string>);
	vector<string> subtractLists(vector<string>, vector<string>);
	vector<string> intersectLists(vector<string>, vector<string>);
	void showVector(string, vector<string>);
	void addNode (int, int, string,string);
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


