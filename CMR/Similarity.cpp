#include "Similarity.h"
#include "Item.h"
#include <cmath>

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
    double dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
    //for(unsigned int i = 0u; i < Vector_Length; ++i) {
        //dot += A[i] * B[i] ;
        //denom_a += A[i] * A[i] ;
        //denom_b += B[i] * B[i] ;
    //}
    return dot / (sqrt(denom_a) * sqrt(denom_b)) ;

}
