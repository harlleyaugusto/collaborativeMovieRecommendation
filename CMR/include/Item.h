#ifndef ITEM_H
#define ITEM_H
#include <map>
#include <string>
#include <iterator>

using namespace std;

class Item
{
    public:
        Item();
        virtual ~Item();
        map<int, double> ratings;
        void calculateMean();
        void addRating(double rating);
        double mean;

    protected:

    private:
};

#endif // ITEM_H
