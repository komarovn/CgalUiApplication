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
    void removePoints();
    void removePoint();
    void buildCube();
    void buildCubeVolume();
    void buildSphere();
    void buildSphereVolume();
private:
    Ui::CgalUiApplicationClass ui;
};

