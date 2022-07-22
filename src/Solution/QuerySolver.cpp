#include "QuerySolver.h"

using namespace std;

/* NU MODIFICATI */
QuerySolver::QuerySolver() 
{
  server = Server::GetInstance();
}

/* NU MODIFICATI */
QuerySolver::~QuerySolver()
{
  if (server != nullptr) 
  {
    server = nullptr;
  }
}

list<Product*> QuerySolver::Query_3a()
{
    list<Product*> lista;
    list<Product*>::iterator it = server->getProductsList().begin();
    while (it != server->getProductsList().end())
    {
      if((*it)->getProductType() == "redus" && (*it)->getCategory() == "espressor")
      {
        lista.push_back(*it);
      }
      it++;
    }
  return lista;  
}

list<User*> QuerySolver::Query_3b()
{
  list<User*> lista;
  list<User*>::iterator it = server->getUsersList().begin();
  while (it != server->getUsersList().end())
  {
    if((*it)->getUserType() == "basic" && (*it)->getTransportCost() <= 11.5)
    {
      lista.push_back(*it);
    }
    it++;
  }
  return lista;
}

list<Product*> QuerySolver::Query_3c()
{
  list<Product*> lista;
  list<Product*>::iterator it = server->getProductsList().begin();
  while (it != server->getProductsList().end())
  {
    ResealedProduct *x = dynamic_cast<ResealedProduct*>(*it);
    if(x)
    {
      if(x->getReason() == "lipsa_accesorii")
      {
        lista.push_back(*it);
      }
    }
    it++;
  }
  lista.sort(Utility::comparePrice);
  return lista;
}

list<Product*> QuerySolver::Query_3d()
{
  list<Product*> lista;
  list<Product*>::iterator it = server->getProductsList().begin();
  while(it != server->getProductsList().end())
  {
    FoodProduct *x = dynamic_cast<FoodProduct*>(*it);
    if(x)
    {
      lista.push_back(*it);
    }
    it++;
  }
  lista.sort(Utility::compareNTP);
  return lista;
}

list<User*> QuerySolver::Query_3e()
{
  vector<string> judete;
  list<User*>::iterator it = server->getUsersList().begin();
  while(it != server->getUsersList().end())
  {
    if((*it)->getBillingData().getCounty() == (*it)->getDeliveryData().getCounty())
        judete.push_back((*it)->getDeliveryData().getCounty());
    it++;
  }

  vector<string>::iterator it1 = judete.begin(), poz = it1;
  sort(judete.begin(),judete.end());
  int max = 1, nr = 1;

  while(it1 != judete.end())
  {
    if(*it1 == *(it1++))
    {
      nr++;
    }
    else
    {
      if(nr > max)
      {
        max = nr;
        poz = it1;
      }
      nr = 1;
    }
    it1++;
  }
  
  if(nr > max)
  {
    max = nr;
    poz = it1--;
  }

  list<User*> lista, lista1 = server->getUsersList();
  lista1.sort(Utility::compareID);
  it = lista1.begin();
  while(it != lista1.end())
  {
    if((*it)->getBillingData().getCounty() == *poz && (*it)->getDeliveryData().getCounty() == *poz)
      if((*it)->getBillingData().getApartment() == 0 && (*it)->getDeliveryData().getApartment() == 0)
        if((*it)->getBillingData().getBlock() == "-" && (*it)->getDeliveryData().getBlock() == "-")
        {
          lista.push_back(*it);
        }
    it++;
  }
  return lista;
}

list<User*> QuerySolver::Query_3f()
{
  list<User*> lista;
  list<User*>::iterator it = server->getUsersList().begin();
  while (it != server->getUsersList().end())
  {
    PremiumUser *x = dynamic_cast<PremiumUser*>(*it);
    if(x)
    {
        map<int,int>::iterator it1 = x->getDiscounts().begin();
        while(it1 != x->getDiscounts().end())
        {
          string tip = Utility::tef_imp(server->getProductsList(),it1->first);
          if(tip == "telefon" || tip == "imprimanta")
          {
            lista.push_back(*it);
            break;
          }
          it1++;
        }
    }
    it++;
  }
  return lista;
}
