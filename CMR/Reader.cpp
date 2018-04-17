#include "Reader.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "Item.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <map>



using namespace std;


Reader::Reader()
{

}

Reader::~Reader()
{
    //dtor
}



/**
   Funcao responsavel por ler o arquivo rating.csv
        
        parametros: map de usuarios, item e o nome do arquivo
        retorno: matriz de utililidade com os ratings. Cada usuario e item sao mapeados 
        em uma linha (usuario) e uma coluna da matriz (item). 
*/
double** Reader::readRatings(map<int, User> &users, map<int, Item> &items, string file)
{
    ifstream inFile;
    string line;
    string s_user;
    string s_item;
    string s_rating;

    int userId, uMatId = 0;     /* userId = id do usuario. uMatId = id do usuario mapeado para matriz */
    int itemId, iMatId = 0;     /* itemId = id do item. iMatId = id do item mapeado para matriz */
    double rating;

   inFile.open(("../files/" + file).c_str());


    getline(inFile, line);

    /* Obtecao dos dados dos usuarios e items */
    while(!inFile.eof())
    {
        getline(inFile, line);

        if(!line.empty())
        {

            s_user = line.substr(1, line.find(":"));

            s_item = line.substr(line.find(":") + 2, (line.find(",") - line.find(":") - 2));

            s_rating = line.substr(line.find(",") + 1, line.length() - line.find(","));

            replace( s_rating.begin(), s_rating.end(), ',', '.');

            userId = atoi(s_user.c_str());
            itemId = atoi(s_item.c_str());
            rating = atof(s_rating.c_str());

            if(items.find(itemId) == items.end())
            {
                items[itemId].id = iMatId;
                if(users.find(userId) == users.end())
                {
                    users[userId].id = uMatId;
                    items[itemId].users.push_back(uMatId);
                    uMatId++;
                    users[userId].items.push_back(iMatId);
                    users[userId].calculateMean(rating);
                }
                else
                {
                    users[userId].items.push_back(iMatId);
                    items[itemId].users.push_back(users[userId].id);
                    users[userId].calculateMean(rating);
                }
                iMatId++;
            }
            else
            {
                if(users.find(userId) == users.end())
                {
                    users[userId].id = uMatId;
                    items[itemId].users.push_back(uMatId);
                    uMatId++;
                    users[userId].items.push_back(items[itemId].id);
                    users[userId].calculateMean(rating);
                }
                else
                {
                    users[userId].items.push_back(items[itemId].id);
                    items[itemId].users.push_back(users[userId].id);
                    users[userId].calculateMean(rating);
                }
            }

            items[itemId].addRating(userId, rating);
        }
    }


    /* Preenchimento da matriz de utilidade */
    double **mat = new double *[users.size()];

    for(unsigned int i = 0; i < users.size(); i++)
        mat[i] = new double[items.size()];

    /* Para o calculo do conseno eh feito a subtracao da nota do item com a media de nota do usuario */
    for(map<int,Item>::iterator it=items.begin(); it!=items.end(); ++it)
    {
        for (map<int, double>::iterator itt = it->second.ratings.begin(); itt != it->second.ratings.end() ; ++itt)
        {
            mat[users[itt->first].id][items[it->first].id] = itt->second - (users[itt->first].getMean());
        }

    }

    inFile.close();
    return mat;
}


/**
    Funcao que faz o parser no arquivo targets.csv
        parametros: nome do arquivo targets.scv, e o map para guardar cada linha contido no arquivo targets.csv
        retorno: map com a tupla idUser e idItem
*/

map<pair<int, int>, double> Reader::readTarget(string file, map<string, string> &stringTargets)
{
    ifstream inFile;
    string line;
    string s_user;
    string s_item;

    ostringstream str1;
    ostringstream str2;

    int userId;
    int itemId;

    map<pair<int, int>, double> targets;

    inFile.open(("../files/" + file).c_str());

    getline(inFile, line);

    while(!inFile.eof())
    {
        getline(inFile, line);
        if(!line.empty())
        {

            s_user = line.substr(1, line.find(":"));
            s_item = line.substr(line.find(":") + 2, (line.find(",") - line.find(":") - 2));

            userId = atoi(s_user.c_str());
            itemId = atoi(s_item.c_str());

            str1 << userId;
            str2 << itemId;

            stringTargets[(str1.str() +  str2.str())] = line;
        
            str1.str("");
            str1.clear();

            str2.str("");
            str2.clear();

            targets[make_pair(userId, itemId)] = 0.0;

        }
    }
    inFile.close();
    return targets;
}


