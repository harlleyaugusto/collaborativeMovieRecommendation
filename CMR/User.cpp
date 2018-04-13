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

void User::calculateMean(double rating)
{

	mean = (mean + rating);

}

double User::getMean()
{

	return mean / items.size();
}