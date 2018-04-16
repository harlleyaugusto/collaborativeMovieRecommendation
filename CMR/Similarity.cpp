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

double Similarity::CosineItem(double **matrixUtility, int i, int j, list<int>listUser)
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


double Similarity::CosineUser(double **matrixUtility, int i, int j, list<int>listItem)
{
    double dot = 0.0, denomI = 0.0, denomJ = 0.0 ;
    for (list<int>::iterator it=listItem.begin(); it != listItem.end() ; ++it)
    {
            dot += matrixUtility[i][*it] * matrixUtility[j][*it];
            denomI += matrixUtility[i][*it] * matrixUtility[i][*it];
            denomJ+= matrixUtility[j][*it] * matrixUtility[j][*it];

    }

    if (dot == 0 || denomJ == 0 || denomI == 0 ) return 0;
    else return dot / (sqrt(denomI) * sqrt(denomJ)) ;
}