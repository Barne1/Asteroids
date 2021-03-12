#pragma once
#include <vector>
#include "SDL.h"

//This header contains code as well, since it is a template class. Otherwise a linker error may occur
//The alternative is to create a third file with all template instantiations.
//See bottom of this page: https://www.learncpp.com/cpp-tutorial/template-classes/

template <class T>
class ObjectPool
{
public:
	ObjectPool(int poolSize = 100);
	~ObjectPool();

	T* GetNextObject();
	std::vector<T*> allObjects;
	std::vector<T*> activeObjects;
	void AddToActive(T* object);
	void RemoveFromActive(T* object);
private:
	int poolSize = 100;
	Uint16 iterator = 0;
};

//code starts here

template<class T>
inline ObjectPool<T>::ObjectPool(int poolSize) : poolSize(poolSize)
{
	SDL_assert(poolSize > 0);
	for (int i = 0; i < poolSize; i++)
	{
		T* temp = new T();
		temp->pool = this;
		temp->active = false;
		allObjects.push_back(temp);
	}
}

template<class T>
inline ObjectPool<T>::~ObjectPool()
{
	for (int i = 0; i < poolSize; i++)
	{
		delete allObjects[i];
	}
}

template<class T>
inline T* ObjectPool<T>::GetNextObject()
{
	T* object = nullptr;
	int count = 0;

	do
	{
		count++;
		if (count == poolSize)
		{
			break;
		}
		object = allObjects[iterator% poolSize];
		++iterator;
	} while (object->active);
	object->active = true;
	AddToActive(object);

	return object;
}

template<class T>
inline void ObjectPool<T>::AddToActive(T* object)
{
	for (auto o : activeObjects)
	{
		if (o == object)
			return;
	}
	activeObjects.push_back(object);
}

template<class T>
inline void ObjectPool<T>::RemoveFromActive(T* object)
{
	for (int i = 0; i < activeObjects.size(); i++)
	{
		if (activeObjects[i] == object)
		{
			object->active = false;
			activeObjects.erase(activeObjects.begin() + i);
			return;
		}
	}
}
