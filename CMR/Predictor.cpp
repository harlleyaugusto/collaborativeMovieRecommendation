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


/**
*    Funcao auxiliar para fazer a ordenacao dos items mais similares
*/
bool greaterFirst (double i, double j) { return (i > j) ; }


/**
*    Funcao que implementa a filtragem colaborativa baseada em item
     Parametros:    userId: usuario que se deseja fazer a predicao
                    itemId: item a ser feito a predicao
                    matUtility: matriz de utilidade
                    users: map com os dados dos usuarios
                    items: map com os dados dos items
                    sims: matriz com as similaridades dos itens ja calculadas
     Retorno:       pred: a predicao do itemId para o userId
*/


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

        //O item que se deseja calcular o score eh comparado com os items que o usuario avaliou previamente
        for (list<int>::iterator it=users[userId].items.begin(); it != users[userId].items.end() ; ++it)
        {
            // Se a similaridade dos itens não estiverem sido calculada, é feito o calculo
            if (sims[itemIdPos][*it] == -1)
            {
                sim = s.cosineItem(matUtility, itemIdPos, *it, items[itemId].users);
                sims[itemIdPos][*it] = sim;
                sims[*it][itemIdPos] = sim;
            }
            else
            {// Caso contrario, a similaridade é obtida da matriz de similiridade
                sim = sims[itemIdPos][*it];
            }
            similarItems.push_back(sim);
            simToItems[sim] = make_pair(userIdPos, *it);
        }

        //Ordena os items pela similaridade
        sort(similarItems.begin(), similarItems.end(), greaterFirst);

        //Calculo da predicao com os k itens mais similares
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

/**
*    Funcao que implementa a filtragem colaborativa baseada em usuario
     Parametros:    userId: usuario que se deseja fazer a predicao
                    itemId: item a ser feito a predicao
                    matUtility: matriz de utilidade
                    users: map com os dados dos usuarios
                    items: map com os dados dos items
     Retorno:       pred: a predicao do itemId para o userId
*/

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

        //Calculo da similaridade dos ususario com os usuarios que avaliaram o itemId
        for (list<int>::iterator it=items[itemId].users.begin(); it != items[itemId].users.end() ; ++it)
        {
            sim = s.cosineUser(matUtility, userIdPos, *it, users[userId].items);
            similarUser.push_back(sim);
            simToUser[sim] = make_pair(*it, itemIdPos);
        }
         //Ordena os usuarios pela similaridade
        sort(similarUser.begin(), similarUser.end(), greaterFirst);

        //Calculo da predicao com os k usuarios mais similares
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
