#pragma once

#include <qglviewer.h>
#include <typedefs.h>

class MyViewer : public QGLViewer {
public:
    MyViewer(QWidget* parent);
    Points3 points;
protected:
    virtual void draw();
    virtual void init();
};
