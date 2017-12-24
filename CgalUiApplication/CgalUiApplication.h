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
    void movePoint();
    void buildCube();
    void buildCubeVolume();
    void buildSphere();
    void buildSphereVolume();
    void drawSpline3();
    void drawSpline2();
    void drawTriangle();
    void buildOctahedron();
    void applyChaikinAlgorithm();
    void parseFile();
private:
    Ui::CgalUiApplicationClass ui;
};

