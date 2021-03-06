#pragma once

#include <qglviewer.h>
#include <typedefs.h>
#include <qmessagebox.h>
#include <qmouseeventtransition.h>
#include "BSpline.h"
#include "PNOctahedron.h"
#include "ChaikinAlgorythm.h"
#include "MeshParser.h"

class MyViewer : public QGLViewer {
public:
    MyViewer(QWidget* parent);
    Points3 points;
    Triangles triangles;
    Tetrahedra tetrahedra;
    size_t movePointIndex = -1;
    QPoint* oldMousePosition;
    int k;
    int detalizationLevel = 1;

    bool isRemovePointMode = false;
    bool isMovePointMode = false;
    bool isSpline = false;
    bool isTriangle = false;
    bool isOctahedron = false;
    bool isChaikin = false;

    void removeAllPoints();
    void generateCube();
    void generateCubeVolume();
    void generateSphere();
    void generateSphereVolume();
    void drawBSpline(BSpline bSpline);
    void drawTriangle();
    void drawOctahedron();
    void applyChaikinAlgorithm();
    void parseFile();
protected:
    virtual void draw();
    virtual void init();
    virtual void postSelection(const QPoint &point);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
private:
    std::vector<int> getSelectedPoints(const QPoint &point);
    PNTriangle pnTriangle = PNTriangle(Point_3(0, -1, 0), Point_3(1, 0, 0), Point_3(0, 0, 1),
        Point_3(0, -1, 0), Point_3(1, 0, 0), Point_3(0, 0, 1));
    PNOctahedron pnOctahedron = PNOctahedron(1.0f);
    ChaikinAlgorythm *chaikinAlgorythm = nullptr;
};
