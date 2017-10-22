#pragma once
#include "typedefs.h"
#include <math.h>

class BSpline {
protected:
    std::vector<double*> coeffs;
    int stepCount;
    Points3* points;
    double* calculateSplineCoeffs3(double t);
    double* calculateSplineCoeffs2(double t);
    void drawSegment3(int segmentIndex);
    void drawSegment2(int segmentIndex);
public:
    bool closed;
    inline int clamp(int value, int min, int max) {
        return std::min(std::max(value, min), max);
    }
    void drawSplineCurve(int k);
    BSpline(Points3* points, int k = 3, int stepCount = 10, bool closed = false);
    ~BSpline();
};