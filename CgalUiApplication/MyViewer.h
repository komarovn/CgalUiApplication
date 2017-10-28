#pragma once

#include <qglviewer.h>
#include <typedefs.h>
#include <qmessagebox.h>
#include <qmouseeventtransition.h>
#include "BSpline.h"

class MyViewer : public QGLViewer {
public:
    MyViewer(QWidget* parent);
    Points3 points;
    //Point_3* movePoint = nullptr;
    size_t movePointIndex = -1;
    QPoint* oldMousePosition;
    int k;
    bool isRemovePointMode = false;
    bool isMovePointMode = false;
    void removeAllPoints();
    void generateCube();
    void generateCubeVolume();
    void generateSphere();
    void generateSphereVolume();
    void drawBSpline(BSpline bSpline);
    bool isSpline = false;
protected:
    virtual void draw();
    virtual void init();
    virtual void postSelection(const QPoint &point);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
private:
    std::vector<int> getSelectedPoints(const QPoint &point);
};
