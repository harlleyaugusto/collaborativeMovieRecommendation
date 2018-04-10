#include <iostream>
#include "Reader.h"
#include <map>

using namespace std;

map<string, int> initMap()
{
    map<string, int> theMap;
    /* do stuff in theMap */
    return theMap;
}

int main()
{
    cout << "Hello world!" << endl;

    map<string, int> myMap;
    myMap = initMap(  );

    return 0;
}
