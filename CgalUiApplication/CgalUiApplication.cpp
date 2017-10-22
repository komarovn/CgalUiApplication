#include "CgalUiApplication.h"
#include "BSpline.h"

CgalUiApplication::CgalUiApplication(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.addPointButton, SIGNAL(clicked()), this, SLOT(addPoint()));
    connect(ui.clearAllButton, SIGNAL(clicked()), this, SLOT(removePoints()));
    connect(ui.removePointButton, SIGNAL(clicked()), this, SLOT(removePoint()));
    connect(ui.movePointButton, SIGNAL(clicked()), this, SLOT(movePoint()));
    connect(ui.buildCubeButton, SIGNAL(clicked()), this, SLOT(buildCube()));
    connect(ui.buildCubeVolumeButton, SIGNAL(clicked()), this, SLOT(buildCubeVolume()));
    connect(ui.buildSphereButton, SIGNAL(clicked()), this, SLOT(buildSphere()));
    connect(ui.buildSphereVolumeButton, SIGNAL(clicked()), this, SLOT(buildSphereVolume()));
    connect(ui.drawSpline3Button, SIGNAL(clicked()), this, SLOT(drawSpline3()));
    connect(ui.drawSpline2Button, SIGNAL(clicked()), this, SLOT(drawSpline2()));
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
    ui.widget->isMovePointMode = false;
    ui.movePointButton->setChecked(false);
    ui.widget->isRemovePointMode = ui.removePointButton->isChecked();
}

void CgalUiApplication::movePoint() {
    ui.widget->isRemovePointMode = false;
    ui.removePointButton->setChecked(false);
    ui.widget->isMovePointMode = ui.movePointButton->isChecked();
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

void CgalUiApplication::drawSpline3() {
    ui.widget->isSpline = !ui.widget->isSpline;
    ui.widget->k = 3;
}

void CgalUiApplication::drawSpline2() {
    ui.widget->isSpline = !ui.widget->isSpline;
    ui.widget->k = 2;
}
