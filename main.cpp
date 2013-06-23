#include <iostream>
#include <vector>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bloom_filter.hpp"
#include "Tables.h"
#include "dbtp.h"

using namespace std;


int main()
{

        /************************************************************************************************/
        /************************************************************************************************/

	/*******************************************************/
        /*** Creation of Query Plan for Example 1           ****/
        /*******************************************************/

        QueryPlan queryPlan;
        queryPlan.addNode(0,0,"O-JOIN","T1.BLcode");
        queryPlan.addNode(1,0,"O-JOIN","T5.BLcode");
        queryPlan.addNode(2,1,"T1","T1.BLcode,T1.country");
        queryPlan.addNode(3,1,"P","T2.year,>,2000");
        queryPlan.addNode(4,3,"T2","T2.BLcode,T2.year");
        queryPlan.addNode(5,0,"O-JOIN","T6.BLcode");
        queryPlan.addNode(6,5,"P","T3.ep,>,40");
        queryPlan.addNode(7,6,"T3","T3.BLcode,T3.ep,T3.year");
        queryPlan.addNode(8,5,"P","T4.yr_sch,>,9");
        queryPlan.addNode(9,8,"T4","T4.BLcode,T4.yr_sch");
        /******************************************************/
        /** Source-Graph for transitively equated predicates **/
        /******************************************************/
        queryPlan.attributesEq.push_back("T1.BLcode,=,T2.BLcode");
        queryPlan.attributesEq.push_back("T1.BLcode,=,T3.BLcode");
        queryPlan.attributesEq.push_back("T1.BLcode,=,T4.BLcode");

        /*******************************************************/
        /** Execution                                         **/
        /*******************************************************/
        queryPlan.createPredLists();
        queryPlan.createSources();
        queryPlan.showVector("GENERAL PREDICATE LIST",queryPlan.generalPredicateList.pList);
        queryPlan.showVector("CONJ PREDICATE LIST",queryPlan.conjPredicateList.pList);
        queryPlan.showMapSources();
        queryPlan.getAip();
        queryPlan.showMapSources();
        queryPlan.showMapInterestedIn();
        /************************************************************************************************/
        /************************************************************************************************/

	/*******************************************************/
        /*** Creation of Query Plan for Example 1           ****/
        /*******************************************************/

        /************************************************************************************************/
        /************************************************************************************************/

        float time1, time2, time3, time4, time5, time6, time7;
        clock_t start, end;
        unsigned long long int bloom_filter5_size;
        unsigned long long int bloom_filter6_size;
        unsigned long long int bloom_filter7_size;
        bloom_parameters parameters;
        parameters.false_positive_probability = 1.0/100.0;

        table BL2013_F;
        table BL2013_F1599;
        table BL2013_F2599;
        table BL2013_MF;
        table BL2013_MF1599;
        table BL2013_MF2599;
        table t1, t2, t3, t4, t5, t6, t7;

        std::vector <std::string> f1, f2, f3, f4;
        f1.push_back("BLcode");
        f1.push_back("country");

        f2.push_back("BLcode");
        f2.push_back("country");

        f3.push_back("BLcode");
        f3.push_back("lp");
        f3.push_back("year");

        f4.push_back("BLcode");
        f4.push_back("yr_sch");


        loadTable("Education/BL2013_F.csv", &BL2013_F);
        loadTable("Education/BL2013_F1599.csv", &BL2013_F1599);
        loadTable("Education/BL2013_F2599.csv", &BL2013_F2599);
        loadTable("Education/BL2013_MF.csv", &BL2013_MF);
        loadTable("Education/BL2013_MF1599.csv", &BL2013_MF1599);
        loadTable("Education/BL2013_MF2599.csv", &BL2013_MF2599);

        start = clock();
        t1 = SELECT(BL2013_MF1599, f1);
        end = clock();
        time1 = (float)(end-start)/CLOCKS_PER_SEC;

        start = clock();
        t2 = SELECT(BL2013_MF2599, f2);
        int k;
        //Filter T2
        k=0;
        while(k<t2.tuples.size())
        {
                if(t2.tuples[k][1] <= "C")
                        t2.tuples.erase(t2.tuples.begin()+k);
                else k++;
        }
        end = clock();
        time2 = (float)(end-start)/CLOCKS_PER_SEC;

        start = clock();
        t3 = SELECT(BL2013_F1599, f3);
        end = clock();
        time3 = (float)(end-start)/CLOCKS_PER_SEC;

        start = clock();
        t4 = SELECT(BL2013_F2599, f4);
        end = clock();
        time4 = (float)(end-start)/CLOCKS_PER_SEC;


        start = clock();
        t6 = JOIN(t3,t4,"BLcode");
        end = clock();
        time6 = (float)(end-start)/CLOCKS_PER_SEC;

        start = clock();
        t5 = JOIN(t1,t2,"BLcode");
        end = clock();
        time5 = (float)(end-start)/CLOCKS_PER_SEC;

        start = clock();
        t7 = JOIN(t5,t6,"BLcode");
        end = clock();
        time7 = (float)(end-start)/CLOCKS_PER_SEC;

        //Info T1
        float tr = 0;
        for(int i=0; i<t1.tuples.size(); i++)
        for(int j=0; j<t1.tuples[i].size(); j++)
        {
                tr+=t1.tuples[i][j].size();
        }
        tr /= 1024;
        cout<<"\nt1 = "<<tr<<" KBytes"<<endl;
        cout<<"time1 = "<<time1<<endl;

        //Info T2
        tr = 0;
        for(int i=0; i<t2.tuples.size(); i++)
        for(int j=0; j<t2.tuples[i].size(); j++)
        {
                tr+=t2.tuples[i][j].size();
        }
        tr /= 1024;
        cout<<"\nt2 = "<<tr<<" KBytes"<<endl;
        cout<<"time2 = "<<time2<<endl;

        //Info T3
        tr = 0;
        for(int i=0; i<t3.tuples.size(); i++)
        for(int j=0; j<t3.tuples[i].size(); j++)
        {
                tr+=t3.tuples[i][j].size();
        }
        tr /= 1024;
        cout<<"\nt3 = "<<tr<<" KBytes"<<endl;
        cout<<"time3 = "<<time3<<endl;

        //Info T4
        tr = 0;
        for(int i=0; i<t4.tuples.size(); i++)
        for(int j=0; j<t4.tuples[i].size(); j++)
        {
                tr+=t4.tuples[i][j].size();
        }
        tr /= 1024;
        cout<<"\nt4 = "<<tr<<" KBytes"<<endl;
        cout<<"time4 = "<<time4<<endl;

        //Info T5
        tr = 0;
        for(int i=0; i<t5.tuples.size(); i++)
        for(int j=0; j<t5.tuples[i].size(); j++)
        {
                tr+=t5.tuples[i][j].size();
        }
        tr /= 1024;
        cout<<"\nt5 = "<<tr<<" KBytes"<<endl;
        cout<<"time5 = "<<time5<<endl;
        //    bloom_filter5_size = filter_t5.size();
        cout<<"Bloom5 size = "<<(float)bloom_filter5_size / (8 * 1024)<<"KBytes \n";

        //Info T6
        tr = 0;
        for(int i=0; i<t6.tuples.size(); i++)
        for(int j=0; j<t6.tuples[i].size(); j++)
        {
                tr+=t6.tuples[i][j].size();
        }
        tr /= 1024;
        cout<<"\nt6 = "<<tr<<" KBytes"<<endl;
        cout<<"time6 = "<<time6<<endl;
        //    bloom_filter6_size = filter_t6.size();
        cout<<"Bloom6 size = "<<(float)bloom_filter6_size / (8 * 1024)<<"KBytes \n";

        //Info T7
        tr = 0;
        for(int i=0; i<t7.tuples.size(); i++)
        for(int j=0; j<t7.tuples[i].size(); j++)
        {
                tr+=t7.tuples[i][j].size();
        }
        tr /= 1024*1024;
        cout<<"\nt7 = "<<tr<<" MBytes"<<endl;
        cout<<"time7 = "<<time7<<endl;

    return 0;
}


