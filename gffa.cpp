#include <pthread.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <sstream>
using namespace std;



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
                int predLoc_, predDef_;
                string predKey_;
                int    getPredicateLoc () const {return predLoc_;}
                string getPredicateKey () const {return predKey_;}
                int getPredicateDef () const {return predDef_;}
        };
	string key;
	map<int,PredicateStruct> registry;
        void addPredicate (int, string, int);
	string checkPredicate (int);
        void showFullRegistry (void);
};

//////////////////////////////////////////////////////////////
// PredicateData:::addPredicate definition
//////////////////////////////////////////////////////////////
void PredicateData::addPredicate (int rloc, string rkey, int rpred)
{
        PredicateStruct predicate;
        predicate.predLoc_ = rloc;
        predicate.predKey_ = rkey;
        predicate.predDef_ = rpred;
        //cout << "Current registry Size: " << registry.size() << endl;
        int newId = registry.size()+1;
        //cout << "New registry Size: " << registry.size() << endl;
        registry.insert(pair<int,PredicateStruct>(newId,predicate));
        cout << "Adding : " << newId << " -- " << rloc << " -- " << rkey << " -- " << rpred << endl;
        //cout << "READ : " << registry[newId].predKey_ << endl;
}

//////////////////////////////////////////////////////////////
// PredicateData::checkPredicate definition
//////////////////////////////////////////////////////////////
string PredicateData::checkPredicate (int key)
{
        cout << "Checking KEY: [" << key << "] on AIP registry ... " ;
        if (registry.find(key) == registry.end())
        {
                cout << "KEY DOES NOT EXIST" << endl;
                return "NULL";
        }
        else
        {
                stringstream predFound;
                predFound << registry[key].predLoc_ << "-" << registry[key].predKey_ << "-" << registry[key].predDef_;
                cout << "KEY EXISTS --> " << predFound.str() << endl;
                return predFound.str() ;
        }
}

//////////////////////////////////////////////////////////////
// PredicateData::getPredicate definition
//////////////////////////////////////////////////////////////
void PredicateData::showFullRegistry(void)
{
        cout << "AIP REGISTRY" << endl << endl;
        for (map<int,PredicateStruct>::const_iterator it=registry.begin(); it!=registry.end(); ++it)
        {
                stringstream predFound;
                predFound << it->second.predLoc_ << "-" << it->second.predKey_ << "-" << it->second.predDef_;
                cout << it->first << " => " << predFound.str() << '\n';
        }
}

//////////////////////////////////////////////////////////////
// NodeQP Constructor definition
//////////////////////////////////////////////////////////////
NodeQP::NodeQP (int a, int b)
{
	nodeId 	 = a;
	nodeType = b;
}

//////////////////////////////////////////////////////////////
// NodeQP addChildren definition
//////////////////////////////////////////////////////////////
void NodeQP::addChildren (int id)
{
}

//////////////////////////////////////////////////////////////
// NodeQP addPredicate definition
//////////////////////////////////////////////////////////////
void NodeQP::addPredicate (int)
{
}
//////////////////////////////////////////////////////////////
// NodeQP getPredicates function definition
//////////////////////////////////////////////////////////////
vector<string> NodeQP::getPredicates (void)
{
}

//////////////////////////////////////////////////////////////
// NodeQP getPredicates function definition
//////////////////////////////////////////////////////////////
vector<int> NodeQP::getChildren (void)
{
}


//////////////////////////////////////////////////////////////
// Main Function
//////////////////////////////////////////////////////////////
int main ()
{
	NodeQP node1 (0,1);
	NodeQP node2 (1,2);

	cout << "Node ID: " << node1.nodeId << " TYPE: " << node1.nodeType << endl;
	cout << "Node ID: " << node2.nodeId << " TYPE: " << node2.nodeType << endl;
        PredicateData predicateList;
	PredicateData aipRegistry;

	aipRegistry.showFullRegistry();
	aipRegistry.checkPredicate(0);

	aipRegistry.addPredicate(0,"proda",0);
	aipRegistry.addPredicate(1,"prodb",1);
	aipRegistry.addPredicate(2,"prodc",2);
	aipRegistry.addPredicate(3,"prodd",3);

        aipRegistry.showFullRegistry();
        aipRegistry.checkPredicate(1);
	exit(0);
}
