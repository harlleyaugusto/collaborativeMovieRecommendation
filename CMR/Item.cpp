#include "Item.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "Item.h"
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

Item::Item()
{
    mean = 0.0;
}

Item::~Item()
{
    //dtor
}


void Item::addRating(int userId, double rating)
{
    ratings[userId] = rating;
    calculateMean(rating);
}

void Item::calculateMean(double rating)
{
    mean += rating;
}

double Item::getMean()
{
    return (mean/ratings.size());
}

void Item::toString()
{

    for (map<int,double>::iterator it=ratings.begin(); it!=ratings.end(); ++it)
    {
        cout << it->first << " => " << it->second << '\n';
    }
}




