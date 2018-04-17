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
    
    /**
        Reader r: objeto responsavel por obter os dados de entrada 
    */
    Reader r;

    /** 
        Predictor p: objeto resposavel pela a predicao dos scores de cada item. 
    */
    Predictor p;

    string fileRatings = argv[1];
    string fileTargets = argv[2];
    double** simsItems;

    /** 
        Hash maps para armazenar os dados dos usuarios e dos items 
    */
    map<int, User> users;
    map<int, Item> items;


    map<string, string> stringTargets;

    // Leitura dos dados contidos em ratings.csv
    double** matUtility = r.readRatings(users, items, fileRatings);

    //Leitura dos dados contidos em targets.csv
    map<pair<int, int>, double> targets = r.readTarget(fileTargets, stringTargets);
   
    
    /**
        Matriz simsItem armazena as similaridade entre os items 
        com objetivo de nao computar as similaridades dos items 
        ja computados
    */
    simsItems = new double *[items.size()];
    for(unsigned int i = 0; i < items.size(); i++)
        simsItems[i] = new double[items.size()];


    for (unsigned int i = 0 ; i < items.size() ;i++)
        for (unsigned int j = 0 ; j < items.size() ; j++)
            simsItems[i][j] =-1;

    double pred;
    ostringstream str1;
    ostringstream str2;


    /**
        Inicio da computacao das predicoes contidas no artigo targets.csv
    */
    cout << "UserId:ItemId,Prediction";
    for(map<pair<int,int>,double>::iterator it=targets.begin(); it!=targets.end(); ++it)
    {
        //Para cada linha no arquivo targets.csv eh feita a predicao
        pred = p.itemBasedPredictor(it->first.first, it->first.second, matUtility, users, items, simsItems);

        str1 << it->first.first;
        str2 << it->first.second;

        cout << '\n' << stringTargets[(str1.str() +  str2.str())] << "," << pred;

        str1.str("");
        str1.clear();

        str2.str("");
        str2.clear();
  
    }


    /*Essa parte esta comentada, pois eh destinada a predicao utilizando user-based CF. Como a predicao
    com melhor resultado no Kaggle foi a item-based CF, deixei o codigo como gerou a predicao que esta no Kaggle. */

    
/*
    for(map<pair<int,int>,double>::iterator it=targets.begin(); it!=targets.end(); ++it)
    {
        pred = p.userBasedPredictor(it->first.first, it->first.second, matUtility, users, items);
        total++;

        str1 << it->first.first;
        str2 << it->first.second;

        cout << '\n' << stringTargets[(str1.str() +  str2.str())] << "," << pred;

        str1.str("");
        str1.clear();

        str2.str("");
        str2.clear();
  
    }*/
    return 0;
}
