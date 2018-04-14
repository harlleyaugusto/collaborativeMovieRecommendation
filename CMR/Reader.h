#ifndef READER_H
#define READER_H
#include <map>
#include "Item.h"
#include "User.h"

class Reader
{
    public:
        Reader();
        virtual ~Reader();
        double** readRatings(map<int, User> &users, map<int, Item> &item, string file);
        map<pair<int, int>, double>readTarget(string file, map<string, string> &stringTargets);

    protected:

    private:
};

#endif // READER_H
