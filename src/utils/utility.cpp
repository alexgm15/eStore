#include "utility.h"

bool Utility::comparePrice(Product *p1, Product *p2)
{
    NonFoodProduct *x = dynamic_cast<NonFoodProduct*>(p1);
    NonFoodProduct *y = dynamic_cast<NonFoodProduct*>(p2);
    if(x->getPrice() <= y->getPrice())
    {
        return true;
    }
    return false;
}

bool Utility::compareNTP(Product *p1, Product* p2)
{
    FoodProduct *x = dynamic_cast<FoodProduct*>(p1);
    FoodProduct *y = dynamic_cast<FoodProduct*>(p2);
    if(x->getName() < y->getName())
        return true;
    if(x->getName() > y->getName())
        return false;

    if(x->getCountryOfOrigin() < y->getCountryOfOrigin())
        return true;
    if(x->getCountryOfOrigin() > y->getCountryOfOrigin())
        return false;

    if(x->getLeiPerKg() < y->getLeiPerKg())
        return true;
    if(x->getLeiPerKg() > y->getLeiPerKg())
        return false;
    
    return false;
}

bool Utility::compareID(User *u1, User *u2)
{
    if(u1->getUserID() < u2->getUserID())
        return true;
    return false;
}

string Utility::tef_imp(list<Product*> lista, int id)
{
    list<Product*>::iterator it = lista.begin();
    while (it != lista.end())
    {
        if((*it)->getId() == id)
        {
            return (*it)->getCategory();
        }
        it++;
    }
    return string();
}


bool Utility::find_user_id(list<User*> lista, int id)
{
    list<User*>::iterator it = lista.begin();
    while(it != lista.end())
    {
        if((*it)->getUserID() == id)
            return true;
        it++;
    }
    return false;
}

bool Utility::find_product_id(list<Product*> lista, int id)
{
    list<Product*>::iterator it = lista.begin();
    while(it != lista.end())
    {
        if((*it)->getId() == id)
            return true;
        it++;
    }
    return false;
}

bool Utility::find_product_cart(map<int, int> cos, int id)
{
    map<int,int>::iterator it = cos.find(id);
    if(it != cos.end())
        return true;
    else
        return false;
}

bool Utility::find_point(vector<int> vec, int punct)
{
    for(auto it = vec.begin(); it != vec.end(); it++)
    {
        if(*it == punct)
            return true;
    }
    return false;
}