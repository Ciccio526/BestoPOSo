#include "ItemData.h"

ItemData::ItemData()
{
}

ItemData::ItemData(string newName, float newPrice, int newStock)
{
	name = newName;
	price = newPrice;
	stock = newStock;
}

ItemData::~ItemData()
{
}

string ItemData::getName()
{
	return name;
}

void ItemData::setName(string newName)
{
	name = newName;
}

float ItemData::getPrice()
{
	return price;
}

void ItemData::setPrice(float newPrice)
{
	price = newPrice;
}

int ItemData::getStock()
{
	return stock;
}

void ItemData::setStock(int newStock)
{
	stock = newStock;
}

void ItemData::decrementStock()
{
	stock -= 1;
}

QString ItemData::makeFileString()
{
	return QString(QString::fromStdString(name) + "," + QString::number(price, 'f', 2) + "," + QString::number(stock));
}
