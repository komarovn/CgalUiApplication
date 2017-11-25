#pragma once
#include "typedefs.h"

class PNOctahedron {
public:
    PNOctahedron(float scale);
    void drawOctahedron();
private:
    float scale;
    Points3 basePoints;
};