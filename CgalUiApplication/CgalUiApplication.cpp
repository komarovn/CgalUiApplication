#include "CgalUiApplication.h"

CgalUiApplication::CgalUiApplication(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.addPointButton, SIGNAL(clicked()), this, SLOT(addPoint()));
    connect(ui.clearAllButton, SIGNAL(clicked()), this, SLOT(removePoints()));
    connect(ui.removePointButton, SIGNAL(clicked()), this, SLOT(removePoint()));
    connect(ui.buildCubeButton, SIGNAL(clicked()), this, SLOT(buildCube()));
    connect(ui.buildCubeVolumeButton, SIGNAL(clicked()), this, SLOT(buildCubeVolume()));
    connect(ui.buildSphereButton, SIGNAL(clicked()), this, SLOT(buildSphere()));
    connect(ui.buildSphereVolumeButton, SIGNAL(clicked()), this, SLOT(buildSphereVolume()));
}

void CgalUiApplication::addPoint() {
    float x = QString(ui.xCoord->text()).toFloat();
    float y = QString(ui.yCoord->text()).toFloat();
    float z = QString(ui.zCoord->text()).toFloat();
    ui.widget->points.push_back(Point_3(x, y, z));
}

void CgalUiApplication::removePoints() {
    ui.widget->removeAllPoints();
}

void CgalUiApplication::removePoint() {
    ui.widget->isRemovePointMode = ui.removePointButton->isChecked();
}

void CgalUiApplication::buildCube() {
    ui.widget->generateCube();
}

void CgalUiApplication::buildCubeVolume() {
    ui.widget->generateCubeVolume();
}

void CgalUiApplication::buildSphere() {
    ui.widget->generateSphere();
}

void CgalUiApplication::buildSphereVolume() {
    ui.widget->generateSphereVolume();
}
