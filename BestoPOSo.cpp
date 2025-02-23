#include "BestoPOSo.h"
#include "POSModeWidget.h"

using namespace Ui;

BestoPOSo::BestoPOSo(QWidget *parent)
    : QWidget(parent)
{
    MainWindow.setupUi(this);
    
    connect(MainWindow.createItemButton, &QPushButton::clicked, this, &BestoPOSo::OpenAddItemWindow);
    connect(MainWindow.POSModeButton, &QPushButton::clicked, this, &BestoPOSo::OpenPOSWindow);
    menuList = new Menu;
}

BestoPOSo::~BestoPOSo()
{}

void BestoPOSo::OpenAddItemWindow()
{
    NewItemWidget* newItemWidget = new NewItemWidget();

    newItemWidget->show();
}

void BestoPOSo::OpenPOSWindow()
{
    POSModeWidget* newPOSModeWidget = new POSModeWidget();
    newPOSModeWidget->show();

}
