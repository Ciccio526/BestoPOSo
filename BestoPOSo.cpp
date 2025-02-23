#include "BestoPOSo.h"
#include "POSModeWidget.h"

using namespace Ui;

BestoPOSo::BestoPOSo(QWidget *parent)
    : QWidget(parent)
{
    MainWindow.setupUi(this);
    
    connect(MainWindow.createItemButton, &QPushButton::clicked, this, &BestoPOSo::OpenAddItemWindow);
    connect(MainWindow.POSModeButton, &QPushButton::clicked, this, &BestoPOSo::OpenPOSWindow);
    connect(MainWindow.endOfDayButton, &QPushButton::clicked, this, &BestoPOSo::OpenEndOfDayWindow);

    menuList = new Menu;
}

BestoPOSo::~BestoPOSo()
{}

void BestoPOSo::OpenAddItemWindow()
{
    bIsOtherWindowOpen = true;
    NewItemWidget* newItemWidget = new NewItemWidget();
    MainWindow.errorLabel->clear();

    newItemWidget->show();
}

void BestoPOSo::OpenPOSWindow()
{
    if (Menu::GetInstance().getAmount() == 0) {
        MainWindow.errorLabel->setText(QString("Error: Please add menu item or load saved menu before entering!"));
        return;
    }

    POSModeWidget* newPOSModeWidget = new POSModeWidget();
    newPOSModeWidget->show();

}

void BestoPOSo::OpenEndOfDayWindow()
{
    EndOfDayWidget* newEndOfDayWidget = new EndOfDayWidget();
    newEndOfDayWidget->show();
}

void BestoPOSo::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::WindowStateChange) {
        if (this->windowState() && Qt::WindowFullScreen) {
            this->setWindowState(Qt::WindowNoState);
        }
    }

    QWidget::changeEvent(event);
}
