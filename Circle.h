/*
 * 圆类
 */
#ifndef GRAPH_LAB_CIRCLE_H
#define GRAPH_LAB_CIRCLE_H
#include "Point.h"
class Circle{
private:
    Point center;  //圆心
    int radius;   //半径
public:
    Circle() = delete;
    Circle(int x, int y, int r);
    Circle(const Point &cen, int r);

private:
    void midpoint(int xCtr, int yCtr) const;
    /****************************
     * 由八分之一圆补全到整个园
     ***************************/
    void Complete(int x, int y) const;

public:
    void draw() const;
};

Circle::Circle(int x, int y, int r):
    center(x,y), radius(r){}

void Circle::midpoint(int xCtr, int yCtr) const {
    int x = 0, y = radius;
    float p = 5.0f/4.0f - static_cast<float>(radius);
    Complete(xCtr, yCtr + radius);
    while(x < y){
        if(p < 0){
            int tmp_x = ++x;
            Complete(tmp_x + xCtr, y + yCtr);
            Complete(y + xCtr, tmp_x + yCtr);
            p = p + 2*x +1;
        }else{
            int tmp_x = ++x, tmp_y = --y;
            Complete(tmp_x + xCtr, tmp_y + yCtr);
            Complete(tmp_y + xCtr, tmp_x + yCtr);
            p = p + 2*x +1 - 2*y;
        }
    }

}

void Circle::draw() const {
    midpoint(center.x,center.y);
}

void Circle::Complete(int x, int y) const {
    setPixel(x,y);
    setPixel(2*center.x-x,y);
    setPixel(x,2*center.y-y);
    setPixel(2*center.x-x,2*center.y-y);
}

Circle::Circle(const Point &cen, int r):center(cen),radius(r){}


#endif //GRAPH_LAB_CIRCLE_H
