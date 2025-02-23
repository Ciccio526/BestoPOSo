#include "ItemData.h"

unordered_map<std::string, int> ItemData::stockMap;

string ItemData::getName()
{
	return name;
}

float ItemData::getPrice()
{
	return price;
}


int ItemData::getStock(string itemName)
{
	if (stockMap.find(itemName) != stockMap.end()) {
		return stockMap[itemName];
	}
	else {
		return 0;
	}
}

void ItemData::decrementStock()
{
	if (stockMap[name] >= 0) {
		stockMap[name] -= 1;
	}
}

void ItemData::incrementStock()
{
	stockMap[name] += 1;
}

QString ItemData::makeFileString()
{
	return QString(QString::fromStdString(name) + "," + QString::number(price, 'f', 2) + "," + QString::number(getStock(name)));
}
