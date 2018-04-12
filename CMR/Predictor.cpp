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


double Predictor::ItemBasedPredictor(int userId, int itemId, map<int, Item> &matUtility, map<int, User> &users,
                                     map<pair<int, int>, double> &sims)
{

    Similarity s;
    double sim = 0.0, pred = 0.0, num = 0.0, den = 0.0;
    int qtd = 0;
    int qtdItem = 10;


    for (list<int>::iterator it=users[userId].items.begin(); it != users[userId].items.end() && qtd < qtdItem; ++it)
    {
        //cout << "User: " << userId << " Item i: " << itemId <<" Item j: " << *it << '\n';
        if ( sims.find(make_pair(itemId, *it)) != sims.end() &&  sims.find(make_pair(*it, itemId)) != sims.end()) {
            sim = sims[make_pair(itemId, *it)];
             //cout << "Nao Calculado\n";

        } else {
             sim = s.Cosine(matUtility[itemId], matUtility[*it]);
             sims[make_pair(itemId, *it)] =  sim;
             sims[make_pair(*it, itemId)] =  sim;
             //cout << "---Calculado\n";
        }
        num += sim * matUtility[*it].ratings[userId] ;
        den += sim;
        qtd++;

        /*cout << "matUtility[*it].ratings[userId]: " << matUtility[*it].ratings[userId] << '\n';
        cout << "sim: " << sim << '\n';
        cout << "num: " << num << '\n';
        cout << "den: " << den << '\n';
*/
         //cin.get();
    }

    pred = num/den;

    //cout << "pred: " << pred << '\n';
    //cin.get();

    return pred;
}
