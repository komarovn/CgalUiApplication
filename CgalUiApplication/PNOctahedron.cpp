#include "PNOctahedron.h"

PNOctahedron::PNOctahedron(float scale) {
    this->scale = scale;

    //base points
    Point_3 p0 = Point_3(0, 0, scale);
    Point_3 p1 = Point_3(0, 0, -scale);
    Point_3 p2 = Point_3(scale, 0, 0);
    Point_3 p3 = Point_3(-scale, 0, 0);
    Point_3 p4 = Point_3(0, scale, 0);
    Point_3 p5 = Point_3(0, -scale, 0);

    triangles.push_back(PNTriangle(p0, p4, p3, p0, p4, p3));
    triangles.push_back(PNTriangle(p0, p2, p4, p0, p2, p4));
    triangles.push_back(PNTriangle(p0, p5, p2, p0, p5, p2));
    triangles.push_back(PNTriangle(p0, p5, p3, p0, p5, p3));

    triangles.push_back(PNTriangle(p3, p1, p5, p3, p1, p5));
    triangles.push_back(PNTriangle(p5, p1, p2, p5, p1, p2));
    triangles.push_back(PNTriangle(p2, p1, p4, p2, p1, p4));
    triangles.push_back(PNTriangle(p4, p1, p3, p4, p1, p3));
}

void PNOctahedron::drawOctahedron(int detalizationLevel) {
    for (int i = 0; i < triangles.size(); i++) {
        triangles.at(i).drawTriangle(detalizationLevel);
    }
}