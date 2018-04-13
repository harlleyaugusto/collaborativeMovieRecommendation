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


map<int, Item> Reader::readRatings(map<int, User> &users, string file)
{
    ifstream inFile;
    string line;
    string s_user;
    string s_item;
    string s_rating;


    int userId;
    int itemId;
    double rating;

    //cout << f << '\n';

    inFile.open(("../files/" + file).c_str());

    map<int, Item> matUtility;


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

            users[userId].items.push_back(itemId);
            matUtility[itemId].addRating(userId, rating);
        }
    }

    inFile.close();
    return matUtility;
}

map<pair<int, int>, double> Reader::readTarget(string file)
{
    ifstream inFile;
    string line;
    string s_user;
    string s_item;

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

             targets[make_pair(userId, itemId)] = 0.0;

        }
    }
    inFile.close();
    return targets;
}


