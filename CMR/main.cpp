#include <iostream>
#include "Reader.h"
#include "Similarity.h"
#include "Item.h"
#include "User.h"
#include <map>
#include <list>
#include "User.h"
#include "Predictor.h"

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

    double** matUtility = r.readRatings(users, items, fileRatings);
    map<pair<int, int>, double> targets = r.readTarget(fileTargets);
   

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
   for(map<pair<int,int>,double>::iterator it=targets.begin(); it!=targets.end(); ++it)
    {
        pred = p.itemBasedPredictor(it->first.first, it->first.second, matUtility, users, items, sims);
        total++;
        cout << "u" << it->first.first << ":" << "i" << it->first.second << "," << pred << '\n';

        //cout << "total: " << total<< '\n';


       // cout << "user: " << it->first << " item: " << it->second <<'\n';
        //cin.get();
    }

    return 0;
}
