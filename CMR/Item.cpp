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

}

Item::~Item()
{
    //dtor
}


void Item::addRating(double rating)
{
    ratings[rating];
    calculateMean();
}

void Item::calculateMean()
{

    for (map<int,double>::iterator it=ratings.begin(); it!=ratings.end(); ++it)
    {
        mean += it->second;
        cout << it->first << " => " << it->second << '\n';
    }
    mean /= ratings.size();
    cout << "mean: " << mean << '\n';
}


