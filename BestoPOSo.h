#pragma once

#include <QtWidgets/QWidget>
#include <qsharedpointer.h>
#include <vector>
#include "ui_BestoPOSo.h"
#include "NewItemWidget.h"
#include "Menu.h"
#include "Order.h"

using namespace Ui;

class BestoPOSo : public QWidget
{
    Q_OBJECT

public:
    BestoPOSo(QWidget *parent = nullptr);
    ~BestoPOSo();

    // VARIABLES
    Menu* menuList;



private:

    // WIDGETS
    BestoPOSoClass MainWindow;

    //FUNCTIONS

    void OpenAddItemWindow();
    void OpenPOSWindow();

};
