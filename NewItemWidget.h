#pragma once

#include <QWidget>
#include "ui_NewItemWidget.h"
#include "ItemData.h"
#include "Menu.h"
#include "BestoPOSo.h"

using namespace Ui;
using namespace std;

class NewItemWidget : public QWidget
{
	Q_OBJECT

public:
	NewItemWidget(QWidget *parent = nullptr);
	~NewItemWidget();

private:
	NewItemWidgetClass ui;

	QPushButton* CreateItemButton;

	void CreateItem();

	void writeToFile(QString qstr);
	
	void OnKeepFileClicked();
	void OnDeleteFileClicked();
	void onExitItemCreatorClicked();

	void changeEvent(QEvent* event) override;

	//CONTROLLER
	bool bFileDecisionMade = false;

	
};
