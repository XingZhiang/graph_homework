/*
 * 点类
 */
#pragma once
#ifndef GRAPH_LAB_POINT_H
#define GRAPH_LAB_POINT_H
#include <GL/glut.h>

#define XL 200
#define XR 600
#define YB 125
#define YT 375

extern COLOR pen;
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
    void set(int x_value, int y_value) {
        x = x_value;
        y = y_value;
    }
    COLOR getColor();
    bool isValid();
    bool inWindow();
    bool operator==(Point& p) {
        return x == p.x && y == p.y;
    }
};

bool Point::isValid() {
    return x < 0 || x >= winWidth || y < 0 || y >= winWidth;
}

bool Point::inWindow()
{
    return x >= XL && x <= XR && y >= YB && y <= YT;
}

/*********************************
* 点亮像素点函数
*********************************/
void setPixel(int x, int y, COLOR c = pen) {
    glColor3f(c.R / 255.0f, c.G / 255.0f, c.B / 255.0f);
    if (x >= 0 && x <= 800 && y >= 0 && y <= 500)
        winColor[x][y] = c;
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

COLOR Point::getColor() {
    return winColor[x][y];
}

#endif //GRAPH_LAB_POINT_H
