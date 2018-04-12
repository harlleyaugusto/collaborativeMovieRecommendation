#ifndef USER_H
#define USER_H
#include <list>

using namespace std;

class User
{
    public:
        User();
        virtual ~User();
        list<int> items;
        int id;
    protected:

    private:
};

#endif // USER_H
