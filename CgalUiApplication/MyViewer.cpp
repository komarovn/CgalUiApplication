#include "MyViewer.h"

#define PI 3.1415926535

MyViewer::MyViewer(QWidget* parent) : QGLViewer(parent) {
    setBackgroundColor(QColor(139, 169, 180));
    setForegroundColor(QColor(139, 169, 180));
}

void MyViewer::draw() {
    glPointSize(2.0);
    //glColor3f(1.0f, .6f, 0.8f);
    glBegin(GL_POINTS);
    for (int i = 0; i < points.size(); ++i) {
        float color = (double) rand() / (RAND_MAX);
        glColor3f(1.0f, color, color * color);
        glVertex3f(points[i].x(), points[i].y(), points[i].z());
    }
    glEnd();
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
        if (abs(points[i].y() - y) < 0.01f && abs(points[i].x() - x) < 0.01f) {
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
        //const QPoint point = QMouseEvent::pos();
        //std::vector<int> selected = getSelectedPoints(point);

        //for (int i = 0; i < selected.size(); i++) {
            //points.erase(selected[i]);
        //}
    }
    else {
        QGLViewer::mousePressEvent(event);
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