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

    int MAX_USER =100000;
    int userTotal = 0;

    vector<double> similarItems;
    map<double, pair<int, int> > simToItems;


    if(items.find(itemId) != items.end())
    {
        int userIdPos = users[userId].id;
        int itemIdPos = items[itemId].id;

        for (list<int>::iterator it=users[userId].items.begin(); it != users[userId].items.end() ; ++it)
        {
            if (sims[itemIdPos][*it] == -1)
            {
                sim = s.CosineItem(matUtility, itemIdPos, *it, items[itemId].users);
                sims[itemIdPos][*it] = sim;
                sims[*it][itemIdPos] = sim;
            }
            else
            {
                sim = sims[itemIdPos][*it];
            }
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
      
        if (users[userId].items.size() > 0) return users[userId].getMean();
        else return 0.0;
    }

    pred = users[userId].getMean() + (num/den);


    if (den == 0 && num == 0)
    {
        if(items[itemId].ratings.size() != 0) return items[itemId].getMean();
        if (users[userId].items.size() != 0) return users[userId].getMean(); 
        else return 0.0;
    } 
    else return  pred;

}


double Predictor::userBasedPredictor(int userId, int itemId, double **matUtility, map<int, User> &users, map<int, Item> &items)
{

    Similarity s;
    double sim = 0.0, pred = 0.0, num = 0.0, den = 0.0;

    int MAX_ITEM = 10;
    int itemTotal = 0;

    vector<double> similarUser;
    map<double, pair<int, int> > simToUser;


    if(users.find(userId) != users.end())
    {
        int userIdPos = users[userId].id;
        int itemIdPos = items[itemId].id;

        for (list<int>::iterator it=items[itemId].users.begin(); it != items[itemId].users.end() ; ++it)
        {
            sim = s.CosineUser(matUtility, userIdPos, *it, users[userId].items);
            similarUser.push_back(sim);
            simToUser[sim] = make_pair(*it, itemIdPos);
        }
        sort(similarUser.begin(), similarUser.end(), greaterFirst);
        for (vector<double>::iterator it=similarUser.begin(); it!=similarUser.end() && itemTotal < MAX_ITEM; ++it)
        {
        
            num += *it * matUtility[simToUser[*it].first][simToUser[*it].second];
            den += abs(*it);
            itemTotal++;
        }
    }
    else 
    {
      
        if (items[itemId].users.size() > 0) return items[itemId].getMean();  
        else return 0.0;
    }

    pred = users[userId].getMean() + (num/den);
    if(pred != pred)
    {

        if (users[userId].items.size() != 0) return users[userId].getMean();
        else if(items[itemId].ratings.size() != 0)  return items[itemId].getMean();
        else return 0.0;

    }
  
    else return  pred;

}
