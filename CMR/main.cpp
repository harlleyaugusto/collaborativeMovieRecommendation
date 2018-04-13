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

    int total = 0;

    map<int, User> users;

    string fileRatings = argv[1];
    string fileTargets = argv[2];

    map<int, Item> matUtility = r.readRatings(users, fileRatings);
    map<pair<int, int>, double> targets = r.readTarget(fileTargets);
    map<pair<int, int>, double> sims;


    Similarity s;
    total = 0;


   for(map<pair<int,int>,double>::iterator it=targets.begin(); it!=targets.end(); ++it)
    {
        p.itemBasedPredictor(it->first.first, it->first.second, matUtility, users, sims);
        total++;
        cout << "Total: " << total << '\n';
       // cout << "user: " << it->first << " item: " << it->second <<'\n';
        //cin.get();
    }

    cout << "targets.size(): " << targets.size();
    return 0;
}
