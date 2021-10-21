#pragma once
#ifndef GRAPH_LAB_COLOR_H
#define GRAPH_LAB_COLOR_H

#include <GL\glut.h>
class COLOR {
public:
    BYTE R;
    BYTE G;
    BYTE B;
    COLOR(BYTE r, BYTE g, BYTE b) :R(r), G(g), B(b) {}
    COLOR() :R(0), G(0), B(0) {}
    COLOR(UINT color);
    bool operator==(COLOR& b) {
        return R == b.R && G == b.G && B == b.B;
    }
    bool operator!=(COLOR& b) {
        return R != b.R || G != b.G || B != b.B;
    }
};

COLOR::COLOR(UINT color){
    if ((color & 0xff000000) == 0) {
        R = color >> 16;
        G = (color & 0xff00) >> 8;
        B = color & 0xff;
    }
}


#endif //GRAPH_LAB_COLOR_H