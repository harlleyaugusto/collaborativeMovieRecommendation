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
        map<int, Item> readRatings(map<int, User> &users, string file);
        map<pair<int, int>, double>readTarget(string file);

    protected:

    private:
};

#endif // READER_H
