#ifndef GRAPH_LAB_POLYGEN_H
#define GRAPH_LAB_POLYGEN_H
#include "Point.h"
#include "Line.h"
#include <vector>
#include<utility>

class Polygen{
public:
    std::vector<Point> point;  //顶点集
    std::vector<Line> vertex;   //边集
public:
    Polygen(){}
    Polygen(std::vector<Point> p);
    //Polygen(const Point &cen, int r);

private:
public:
    void draw() const;
    void drawBySutherlandHodgman();
    void setVertex();
};

Polygen::Polygen(std::vector<Point> p):point(p) {
    for (auto iter = p.begin(); iter != p.end() - 1; iter++) {
        Line line(*iter, *(iter + 1));
        vertex.push_back(line);
    }
    Line line(*p.begin(), *(p.end() - 1));
    vertex.push_back(line);
}



void Polygen::draw() const {
    for (auto line : vertex) {
        line.drawByBresenham();
    }
}


void Polygen::drawBySutherlandHodgman()
{
    Polygen res;
    Point s(0, 0), p(0, 0), ip(0, 0);
    int j;
    s = *(point.end() - 1);
    for (j = 0; j < point.size(); j++) {
        p = point[j];
        if (p.x >= XL) {
            if (s.x >= XL) {
                res.point.push_back(p);
            }
            else {
                ip.x = XL;
                ip.y = s.y + (p.y - s.y) * (XL - s.x) / (float)(p.x - s.x);
                res.point.push_back(ip);
                res.point.push_back(p);
            }
        }
        else if (s.x >= XL) {
            ip.x = XL;
            ip.y = s.y + (p.y - s.y) * (XL - s.x) / (float)(p.x - s.x);
            res.point.push_back(ip);
        }
        s = p;
    }
    point.clear();
    s = *(res.point.end() - 1);
    for (j = 0; j < res.point.size(); j++) {
        p = res.point[j];
        if (p.y <= YT) {
            if (s.y <= YT) {
                point.push_back(p);
            }
            else {
                ip.x = p.x + (s.x - p.x) * (YT - p.y) / (float)(s.y - p.y);
                ip.y = YT;
                point.push_back(ip);
                point.push_back(p);
            }
        }
        else if (s.y <= YT) {
            ip.x = p.x + (s.x - p.x) * (YT - p.y) / (float)(s.y - p.y);
            ip.y = YT;
            point.push_back(ip);
        }
        s = p;
    }
    res.point.clear();
    s = *(point.end() - 1);
    for (j = 0; j < point.size(); j++) {
        p = point[j];
        if (p.x <= XR) {
            if (s.x <= XR) {
                res.point.push_back(p);
            }
            else {
                ip.x = XR;
                ip.y = s.y + (p.y - s.y) * (XR - s.x) / (float)(p.x - s.x);
                res.point.push_back(ip);
                res.point.push_back(p);
            }
        }
        else if (s.x <= XR) {
            ip.x = XR;
            ip.y = s.y + (p.y - s.y) * (XR - s.x) / (float)(p.x - s.x);
            res.point.push_back(ip);
        }
        s = p;
    }
    point.clear();
    s = *(res.point.end() - 1);
    for (j = 0; j < res.point.size(); j++) {
        p = res.point[j];
        if (p.y >= YB) {
            if (s.y >= YB) {
                point.push_back(p);
            }
            else {
                ip.x = p.x + (s.x - p.x) * (YB - p.y) / (float)(s.y - p.y);
                ip.y = YB;
                point.push_back(ip);
                point.push_back(p);
            }
        }
        else if (s.y >= YB) {
            ip.x = p.x + (s.x - p.x) * (YB - p.y) / (float)(s.y - p.y);
            ip.y = YB;
            point.push_back(ip);
        }
        s = p;
    }
    vertex.clear();
    setVertex();
}

void Polygen::setVertex()
{
    for (auto iter = point.begin(); iter != point.end() - 1; iter++) {
        Line line(*iter, *(iter + 1));
        vertex.push_back(line);
    }
    Line line(*point.begin(), *(point.end() - 1));
    vertex.push_back(line);
}


#endif //GRAPH_LAB_POLYGEN_H
