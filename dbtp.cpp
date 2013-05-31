#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
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
        stringstream msg;
        msg << "\n\t\t\tPREDICATE LIST";
        msg << "\n\t\t\t--------------";
        for (map<int,string>::const_iterator it=pList.begin(); it!=pList.end(); ++it)
        {
                stringstream predFound;
                msg << "\n\t\t\t" << it->first << " => " << it->second ;
        }
        msg << endl;
        logMsgT(__func__, msg.str() ,2,LOGFILE);
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
        stringstream msg;
        msg << "\n\t\t\tAIP REGISTRY";
        msg << "\n\t\t\t------------";
        for (map<int,PredicateStruct>::const_iterator it=registry.begin(); it!=registry.end(); ++it)
        {
                stringstream predFound;
                //predFound << it->second.predLoc_ << "-" << it->second.predKey_ << "-" << it->second.predDef_;
                predFound << it->second.getPredLoc() << "-" << it->second.getPredKey() << "-" << it->second.getPredDef();
                msg << "\n\t\t\t" << it->first << " => " << predFound.str();
        }
        msg << endl;
        logMsgT(__func__,msg.str(),2,LOGFILE);
}

//////////////////////////////////////////////////////////////
// QP showPredicateNode function definition
//////////////////////////////////////////////////////////////
void QueryPlan::showVector(string title, vector<string> rpnode)
{
        stringstream msg;
        msg << "\n\t\t" << title;
        msg << "\n\t\t---------------";
        for (unsigned i=0; i<rpnode.size(); i++)
        {
                msg << "\n\t\t-->" << rpnode[i];
        }
        msg << endl;
        logMsgT(__func__,msg.str(),2,LOGFILE);
}

//////////////////////////////////////////////////////////////
// QP getPredicateNode function definition
//////////////////////////////////////////////////////////////
vector<string> QueryPlan::getPredicatesNode(int rnid)
{
        NodeQP* node;
        node = &nodeList[rnid];
        stringstream msg;
        vector<string> predicates, predicatesChild;
        msg << "\n\t\tChecking Node ID (" << rnid << ") Type (" << node->nodeType << ")";
        if (node->nodeType.compare("P") == 0)
        {
                predicates.push_back(node->nodeDefinition);
                msg << "\n\t\t\tAdded From ID (" << rnid << ") P (" ;
                msg << node->nodeDefinition << ")" ;
        }
        for(unsigned i=0; i<node->nodeChildren.size(); i++)
        {
                predicatesChild = getPredicatesNode(node->nodeChildren[i]);
                predicates.insert (predicates.end(),predicatesChild.begin(),predicatesChild.end());
        }
        logMsgT(__func__,msg.str(),2,LOGFILE);
        return predicates;
}

//////////////////////////////////////////////////////////////
// QP getPredicatesOver function definition
//////////////////////////////////////////////////////////////
vector<string> QueryPlan::getPredicatesOver(vector<string> rattrib)
{
        stringstream msg;
        vector<string> predicatesOver;
        map<int,string>::iterator it;

        for(unsigned i=0; i<rattrib.size(); i++)
        {
                msg << "\n\t\tChecking A (" << rattrib[i] << ") on GPL";
                for (it=generalPredicateList.pList.begin(); it!=generalPredicateList.pList.end(); ++it)
                {
                        if(it->second.find(rattrib[i]) != std::string::npos)
                        {
                                predicatesOver.push_back(it->second);
                                msg << "\n\t\t\t Found A on GPL - Predicated (" << it->second << ") Added to POA List" ;
                        }
                }
        }
        logMsgT(__func__,msg.str(),2,LOGFILE);
        return predicatesOver;
}


//////////////////////////////////////////////////////////////
// QP Constructor definition
//////////////////////////////////////////////////////////////
void QueryPlan::addNode (int rnid, int rpid, string rtype, string rdef)
{
	stringstream msg;
	NodeQP node;
	NodeQP* nodeTmp;
	node.nodeType   = rtype;
	node.nodeParent = rpid;
	node.nodeDefinition = rdef;
	msg << "Adding new NodeQP with ID (" << rnid << ") and PID (" << rpid << ") and TYPE (" << rtype << ")";
	logMsgT(__func__,msg.str(),2,LOGFILE);
	nodeList.insert(pair<int,NodeQP>(rnid,node));
	if (rnid == 0)
	{
	        //cout << "PID 0. Main node " << endl;
	}
	else
	{
	        nodeTmp = &nodeList[rpid];
	        nodeTmp->nodeChildren.push_back(rnid);
                //cout << "Reading info for ID: " << rpid << " PARENT: " << nodeTmp->nodeParent << "- " << nodeTmp->nodeType << "- " << nodeTmp->getChildren() << endl;
	}

}


//////////////////////////////////////////////////////////////
// QP ShowNodeList definition
//////////////////////////////////////////////////////////////
void QueryPlan::showNodeList (void)
{
        stringstream msg;
        msg << "\n\t\t\tNODE LIST";
        msg << "\n\t\t\t---------";
        for (map<int,NodeQP>::const_iterator it=nodeList.begin(); it!=nodeList.end(); ++it)
        {
                stringstream nodeFound;
                nodeFound << "ID: " << it->first << " TYPE: " << it->second.nodeType << " CHILDREN: " << showChildren(it->first) ;
                msg << "\n\t\t\t" << nodeFound.str();
        }
        msg << endl;
        logMsgT(__func__, msg.str() ,2,LOGFILE);
}

//////////////////////////////////////////////////////////////
// QP createPredLists definition
//////////////////////////////////////////////////////////////
void QueryPlan::createPredLists (void)
{
        stringstream msg;
        for (map<int,NodeQP>::const_iterator it=nodeList.begin(); it!=nodeList.end(); ++it)
        {
                if (it->second.nodeType.compare("P") == 0)
                {
                        generalPredicateList.addPredicate(it->second.nodeDefinition);
                        msg << "\n\t\tAdded predicate to GPL - Node: (" << it->first;
                        msg << ") TYPE: (" << it->second.nodeType << ") P: (" << it->second.nodeDefinition << ")" ;
                        if (it->second.nodeDefinition.find("AND") != std::string::npos)
                        {
                                conjPredicateList.addPredicate(it->second.nodeDefinition);
                                msg << "\n\t\tAdded predicate to CPL - Node: (" << it->first;
                                msg << ") TYPE: (" << it->second.nodeType << ") P: (" << it->second.nodeDefinition << ")" ;
                        }
                }
        }
        msg << endl;
        logMsgT(__func__, msg.str() ,2,LOGFILE);
}


//////////////////////////////////////////////////////////////
// QP showChildren function definition
//////////////////////////////////////////////////////////////
string QueryPlan::showChildren (int rpid)
{
        NodeQP* nodeTmp;
        nodeTmp = &nodeList[rpid];
        stringstream childrenList;
        string children;
        for (unsigned i=0; i<nodeTmp->nodeChildren.size(); i++)
        {
                childrenList << nodeTmp->nodeChildren.at(i) << ",";
        }
        children = childrenList.str();
        return children;
}

//////////////////////////////////////////////////////////////
// QP addPredicate definition
//////////////////////////////////////////////////////////////
void QueryPlan::addDefinition (int rnid, string rdef)
{
        stringstream msg;
        NodeQP* node;
        node = &nodeList[rnid];
        node->nodeDefinition = rdef;
        msg << "Adding definition (" << rdef << ") to NODE: (" << rnid <<")" ;
        logMsgT(__func__, msg.str() ,2,LOGFILE);
}

//////////////////////////////////////////////////////////////
// QP getAttributes function definition
//////////////////////////////////////////////////////////////
vector<string> QueryPlan::getAttributes (int rnid)
{
        NodeQP* node;
        node = &nodeList[rnid];
        stringstream msg;
        string p;
        istringstream predicateF(node->nodeDefinition);
        vector<string> attribList, attribListChild;

        msg << "\n\t\tChecking Node ID (" << rnid << ") Type (" << node->nodeType << ")";
        logMsgT(__func__,msg.str(),2,LOGFILE);
        if (node->nodeType.compare("P") == 0)
        {
                while (getline(predicateF, p, ','))
                {
                        if (p.compare("<") != 0 and p.compare(">") != 0 and p.compare("AND") != 0)
                        {
                                attribList.push_back(p);
                                msg << "\n\t\t\tAdded ATTRIB From ID (" << rnid << ") A (" ;
                                msg << p << ")" ;
                                logMsgT(__func__,msg.str(),2,LOGFILE);
                        }
                }
        }
        for(unsigned i=0; i<node->nodeChildren.size(); i++)
        {
                attribListChild = getAttributes(node->nodeChildren[i]);
                attribList.insert (attribList.end(),attribListChild.begin(),attribListChild.end());
        }
        return attribList;
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
         << function_name << "] --> " << msg_data << endl;
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
