#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <algorithm>
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
        pList.push_back(rpred);
        stringstream msg;
        msg << "Adding Predicate (" << rpred << ") to PredicateList";
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
        msg << "\n\t\t\t" << title;
        msg << "\n\t\t\t---------------";
        for (unsigned i=0; i<rpnode.size(); i++)
        {
                msg << "\n\t\t\t> " << rpnode[i];
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
        msg << "\n\t\t\tChecking Node ID (" << rnid << ") Type (" << node->nodeType << ")";
        logMsgT(__func__,msg.str(),2,LOGFILE);
        msg.str("");
        if (node->nodeType.compare("P") == 0)
        {
                predicates.push_back(node->nodeDefinition);
                msg << "\n\t\t\tAdded From ID (" << rnid << ") P (" ;
                msg << node->nodeDefinition << ")" ;
                logMsgT(__func__,msg.str(),2,LOGFILE);
                msg.str("");
        }
        for(unsigned i=0; i<node->nodeChildren.size(); i++)
        {
                predicatesChild = getPredicatesNode(node->nodeChildren[i]);
                predicates.insert (predicates.end(),predicatesChild.begin(),predicatesChild.end());
        }
        return predicates;
}

//////////////////////////////////////////////////////////////
// QP getPredicatesOver function definition
//////////////////////////////////////////////////////////////
vector<string> QueryPlan::getPredicatesOver(vector<string> rattrib)
{
        stringstream msg;
        vector<string> predicatesOver;
        for(unsigned i=0; i<rattrib.size(); i++)
        {
                msg << "\n\t\t\tChecking A (" << rattrib[i] << ") on GPL";
                for (unsigned j=0; j<generalPredicateList.pList.size(); j++)
                {
                        if(find(generalPredicateList.pList.begin(),generalPredicateList.pList.end(),rattrib[i]) == generalPredicateList.pList.end())
                        {
                                if(find(predicatesOver.begin(), predicatesOver.end(), generalPredicateList.pList[i])==predicatesOver.end())
                                {
                                        predicatesOver.push_back(generalPredicateList.pList[i]);
                                        msg << "\n\t\t\t\t Found A on GPL - Predicate (" << generalPredicateList.pList[i] << ") Added to POA List" ;
                                }
                        }
                }
        }
        logMsgT(__func__,msg.str(),2,LOGFILE);
        return predicatesOver;
}

//////////////////////////////////////////////////////////////
// QP subtractLists function definition
//////////////////////////////////////////////////////////////
vector<string> QueryPlan::subtractLists(vector<string> ra, vector<string> rb)
{
        string* a = &ra[0];
        string* b = &rb[0];
        vector<string> sub(ra.size()+rb.size());
        vector<string>::iterator it;
        sort (a,a+ra.size());
        sort (b,b+rb.size());
        it=set_difference (a, a+ra.size(), b, b+rb.size(), sub.begin());
        sub.resize(it-sub.begin());
        return sub;
}

//////////////////////////////////////////////////////////////
// QP intersectLists function definition
//////////////////////////////////////////////////////////////
vector<string> QueryPlan::intersectLists(vector<string> ra, vector<string> rb)
{
        string* a = &ra[0];
        string* b = &rb[0];
        vector<string> sub(ra.size()+rb.size());
        vector<string>::iterator it;
        sort (a,a+ra.size());
        sort (b,b+rb.size());
        it=set_intersection (a, a+ra.size(), b, b+rb.size(), sub.begin());
        sub.resize(it-sub.begin());
        return sub;
}

//////////////////////////////////////////////////////////////
// QP unionLists function definition
//////////////////////////////////////////////////////////////
vector<string> QueryPlan::unionLists(vector<string> ra, vector<string> rb)
{
        string* a = &ra[0];
        string* b = &rb[0];
        vector<string> sub(ra.size()+rb.size());
        vector<string>::iterator it;
        sort (a,a+ra.size());
        sort (b,b+rb.size());
        it=set_union (a, a+ra.size(), b, b+rb.size(), sub.begin());
        sub.resize(it-sub.begin());
        return sub;
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
	msg << "Ned Node:ID (" << rnid << ") PID (" << rpid << ") TYPE (" << rtype << ") DEF (" << rdef << ")";
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
        msg << "Creating Predicate List: GPL and CPL";
        logMsgT(__func__, msg.str() ,2,LOGFILE);
        msg.str("");
        for (map<int,NodeQP>::const_iterator it=nodeList.begin(); it!=nodeList.end(); ++it)
        {
                if (it->second.nodeType.compare("P") == 0)
                {
                        generalPredicateList.addPredicate(it->second.nodeDefinition);
                        msg << "\n\t\t\tAdded predicate to GPL - Node: (" << it->first;
                        msg << ") TYPE: (" << it->second.nodeType << ") P: (" << it->second.nodeDefinition << ")" ;
                        if (it->second.nodeDefinition.find("AND") != std::string::npos)
                        {
                                conjPredicateList.addPredicate(it->second.nodeDefinition);
                                msg << "\n\t\t\tAdded predicate to CPL - Node: (" << it->first;
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
        msg << "\n\t\t\tChecking Node ID (" << rnid << ") Type (" << node->nodeType << ")";
        if (node->nodeType.compare("P") == 0)
        {
                while (getline(predicateF, p, ','))
                {
                        if (p.compare("<") != 0 and p.compare(">") != 0 and p.compare("AND") != 0)
                        {
                                attribList.push_back(p);
                                msg << "\n\t\t\t\tAdded ATTRIB From ID (" << rnid << ") A (" ;
                                msg << p << ")" ;
                        }
                }
        }
        logMsgT(__func__,msg.str(),2,LOGFILE);
        msg.str("");
        for(unsigned i=0; i<node->nodeChildren.size(); i++)
        {
                attribListChild = getAttributes(node->nodeChildren[i]);
                attribList.insert (attribList.end(),attribListChild.begin(),attribListChild.end());
        }
        return attribList;
}

//////////////////////////////////////////////////////////////
// QP getAttributes function definition
//////////////////////////////////////////////////////////////
vector<string> QueryPlan::getAttributes (string rdef)
{
        stringstream msg;
        string p;
        istringstream predicateF(rdef);
        vector<string> attribList;
        msg << "\n\t\t\tChecking A (" << rdef << ") to extract attributes";
        while (getline(predicateF, p, ','))
        {
                if (p.compare("<") != 0 and p.compare(">") != 0 and p.compare("AND") != 0)
                {
                        attribList.push_back(p);
                        msg << "\n\t\t\t\tAdded ATTRIB (" << p << ")" ;
                }
        }
        logMsgT(__func__,msg.str(),2,LOGFILE);
        return attribList;
}


//////////////////////////////////////////////////////////////
// logMsgT function definition
//////////////////////////////////////////////////////////////
void QueryPlan::getAip (void)
{
        stringstream msg;
        vector<string> predInN, predOverC, predP, attribA, attribC, attribP, aip, tmpsrc;
        for (map<int,NodeQP>::const_iterator n=nodeList.begin(); n!=nodeList.end(); ++n)
        {
                msg << "\n\t\tIter Node (" << n->first << ")" << endl;
                logMsgT(__func__,msg.str(),2,LOGFILE);
                msg.str("");
                if (n->second.nodeType.compare("O-JOIN") == 0)
                {
                        predInN   = getPredicatesNode(n->first);
                        for(unsigned c=0; c<n->second.nodeChildren.size(); c++)
                        {
                                msg << "\n\t\t\tIter Child (" << n->second.nodeChildren[c] << ")";
                                logMsgT(__func__,msg.str(),2,LOGFILE);
                                msg.str("");
                                attribC = getAttributes(n->second.nodeChildren[c]);
                                predOverC = getPredicatesOver(attribC);
                                predP = intersectLists(subtractLists(predOverC,predInN),generalPredicateList.pList);
                                for(unsigned p=0; p<predP.size(); p++)
                                {
                                        attribP = getAttributes(predP[p]);
                                        attribA = intersectLists(attribP,attribC);
                                        for(unsigned a=0; a<attribA.size(); a++)
                                        {
                                                string p;
                                                stringstream src,att, nid;
                                                att << attribA[a];
                                                nid << n->first;
                                                istringstream attrF(att.str());
                                                src << n->first << ",";
                                                msg << "Added N (" << nid.str() << ") to sources";
                                                while (getline(attrF, p, ','))
                                                {
                                                        if (p.compare(nid.str()) != 0)
                                                        {
                                                                src << src << p << ",";
                                                                msg << "Appending source (" << p << ")";
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }
}

//////////////////////////////////////////////////////////////
// QueryPlan::createSources function definition
//////////////////////////////////////////////////////////////
void QueryPlan::createSources (void)
{
        string p;
        stringstream msg;
        for (map<int,NodeQP>::const_iterator it=nodeList.begin(); it!=nodeList.end(); ++it)
        {
                msg << "\n\t\t\tExtracting Attrib from Node ID (" << it->first << ") Type (" << it->second.nodeType << ")";
                istringstream predicateF(it->second.nodeDefinition);
                if (it->second.nodeType.compare("P") == 0)
                {
                        while (getline(predicateF, p, ','))
                        {
                                if (p.compare("<") != 0 and p.compare(">") != 0 and p.compare("AND") != 0)
                                {
                                        stringstream tmpid;
                                        tmpid << "," << it->first << ",";
                                        if (sources.find(p) == sources.end())
                                        {
                                                stringstream src;
                                                src << it->first;
                                                sources.insert(pair<string,string>(p,src.str()));
                                                msg << "\n\t\t\t\tAdded NEW Source (" << it->first << ") to A (" << p << ")" ;
                                        }
                                        else
                                        {
                                                stringstream src;
                                                src << sources.at(p) << "," << it->first;
                                                sources[p] = src.str() ;
                                                msg << "\n\t\t\t\tAdded Source (" << it->first << ") to A (" << p << ") UPD (" << src.str() << ")" ;
                                        }

                                }
                        }
                }
        }
        logMsgT(__func__,msg.str(),2,LOGFILE);
        msg.str("");
}

//////////////////////////////////////////////////////////////
// showMap function definition
//////////////////////////////////////////////////////////////
void QueryPlan::showMapSources (void)
{
        stringstream msg;
        msg << "\n\t\t\tSOURCES LIST";
        msg << "\n\t\t\t------------";
        for (map<string,string>::const_iterator it=sources.begin(); it!=sources.end(); ++it)
        {
                msg << "\n\t\t\t ID: (" << it->first << ") SRC (" << it->second << ")";
        }
        msg << endl;
        logMsgT(__func__,msg.str(),2,LOGFILE);
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
