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
    double** sims;

    int total = 0;

    map<int, User> users;
    map<int, Item> items;

    map<string, string> stringTargets;

    double** matUtility = r.readRatings(users, items, fileRatings);
    map<pair<int, int>, double> targets = r.readTarget(fileTargets, stringTargets);
   

    cout << "File... (done)\n";

    Similarity s;
    total = 0;

      cout << "Similarity matrix";
    sims = new double *[items.size()];
    for(int i = 0; i < items.size(); i++)
        sims[i] = new double[items.size()];


    for (int i = 0 ; i < items.size() ;i++)
        for (int j = 0 ; j < items.size() ; j++)
            sims[i][j] =-1;


    double pred;
     ostringstream str1;
     ostringstream str2;
   for(map<pair<int,int>,double>::iterator it=targets.begin(); it!=targets.end(); ++it)
    {
        pred = p.itemBasedPredictor(it->first.first, it->first.second, matUtility, users, items, sims);
        total++;
        //cout << "u" << << ":" << "i" << it->first.second << "," << pred << '\n';

        str1 << it->first.first;
        str2 << it->first.second;
        
        cout << stringTargets[(str1.str() +  str2.str())] << "," << pred << '\n';

        str1.str("");
        str1.clear();

        str2.str("");
        str2.clear();
        
        //cout << "total: " << total<< '\n';


       // cout << "user: " << it->first << " item: " << it->second <<'\n';
        //cin.get();
    }

    return 0;
}
