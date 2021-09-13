#pragma once
#ifndef GRAPH_LAB_LINE_H
#define GRAPH_LAB_LINE_H
#include <GL/glut.h>
#include <cmath>

class Line{
private:
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;

public:
    Line() = delete;
    Line(int xS, int yS, int xE, int yE);
private:
    static void setPixel(int x, int y);
    static void DDA(int xS, int yS, int xE, int yE);

public:
    void drawByDDA() const;
};

Line::Line(int xS, int yS, int xE, int yE):
    xStart(xS),yStart(yS),xEnd(xE),yEnd(yE){}

    static void setPixel(int x, int y) {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void Line::setPixel(int x, int y) {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void Line::DDA(int xS, int yS, int xE, int yE) {
    int dx = xE - xS, dy = yE - yS, steps = 0;
    float xIncrement, yIncrement, x = xS, y = yS;
    steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    xIncrement = float(dx) / float(steps);
    yIncrement = float(dy) / float(steps);

    setPixel(static_cast<int>(x + 0.5), static_cast<int>(x + 0.5));
    for (int i = 0; i < steps; ++i) {
        x += xIncrement;
        y += yIncrement;
        setPixel(static_cast<int>(x + 0.5), static_cast<int>(x + 0.5));
    }
}

void Line::drawByDDA() const {
    DDA(xStart, yStart, xEnd, yEnd);
}

#endif //GRAPH_LAB_LINE_H
