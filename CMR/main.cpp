#include <iostream>
#include "Reader.h"
#include "Similarity.h"
#include "Item.h"
#include "User.h"
#include <map>
#include <list>
#include "User.h"
#include "Predictor.h"
#include <string>
#include <iostream>
#include <sstream>


using namespace std;

int main(int argc, const char * argv[])
{
    Reader r;
    Predictor p;

    string fileRatings = argv[1];
    string fileTargets = argv[2];
    double** simsItems;

    int total = 0;

    map<int, User> users;
    map<int, Item> items;

    map<string, string> stringTargets;

    double** matUtility = r.readRatings(users, items, fileRatings);
    map<pair<int, int>, double> targets = r.readTarget(fileTargets, stringTargets);
   
    Similarity s;
    total = 0;

    simsItems = new double *[items.size()];
    for(unsigned int i = 0; i < items.size(); i++)
        simsItems[i] = new double[items.size()];


    for (unsigned int i = 0 ; i < items.size() ;i++)
        for (unsigned int j = 0 ; j < items.size() ; j++)
            simsItems[i][j] =-1;

    double pred;
     ostringstream str1;
     ostringstream str2;

    cout << "UserId:ItemId,Prediction";
    for(map<pair<int,int>,double>::iterator it=targets.begin(); it!=targets.end(); ++it)
    {
        pred = p.itemBasedPredictor(it->first.first, it->first.second, matUtility, users, items, simsItems);
        total++;

        str1 << it->first.first;
        str2 << it->first.second;

        cout << '\n' << stringTargets[(str1.str() +  str2.str())] << "," << pred;

        str1.str("");
        str1.clear();

        str2.str("");
        str2.clear();
  
    }

/*
    for(map<pair<int,int>,double>::iterator it=targets.begin(); it!=targets.end(); ++it)
    {
        pred = p.userBasedPredictor(it->first.first, it->first.second, matUtility, users, items);
        total++;

        str1 << it->first.first;
        str2 << it->first.second;

        cout << '\n' << stringTargets[(str1.str() +  str2.str())] << "," << pred;

        str1.str("");
        str1.clear();

        str2.str("");
        str2.clear();
  
    }*/
    return 0;
}
