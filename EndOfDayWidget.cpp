#include "EndOfDayWidget.h"
#include <vector>
#include "ItemData.h"
#include "OrderManager.h"
#include "Order.h"

EndOfDayWidget::EndOfDayWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	CentralWidget = new QWidget(this);
	ui.dataTable->setRowCount(0);
	ui.dataTable->setColumnCount(2);
	ui.dataTable->setHorizontalHeaderLabels(QStringList() << "Category" << "Value");

	connect(ui.exitEndOfDayMode, &QPushButton::clicked, this, &EndOfDayWidget::onExitEODModeClicked);
	
	calculateSales();
}

EndOfDayWidget::~EndOfDayWidget()
{}

void EndOfDayWidget::onExitEODModeClicked()
{
	this->close();
}

void EndOfDayWidget::calculateSales()
{
	vector<Order> orderList = OrderManager::GetInstance().orderList;

	for (Order order : orderList) {
		for (ItemData item : order.getItems()) {
			subtotalPrice += item.getPrice();
		}
	}

	ui.dataTable->insertRow(tableRow);
	ui.dataTable->setItem(tableRow, 0, new QTableWidgetItem(QString("Total Sales | Subtotal")));
	ui.dataTable->setItem(tableRow, 1, new QTableWidgetItem(QString::number(subtotalPrice, 'f', 2)));
	tableRow++;
	ui.dataTable->insertRow(tableRow);
	ui.dataTable->setItem(tableRow, 0, new QTableWidgetItem(QString("Total Sales | Total")));
	ui.dataTable->setItem(tableRow, 1, new QTableWidgetItem(QString::number((subtotalPrice + (subtotalPrice * .06625)), 'f', 2)));
	ui.dataTable->resizeColumnsToContents();

}

void EndOfDayWidget::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::WindowStateChange) {
		if (this->windowState() && Qt::WindowFullScreen) {
			this->setWindowState(Qt::WindowNoState);
		}
	}

	QWidget::changeEvent(event);
}
