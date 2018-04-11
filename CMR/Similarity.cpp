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


double Consine(Item i, Item j)
{
    double dot = 0.0, denomA = 0.0, denomB = 0.0 ;

    map<int, double> ri = i.ratings;

    map<int, double> rj = j.ratings;


    for(map<int,double>::iterator it = ri.begin(); it != ri.end(); ++it) {
        if ( rj.find(it->first) != rj.end() ) {
            // found
            dot += it->second * rj[it->first];
            denomA += it->second * it->second;
            denomB += rj[it->first]*rj[it->first];
        }
    }
    return dot / (sqrt(denomA) * sqrt(denomA)) ;

}
