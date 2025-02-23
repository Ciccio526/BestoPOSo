#pragma once

#include <QWidget>
#include "ui_POSModeWidget.h"
#include "Order.h"


using namespace Ui;

class POSModeWidget : public QWidget
{
	Q_OBJECT

public:
	POSModeWidget(QWidget *parent = nullptr);
	~POSModeWidget();

private:
	POSModeWidgetClass ui;

	void addItemButtons();

	void onItemButtonClicked();

	void onNewOrderButtonClicked();

	void onConfirmOrderButtonClicked();

	void onDropdownIndexChanged(int index);

	void onDeletePreviousOnClick();
	void onDeleteIndexOnClick(int index);

	void ToggleFlash();
	void SetColorGray(QPushButton* button);

	int row = 0;
	int col = 0;

	int tableRow = 0;

	float subtotalPrice = 0;

	QWidget* CentralWidget;

	// ORDERS
	Order* currentOrder;

	int orderAmount;


	//CONTROLLERS
	bool bEditOldOrder = false;
	bool bIsGreen = false;

	//TIMERS
	QTimer* flashTimer;
};
