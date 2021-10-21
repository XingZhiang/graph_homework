/*
 * 点类
 */
#pragma once
#ifndef GRAPH_LAB_POINT_H
#define GRAPH_LAB_POINT_H
#include <GL/glut.h>

extern COLOR winColor[800][500];
typedef unsigned int uint;
extern GLsizei winWidth, winHeight;

class Point{
public:
    int x;
    int y;
public:
    Point(int x_value, int y_value):x(x_value),y(y_value){}
    Point(const Point &p):x(p.x),y(p.y){}
    COLOR getColor();
    bool isValid();
};

bool Point::isValid() {
    return x < 0 || x >= winWidth || y < 0 || y >= winWidth;
}

/*********************************
* 点亮像素点函数
*********************************/
void setPixel(int x, int y, COLOR c = COLOR(0xff, 0, 0)) {
    glColor3f(c.R / 255.0f, c.G / 255.0f, c.B / 255.0f);
    winColor[x][y] = c;
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

COLOR Point::getColor() {
    return winColor[x][y];
}

#endif //GRAPH_LAB_POINT_H
