#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Point_3 Point_3;

class Triangle {
private:
    Point_3 point1;
    Point_3 point2;
    Point_3 point3;
public:
    Triangle(Point_3 _point1 = Point_3(0, 0, 0), Point_3 _point2 = Point_3(0, 0, 0), Point_3 _point3 = Point_3(0, 0, 0)) {
        point1 = _point1;
        point2 = _point2;
        point3 = _point3;
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

    void setPoint1(Point_3 point) {
        point1 = point;
    }

    void setPoint2(Point_3 point) {
        point2 = point;
    }

    void setPoint3(Point_3 point) {
        point3 = point;
    }
};