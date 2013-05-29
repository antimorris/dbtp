#include <iostream>
#include "dbtp.h"
using namespace std;

//////////////////////////////////////////////////////////////
// Main Function
//////////////////////////////////////////////////////////////
int main ()
{
	PredicateList conjPredicateList;
        NodeQP queryPlan;
        queryPlan.initialize();
        queryPlan.addNode(1,'O');
        queryPlan.addNode(2,'P');
        queryPlan.addNode(1,'P');
        queryPlan.addNode(1,'O');
        queryPlan.addNode(1,'P');
        queryPlan.addNode(3,'P');
        queryPlan.addNode(3,'P');
        queryPlan.showNodeList();

        // TEST
        conjPredicateList.addPredicate("p1 = p2");
        conjPredicateList.addPredicate("p2 = p3");
        conjPredicateList.addPredicate("p2 = p4");
        conjPredicateList.addPredicate("p4 = p5");
        conjPredicateList.addPredicate("p5 = p1");
        conjPredicateList.addPredicate("p6 = p9");
        conjPredicateList.addPredicate("p9 = p8");
        conjPredicateList.addPredicate("p8 = p10");
        conjPredicateList.addPredicate("p4 = p10");
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
