#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "ItemData.h"

using namespace std;

class Menu
{
public:
	Menu() {};
	~Menu() {};

public:
	static Menu& GetInstance() {
		static Menu instance;
		return instance;
	}

	void addItem(ItemData item);
	ItemData getItem(int index);
	int getAmount();

	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;

	vector<ItemData> menuItems;

	

};

