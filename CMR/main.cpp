#include <iostream>
#include "Reader.h"
#include <map>

using namespace std;

int main()
{
    Reader r;
    map<int, Item> matUtility = r.readRatings();
    map<int, int> targets = r.readTarget();

    Item i;
    matUtility[2171847].calculateMean();

    return 0;
}
