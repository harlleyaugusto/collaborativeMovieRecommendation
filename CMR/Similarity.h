#ifndef SIMILARITY_H
#define SIMILARITY_H
#include "Item.h"

class Similarity
{
    public:
        Similarity();
        virtual ~Similarity();
        double Cosine(Item i, Item j);
        double Spearman(Item i, Item j);
    protected:

    private:
};

#endif // SIMILARITY_H
