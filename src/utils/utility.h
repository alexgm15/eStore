#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "../Solution/Product/NonFoodProduct.h"
#include "../Solution/Product/FoodProduct.h"
#include "../Solution/User/User.h"

class Utility{

public:
    static bool comparePrice(Product*, Product*);
    static bool compareNTP(Product*, Product*);
    static bool compareID(User*, User*);
    static string tef_imp(list<Product*>, int);
    static bool find_user_id(list<User*>, int);
    static bool find_product_id(list<Product*>,int);
    static bool find_product_cart(map<int,int>, int);
    static bool find_point(vector<int>, int);
};