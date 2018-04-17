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


/* Agregador de votos do item
*       parametro: nota do item
*/
void Item::calculateMean(double rating)
{
    mean += rating;
}

/*
*   Media do score para o item
*/

double Item::getMean()
{
    return (mean/ratings.size());
}




