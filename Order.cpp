#include "Order.h"


void Order::addItemToOrder(ItemData item)
{
	itemsInOrder.push_back(item);
}

void Order::setOrderID(int num)
{
	orderID = num;
}

int Order::getOrderID()
{
	return orderID;
}

int Order::getOrderSize()
{
	return itemsInOrder.size();
}

ItemData Order::getItemInOrder(int index)
{
	return itemsInOrder.at(index);
}

void Order::removeItemInOrder(int index)
{
	itemsInOrder.erase(itemsInOrder.begin() + index);
}

vector<ItemData> Order::getItems()
{
	return itemsInOrder;
}

