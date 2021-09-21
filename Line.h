#pragma once
#ifndef GRAPH_LAB_LINE_H
#define GRAPH_LAB_LINE_H
#include <GL/glut.h>
#include <cmath>
#include "Point.h"

class Line{
private:
    Point start;
    Point end;

public:
    Line() = delete;
    Line(int xS, int yS, int xE, int yE);
private:
    static void DDA(int xS, int yS, int xE, int yE);
    static void Bresenham(int xS, int yS, int xE, int yE);

public:
    void drawByDDA() const;
    void drawByBresenham() const;
};

Line::Line(int xS, int yS, int xE, int yE):
    start(xS,yS),end(xE,yE){}


void Line::DDA(int xS, int yS, int xE, int yE) {
    int dx = xE - xS, dy = yE - yS, steps = 0;
    float xIncrement, yIncrement, x = static_cast<float >(xS), y = static_cast<float>(yS);
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    xIncrement = float(dx) / float(steps);
    yIncrement = float(dy) / float(steps);

    setPixel(static_cast<int>(x + 0.5), static_cast<int>(x + 0.5));
    for (int i = 0; i < steps; ++i) {
        x += xIncrement;
        y += yIncrement;
        setPixel(static_cast<int>(x + 0.5), static_cast<int>(y + 0.5));
    }
}

void Line::drawByDDA() const {
    DDA(start.x, start.y, end.x, end.y);
}

void Line::Bresenham(int xS, int yS, int xE, int yE) {
    int dx = xE - xS, dy = yE - yS;
    int x = xS, y = yS;
    setPixel(xS,yS);
    int ux = dx > 0?1:-1;
    int uy = dy > 0?1 : -1;
    dx = abs(dx); dy= abs(dy);
    if( dx > dy){
        int p = 2*dy - dx;
        for(int i = 0; i< abs(dx); ++i){
            if(p < 0) {
                x+=ux;
                p = p + 2*dy;
            }else{
                x+=ux; y+=uy;
                p = p + 2*dy - 2*dx;
            }
            setPixel(x,y);
        }
    }else{
        int p = 2 * dx - dy;
        for(int i = 0; i< abs(dy); ++i){
            if(p < 0) {
                y+=uy;
                p = p + 2*dx;
            }else{
                x+=ux; y+=uy;
                p = p + 2*dx - 2*dy;
            }
            setPixel(x,y);
        }
    }
}

void Line::drawByBresenham() const {
    Bresenham(start.x, start.y, end.x, end.y);
}

#endif //GRAPH_LAB_LINE_H
