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
        vector<string> pList;
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
        map<string,string> sources, interestedIn;
        map<int,vector<string> > nodePredicates, nodeAttributes;
        PredicateList conjPredicateList, generalPredicateList;
        void initialize (void);
	void addDefinition (int, string);
	void addNode (int, int, string,string);
	void createPredLists (void);
	void createSources (void);
	void showVector(string, vector<string>);
	void showNodeList (void);
        void showMapSources (void);
        void getAip (void);
        vector<string> getAttributes (int);
	vector<string> getAttributes (string);
	vector<string> getPredicatesNode(int);
	vector<string> getPredicatesOver(vector<string>);
	vector<string> subtractLists(vector<string>, vector<string>);
	vector<string> intersectLists(vector<string>, vector<string>);
	vector<string> unionLists(vector<string>, vector<string>);
	string showChildren (int);
	string getPredicate (void) const;
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


