#include <pthread.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
using namespace std;

#define LOGFILE "/home/jusafing/test.log"
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


//////////////////////////////////////////////////////////////
// PredicateList:::addPredicate definition
//////////////////////////////////////////////////////////////
void PredicateList::addPredicate(string rpred)
{
        int newId = pList.size()+1;
        pList.insert(pair<int,string>(newId,rpred));
        stringstream msg;
        msg << "Adding Predicate (" << rpred << ") to PredicateList";
        logMsgT(__func__, msg.str() ,2,LOGFILE);
}


//////////////////////////////////////////////////////////////
// PredicateList::getPredicate definition
//////////////////////////////////////////////////////////////
void PredicateList::showFullRegistry(void)
{
        cout << "PREDICATE LIST" << endl << endl;
        for (map<int,string>::const_iterator it=pList.begin(); it!=pList.end(); ++it)
        {
                stringstream predFound;
                cout << it->first << " => " << it->second << '\n';
        }
}


//////////////////////////////////////////////////////////////
// PredicateData:::addPredicate definition
//////////////////////////////////////////////////////////////
void PredicateData::addPredicate (int rloc, string rkey, int rpred)
{
        PredicateStruct predicate;
        predicate.predLoc = rloc;
        predicate.predKey = rkey;
        predicate.predDef = rpred;
        int newId = registry.size()+1;
        registry.insert(pair<int,PredicateStruct>(newId,predicate));
        stringstream msg;
        msg << "Adding : " << newId << " -- " << rloc << " -- " << rkey << " -- " << rpred;
        logMsgT(__func__, msg.str() ,2,LOGFILE);
}

//////////////////////////////////////////////////////////////
// PredicateData::checkPredicate definition
//////////////////////////////////////////////////////////////
string PredicateData::checkPredicate (int key)
{
        stringstream msg;
        msg << "Checking KEY: (" << key << ") on AIP registry ... " ;
        logMsgT(__func__, msg.str(),2,LOGFILE);
        if (registry.find(key) == registry.end())
        {
                logMsgT(__func__,"KEY DOES NOT EXIST",2,LOGFILE);
                return "NULL";
        }
        else
        {
                stringstream predFound,msg;
                predFound << registry[key].predLoc << "-" << registry[key].predKey << "-" << registry[key].predDef;
                msg << "KEY EXISTS --> " << predFound.str();
                logMsgT(__func__,msg.str(),2,LOGFILE);
                return predFound.str() ;
        }
}

//////////////////////////////////////////////////////////////
// PredicateData::getPredicate definition
//////////////////////////////////////////////////////////////
void PredicateData::showFullRegistry(void)
{
        cout << endl << "AIP REGISTRY" << endl;
        for (map<int,PredicateStruct>::const_iterator it=registry.begin(); it!=registry.end(); ++it)
        {
                stringstream predFound;
                //predFound << it->second.predLoc_ << "-" << it->second.predKey_ << "-" << it->second.predDef_;
                predFound << it->second.getPredLoc() << "-" << it->second.getPredKey() << "-" << it->second.getPredDef();
                cout << it->first << " => " << predFound.str() << '\n';
        }
        cout << "-------------" << endl << endl;
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
// logMsgT function definition
//////////////////////////////////////////////////////////////
void logMsgT (string function_name, string msg_data, int msg_code, string logfile)
{
        string msg_prefix;
        string msg_timestamp;
        string msg_log;
        if      ( msg_code ==-1 ){msg_prefix = "FATAL ERROR";   }
        else if ( msg_code == 0 ){msg_prefix = "ERROR";         }
        else if ( msg_code == 1 ){msg_prefix = "WARNING";       }
        else if ( msg_code == 2 ){msg_prefix = "INFO";          }
        else if ( msg_code == 3 ){msg_prefix = "DEBUG";         }
        else                     {msg_prefix = "UNDEFINED";     }
        msg_timestamp = getTime();
        ofstream myfile;
        myfile.open (logfile.c_str());
        myfile << "[" << msg_timestamp << "] [" << msg_prefix << "] ["
         << function_name << "] [" << msg_data << "]" << endl;
        cout << "[" << msg_timestamp << "] [" << msg_prefix << "] ["
         << function_name << "] [" << msg_data << "]" << endl;
        myfile.close();
}
//////////////////////////////////////////////////////////////
// getTime function definition
//////////////////////////////////////////////////////////////
string getTime (void)
{
        time_t rawtime;
        struct tm * timeinfo;
        char buffer [80];
        time (&rawtime);
        timeinfo = localtime (&rawtime);
        strftime (buffer,80,"%F %T",timeinfo);
        return buffer;
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
        PredicateList conjPredicateList;

        // TEST
        conjPredicateList.addPredicate("p1 = p2");
        conjPredicateList.addPredicate("p1 = p3");
        conjPredicateList.addPredicate("p3 = p4");
        conjPredicateList.addPredicate("p4 = p5");
        conjPredicateList.addPredicate("p5 = p6");
        conjPredicateList.addPredicate("p6 = p7");
        conjPredicateList.addPredicate("p7 = p8");
        conjPredicateList.addPredicate("p8 = p9");
        conjPredicateList.addPredicate("p9 = p0");
        conjPredicateList.addPredicate("p0 = p1");
        conjPredicateList.showFullRegistry();

	PredicateData aipRegistry;
	aipRegistry.showFullRegistry();
	aipRegistry.checkPredicate(0);

        //TEST
	aipRegistry.addPredicate(0,"proda",0);
	aipRegistry.addPredicate(1,"prodb",1);
	aipRegistry.addPredicate(2,"prodc",2);
	aipRegistry.addPredicate(3,"prodd",3);

        aipRegistry.showFullRegistry();
        aipRegistry.checkPredicate(1);
	exit(0);
}
