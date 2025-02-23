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
	//Setup
	POSModeWidgetClass ui;

	void addItemButtons();

	// Button Callbacks
	void onItemButtonClicked();

	void onNewOrderButtonClicked();

	void onConfirmOrderButtonClicked();

	void onDropdownIndexChanged(int index);

	void onDeletePreviousOnClick();

	void onDeleteIndexOnClick(int index);

	void onExitPOSClicked();

	// Color
	void ToggleFlash();
	void SetColorGray(QPushButton* button);

	
	// Data table
	int row = 0;
	int col = 0;

	int tableRow = 0;

	float subtotalPrice = 0;

	QWidget* CentralWidget;

	// ORDERS
	Order* currentOrder;

	int orderAmount;

	//FUNCTIONS
	void changeEvent(QEvent* event) override;

	//CONTROLLERS
	bool bEditOldOrder = false;
	bool bIsGreen = false;

	//TIMERS
	QTimer* flashTimer;
};
