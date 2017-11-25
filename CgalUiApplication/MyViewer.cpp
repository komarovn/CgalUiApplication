#include "MyViewer.h"

#include <QMouseEvent>
#include <typedefs.h>

#define PI 3.1415926535

MyViewer::MyViewer(QWidget* parent) : QGLViewer(parent) {
    setBackgroundColor(QColor(139, 169, 180));
    setForegroundColor(QColor(139, 169, 180));
}

void MyViewer::draw() {
    glPointSize(2.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < points.size(); ++i) {
        float color = (double) rand() / (RAND_MAX);
        glColor3f(1.0f, color, color * color);
        glVertex3f(points[i].x(), points[i].y(), points[i].z());
    }
    glEnd();
    if (isSpline) {
        BSpline spline = BSpline(&points);
        drawBSpline(spline);
    }
    if (isTriangle) {
        drawTriangle();
    }
    if (isOctahedron) {
        drawOctahedron();
    }

    std::vector<Point_3> points;
    points.push_back(Point_3(-0.5, -0.5, 0));
    points.push_back(Point_3(-0.5, 0.5, 0));
    points.push_back(Point_3(0.5, -0.5, 0));
    points.push_back(Point_3(0.5, 0.5, 0));

    ChaikinAlgorythm chaikinAlgorythm(points);
    chaikinAlgorythm.apply();
    chaikinAlgorythm.apply();
    chaikinAlgorythm.apply(); 
    chaikinAlgorythm.apply();
    chaikinAlgorythm.apply();
    chaikinAlgorythm.apply();
    chaikinAlgorythm.drawQuadrangle();
}

void MyViewer::init() {
    restoreStateFromFile();
    points.push_back(Point_3(0.1, 0.1, 0.1));
}

std::vector<int> MyViewer::getSelectedPoints(const QPoint &point) {
    qglviewer::Vec orig, dir;
    camera()->convertClickToLine(point, orig, dir);
    std::vector<int> selected = std::vector<int>();

    for (int i = 0; i < points.size(); i++) {
        float t = (points[i].z() - orig.z) / dir.z;
        float x = orig.x + dir.x * t;
        float y = orig.y + dir.y * t;
        if (abs(points[i].y() - y) < 0.04f && abs(points[i].x() - x) < 0.04f) {
            selected.push_back(i);
        }
    }
    return selected;
}

void MyViewer::postSelection(const QPoint &point) {
    std::vector<int> selected = getSelectedPoints(point);
    QString result;

    for (int i = 0; i < selected.size(); i++) {
        QString tmp = "Vertex number " + QString::number(selected[i]) + ": " +
            QString::number(points[selected[i]].x()) + " " +
            QString::number(points[selected[i]].y()) + " " +
            QString::number(points[selected[i]].z()) + "\n";
        result.append(tmp);
    }
    QMessageBox::information(this, "Selection", result);
}

void MyViewer::mousePressEvent(QMouseEvent *event) {
    if (isRemovePointMode) {
        const QPoint point = event->pos();
        std::vector<int> selected = getSelectedPoints(point);

        for (int i = 0; i < selected.size(); i++) {
            points.erase(points.begin() + selected[i]);
        }

        update();
    }
    else if (isMovePointMode) {
        const QPoint point = event->pos();
        std::vector<int> selected = getSelectedPoints(point);

        if (selected.size() > 0) {
            //movePoint = &points[selected[0]];
            movePointIndex = selected[0];
        }

        oldMousePosition = new QPoint(point);
    } else {
        QGLViewer::mousePressEvent(event);
    }
}

void MyViewer::mouseMoveEvent(QMouseEvent *event) {
    if (isMovePointMode) {
        if (movePointIndex != -1) {
            int x = event->x();
            int y = event->y();

            int dx = x - oldMousePosition->x();
            int dy = y - oldMousePosition->y();

            delete oldMousePosition;
            oldMousePosition = new QPoint(event->pos());

            Point_3 oldPoint = points.at(movePointIndex);
            points.at(movePointIndex) = Point_3(oldPoint.x() + 0.01f * dx, oldPoint.y() + 0.01f * dy, oldPoint.z());

            update();
        }
    } else {
        QGLViewer::mouseMoveEvent(event);
    }
}

void MyViewer::mouseReleaseEvent(QMouseEvent *event) {
    if (isMovePointMode) {
        //movePoint = nullptr;
        movePointIndex = -1;
        oldMousePosition = nullptr;
    } else {
        QGLViewer::mouseReleaseEvent(event);
    }
}

void MyViewer::removeAllPoints() {
    points.clear();
}

void MyViewer::generateCube() {
    removeAllPoints();
    for (int i = -5; i <= 5; i++) {
        for (int j = -5; j <= 5; j++) {
            for (int k = -5; k <= 5; k++) {
                points.push_back(Point_3(i * 0.1, j * 0.1, k * 0.1));
            }
        }
    }
}

void MyViewer::generateCubeVolume() {
    removeAllPoints();
    int boundary = 5;
    for (int i = -boundary; i <= boundary; i++) {
        for (int j = -boundary; j <= boundary; j++) {
            for (int k = -boundary; k <= boundary; k++) {
                float x = (i == 0 ? ((double) rand() / (RAND_MAX) - 0.5) : i) * 0.1 * ((double) rand() / (RAND_MAX) + 1);
                float y = (j == 0 ? ((double) rand() / (RAND_MAX) - 0.5) : j) * 0.1 * ((double) rand() / (RAND_MAX) + 1);
                float z = (k == 0 ? ((double) rand() / (RAND_MAX) - 0.5) : k) * 0.1 * ((double) rand() / (RAND_MAX) + 1);
                points.push_back(Point_3(x > boundary * 0.1 ? boundary * 0.1 : (x < -boundary * 0.1 ? -boundary * 0.1 : x),
                    y > boundary * 0.1 ? boundary * 0.1 : (y < -boundary * 0.1 ? -boundary * 0.1 : y),
                    z > boundary * 0.1 ? boundary * 0.1 : (z < -boundary * 0.1 ? -boundary * 0.1 : z)));
            }
        }
    }
}

void MyViewer::generateSphere() {
    removeAllPoints();
    int boundary = 5;
    for (int i = -boundary; i <= boundary; i++) {
        for (int j = -boundary; j <= boundary; j++) {
            for (int k = -boundary; k <= boundary; k++) {
                float x = (i == 0 ? ((double) rand() / (RAND_MAX) - 0.5) : i) * 0.1 * ((double) rand() / (RAND_MAX) + 1);
                float y = (j == 0 ? ((double) rand() / (RAND_MAX) - 0.5) : j) * 0.1 * ((double) rand() / (RAND_MAX) + 1);
                float z = (k == 0 ? ((double) rand() / (RAND_MAX) - 0.5) : k) * 0.1 * ((double) rand() / (RAND_MAX) + 1);
                if (x * x + y * y + z * z <= boundary * boundary * 0.01) {
                    points.push_back(Point_3(x, y, z));
                }
            }
        }
    }
}

void MyViewer::generateSphereVolume() {
    removeAllPoints();
    int boundary = 5;
    for (int i = -boundary; i <= boundary; i++) {
        for (int j = -boundary; j <= boundary; j++) {
            for (int k = -boundary; k <= boundary; k++) {
                float randNumber1 = (double) rand() / (RAND_MAX);
                float randNumber2 = (double) rand() / (RAND_MAX) + 1;
                float randNumber3 = (double) rand() / (RAND_MAX) - 2;
                float x1 = boundary * 0.1 * cos((float) PI * randNumber2 * randNumber3) * sin((float) PI * randNumber1);
                float y1 = boundary * 0.1 * sin((float) PI * randNumber2 * randNumber3) * sin((float) PI * randNumber1);
                float z1 = boundary * 0.1 * cos((float) PI * randNumber1);
                points.push_back(Point_3(x1, y1, z1));
            }
        }
    }
}

void MyViewer::drawBSpline(BSpline bSpline) {
    bSpline.drawSplineCurve(k);
}

void MyViewer::drawTriangle() {
    this->pnTriangle.drawTriangle(detalizationLevel);
}

void MyViewer::drawOctahedron() {
    this->pnOctahedron.drawOctahedron(detalizationLevel);
}