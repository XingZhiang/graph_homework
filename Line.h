#pragma once
#ifndef GRAPH_LAB_LINE_H
#define GRAPH_LAB_LINE_H

#include <cmath>
#include "Point.h"
#include<algorithm>

class Line {
private:
    Point start;
    Point end;

public:
    Line() = delete;

    Line(int xS, int yS, int xE, int yE);

    Line(Point s, Point e);

private:
    static void DDA(int xS, int yS, int xE, int yE);

    static void MidPoint(int xS, int yS, int xE, int yE);

    static void Bresenham(int xS, int yS, int xE, int yE);

public:
    void drawByDDA() const;

    void drawByMidPoint() const;

    void drawByBresenham() const;
};

Line::Line(int xS, int yS, int xE, int yE) :
        start(xS, yS), end(xE, yE) {}

void Line::DDA(int xS, int yS, int xE, int yE) {
    int dx = xE - xS, dy = yE - yS, steps = 0;
    float xIncrement, yIncrement, x = static_cast<float>(xS), y = static_cast<float>(yS);
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    xIncrement = float(dx) / float(steps);
    yIncrement = float(dy) / float(steps);

    setPixel(static_cast<int>(x + 0.5), static_cast<int>(y + 0.5));
    for (int i = 0; i < steps; ++i) {
        x += xIncrement;
        y += yIncrement;
        setPixel(static_cast<int>(x + 0.5), static_cast<int>(y + 0.5));
    }
}

void Line::drawByDDA() const {
    DDA(start.x, start.y, end.x, end.y);
}

void Line::MidPoint(int xS, int yS, int xE,
                    int yE) {                                                                                                                                  
    if (xS > xE) {
        std::swap(xS, xE);
        std::swap(yS, yE);
    }
    int a = yS - yE, b = xE - xS, c = xS * yE - xE *
                                                yS;                                                                           //ֱ直线方程 50 50 -250
    int u = a * b > 0 ? 0
                      : 1;                                                                                                     //斜率大于0时u=1，反之=0
    int delta0 = u == 1 ? a + a + b : a + a - b, delta1 = u == 1 ? a + a : a + a - b - b, delta2 =
            u == 1 ? a + a + b + b : a + a; //变化量 50 0 100
    int x = xS, y = yS;                                                                                                            //当前点坐标

    setPixel(x, y);
    if (abs(a) <= abs(b)) { //|k|<=1
        while (x < xE) {
            if (delta0 < 0) {
                x++, y += u;
                delta0 += delta2;
            } else {
                x++, y += u - 1;
                delta0 += delta1;
            }
            setPixel(x, y);
        }
    } else {
        delta0 = u == 1 ? b + b + a : -b - b + a, delta1 = u == 1 ? b + b + a + a : -b - b, delta2 =
                u == 1 ? b + b : -b - b + a + a;
        int d = u == 1 ? 1 : -1;
        while (abs(y - yE) > 0) {
            if (delta0 < 0) { //k>0时x不动，k<0时x+1
                y += d, x += 1 - u;
                delta0 += delta2;
            } else {
                y += d, x += u;
                delta0 += delta1;
            }
            setPixel(x, y);
        }
    }
}

void Line::drawByMidPoint() const {
    MidPoint(start.x, start.y, end.x, end.y);
}

void Line::Bresenham(int xS, int yS, int xE, int yE) {
    int dx = xE - xS, dy = yE - yS;
    int x = xS, y = yS;
    setPixel(xS, yS);
    int ux = dx > 0 ? 1 : -1;
    int uy = dy > 0 ? 1 : -1;
    dx = abs(dx);
    dy = abs(dy);
    if (dx > dy) {
        int p = 2 * dy - dx;
        for (int i = 0; i < abs(dx); ++i) {
            if (p < 0) {
                x += ux;
                p = p + 2 * dy;
            } else {
                x += ux;
                y += uy;
                p = p + 2 * dy - 2 * dx;
            }
            setPixel(x, y);
        }
    } else {
        int p = 2 * dx - dy;
        for (int i = 0; i < abs(dy); ++i) {
            if (p < 0) {
                y += uy;
                p = p + 2 * dx;
            } else {
                x += ux;
                y += uy;
                p = p + 2 * dx - 2 * dy;
            }
            setPixel(x, y);
        }
    }
}

void Line::drawByBresenham() const {
    Bresenham(start.x, start.y, end.x, end.y);
}

Line::Line(Point s, Point e) : start(s), end(e){}

#endif //GRAPH_LAB_LINE_H
