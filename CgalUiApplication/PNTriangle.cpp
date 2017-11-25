#include "PNTriangle.h"
#include "PNHelper.h"

PNTriangle::PNTriangle(Point_3 p1, Point_3 p2, Point_3 p3,
    Point_3 n1, Point_3 n2, Point_3 n3) {
    p300 = p1; p030 = p2; p003 = p3;
    n200 = n1; n020 = n2; n002 = n3;
}

void PNTriangle::drawTriangle(int level) {
    int trianglesCount = (level + 1) * (level + 1);
    double size = 1.0 / (double) (level + 1);
    Triangles triangles;

    int *level_counter = new int[level + 1];
    for (int i = 0; i <= level; i++) {
        level_counter[i] = 1 + 2 * i;
    }

    triangles.push_back(Triangle(Point_3(0, 0, 1), Point_3(size, 0, 1 - size), Point_3(0, size, 1 - size)));

    int side = 1;

    for (int i = 0; i <= level; i++)
        for (int j = 0; j < level_counter[i]; j++) {
            if (j == 0 && i != 0) {
                Point_3 point2 = triangles[triangles.size() - level_counter[i - 1]].getPoint2();
                triangles.push_back(Triangle(
                    point2,
                    Point_3(point2.x() + size, 0, point2.z() - size),
                    Point_3(point2.x(), point2.y() + size, point2.z() - size)));
            }
            else if (j != 0) {
                Point_3 point1 = triangles.back().getPoint1();
                Point_3 point2 = triangles.back().getPoint2();
                Point_3 point3 = triangles.back().getPoint3();
                if (side == 0) {
                    triangles.push_back(Triangle(
                        point2,
                        point3,
                        Point_3(point2.x(), point2.y() + size, point2.z() - size)));
                    side = 1;
                }
                else {
                    triangles.push_back(Triangle(
                        point1,
                        Point_3(point1.x() - size, point1.y() + size, point1.z()),
                        Point_3(point1.x(), point1.y() + size, point1.z() - size)));
                    side = 0;
                }
            }

        }

    calcPNcoefs();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.2, 0.6, 0.9);
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < trianglesCount; i++) {
        Point_3 point1 = triangles[i].getPoint1();
        Point_3 point2 = triangles[i].getPoint2();
        Point_3 point3 = triangles[i].getPoint3();

        //glColor3f(0.0, 0.0, 1.0);
        drawPoint(point1.x(), point1.y(), point1.z());
        //glColor3f(0.0, 1.0, 0.0);
        drawPoint(point2.x(), point2.y(), point2.z());
        //glColor3f(1.0, 0.0, 0.0);
        drawPoint(point3.x(), point3.y(), point3.z());
    }

    glEnd();
}

void PNTriangle::drawPoint(double u, double v, double w) {
    Point_3 p = calculateP(u, v, w);
    Point_3 n = calculateN(u, v, w);
    glNormal3f(n.x(), n.y(), n.z());
    glVertex3f(p.x(), p.y(), p.z());
}

void PNTriangle::calcPNcoefs() {
    n110 = nn(n200, n020);
    n101 = nn(n200, n002);
    n011 = nn(n020, n002);

    p210 = bb(p300, p030, n200);
    p120 = bb(p030, p300, n020);
    p021 = bb(p030, p003, n020);
    p012 = bb(p003, p030, n002);
    p201 = bb(p300, p003, n200);
    p102 = bb(p003, p300, n002);

    double Ex = (p210.x() + p120.x() + p021.x()
        + p012.x() + p201.x() + p102.x()) / 6.0;
    double Ey = (p210.y() + p120.y() + p021.y()
        + p012.y() + p201.y() + p102.y()) / 6.0;
    double Ez = (p210.z() + p120.z() + p021.z()
        + p012.z() + p201.z() + p102.z()) / 6.0;
    double Vx = (p300.x() + p030.x() + p003.x()) / 3.0;
    double Vy = (p300.y() + p030.y() + p003.y()) / 3.0;
    double Vz = (p300.z() + p030.z() + p003.z()) / 3.0;
    p111 = Point_3(1.5 * Ex - 0.5 * Vx,
        1.5 * Ey - 0.5 * Vy,
        1.5 * Ez - 0.5 * Vz);
}

Point_3 PNTriangle::calculateP(double u, double v, double w) {
    float x = (p300.x() * u + 3 * p210.x() * v + 3 * p201.x() * w) * u * u +
        (p030.x() * v + 3 * p120.x() * u + 3 * p021.x() * w) * v * v +
        (p003.x() * w + 3 * p012.x() * v + 3 * p102.x() * u) * w * w +
        6 * p111.x() * u * v * w;
    float y = (p300.y() * u + 3 * p210.y() * v + 3 * p201.y() * w) * u * u +
        (p030.y() * v + 3 * p120.y() * u + 3 * p021.y() * w) * v * v +
        (p003.y() * w + 3 * p012.y() * v + 3 * p102.y() * u) * w * w +
        6 * p111.y() * u * v * w;
    float z = (p300.z() * u + 3 * p210.z() * v + 3 * p201.z() * w) * u * u +
        (p030.z() * v + 3 * p120.z() * u + 3 * p021.z() * w) * v * v +
        (p003.z() * w + 3 * p012.z() * v + 3 * p102.z() * u) * w * w +
        6 * p111.z() * u * v * w;
    return Point_3(x, y, z);
}

Point_3 PNTriangle::calculateN(double u, double v, double w) {
    return Point_3(
        n200.x() * u * u + n020.x() * v * v + n002.x() * w * w +
        2 * n110.x() * u * v + 2 * n011.x() * v * w + 2 * n101.x() * u * w,
        n200.y() * u * u + n020.y() * v * v + n002.y() * w * w +
        2 * n110.y() * u * v + 2 * n011.y() * v * w + 2 * n101.y() * u * w,
        n200.z() * u * u + n020.z() * v * v + n002.z() * w * w +
        2 * n110.z() * u * v + 2 * n011.z() * v * w + 2 * n101.z() * u * w
    );
}