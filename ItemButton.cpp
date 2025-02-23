#include "ItemButton.h"


ItemButton::ItemButton(QWidget* parent, ItemData data)
{
	parent = nullptr;
	itemData = data;

	setMinimumSize(75, 50);
	setMaximumSize(150, 100);

	setText(QString::fromStdString(itemData.getName()));
	QFont font = this->font();
	font.setPointSize(13);
	setFont(font);
}

ItemData ItemButton::getItemData()
{
	return itemData;
}

void ItemButton::setItemData(ItemData data)
{
	itemData = data;
}
