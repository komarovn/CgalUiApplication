#pragma once
#include "typedefs.h"
#include <QtOpenGL\qgl.h>

struct ChaikinPoint {
    Point_3 point;
    int weight;
    ChaikinPoint() {}
    ChaikinPoint(Point_3 point, int weight = 1) {
        this->point = point;
        this->weight = weight;
    }
};

class ChaikinAlgorythm {
private:
    std::vector<ChaikinPoint> points;
    bool isLooped = false;
public:
    void drawQuadrangle();
    ChaikinAlgorythm(std::vector<ChaikinPoint> points);
    void apply();
};