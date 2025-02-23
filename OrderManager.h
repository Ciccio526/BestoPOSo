#pragma once
#include "Order.h"
#include <vector>

using namespace std;

class OrderManager
{
public:
	OrderManager() {};
	~OrderManager() {};

public:
	static OrderManager& GetInstance() {
		static OrderManager instance;
		return instance;
	}

	vector<Order> orderList;

	void addOrder(Order newOrder);
	Order* GetOrder(int index);
};

