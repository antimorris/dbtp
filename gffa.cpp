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
// nodeQP Class definition
//////////////////////////////////////////////////////////////
class nodeQP {
	public:
	int nodeId, nodeType;
	string children, definition;
	void addChildren (int);
	void addPredicate (int);
	vector<int> getChildren (void);
	vector<string>	getPredicates (void);
	nodeQP (int, int);
};


//////////////////////////////////////////////////////////////
// AIP Class definition
//////////////////////////////////////////////////////////////
class aip {
	public:
	int loc,predicate;
	string key;
	map<int,string> registry;
        map<int,string>::iterator it;
	void addPredicate (int, string, int);
	string checkPredicate (int);
	string getPredicate (int);
        void showFullRegistry (void);
};

//////////////////////////////////////////////////////////////
// AIP:::addPredicate definition
//////////////////////////////////////////////////////////////
void aip::addPredicate (int r_loc, string r_key, int r_pred)
{
        stringstream key;
        key << r_loc << "," << r_key << "," << r_pred;
        registry.insert(pair<int,string>(r_pred,key.str()));
}

//////////////////////////////////////////////////////////////
// AIP::checkPredicate definition
//////////////////////////////////////////////////////////////
string aip::checkPredicate (int key)
{
        map<string,string>::iterator it;

        if (registry.find(key) == registry.end())
        {
                cout << "KEY DOES NOT EXIST\n";
                return "NULL";
        }
        else
        {
                cout << "KEY EXISTSSSSSSS --> " << registry[key] << endl;
                return registry[key];
        }
}

//////////////////////////////////////////////////////////////
// AIP::getPredicate definition
//////////////////////////////////////////////////////////////
string aip::getPredicate(int)
{

}

//////////////////////////////////////////////////////////////
// AIP::getPredicate definition
//////////////////////////////////////////////////////////////
void aip::showFullRegistry(void)
{
        for (map<int,string>::iterator it=registry.begin(); it!=registry.end(); ++it)
        {
                cout << it->first << " => " << it->second << '\n';
        }
}

//////////////////////////////////////////////////////////////
// NodeQP Constructor definition
//////////////////////////////////////////////////////////////
nodeQP::nodeQP (int a, int b)
{
	nodeId 	 = a;
	nodeType = b;
}

//////////////////////////////////////////////////////////////
// NodeQP addChildren definition
//////////////////////////////////////////////////////////////
void nodeQP::addChildren (int id)
{
}

//////////////////////////////////////////////////////////////
// NodeQP addPredicate definition
//////////////////////////////////////////////////////////////
void nodeQP::addPredicate (int)
{
}
//////////////////////////////////////////////////////////////
// NodeQP getPredicates function definition
//////////////////////////////////////////////////////////////
vector<string> nodeQP::getPredicates (void)
{
}

//////////////////////////////////////////////////////////////
// NodeQP getPredicates function definition
//////////////////////////////////////////////////////////////
vector<int> nodeQP::getChildren (void)
{
}

//////////////////////////////////////////////////////////////
// Main Function
//////////////////////////////////////////////////////////////
int main ()
{
	nodeQP node1 (0,1);
	nodeQP node2 (1,2);
	aip aipRegistry;
	aipRegistry.addPredicate(0,"prod1",0);
	cout << "Node ID: " << node1.nodeId << " TYPE: " << node1.nodeType << endl;
	cout << "Node ID: " << node2.nodeId << " TYPE: " << node2.nodeType << endl;
        aipRegistry.checkPredicate(1);
        aipRegistry.checkPredicate(0);
        cout << "AIP REGISTRY" << endl << endl;
        aipRegistry.showFullRegistry();
	exit(0);
}
