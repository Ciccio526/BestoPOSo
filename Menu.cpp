#include "Menu.h"


void Menu::addItem(ItemData item)
{
	menuItems.push_back(item);
}

ItemData Menu::getItem(int index)
{
	return menuItems.at(index);
}

int Menu::getAmount()
{
	return menuItems.size();
}
