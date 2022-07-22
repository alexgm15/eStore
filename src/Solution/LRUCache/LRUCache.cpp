#include "LRUCache.h"
#include <algorithm>

bool compare_int(int a, int b)
{
    if(a > b)
        return  true;
    return false;
}

using namespace std;

LRUCache::LRUCache(int capacity)
{
	this->capacity = capacity;
	size = 0;
}

vector<int> LRUCache::processRequests(vector<int> requestsNo)
{
	for(auto it = requestsNo.begin(); it != requestsNo.end(); it++)
	{
		auto it1 = lru.begin();
		if(Utility::find_point(lru,*it))
			{
				for(auto it2 = lru.begin(); it2 != lru.end(); it2++)
					if(*it2 == *it)
					{
						lru.erase(it2,it2+1);
						break;
					}
			}

		if(lru.size() < capacity)
		{
			lru.insert(it1,*it);
		}
		else
		{
			lru.insert(it1,*it);
			lru.pop_back();
		}
	}
	
	lru.reserve(capacity);
	return lru;
}

int LRUCache::getCapacity()
{
	return capacity;
}

int LRUCache::getSize()
{
	return size;
}

vector<int> LRUCache::getLRU()
{
	return lru;
}

int LRUCache::getLRUCapacity()
{
	return lru.capacity();
}

void LRUCache::setCapacity(int capacity)
{
	this->capacity = capacity;
}

void LRUCache::setLRU(vector<int> aux)
{
	lru = aux;
}
