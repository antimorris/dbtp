#include <iostream>
#include "dbtp.h"
using namespace std;

//////////////////////////////////////////////////////////////
// Main Function
//////////////////////////////////////////////////////////////
int main ()
{
	// *************************************
        // Creation of Query Plan for Example 1
        // *************************************
        QueryPlan queryPlan;
        queryPlan.addNode(0,0,"O","JOIN,partkey");
        queryPlan.addNode(1,0,"O","DISTINCT,partkey");
        queryPlan.addNode(2,1,"O","PROJECTION,partkey");
        queryPlan.addNode(3,2,"P","2*supplycost,<,retailprice");
        queryPlan.addNode(4,3,"O","JOIN,retailprice");
        queryPlan.addNode(5,4,"T","P");
        queryPlan.addNode(6,4,"T","PS1");
        queryPlan.addNode(7,0,"P","10*avail,<,numsold");
        queryPlan.addNode(8,7,"O","JOIN,partkey");
        queryPlan.addNode(9,8,"O","SUM(availqty) as avail partkey");
        queryPlan.addNode(10,9,"T","PS2");
        queryPlan.addNode(11,8,"O","SUM(availqty) as numsold partkey");
        queryPlan.addNode(12,11,"P","receiptdate,>,2007-1-1,AND,OTHER");
        queryPlan.addNode(13,12,"T","L");
        queryPlan.createPredLists();

        // Show List of Nodes
        queryPlan.showNodeList();

        // Adding definition for predicate nodes


        // TEST for AIP Registry
	PredicateData aipRegistry;
	//aipRegistry.checkPredicate(0);
	aipRegistry.addPredicate(0,"preda",0);
	aipRegistry.addPredicate(1,"predb",1);
	aipRegistry.addPredicate(2,"predc",2);
	aipRegistry.addPredicate(3,"predd",3);
        aipRegistry.showFullRegistry();

        aipRegistry.checkPredicate(1);

        vector<string> att;
        att = queryPlan.getAttributes(2);
        queryPlan.showAttributes(2);

	exit(0);
}
