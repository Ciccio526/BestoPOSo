#pragma once

#include <QWidget>
#include "ui_EndOfDayWidget.h"

using namespace Ui;

class EndOfDayWidget : public QWidget
{
	Q_OBJECT

public:
	EndOfDayWidget(QWidget *parent = nullptr);
	~EndOfDayWidget();

private:
	EndOfDayWidgetClass ui;

	//Button callbacks
	void onExitEODModeClicked();


	//Functions
	void calculateSales();

	void changeEvent(QEvent* event) override;

	//Variables
	float subtotalPrice;
	float totalPrice;


	// Data Table
	int row = 0;
	int col = 0;

	int tableRow = 0;

	QWidget* CentralWidget;

};
