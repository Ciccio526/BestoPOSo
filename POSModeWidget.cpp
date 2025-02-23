#include "POSModeWidget.h"
#include "ItemData.h"
#include "ItemButton.h"
#include "qcombobox.h"
#include "Menu.h"
#include "OrderManager.h"
#include "qtimer.h"

POSModeWidget::POSModeWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	CentralWidget = new QWidget(this);
	ui.itemTable->setRowCount(0);
	ui.itemTable->setColumnCount(2);
	ui.itemTable->setHorizontalHeaderLabels(QStringList() << "Name" << "Price");

	connect(ui.newOrderButton, &QPushButton::clicked, this, &POSModeWidget::onNewOrderButtonClicked);
	connect(ui.confirmOrderButton, &QPushButton::clicked, this, &POSModeWidget::onConfirmOrderButtonClicked);
	connect(ui.deletePreviousItemButton, &QPushButton::clicked, this, &POSModeWidget::onDeletePreviousOnClick);
	connect(ui.deleteIndexButton, &QPushButton::clicked, this, &POSModeWidget::onDeleteIndexOnClick);
	connect(ui.exitPOSModeButton, &QPushButton::clicked, this, &POSModeWidget::onExitPOSClicked);

	connect(ui.orderDropdown, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &POSModeWidget::onDropdownIndexChanged);

	flashTimer = new QTimer(this);
	connect(flashTimer, &QTimer::timeout, this, &POSModeWidget::ToggleFlash);
	flashTimer->start(500);
	bIsGreen = true;

	addItemButtons();
}

POSModeWidget::~POSModeWidget()
{}

void POSModeWidget::addItemButtons()
{
	for (int i = 0; i < Menu::GetInstance().getAmount(); i++) {
		ItemButton* newButton = new ItemButton(this, Menu::GetInstance().getItem(i));

		connect(newButton, &ItemButton::clicked, this, &POSModeWidget::onItemButtonClicked);

		ui.buttonGrid->addWidget(newButton, row, col);
		newButton->resize(500,100);
		if (col == 2) {
			row++;
			col = 0;
		}
		if (row == 6) {
			return;
		}
		col++;
	}
}

void POSModeWidget::onItemButtonClicked()
{
	if (!currentOrder) return;

	ItemButton* button = qobject_cast<ItemButton*>(sender());
	
	QString name = QString::fromStdString(button->getItemData().getName());
	float price = button->getItemData().getPrice();

	if (button->getItemData().getStock(name.toStdString()) == 0) {
		ui.errorLabel->setText(QString("Out of stock!"));
		return;
	}
	

	ui.itemTable->insertRow(tableRow);

	ui.itemTable->setItem(tableRow, 0, new QTableWidgetItem(name));
	ui.itemTable->setItem(tableRow, 1, new QTableWidgetItem(QString::number(price, 'f', 2)));
	ui.itemTable->resizeRowsToContents();
	ui.itemTable->resizeColumnsToContents();
	ui.itemTable->update();

	subtotalPrice += price;
	price += price * .06625;

	currentOrder->addItemToOrder(button->getItemData());

	button->getItemData().decrementStock();

	if (button->getItemData().getStock(button->getItemData().getName()) == 0) {
		//button->setEnabled(false);
		ui.errorLabel->setText(QString("Out of stock!"));
	}

	ui.subtotalCountText->setText(QString::number(subtotalPrice, 'f', 2));
	ui.totalCountText->setText(QString::number(subtotalPrice + (subtotalPrice * .06625), 'f', 2));
	ui.errorLabel->clear();

	tableRow++;
}

void POSModeWidget::onNewOrderButtonClicked()
{
	if (currentOrder) return;

	flashTimer->stop();
	SetColorGray((ui.newOrderButton));

	ui.orderDropdown->setEnabled(false);

	currentOrder = new Order();
	currentOrder->setOrderID(orderAmount);
	orderAmount++;
	
}

void POSModeWidget::onConfirmOrderButtonClicked()
{
	if (currentOrder == nullptr || currentOrder->getOrderSize() == 0) return;
	
	QString name = ui.nameInputBox->text();

	if (name.isEmpty()) {
		ui.errorLabel->setText(QString("Input name!"));
		return;
	}

	currentOrder->setCustomerName(ui.nameInputBox->text().toStdString());

	flashTimer->start(500);

	if (bEditOldOrder) {
		OrderManager::GetInstance().orderList.at(currentOrder->getOrderID()) = *currentOrder;
	}
	else {
		OrderManager::GetInstance().addOrder(*currentOrder);
		ui.orderDropdown->addItem((QString::number(currentOrder->getOrderID()) + ": " + (QString::fromStdString(currentOrder->getCustomerName()))));
		
	}

	ui.itemTable->clearContents();
	ui.itemTable->setRowCount(0);
	tableRow = 0;

	subtotalPrice = 0.f;

	ui.subtotalCountText->clear();
	ui.totalCountText->clear();

	ui.nameInputBox->clear();

	ui.orderDropdown->setEnabled(true);

	currentOrder = nullptr;
}

void POSModeWidget::onDropdownIndexChanged(int index)
{
	if (currentOrder) return; //TODO add message

	ui.orderDropdown->setEnabled(false);

	flashTimer->stop();
	SetColorGray(ui.newOrderButton);

	bEditOldOrder = true;

	currentOrder = OrderManager::GetInstance().GetOrder(index);

	for (int i = 0; i < currentOrder->getOrderSize();i++) {
		QString itemName = QString::fromStdString(currentOrder->getItemInOrder(i).getName());

		float price = currentOrder->getItemInOrder(i).getPrice();

		ui.itemTable->insertRow(i);

		ui.itemTable->setItem(tableRow, 0, new QTableWidgetItem(itemName));
		ui.itemTable->setItem(tableRow, 1, new QTableWidgetItem(QString::number(price, 'f', 2)));

		ui.itemTable->resizeRowsToContents();

		ui.itemTable->update();

		subtotalPrice += price;

		tableRow++;
	}
	ui.nameInputBox->setText(QString::fromStdString(currentOrder->getCustomerName()));
	ui.subtotalCountText->setText(QString::number(subtotalPrice, 'f', 2));
	ui.totalCountText->setText(QString::number(subtotalPrice + (subtotalPrice * .06625), 'f', 2));
}

void POSModeWidget::onDeletePreviousOnClick()
{
	if ((!currentOrder) || (!currentOrder->getOrderSize() > 0)) return;
	
	subtotalPrice -= (currentOrder->getItemInOrder(currentOrder->getOrderSize()-1)).getPrice();
	ui.subtotalCountText->setText(QString::number(subtotalPrice, 'f', 2));
	ui.totalCountText->setText(QString::number(subtotalPrice + (subtotalPrice * .06625), 'f', 2));

	currentOrder->getItemInOrder(currentOrder->getOrderSize() - 1).incrementStock();
	currentOrder->removeItemInOrder(currentOrder->getOrderSize() - 1);

	if (currentOrder->getOrderSize() == 0) {
		ui.itemTable->removeRow(currentOrder->getOrderSize());
	}
	else {
		ui.itemTable->removeRow(currentOrder->getOrderSize() - 1);
	}

	tableRow--;
}

void POSModeWidget::onDeleteIndexOnClick(int index)
{
	if ((!currentOrder) || (ui.indexSpinBox->value() > currentOrder->getOrderSize()) || (!currentOrder->getOrderSize() > 0)) return;
	
	subtotalPrice -= (currentOrder->getItemInOrder(ui.indexSpinBox->value() -1)).getPrice();
	ui.subtotalCountText->setText(QString::number(subtotalPrice, 'f', 2));
	ui.totalCountText->setText(QString::number(subtotalPrice + (subtotalPrice * .06625), 'f', 2));

	currentOrder->getItemInOrder(ui.indexSpinBox->value() - 1).incrementStock();
	currentOrder->removeItemInOrder(ui.indexSpinBox->value() -1);
	
	ui.itemTable->removeRow(ui.indexSpinBox->value() - 1);

	tableRow--;
}

void POSModeWidget::onExitPOSClicked()
{
	this->close();
}

void POSModeWidget::ToggleFlash()
{
	bIsGreen = !bIsGreen;

	QPalette palette = ui.newOrderButton->palette();

	if (bIsGreen) {
		palette.setColor(QPalette::Button, Qt::darkGray);
	}
	else if (!bIsGreen) {
		palette.setColor(QPalette::Button, Qt::darkGreen);
	}
	ui.newOrderButton->setPalette(palette);
}

void POSModeWidget::SetColorGray(QPushButton* button)
{
	QPalette palette = button->palette();
	palette.setColor(QPalette::Button, Qt::darkGray);
	button->setPalette(palette);
}

void POSModeWidget::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::WindowStateChange) {
		if (this->windowState() && Qt::WindowFullScreen) {
			this->setWindowState(Qt::WindowNoState);
		}
	}

	QWidget::changeEvent(event);
}


