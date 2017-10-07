#include "MyViewer.h"

MyViewer::MyViewer(QWidget* parent) : QGLViewer(parent) {
}

void MyViewer::draw() {
    glPointSize(3.0);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < points.size(); ++i) {
        glVertex3f(points[i].x(), points[i].y(), points[i].z());
    }
    glEnd();
}

void MyViewer::init() {
    restoreStateFromFile();
    points.push_back(Point_3(0.1, 0.1, 0.1));
}
