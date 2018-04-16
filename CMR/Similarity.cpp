#include "Similarity.h"
#include "Item.h"
#include <cmath>
#include <map>
#include <list>

Similarity::Similarity()
{
    //ctor
}

Similarity::~Similarity()
{
    //dtor
}

double Similarity::Cosine(double **matrixUtility, int i, int j, list<int>listUser)
{
    double dot = 0.0, denomI = 0.0, denomJ = 0.0 ;
    for (list<int>::iterator it=listUser.begin(); it != listUser.end() ; ++it)
    {
            dot += matrixUtility[*it][i] * matrixUtility[*it][j];
            denomI += matrixUtility[*it][i] * matrixUtility[*it][i];
            denomJ+= matrixUtility[*it][j] * matrixUtility[*it][j];

    }

    if (dot == 0 ) return 0;
    else return dot / (sqrt(denomI) * sqrt(denomJ)) ;
}
