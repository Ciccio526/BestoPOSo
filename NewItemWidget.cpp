#include "NewItemWidget.h"
#include <qvalidator.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "qfile.h"
#include <warning.h>


NewItemWidget::NewItemWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);


	connect(ui.submitButton, &QPushButton::clicked, this, &NewItemWidget::CreateItem);
	connect(ui.wipeSaveFileButton, &QPushButton::clicked, this, &NewItemWidget::OnDeleteFileClicked);
	connect(ui.useSaveFileButton, &QPushButton::clicked, this, &NewItemWidget::OnKeepFileClicked);

	ui.itemNameInput->setEnabled(false);
	ui.itemPriceInput->setEnabled(false);
	ui.itemStockInput->setEnabled(false);
	ui.submitButton->setEnabled(false);

	QRegularExpressionValidator* decValidator = new QRegularExpressionValidator(QRegularExpression(R"(\d*\.?\d*)"), this);
	QIntValidator* intValidator = new QIntValidator(0, 9999, this);
	ui.itemPriceInput->setValidator(decValidator);
	ui.itemStockInput->setValidator(intValidator);
}

NewItemWidget::~NewItemWidget()
{}

void NewItemWidget::CreateItem()
{

	if (bFileDecisionMade == false) return;

	string name = ui.itemNameInput->text().toStdString();
	float price = ui.itemPriceInput->text().toFloat();
	int stock = ui.itemStockInput->text().toInt();

	if (Menu::GetInstance().getAmount() > 0) {
		for (int i = 0; i < Menu::GetInstance().getAmount(); i++) {
			if (name == Menu::GetInstance().getItem(i).getName()) {
				ui.errorLabel->setText(QString("Cannot enter a repeat item!"));
				return;
			}
		}
	}
	ItemData item(name, price, stock);

	Menu::GetInstance().addItem(item);
	ui.errorLabel->clear();

	writeToFile(Menu::GetInstance().getItem(Menu::GetInstance().getAmount() - 1).makeFileString());


	ui.itemNameInput->clear();
	ui.itemPriceInput->clear();
	ui.itemStockInput->clear();
}

void NewItemWidget::writeToFile(QString qstr)
{
	QFile menuFile("items.txt");

	if (!menuFile.open(QIODevice::Append | QIODevice::Text)) {
		ui.errorLabel->setText(QString("File Error: Could not open the file for writing."));
		return;
	}

	QTextStream out(&menuFile);

	out << qstr << "\n";
	menuFile.close();

}

void NewItemWidget::OnKeepFileClicked()
{
	bFileDecisionMade = true;

	ui.itemNameInput->setEnabled(true);
	ui.itemPriceInput->setEnabled(true);
	ui.itemStockInput->setEnabled(true);
	ui.submitButton->setEnabled(true);

	QFile menuFile("items.txt");

	if (!menuFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		ui.errorLabel->setText(QString("No file found... making new one"));
		return;
	}

	QTextStream in(&menuFile);
	Menu::GetInstance().menuItems.clear();

	while (!in.atEnd()) {
		QString line = in.readLine();

		QStringList parts = line.split(",");
		if (parts.size() != 3) continue;

		QString name = parts[0];
		float price = parts[1].toFloat();
		int stock = parts[2].toInt();

		ItemData item(name.toStdString(), price, stock);
		Menu::GetInstance().addItem(item);
	}

	ui.useSaveFileButton->hide();
	ui.wipeSaveFileButton->hide();
}

void NewItemWidget::OnDeleteFileClicked()
{
	bFileDecisionMade = true;

	ui.itemNameInput->setEnabled(true);
	ui.itemPriceInput->setEnabled(true);
	ui.itemStockInput->setEnabled(true);
	ui.submitButton->setEnabled(true);

	QFile menuFile("items.txt");

	if (menuFile.open(QIODevice::WriteOnly | QIODevice::Text)) { 
		menuFile.remove();
	}

	ui.wipeSaveFileButton->hide();
	ui.useSaveFileButton->hide();
}
