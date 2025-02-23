#pragma once

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include "ItemData.h"

class ItemButton : public QPushButton
{
	Q_OBJECT

public:
	ItemButton() {};
	ItemButton(QWidget* parent, ItemData data);

	ItemData getItemData();
	void setItemData(ItemData data);

private:
	ItemData itemData;


};

