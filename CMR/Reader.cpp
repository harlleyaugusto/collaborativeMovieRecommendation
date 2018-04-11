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
    //readRatings();
    //readTarget();
}


map<int, Item> Reader::readRatings()
{
    ifstream inFile;
    string line;
    string s_user;
    string s_item;
    string s_rating;


    int userId;
    int itemId;
    double rating;

    inFile.open("../files/ratings.csv");

    map<int, Item> items;


    getline(inFile, line);

    long total = 0;

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

            //std::cin.get();

          //  cout << rating << endl;

            items[itemId].addRating(rating);

            /*
            if (!items.find(itemId) == items.end() )
            {//found
                items[itemId].ratings[userId] = rating;

            } else {
                items[itemId].ratings[userId] = rating;
            }*/

            total++;
        }

    }

   /* for (map<int,double>::iterator it=items[2171847].ratings.begin(); it!=items[2171847].ratings.end(); ++it)
    {
            cout << it->first << " => " << it->second << '\n';
    }
    cout << total << endl;
    */

    inFile.close();
    return items;
}

map<int, int> Reader::readTarget()
{
    ifstream inFile;
    string line;
    string s_user;
    string s_item;

    int userId;
    int itemId;
    int total = 0;

    map<int, int> targets;

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

             targets[userId] = itemId;

        }
    }
    inFile.close();
    return targets;
}

Reader::~Reader()
{
    //dtor
}
