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
        double Cosine(double **matrixUtility, int i, int j, list<int> listUser);
        double Spearman(Item i, Item j);
    protected:

    private:
};

#endif // SIMILARITY_H
