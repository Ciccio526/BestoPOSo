#pragma once
#include <string>
#include <iostream>
#include <qstring.h>
#include <unordered_map>

using namespace std;


class ItemData
{
private:
	string name;
	float price;
	static unordered_map<string, int> stockMap;

public:
	ItemData() : name("Unknown"), price(0.f) {};
	ItemData(string newName, float newPrice, int newStock) :
		name(newName), price(newPrice) {
		if (stockMap.find(name) == stockMap.end()) {
			stockMap[name] = newStock;
		}
	}

	~ItemData() {};


public:
	string getName();
	float getPrice();

	static int getStock(string ItemName);
	void decrementStock();

	QString makeFileString();
};



