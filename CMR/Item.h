#ifndef ITEM_H
#define ITEM_H
#include <map>
#include <string>
#include <iterator>
#include <list>

using namespace std;

class Item
{
    public:
        Item();
        virtual ~Item();
        map<int, double> ratings;
        list<int> users;
        void calculateMean(double rating);
        void addRating(int userId, double rating);
        void toString();
        double mean;
        int id;
    protected:

    private:
};

#endif // ITEM_H
