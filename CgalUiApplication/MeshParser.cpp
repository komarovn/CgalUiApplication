#include "MeshParser.h"
#include <fstream>
#include <iostream>

MeshParser::MeshParser(std::string fileName_) : fileName(fileName_) {}

std::ifstream MeshParser::openFile() {
    std::ifstream is(fileName);
    return is;
}

void MeshParser::closeFile(std::ifstream &is) {
    is.close();
}

void MeshParser::parse() {
    std::ifstream is = openFile();

    while (!is.eof()) {
        std::string out;
        is >> out;
        if (out == "Vertices") {
            is >> out;
            int size = atoi(out.c_str());
            for (int i = 0; i < size; i++) {
                double x, y, z;
                for (int j = 0; j < 4; j++) {
                    std::string coord;
                    is >> coord;
                    switch (j)
                    {
                    case 0:
                        x = atof(coord.c_str());
                        break;
                    case 1:
                        y = atof(coord.c_str());
                        break;
                    case 2:
                        z = atof(coord.c_str());
                        break;
                    case 3:
                        break;
                    }
                }
                points.push_back(Point_3(x/100, y/100, z/100));
            }
        }
        if (out == "Triangles") {
            is >> out;
            int size = atoi(out.c_str());
            for (int i = 0; i < size; i++) {
                int k1, k2, k3;
                for (int j = 0; j < 4; j++) {
                    std::string coord;
                    is >> coord;
                    switch (j)
                    {
                    case 0:
                        k1 = atoi(coord.c_str());
                        break;
                    case 1:
                        k2 = atoi(coord.c_str());
                        break;
                    case 2:
                        k3 = atoi(coord.c_str());
                        break;
                    default:
                        break;
                    }
                }
                triangles.push_back(Triangle(points[k1 - 1], points[k2 - 1], points[k3 - 1]));
            }
        }

        if (out == "Tetrahedra") {
            is >> out;
            int size = atoi(out.c_str());
            for (int i = 0; i < size; i++) {
                int m1, m2, m3, m4;
                for (int j = 0; j < 5; j++) {
                    std::string coord;
                    is >> coord;
                    switch (j)
                    {
                    case 0:
                        m1 = atoi(coord.c_str());
                        break;
                    case 1:
                        m2 = atoi(coord.c_str());
                        break;
                    case 2:
                        m3 = atoi(coord.c_str());
                        break;
                    case 3:
                        m4 = atoi(coord.c_str());;
                        break;
                    default:
                        break;
                    }
                }
                tetrahedra.push_back(Tetrahedron(points[m1 - 1], points[m2 - 1], points[m3 - 1], points[m4 - 1]));
            }
        }
    }


    closeFile(is);
}

Points3 MeshParser::getPoints() {
    return this->points;
}

Triangles MeshParser::getTriangles() {
    return this->triangles;
}

Tetrahedra MeshParser::getTetrahedra() {
    return this->tetrahedra;
}