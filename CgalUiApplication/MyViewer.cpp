#include "MyViewer.h"

#include <QMouseEvent>
#include <typedefs.h>
#include "ChaikinAlgorythm.h"
#include "MeshParser.h"


#define PI 3.1415926535

double len1(Point_3 p) {
    return sqrt(p.x() * p.x() + p.y() * p.y() + p.z() * p.z());
}

Point_3 normalize1(Point_3 p) {
    double length = len1(p);
    return Point_3(p.x() / length, p.y() / length, p.z() / length);
}

Point_3 calculateNormal1(Point_3 base, Point_3 point1, Point_3 point2) {
    Point_3 v1 = Point_3(point1.x() - base.x(), point1.y() - base.y(), point1.z() - base.z());
    Point_3 v2 = Point_3(point2.x() - base.x(), point2.y() - base.y(), point2.z() - base.z());

    Point_3 normal = Point_3(v1.y() * v2.z() - v2.y() * v1.z(),
        -v1.x() * v2.z() + v2.x() * v1.z(),
        v1.x() * v2.y() - v2.x() * v1.y());

    return normalize1(normal);
}

double calcScalar(Point_3 p1, Point_3 p2) {
    return p1.x() * p2.x() + p1.y() * p2.y() + p1.x() * p2.y();
}

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

    /*glBegin(GL_LINES);
    glColor3f(240.0f, 15.0f, 23.0f);
    for (int i = 0; i < triangles.size(); ++i) {
        Triangle triangle = triangles[i];
        glVertex3f(triangle.getPoint1().x(), triangle.getPoint1().y(), triangle.getPoint1().z());
        glVertex3f(triangle.getPoint2().x(), triangle.getPoint2().y(), triangle.getPoint2().z());
        glVertex3f(triangle.getPoint2().x(), triangle.getPoint2().y(), triangle.getPoint2().z());
        glVertex3f(triangle.getPoint3().x(), triangle.getPoint3().y(), triangle.getPoint3().z());
        glVertex3f(triangle.getPoint3().x(), triangle.getPoint3().y(), triangle.getPoint3().z());
        glVertex3f(triangle.getPoint1().x(), triangle.getPoint1().y(), triangle.getPoint1().z());
    }
    glEnd();*/

    /*glBegin(GL_LINES);
    glColor3f(.9f, .3f, .1f);
    for (int i = 0; i < tetrahedra.size(); i++) {
        Tetrahedron tetrahedron = tetrahedra[i];
        glVertex3f(tetrahedron.getPoint1().x(), tetrahedron.getPoint1().y(), tetrahedron.getPoint1().z());
        glVertex3f(tetrahedron.getPoint2().x(), tetrahedron.getPoint2().y(), tetrahedron.getPoint2().z());

        glVertex3f(tetrahedron.getPoint3().x(), tetrahedron.getPoint3().y(), tetrahedron.getPoint3().z());
        glVertex3f(tetrahedron.getPoint4().x(), tetrahedron.getPoint4().y(), tetrahedron.getPoint4().z());

        glVertex3f(tetrahedron.getPoint1().x(), tetrahedron.getPoint1().y(), tetrahedron.getPoint1().z());
        glVertex3f(tetrahedron.getPoint4().x(), tetrahedron.getPoint4().y(), tetrahedron.getPoint4().z());

        glVertex3f(tetrahedron.getPoint2().x(), tetrahedron.getPoint2().y(), tetrahedron.getPoint2().z());
        glVertex3f(tetrahedron.getPoint4().x(), tetrahedron.getPoint4().y(), tetrahedron.getPoint4().z());

        glVertex3f(tetrahedron.getPoint1().x(), tetrahedron.getPoint1().y(), tetrahedron.getPoint1().z());
        glVertex3f(tetrahedron.getPoint3().x(), tetrahedron.getPoint3().y(), tetrahedron.getPoint3().z());

        glVertex3f(tetrahedron.getPoint2().x(), tetrahedron.getPoint2().y(), tetrahedron.getPoint2().z());
        glVertex3f(tetrahedron.getPoint3().x(), tetrahedron.getPoint3().y(), tetrahedron.getPoint3().z());
    }
    glEnd();*/

    glBegin(GL_TRIANGLES);
    glColor3f(.9f, .3f, .1f);
    for (int i = 0; i < tetrahedra.size(); i++) {
        Tetrahedron tetrahedron = tetrahedra[i];
        glVertex3f(tetrahedron.getPoint1().x(), tetrahedron.getPoint1().y(), tetrahedron.getPoint1().z());
        glVertex3f(tetrahedron.getPoint2().x(), tetrahedron.getPoint2().y(), tetrahedron.getPoint2().z());
        glVertex3f(tetrahedron.getPoint3().x(), tetrahedron.getPoint3().y(), tetrahedron.getPoint3().z());
    }
    glEnd();

    glBegin(GL_LINES);
    for (int i = 0; i < triangles.size(); i++) {
        Triangle triangle = triangles[i];

        glVertex3f(triangle.getPoint1().x(), triangle.getPoint1().y(), triangle.getPoint1().z());
        Point_3 normal = calculateNormal1(triangle.getPoint1(), triangle.getPoint2(), triangle.getPoint3());
        glVertex3f(triangle.getPoint1().x() + normal.x(), triangle.getPoint1().y() + normal.y(), triangle.getPoint1().z() + normal.z());

        //glVertex3f(tetrahedron.getPoint2().x(), tetrahedron.getPoint2().y(), tetrahedron.getPoint2().z());
        //glVertex3f(tetrahedron.getPoint3().x(), tetrahedron.getPoint3().y(), tetrahedron.getPoint3().z());
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
    if (isChaikin) {
        if (chaikinAlgorythm != nullptr) {
            chaikinAlgorythm->drawQuadrangle();
        }
    }
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

void MyViewer::applyChaikinAlgorithm() {
    if (chaikinAlgorythm == nullptr) {
        std::vector<ChaikinPoint> points;
        points.push_back(ChaikinPoint(Point_3(-0.5, -0.5, 0), 1));
        points.push_back(ChaikinPoint(Point_3(-0.5, 0.5, 0), 2));
        points.push_back(ChaikinPoint(Point_3(0.5, -0.5, 0), 3));
        points.push_back(ChaikinPoint(Point_3(0.5, 0.5, 0), 2));
        chaikinAlgorythm = new ChaikinAlgorythm(points);
    }
    chaikinAlgorythm->apply();
    chaikinAlgorythm->drawQuadrangle();
    this->update();
}

void MyViewer::parseFile() {
    MeshParser parser = MeshParser("Resources/out_bis.mesh");
    parser.parse();
    points.clear();
    //for (Point_3 point : parser.getPoints()) {
    //    points.push_back(point);
    //}
    for (Triangle triangle : parser.getTriangles()) {
        triangles.push_back(triangle);
    }
    for (Tetrahedron tetrahedron : parser.getTetrahedra()) {
        tetrahedra.push_back(tetrahedron);
    }
}