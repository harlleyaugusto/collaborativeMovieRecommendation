#include "Predictor.h"
#include <map>
#include <cmath>
#include "Item.h"
#include "Similarity.h"
#include <iostream>
#include <vector> 
#include <algorithm>  

using namespace std;

Predictor::Predictor()
{
    //ctor
}

Predictor::~Predictor()
{
    //dtor
}



bool greaterFirst (double i, double j) { return (i>j); }

double Predictor::itemBasedPredictor(int userId, int itemId, double **matUtility, map<int, User> &users, map<int, Item> &items,
                                     double **sims)
{

    Similarity s;
    double sim = 0.0, pred = 0.0, num = 0.0, den = 0.0;
    int qtd = 0;
    int qtdItem = 10;
    int currentIdItem;

    int MAX_USER = 30;
    int userTotal = 0;

    vector<double> similarItems;
    map<double, pair<int, int> > simToItems;


    if(items.find(itemId) != items.end())
    {
        int userIdPos = users[userId].id;
        int itemIdPos = items[itemId].id;

        for (list<int>::iterator it=users[userId].items.begin(); it != users[userId].items.end() ; ++it)
        {
            userTotal++;
            if (sims[itemIdPos][*it] == -1)
            {
                sim = s.Cosine(matUtility, itemIdPos, *it, items[itemId].users);
                sims[itemIdPos][*it] = sim;
                sims[*it][itemIdPos] = sim;
            }
            else
            {
                sim = sims[itemIdPos][*it];
            }

            //num += sim * matUtility[userIdPos][*it] ;
            //den += abs(sim);
            similarItems.push_back(sim);
            simToItems[sim] = make_pair(userIdPos, *it);
        }
        sort(similarItems.begin(), similarItems.end(), greaterFirst);
        for (vector<double>::iterator it=similarItems.begin(); it!=similarItems.end() && userTotal < MAX_USER; ++it)
        {
            num += *it * matUtility[simToItems[*it].first][simToItems[*it].second];
            den += abs(*it);
            userTotal++;
        }
    }
    else 
    {
        //cout << "Item not found" << "\n";
        //cout << "userId: " << userId << " " << " itemId: " << itemId << "\n"; 
         //cout << "mean: " << users[userId].getMean() << "\n";
        //cin.get();
        if (users[userId].items.size() > 0) return users[userId].getMean();
        else return 0.0;
    }

   // if (den == 0) return  users[userId].getMean();
    pred = users[userId].getMean() + (num/den);
    

    //if (pred != pred)
    //{
        //cout << "pred: " << ((num/den) +  users[userId].getMean()) << "\n";
        //cout << "mean: " << users[userId].getMean() << "\n";
        //cout << "QtdItems: " << users[userId].items.size() << "\n";
        //cout << "userId: " << userId << " " << " itemId: " << itemId << "\n"; 
        //cin.get();
    //}

    if (den == 0 && num == 0)
    {
       // cout << "userId: " << userId << " " << " itemId: " << itemId << "\n"; 
        //cout << "mean: " << users[userId].getMean() << "\n";
        //cin.get();
        
        if(items[itemId].ratings.size() != 0) return items[itemId].getMean();
        if (users[userId].items.size() != 0) return users[userId].getMean(); 
        else return 0.0;
    } 
    else return  pred;

}
