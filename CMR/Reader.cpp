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


double** Reader::readRatings(map<int, User> &users, map<int, Item> &items, string file)
{
    ifstream inFile;
    string line;
    string s_user;
    string s_item;
    string s_rating;

    int userId, uMatId = 0;
    int itemId, iMatId = 0;
    double rating;

   inFile.open(("../files/" + file).c_str());

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

    double **mat = new double *[users.size()];

    for(int i = 0; i < users.size(); i++)
        mat[i] = new double[items.size()];

    for(map<int,Item>::iterator it=items.begin(); it!=items.end(); ++it)
    {
        for (map<int, double>::iterator itt = it->second.ratings.begin(); itt != it->second.ratings.end() ; ++itt)
        {
            //users[itt->first].mean = users[itt->first].mean/users[itt->first].items.size();
            mat[users[itt->first].id][items[it->first].id] = itt->second - (users[itt->first].getMean());
            
          /*  if(users[itt->first].id == 29279)
            {
                cout << "item: " << it->first << " user: " << itt->first << " id:" << users[itt->first].id <<" mean: " << users[itt->first].getMean() << " rating: "<< itt->second <<" diff:" << mat[users[itt->first].id][items[it->first].id] << '\n';
                cout << "item: " << it->first << " user: " << itt->first << " qtdItems: " <<  users[itt->first].items.size() << '\n';
    
            }*/
            
            //cin.get();

        }

    }

    inFile.close();
    return mat;
}

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


