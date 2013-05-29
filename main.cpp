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

        queryPlan.addPredicate(2,"p1,=,p2");
        queryPlan.addPredicate(2,"p2,=,p4");
        queryPlan.addPredicate(3,"p5,=,p6");
        queryPlan.addPredicate(4,"p7,=,p9");

        vector<string> att;
        cout << "Attributes --> ";
        att = queryPlan.getAttributes(2);
        for (unsigned i=0; i<att.size(); i++)
        {
                cout << "-" << att.at(i);
        }
        cout << endl;


        // TEST
        conjPredicateList.addPredicate("p1=p2");
        conjPredicateList.addPredicate("p2=p3");
        conjPredicateList.addPredicate("p2=p4");
        conjPredicateList.addPredicate("p4=p5");
        conjPredicateList.addPredicate("p5=p1");
        conjPredicateList.addPredicate("p6=p9");
        conjPredicateList.addPredicate("p9=p8");
        conjPredicateList.addPredicate("p8=p10");
        conjPredicateList.addPredicate("p4=p10");
        conjPredicateList.addPredicate("p0=p1");
        conjPredicateList.showFullRegistry();


	PredicateData aipRegistry;
	aipRegistry.showFullRegistry();
	aipRegistry.checkPredicate(0);

        //TEST
	aipRegistry.addPredicate(0,"preda",0);
	aipRegistry.addPredicate(1,"predb",1);
	aipRegistry.addPredicate(2,"predc",2);
	aipRegistry.addPredicate(3,"predd",3);

        aipRegistry.showFullRegistry();
        aipRegistry.checkPredicate(1);
	exit(0);
}
