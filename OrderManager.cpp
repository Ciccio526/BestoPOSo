#include "OrderManager.h"

void OrderManager::addOrder(Order newOrder)
{
	orderList.push_back(newOrder);
}

Order* OrderManager::GetOrder(int index)
{
	return &orderList.at(index);
}
