#ifndef USER_H
#define USER_H
#include <list>

using namespace std;

class User
{
    public:
        User();
        virtual ~User();
        list<int> items;					/* Lista de itens avaliados pelo o usuario */
        int id;								/* Id criado para mapear o usuario a sua linha na matriz de utilidade */
        double mean;						/* Media dos scores do usuario */
        void calculateMean(double rating);
        double getMean();
    protected:

    private:
};

#endif // USER_H
