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
        double ItemBasedPredictor(int userId, int itemId, map<int, Item> matUtility, map<int, User> users,   map<pair<int, int>, double> sims);

    protected:

    private:
};

#endif // PREDICTOR_H
