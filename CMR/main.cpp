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

int main()
{
    Reader r;
    Predictor p;

    int total = 0;

    map<int, User> users;
    map<int, Item> items;

    double** matUtility = r.readRatings(users, items);
    map<pair<int, int>, double> targets = r.readTarget();
    map<pair<int, int>, double> sims;

    cout << "File... (done)\n";

    Similarity s;
    total = 0;


   for(map<pair<int,int>,double>::iterator it=targets.begin(); it!=targets.end(); ++it)
    {
        p.itemBasedPredictor(it->first.first, it->first.second, matUtility, users, items, sims);
        total++;
        cout << "total: " << total<< '\n';
       // cout << "user: " << it->first << " item: " << it->second <<'\n';
        //cin.get();
    }

    return 0;
}
