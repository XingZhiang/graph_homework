/*
 * 点类
 */
#pragma once
#ifndef GRAPH_LAB_POINT_H
#define GRAPH_LAB_POINT_H
#include <GL/glut.h>

typedef unsigned int uint;

class Point{
public:
    int x;
    int y;
public:
    Point(int x_value, int y_value):x(x_value),y(y_value){}
    Point(Point &p):x(p.x),y(p.y){}
};

/*********************************
* 点亮像素点函数
*********************************/
void setPixel(int x, int y) {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}
#endif //GRAPH_LAB_POINT_H
