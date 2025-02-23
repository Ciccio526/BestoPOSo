#pragma once
#include <string>
#include <iostream>
#include <qstring.h>

using namespace std;


class ItemData
{
public:
	ItemData();
	ItemData(string newName, float newPrice, int newStock);
	~ItemData();

private:
	string name;
	float price;
	int stock;

public:
	string getName();
	void setName(string newName);

	float getPrice();
	void setPrice(float newPrice);

	int getStock();
	void setStock(int newStock);
	void decrementStock();

	QString makeFileString();

};

