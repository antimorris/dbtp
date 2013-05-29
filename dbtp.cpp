#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include "dbtp.h"
using namespace std;

#define LOGFILE "/home/jusafing/test.log"

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
        int newId = registry.size() + 1;
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
void NodeQP::addNode (int rpid, char rtype)
{
	stringstream msg;
	NodeQP node;
	NodeQP* nodeTmp;
	node.nodeType = rtype;
	node.nodeParent = rpid;
	int newId = nodeList.size() + 1;
	msg << "Adding new NodeQP with ID (" << newId << ") and PID (" << rpid << ") and TYPE (" << rtype << ")";
	logMsgT(__func__,msg.str(),2,LOGFILE);
	nodeList.insert(pair<int,NodeQP>(newId,node));
	if (rpid == 0)
	{
	        cout << "PID 0. Main node " << endl;
	}
	else
	{
	        nodeTmp = &nodeList[rpid];
	        nodeTmp->nodeChildren.push_back(newId);
                cout << "Reading info for ID: " << rpid << " PARENT: " << nodeTmp->nodeParent << "- " << nodeTmp->nodeType << "- " << nodeTmp->getChildren() << endl;
	}

}

//////////////////////////////////////////////////////////////
// NodeQP initialize function definition
//////////////////////////////////////////////////////////////
void NodeQP::initialize(void)
{
        addNode(0,'M');
};

//////////////////////////////////////////////////////////////
// NodeQP ShowNodeList definition
//////////////////////////////////////////////////////////////
void NodeQP::showNodeList (void)
{
        cout << endl << "NODE LIST" << endl;
        for (map<int,NodeQP>::const_iterator it=nodeList.begin(); it!=nodeList.end(); ++it)
        {
                stringstream nodeFound;
                nodeFound << "ID: " << it->first << " TYPE: " << it->second.nodeType << " CHILDREN: " << it->second.getChildren() ;
                cout << nodeFound.str() << '\n';
        }
        cout << "-------------" << endl << endl;
}

//////////////////////////////////////////////////////////////
// NodeQP getChildren function definition
//////////////////////////////////////////////////////////////
string NodeQP::getChildren (void) const
{
        stringstream childrenList;
        string children;
        for (unsigned i=0; i<nodeChildren.size(); i++)
        {
                childrenList << nodeChildren.at(i) << ",";
        }
        children = childrenList.str();
        return children;
}


//////////////////////////////////////////////////////////////
// NodeQP addPredicate definition
//////////////////////////////////////////////////////////////
void NodeQP::addPredicate (int rnid, string rpredicate)
{
        stringstream msg;
        NodeQP* node;
        node = &nodeList[rnid];
        node->nodeDefinition = rpredicate;
        msg << "Adding predicate : (" << rpredicate << ") to NODE: " << rnid ;
        logMsgT(__func__, msg.str() ,2,LOGFILE);

}
//////////////////////////////////////////////////////////////
// NodeQP getAttributes function definition
//////////////////////////////////////////////////////////////
vector<string> NodeQP::getAttributes (int rnid)
{
        NodeQP* node;
        node = &nodeList[rnid];
        istringstream predicateF(node->nodeDefinition);
        string p;
        vector<string> predList;
        while (getline(predicateF, p, ','))
        {
                predList.push_back(p);
        }
        return predList;
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
        myfile.open (logfile.c_str(), ofstream::out | ofstream::app);
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
