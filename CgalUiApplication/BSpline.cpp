#include "BSpline.h"
#include <QtOpenGL\qgl.h>

double* BSpline::calculateSplineCoeffs3(double t) {
    double* coefs = new double[4];

    coefs[0] = pow(1.0 - t, 3) / 6.0;
    coefs[1] = (3.0*t*t*t - 6.0*t*t + 4) / 6.0;
    coefs[2] = (-3.0*t*t*t + 3 * t*t + 3 * t + 1) / 6.0;
    coefs[3] = t*t*t / 6.0;

    return coefs;
}

double* BSpline::calculateSplineCoeffs2(double t) {
    double* coefs = new double[3];

    coefs[0] = (1.0 - t) * (1.0 - t) / 2.0;
    coefs[1] = (-2.0 * t * t + 2 * t + 1) / 2.0;
    coefs[2] = t * t / 2.0;

    return coefs;
}

BSpline::BSpline(Points3* points, int k, int stepCount, bool closed) {
    this->closed = closed;
    this->stepCount = stepCount;
    this->points = points;

    this->coeffs = std::vector<double*>();
    for (int i = 0; i < stepCount; i++) {
        double* coef = k == 3 ? calculateSplineCoeffs3(i / (double) stepCount) : calculateSplineCoeffs2(i / (double) stepCount);
        coeffs.push_back(coef);
    }
}
void BSpline::drawSegment3(int segNum) {
    int pNum = points->size();
    int p0, p1, p2, p3;

    if (!closed) {
        p0 = clamp(segNum - 1, 0, pNum - 1);
        p1 = clamp(segNum, 0, pNum - 1);
        p2 = clamp(segNum + 1, 0, pNum - 1);
        p3 = clamp(segNum + 2, 0, pNum - 1);
    } else {
        p0 = (segNum - 1 + pNum) % pNum;
        p1 = (segNum + pNum) % pNum;
        p2 = (segNum + 1 + pNum) % pNum;
        p3 = (segNum + 2 + pNum) % pNum;
    }

    for (int i = 0; i < stepCount; i++) {
        double x = coeffs.at(i)[0] * points->at(p0).x()
            + coeffs.at(i)[1] * points->at(p1).x()
            + coeffs.at(i)[2] * points->at(p2).x()
            + coeffs.at(i)[3] * points->at(p3).x();
        double y = coeffs.at(i)[0] * points->at(p0).y()
            + coeffs.at(i)[1] * points->at(p1).y()
            + coeffs.at(i)[2] * points->at(p2).y()
            + coeffs.at(i)[3] * points->at(p3).y();
        double z = coeffs.at(i)[0] * points->at(p0).z()
            + coeffs.at(i)[1] * points->at(p1).z()
            + coeffs.at(i)[2] * points->at(p2).z()
            + coeffs.at(i)[3] * points->at(p3).z();
        glVertex3f(x, y, z);
    }
}

void BSpline::drawSegment2(int segmentIndex) {
    int pNum = points->size();
    int p0, p1, p2;

    if (!closed) {
        p0 = clamp(segmentIndex - 1, 0, pNum - 1);
        p1 = clamp(segmentIndex, 0, pNum - 1);
        p2 = clamp(segmentIndex + 1, 0, pNum - 1);
    }
    else {
        p0 = (segmentIndex - 1 + pNum) % pNum;
        p1 = (segmentIndex + pNum) % pNum;
        p2 = (segmentIndex + 1 + pNum) % pNum;
    }

    for (int i = 0; i < stepCount; i++) {
        double x = coeffs.at(i)[0] * points->at(p0).x()
            + coeffs.at(i)[1] * points->at(p1).x()
            + coeffs.at(i)[2] * points->at(p2).x();
        double y = coeffs.at(i)[0] * points->at(p0).y()
            + coeffs.at(i)[1] * points->at(p1).y()
            + coeffs.at(i)[2] * points->at(p2).y();
        double z = coeffs.at(i)[0] * points->at(p0).z()
            + coeffs.at(i)[1] * points->at(p1).z()
            + coeffs.at(i)[2] * points->at(p2).z();
        glVertex3f(x, y, z);
    }
}

void BSpline::drawSplineCurve(int k) {
    int segmentsCount;
    if (closed == false) {
        segmentsCount = points->size() - 1;
        glBegin(GL_LINE_STRIP);
    } else {
        segmentsCount = points->size();
        glBegin(GL_LINE_LOOP);
    }
    glColor3f(1.0f, 1.0f, 0.0f);
    for (int i = 0; i < segmentsCount; i++) {
        if (k == 3) {
            drawSegment3(i);
        }
        else if (k == 2) {
            drawSegment2(i);
        }
    }
    glEnd();

}

BSpline::~BSpline() {
}