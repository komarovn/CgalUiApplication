#include "ChaikinAlgorythm.h"
#include <math.h>

void ChaikinAlgorythm::drawQuadrangle() {
    glColor3f(0.2, 0.6, 0.9);
    glBegin(isLooped ? GL_LINE_LOOP : GL_LINE_STRIP);

    for (int i = 0; i < points.size(); i++) {
        Point_3 point = points.at(i).point;
        glVertex3f(point.x(), point.y(), point.z());
    }

    glEnd();
}

ChaikinAlgorythm::ChaikinAlgorythm(std::vector<ChaikinPoint> points) {
    this->points = points;
}

void ChaikinAlgorythm::apply() {
    std::vector<ChaikinPoint> newPoints;

    for (int i = 0; i < points.size(); i++) {
        ChaikinPoint leftPoint = points.at(i);
        ChaikinPoint rightPoint;
        if (i == points.size() - 1) {
            rightPoint = points.at(0);
            if (!isLooped) {
                continue;
            }
        } else {
            rightPoint = points.at(i + 1);
        }

        int weightLeft = leftPoint.weight;
        int weightRight = rightPoint.weight;
        float a = 1.0f / weightLeft;
        float c = 1.0f / weightRight;
        float b = 2.0f + a + c;
        float d = a > c ? c : a;

        float segmentLengthX = (rightPoint.point.x() - leftPoint.point.x()) * d / 4.0f;
        float segmentLengthY = (rightPoint.point.y() - leftPoint.point.y()) * d / 4.0f;
        float segmentLengthZ = (rightPoint.point.z() - leftPoint.point.z()) * d / 4.0f;

        newPoints.push_back(ChaikinPoint(
            Point_3(
                leftPoint.point.x() + segmentLengthX / a,
                leftPoint.point.y() + segmentLengthY / a,
                leftPoint.point.z() + segmentLengthZ / a
                ), weightLeft)
        );

        newPoints.push_back(ChaikinPoint(
            Point_3(
                rightPoint.point.x() - segmentLengthX / c,
                rightPoint.point.y() - segmentLengthY / c,
                rightPoint.point.z() - segmentLengthZ / c
            ), weightRight)
        );
    }

    points.clear();
    points.insert(points.end(), newPoints.begin(), newPoints.end());
}
