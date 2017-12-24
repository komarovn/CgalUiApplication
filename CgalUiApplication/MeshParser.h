#pragma once

#include "typedefs.h"
#include <math.h>
#include <QtOpenGL\qgl.h>

class Tetrahedron {
private:
    Point_3 point1;
    Point_3 point2;
    Point_3 point3;
    Point_3 point4;
public:
    Tetrahedron(Point_3 _point1 = Point_3(0, 0, 0), Point_3 _point2 = Point_3(0, 0, 0), Point_3 _point3 = Point_3(0, 0, 0), Point_3 _point4 = Point_3(0, 0, 0)) {
        point1 = _point1;
        point2 = _point2;
        point3 = _point3;
        point4 = _point4;
    }

    Point_3 getPoint1() {
        return point1;
    }

    Point_3 getPoint2() {
        return point2;
    }

    Point_3 getPoint3() {
        return point3;
    }

    Point_3 getPoint4() {
        return point4;
    }

    void setPoint1(Point_3 point) {
        point1 = point;
    }

    void setPoint2(Point_3 point) {
        point2 = point;
    }

    void setPoint3(Point_3 point) {
        point3 = point;
    }

    void setPoint4(Point_3 point) {
        point4 = point;
    }
};

typedef std::vector<Tetrahedron> Tetrahedra;

class MeshParser {
private:
    std::string fileName;
    Points3 points;
    Triangles triangles;
    Tetrahedra tetrahedra;
public:
    MeshParser(std::string fileName);
    std::ifstream openFile();
    void closeFile(std::ifstream &is);
    void parse();

    Points3 getPoints();
    Triangles getTriangles();
    Tetrahedra getTetrahedra();
};