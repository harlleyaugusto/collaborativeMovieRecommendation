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
        map<int, double> ratings;   /* Map dos ratigns recebidos por cada usuario  */
        list<int> users;            /* Lista de usuario que avaliaram um determinado item */
        double mean;                /* Media dos scores do item */
        int id;                     /* Id criado para mapear o item a sua coluna na matriz de utilidade */

        void calculateMean(double rating);
        void addRating(int userId, double rating);
        void toString();
        double getMean();
       
    protected:

    private:
};

#endif // ITEM_H
