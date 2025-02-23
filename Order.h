#pragma once
#include <vector>
#include "ItemData.h"

using namespace std;

class Order
{
public:
	Order() {};
	~Order() {};

private:
	vector<ItemData> itemsInOrder;

	int orderID;

public:
	void addItemToOrder(ItemData item);
	void setOrderID(int num);
	int getOrderID();
	int getOrderSize();
	ItemData getItemInOrder(int index);
	void removeItemInOrder(int index);
};


