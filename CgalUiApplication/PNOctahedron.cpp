#include "PNOctahedron.h"
//#include "PNHelper.h"

PNOctahedron::PNOctahedron(float scale) {
    this->scale = scale;

    //base points
    Point_3 p0 = Point_3(0, 0, scale);
    Point_3 p1 = Point_3(0, 0, -scale);
    Point_3 p2 = Point_3(scale, 0, 0);
    Point_3 p3 = Point_3(-scale, 0, 0);
    Point_3 p4 = Point_3(0, scale, 0);
    Point_3 p5 = Point_3(0, -scale, 0);

    //basePoints[0] = p0; basePoints[1] = p1; basePoints[2] = p2;
    //basePoints[3] = p3; basePoints[4] = p4; basePoints[5] = p5;
}

void PNOctahedron::drawOctahedron() {

}