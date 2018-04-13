#ifndef PREDICTOR_H
#define PREDICTOR_H
#include <map>
#include "Item.h"
#include "User.h"

class Predictor
{
    public:
        Predictor();
        virtual ~Predictor();
        double itemBasedPredictor(int userId, int itemId, double **matUtility, map<int, User> &users, map<int, Item> &items,
                                     double **simssims);
    protected:

    private:
};

#endif // PREDICTOR_H
