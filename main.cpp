#define NDEBUG
#include <cstdlib>
#include <cmath>
#include <GL/glut.h>
#include "Line.h"

Line line1(0,0,100,50);
Line line2(0, 0, 100, 200);
Line line3(25, 100, 50, 0);
Line line4(0, 100, 200, 0);


GLsizei winWidth = 800, winHeight = 500;
// 光栅位置参数
GLint xRaster = 25, yRaster = 150;
GLint x = 30;

void init( ) {
    // 白色背景
    glEnable(GL_BLEND);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 600.0, 0.0, 500.0);
}


void winReshapeFcn(GLint newWidth, GLint newHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
    glClear(GL_COLOR_BUFFER_BIT);
}

void DDA(){
    line1.drawByDDA();
}

void MidPoint() {
    line1.drawByMidPoint();
    line2.drawByMidPoint();
    line3.drawByMidPoint();
    line4.drawByMidPoint();
}

void Breseham(){
    line1.drawByBresenham();
}

int main(int argc, char** argv) {
    // 初始化GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    // 设置窗口位置
    glutInitWindowPosition(100, 100);
    // 设置窗口尺寸
    glutInitWindowSize(winWidth, winHeight);
    // 创建窗口
    glutCreateWindow("Hello World");

    init();
    //glutDisplayFunc(Breseham);
    glutDisplayFunc(MidPoint);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
    
}