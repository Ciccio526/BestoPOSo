#pragma once

#include <QtWidgets/QWidget>
#include "ui_BestoPOSo.h"

class BestoPOSo : public QWidget
{
    Q_OBJECT

public:
    BestoPOSo(QWidget *parent = nullptr);
    ~BestoPOSo();

private:
    Ui::BestoPOSoClass ui;
};
