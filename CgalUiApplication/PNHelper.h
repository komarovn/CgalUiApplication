#pragma once

double w(Point_3 i, Point_3 j, Point_3 n) {
    Point_3 dv = Point_3(j.x() - i.x(), j.y() - i.y(), j.z() - i.z());
    return (dv.x()* n.x() + dv.y() * n.y() + dv.z() * n.z());
}

Point_3 bb(Point_3 i, Point_3 j, Point_3 normal) {
    double w2 = w(i, j, normal);
    return Point_3(
        (2.0 * i.x() + j.x() - w2 * normal.x()) / 3.0,
        (2.0 * i.y() + j.y() - w2 * normal.y()) / 3.0,
        (2.0 * i.z() + j.z() - w2 * normal.z()) / 3.0);
}

double len(Point_3 p) {
    return sqrt(p.x() * p.x() + p.y() * p.y() + p.z() * p.z());
}

Point_3 normalize(Point_3 p) {
    double length = len(p);
    return Point_3(p.x() / length, p.y() / length, p.z() / length);
}

Point_3 nn(Point_3 i, Point_3 j) {
    Point_3 dv = Point_3(j.x() - i.x(), j.y() - i.y(), j.z() - i.z());
    Point_3 vij = Point_3(2.0 * (dv.x() * (i.x() + j.x())) / len(dv) / len(dv),
        2.0 * (dv.x() * (i.x() + j.x())) / len(dv) / len(dv),
        2.0 * (dv.z() * (i.z() + j.z())) / len(dv) / len(dv));
    Point_3 nij = Point_3(
        i.x() + j.x() - vij.x() * dv.x(),
        i.y() + j.y() - vij.y() * dv.y(),
        i.z() + j.z() - vij.z() * dv.z()
    );
    return normalize(nij);
}
