#pragma once

#include <qglviewer.h>
#include <typedefs.h>
#include <qmessagebox.h>
#include <qmouseeventtransition.h>

class MyViewer : public QGLViewer {
public:
    MyViewer(QWidget* parent);
    Points3 points;
    bool isRemovePointMode = false;
    void removeAllPoints();
    void generateCube();
    void generateCubeVolume();
    void generateSphere();
    void generateSphereVolume();
protected:
    virtual void draw();
    virtual void init();
    virtual void postSelection(const QPoint &point);
    virtual void mousePressEvent(QMouseEvent *event);
private:
    std::vector<int> getSelectedPoints(const QPoint &point);
};
