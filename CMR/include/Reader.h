#ifndef READER_H
#define READER_H
#include <map>
#include "Item.h"

class Reader
{
    public:
        Reader();
        virtual ~Reader();
        static map<int, Item> readRatings();
        static map<int, int>readTarget();

    protected:

    private:
};

#endif // READER_H
