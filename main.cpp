#include <iostream>
#include "dbtp.h"
using namespace std;

//////////////////////////////////////////////////////////////
// Main Function
//////////////////////////////////////////////////////////////
int main ()
{
	NodeQP node1(0,1);
	NodeQP node2(1,2);

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
