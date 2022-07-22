#include "Server.h"

using namespace std;

/* NU MODIFICATI */
Server::Server(){}

/* NU MODIFICATI */
Server *Server::GetInstance()
{
	if (!instance)
	{
		instance = new Server;
	}

	return instance;
}

/* NU MODIFICATI */
Server::~Server()
{
	if (instance != NULL)
		instance = NULL;

	if (!__UserID__ProductsCart__.empty())
		__UserID__ProductsCart__.clear();
}

void Server::set__UserID__ProductsCart__()
{
	list<User *>::iterator it = usr.begin();
	while(it != usr.end())
	{
		__UserID__ProductsCart__.insert(pair<int,ShoppingCart *>((*it)->getUserID(),new ShoppingCart));
		it++;
	}
}

list<Product *> &Server::getProductsList()
{
	return prod;
}

list<User *> &Server::getUsersList()
{
	return usr;
}

map<int, ShoppingCart *> Server::get__UserID__ProductsCart__()
{
	return __UserID__ProductsCart__;
}

bool Server::requestAddProduct(int userID, int productID, int quantity)
{	
	if(quantity <= 0)
		return false;
	if(!(Utility::find_user_id(usr,userID)))
		return false;
	if(!(Utility::find_product_id(prod,productID)))
		return false;
	//iterator catre cosul userID
	map<int, ShoppingCart*>::iterator it = __UserID__ProductsCart__.find(userID);
	//iterator catre produsul necesar in lista de produse
	list<Product*>::iterator it1 = prod.begin();
	while(it1 != prod.end())
	{
		if((*it1)->getId() == productID)
			break;
		it1++;
	}
	//verificare existenta cantitate in lista de produse
	if(!((*it1)->checkQuantity(quantity)))
		return false;
	//daca produsul exista, adaugare cantitate, sau adaugare produs daca nu exista
	if((*it).second->getQuantity(productID) != -1)
	{
		(*it1)->decreaseQuantity(quantity);
		(*it).second->raiseQuantity(productID,quantity);
	}
	else
	{	
		(*it1)->decreaseQuantity(quantity);
		(*it).second->addProduct(productID,quantity);
	}
	
	return true;
}

bool Server::requestDeleteProduct(int userID, int productID, int quantity)
{
	if(quantity <= 0)
		return false;
	if(!(Utility::find_user_id(usr,userID)))
		return false;
	if(!(Utility::find_product_id(prod,productID)))
		return false;
	//iterator catre cosul userID
	map<int, ShoppingCart*>::iterator it = __UserID__ProductsCart__.find(userID);	
	//verificare daca produsul exista in cos
	if((*it).second->getQuantity(productID) != -1)
	{
		//iterator catre produsul necesar in lista de produse
		list<Product*>::iterator it1 = prod.begin();
		while(it1 != prod.end())
		{
			if((*it1)->getId() == productID)
				break;
			it1++;
		}
		//verificare daca cantitatea data ca parametru este mai mica, atunci se modifica 
		//in ambele(cas scade, lista produse creste), iar in caz contrat, crestere
		//cantitate produs in lista cu cantitatea de produs din cos, si stergerea produ-
		//sului din cos
		if((*it).second->getQuantity(productID) <= quantity)
		{
			(*it1)->increaseQuantity((*it).second->getQuantity(productID));
			(*it).second->deleteProduct(productID);
		}
		else
		{
			(*it1)->increaseQuantity(quantity);
			(*it).second->lowerQuantity(productID,quantity);
		}
	}
	else
		return false;
	
	return true;
}

/* NU MODIFICATI */
void Server::populateProducts(const json &input)
{
	prod = ObjectFactory::getProductList(input["shoppingCart"]);
}

/* NU MODIFICATI */
void Server::populateUsers(const json &input)
{
	usr = ObjectFactory::getUserList(input["useri"]);
}