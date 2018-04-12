#include "Similarity.h"
#include "Item.h"
#include <cmath>
#include <map>

Similarity::Similarity()
{
    //ctor
}

Similarity::~Similarity()
{
    //dtor
}


double Similarity::Cosine(Item i, Item j)
{
    double dot = 0.0, denomA = 0.0, denomB = 0.0 ;

    map<int, double> ri = i.ratings;

    map<int, double> rj = j.ratings;

    int qtdUser = 3;
    int qtd = 0;

    for(map<int,double>::iterator it = ri.begin(); it != ri.end() && qtd < qtdUser; ++it) {
        if ( rj.find(it->first) != rj.end() ) {
            // found
            dot += it->second * rj[it->first];
            denomA += it->second * it->second;
            denomB += rj[it->first]*rj[it->first];
            qtd++;
        }
    }
    if (dot == 0) return 0;
    else return dot / (sqrt(denomA) * sqrt(denomA)) ;
}
