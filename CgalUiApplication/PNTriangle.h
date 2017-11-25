#pragma once
#include "typedefs.h"
#include <math.h>
#include <QtOpenGL\qgl.h>

class PNTriangle {
    Point_3 p300, p030, p003;
    Point_3 n200, n020, n002;
    Point_3 p210, p120, p201, p102, p021, p012, p111;
    Point_3 n110, n011, n101;
public:
    PNTriangle(Point_3 p1, Point_3 p2, Point_3 p3, Point_3 n1, Point_3 n2, Point_3 n3);
    void drawTriangle(int level);
    void drawPoint(double u, double v, double w);
    void calcPNcoefs();
    Point_3 calculateP(double u, double v, double w);
    Point_3 calculateN(double u, double v, double w);
};