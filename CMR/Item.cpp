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


void Item::calculateMean()
{

    cout << "Harlley";
    for (map<int,double>::iterator it=ratings.begin(); it!=ratings.end(); ++it)
    {
        cout << it->first << " => " << it->second << '\n';
    }

}
