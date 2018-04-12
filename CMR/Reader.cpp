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


double** Reader::readRatings(map<int, User> &users, map<int, Item> &items)
{
    ifstream inFile;
    string line;
    string s_user;
    string s_item;
    string s_rating;

    int userId, uMatId = 0;
    int itemId, iMatId = 0;
    double rating;

    inFile.open("../files/ratings.csv");

    //map<int, Item> matUtility;


    getline(inFile, line);

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
                    uMatId++;
                    users[userId].items.push_back(iMatId);
                }
                else
                {
                    users[userId].items.push_back(iMatId);
                }
                iMatId++;
            }
            else
            {
                if(users.find(userId) == users.end())
                {
                    users[userId].id = uMatId;
                    uMatId++;
                    users[userId].items.push_back(items[itemId].id);
                }
                else
                {
                    users[userId].items.push_back(items[itemId].id);
                }
            }

            items[itemId].addRating(userId, rating);
        }
    }

    double **mat = new double *[users.size()];

        for(int i = 0; i < users.size(); i++)
            mat[i] = new double[items.size()];

    for(map<int,Item>::iterator it=items.begin(); it!=items.end(); ++it)
    {
        for (map<int, double>::iterator itt = it->second.ratings.begin(); itt != it->second.ratings.end() ; ++itt)
        {
            mat[users[itt->first].id][items[it->first].id] = itt->second;

        }

    }

    inFile.close();
    return mat;
}

map<pair<int, int>, double> Reader::readTarget()
{
    ifstream inFile;
    string line;
    string s_user;
    string s_item;

    int userId;
    int itemId;

    map<pair<int, int>, double> targets;

    inFile.open("../files/targets.csv");

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

             targets[make_pair(userId, itemId)] = 0.0;

        }
    }
    inFile.close();
    return targets;
}


