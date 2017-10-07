#include "CgalUiApplication.h"

CgalUiApplication::CgalUiApplication(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.addPointButton, SIGNAL(clicked()), this, SLOT(addPoint()));
}

void CgalUiApplication::addPoint() {
    float x = QString(ui.xCoord->text()).toFloat();
    float y = QString(ui.yCoord->text()).toFloat();
    float z = QString(ui.zCoord->text()).toFloat();
    ui.widget->points.push_back(Point_3(x, y, z));
}