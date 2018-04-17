#ifndef SIMILARITY_H
#define SIMILARITY_H
#include "Item.h"
#include <map>
#include <list>

class Similarity
{
    public:
        Similarity();
        virtual ~Similarity();
        double cosineItem(double **matrixUtility, int i, int j, list<int> listUser);
        double cosineUser(double **matrixUtility, int i, int j, list<int> listUser);
        double spearman(Item i, Item j);
    protected:

    private:
};

#endif // SIMILARITY_H
