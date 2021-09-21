#define NDEBUG
#include <GL/glut.h>
#include "Line.h"
#include "Circle.h"
#include "Oval.h"

Line line(0,50,50,0);
Circle circle(200,200,100);

Oval oval(200,200,50,100);

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
    line.drawByDDA();
}

void Breseham(){
    line.drawByBresenham();
}

void circle_draw(){
    circle.draw();
}

void oval_draw(){
    oval.draw();
};

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
    glutDisplayFunc(oval_draw);
    glutReshapeFunc(winReshapeFcn);
    glutMainLoop();
    
}