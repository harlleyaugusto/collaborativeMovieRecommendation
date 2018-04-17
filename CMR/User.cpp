#include "User.h"
#include <iostream>
#include <list>

using namespace std;

User::User()
{
    mean = 0;
}

User::~User()
{
    //dtor
}


/* Agregador de votos do usuario
*       parametro: nota dada pelo o usuario
*/
void User::calculateMean(double rating)
{

	mean = (mean + rating);

}


/*
*   Media do score do usuario
*/

double User::getMean()
{

	return mean / items.size();
}