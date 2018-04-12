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

    map<int, Item> matUtility = r.readRatings(users);
    map<pair<int, int>, double> targets = r.readTarget();
    map<pair<int, int>, double> sims;


   /* for(map<int,Item>::iterator it=matUtility.begin(); it!=matUtility.end(); ++it)
        for(map<int,double>::iterator itt=matUtility[it->first].ratings.begin(); itt!=matUtility[it->first].ratings.end(); ++itt)
            total++;
     cout << "Total: " << total << '\n';*/
/*
    for(map<int,User>::iterator it=users.begin(); it!=users.end(); ++it)
    {
        cout << "user: " << it->first << '\n';
        for (list<int>::iterator it2=users[it->first].items.begin(); it2 != users[it->first].items.end(); ++it2)
        {
             cout << *it2 << '\n';
        }
        cin.get();
    }
    /*

    */
    Similarity s;
    total = 0;


   for(map<pair<int,int>,double>::iterator it=targets.begin(); it!=targets.end(); ++it)
    {
        p.ItemBasedPredictor(it->first.first, it->first.second, matUtility, users, sims);
        total++;
        cout << "Total: " << total << '\n';
       // cout << "user: " << it->first << " item: " << it->second <<'\n';
        //cin.get();
    }

    cout << "targets.size(): " << targets.size();
    return 0;
}
