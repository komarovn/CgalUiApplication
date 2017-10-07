#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CgalUiApplication.h"

class CgalUiApplication : public QMainWindow
{
    Q_OBJECT

public:
    CgalUiApplication(QWidget *parent = Q_NULLPTR);
    public slots:
    void addPoint();
private:
    Ui::CgalUiApplicationClass ui;
};

