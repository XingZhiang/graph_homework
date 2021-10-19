#define NDEBUG
#include <GL/glut.h>
#include <iostream>
#include "Line.h"
#include "Circle.h"
#include "Oval.h"
#include <vector>
#include <Windows.h>

// Oval oval1(200,200,500,100);

std::vector<Point> point;
enum drawType { line_DDA, line_midpoint, line_Bre, circle_mid, polygen, CLEAR, help, TODO };
drawType type = line_Bre;
GLsizei winWidth = 800, winHeight = 500;
// 光栅位置参数
GLint xRaster = 25, yRaster = 150;
GLint x = 30;
bool status = false;


void init( ) {
    // 白色背景
    glEnable(GL_BLEND);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    // glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 600.0, 0.0, 500.0);
}

/********************************
 * 窗口刷新回调函数
 *******************************/
void winReshapeFcn(GLint newWidth, GLint newHeight);

/********************************
 * 绘制函数，所有要绘制的图形都在这里
 *******************************/
void Drew();

/*********************************
 * 鼠标回调函数
 ********************************/
void mouseCB(int button, int state, int x, int y);

/*********************************
 * 键盘回调函数
 ********************************/
void keyboardCB(unsigned char key, int x, int y);

/*******************************
 * 右键菜单功能设置
 ******************************/
void processMenuEvents(int option);

/****************************
 * 创建右键菜单
 ***************************/
void createGLUTMenus();

int main(int argc, char** argv) {
    // 初始化GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    // 设置窗口位置
    glutInitWindowPosition(100, 100);
    // 设置窗口尺寸
    glutInitWindowSize(winWidth, winHeight);
    // 创建窗口
    glutCreateWindow("Hello World");

    init();

    glutMouseFunc(mouseCB);
    glutKeyboardFunc(keyboardCB);
    glutDisplayFunc(Drew);
    //glutIdleFunc(line_dda_drew);
    glutReshapeFunc(winReshapeFcn);
    createGLUTMenus();
    glutMainLoop();
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
    glClear(GL_COLOR_BUFFER_BIT);
}

void Drew(){
    if(type != polygen && point.size()==2){
        Point start = point[0];
        Point end = point[1];
        switch (type) {
            case line_DDA:{
                Line line1(start,end);
                line1.drawByDDA();
                point.clear();
                break;
            }
            case line_midpoint:{
                Line line2(start,end);
                line2.drawByMidPoint();
                point.clear();
                break;
            }
            case line_Bre:{
                Line line3(start,end);
                line3.drawByBresenham();
                point.clear();
                break;
            }
            case circle_mid:{
                int r = pow(pow(end.x - start.x,2) + pow(end.y - start.y, 2),0.5);
                std::cout<<"r = "<<r<<std::endl;
                Circle circle(start,r);
                circle.draw();
                point.clear();
                break;
            }
            default:{
                //Line line(start,end);
                //line.drawByDDA();
                point.clear();
            }
        }
    }
    else if (type == polygen && point.size() >= 2) {
        Point start = *(point.end() - 2);
        Point end = *(point.end() - 1);
        Line line(start, end);
        line.drawByBresenham();
    }
    setPixel(0,0);
    glFlush();
}

void mouseCB(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            y =  abs(y-winHeight);
            Point p(x,y);
            point.push_back(p);
            std::cout<<"x = "<<x<<"y = "<<y<<std::endl;
        }
    }
}

void keyboardCB(unsigned char key, int x, int y) {
    if (type == polygen && key == '\r') {
        Point start = *(point.begin());
        Point end = *(point.end() - 1);
        Line line(start, end);
        line.drawByBresenham();
        setPixel(0, 0);
        glFlush();
        point.clear();
    }
}

void processMenuEvents(int option) {
    //option，就是传递过来的value的值。
    switch (option) {
        case line_DDA:
            type = line_DDA;
            break;
        case line_midpoint:
            type = line_midpoint;
            break;
        case line_Bre:
            type = line_Bre;
            break;
        case circle_mid:
            type = circle_mid;
            break;
        case polygen:
            type = polygen;
            break;
        case CLEAR:
            type = TODO;
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // (or whatever buffer you want to clear)
            glFlush();
            break;
        case help:
            type = TODO;
            MessageBoxA(0, "When drawing a polygen, press ENTER to finish", "help", MB_OK | MB_ICONEXCLAMATION);
            MessageBoxA(0, "If nothing happened after choose clear, just click the mouse", "help", MB_OK | MB_ICONEXCLAMATION);
            break;
        default:
            type = TODO;
    }
}

void createGLUTMenus() {
    int menu;
    //创建菜单并告诉GLUT，processMenuEvents处理菜单事件。
    menu = glutCreateMenu(processMenuEvents);
    //给菜单增加条目
    glutAddMenuEntry("DDA",line_DDA);
    glutAddMenuEntry("midpoint",line_midpoint);
    glutAddMenuEntry("Bresenhem",line_Bre);
    glutAddMenuEntry("Cirlce",circle_mid);
    glutAddMenuEntry("Polygen", polygen);
    glutAddMenuEntry("clear",CLEAR);
    glutAddMenuEntry("Help", help);
    //把菜单和鼠标右键关联起来。
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
