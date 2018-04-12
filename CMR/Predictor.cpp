#include "Predictor.h"
#include <map>
#include "Item.h"
#include "Similarity.h"
#include <iostream>

using namespace std;

Predictor::Predictor()
{
    //ctor
}

Predictor::~Predictor()
{
    //dtor
}


double Predictor::itemBasedPredictor(int userId, int itemId, double **matUtility, map<int, User> &users, map<int, Item> &items,
                                     map<pair<int, int>, double> &sims)
{

    Similarity s;
    double sim = 0.0, pred = 0.0, num = 0.0, den = 0.0;
    int qtd = 0;
    int qtdItem = 10;
    int currentIdItem;

    if(items.find(itemId) != items.end())
    {
        int userIdPos = users[userId].id;
        int itemIdPos = items[itemId].id;

        for (list<int>::iterator it=users[userId].items.begin(); it != users[userId].items.end() ; ++it)
        {
            //currentIdItem = items[*it].id;
            sim = s.Cosine(matUtility, itemIdPos, *it, users[userId].items);

            num += sim * matUtility[userIdPos][*it] ;
            den += sim;
        }
    }
    else
    {

        return 0.0;
    }

    pred = num/den;

    //cout << "pred: " << pred << '\n';
    //cin.get();

    return pred;
}
