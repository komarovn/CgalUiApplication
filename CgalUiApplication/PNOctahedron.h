#pragma once
#include "PNTriangle.h"

class PNOctahedron {
public:
    PNOctahedron(float scale);
    void drawOctahedron(int detalizationLevel);
private:
    float scale;
    std::vector<PNTriangle> triangles;
};