#define NDEBUG
#include <GL/glut.h>
#include <iostream>
#include "Color.h"
#include "Line.h"
#include "Circle.h"
#include "Oval.h"
#include "Polygen.h"
#include "fillArea.h"
#include "cut.h"
#include <vector>
#include <Windows.h>

// Oval oval1(200,200,500,100);

std::vector<Point> point;
enum drawType {
    line_DDA, line_midpoint, line_Bre, circle_mid, polygen, fill, new_window, CohenSutherland,
    SutherlandHodgman, RED, GREEN, BLUE, CLEAR, help, TODO
};
drawType type = TODO;
GLsizei winWidth = 800, winHeight = 500;
// ��դλ�ò���
GLint xRaster = 25, yRaster = 150;
GLint x = 30;
bool status = false;
COLOR winColor[800][500];   //����������ɫ
COLOR pen;

void init( ) {
    // ��ɫ����
    glEnable(GL_BLEND);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glReadPixels(0, 0, winWidth, winHeight, GL_RGB, GL_UNSIGNED_BYTE, winColor);
    // glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 600.0, 0.0, 500.0);
}

/********************************
 * ����ˢ�»ص�����
 *******************************/
void winReshapeFcn(GLint newWidth, GLint newHeight);

/********************************
 * ���ƺ���������Ҫ���Ƶ�ͼ�ζ�������
 *******************************/
void Drew();

/*********************************
 * ���ص�����
 ********************************/
void mouseCB(int button, int state, int x, int y);

/*********************************
 * ���̻ص�����
 ********************************/
void keyboardCB(unsigned char key, int x, int y);

/*******************************
 * �Ҽ��˵���������
 ******************************/
void processMenuEvents(int option);

/****************************
 * �����Ҽ��˵�
 ***************************/
void createGLUTMenus();

int main(int argc, char** argv) {
    // ��ʼ��GLUT
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    // ���ô���λ��
    glutInitWindowPosition(100, 100);
    // ���ô��ڳߴ�
    glutInitWindowSize(winWidth, winHeight);
    // ��������
    glutCreateWindow("Hello World");
    pen.setColor(255, 0, 0);
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
            case CohenSutherland: {
                Line line4(start, end);
                line4.drawByCohenSutherland();
                point.clear();
                break;
            }
            case polygen: {
                break;
            }
            case SutherlandHodgman:
                break;
            default:{
                //Line line(start,end);
                //line.drawByDDA();
                point.clear();
            }
        }
    }
    /*else if (type == polygen && point.size() >= 2) {
        Point start = *(point.end() - 2);
        Point end = *(point.end() - 1);
        Line line(start, end);
        line.drawByBresenham();
    }
    */
    else if (type == fill && point.size() == 1) {
        Point p = point[0];
        fillArea(p, pen);
        point.clear();
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
    if ((type == polygen || type == SutherlandHodgman) && key == '\r') {
        Polygen poly(point);
        if (type == SutherlandHodgman) {
            poly.drawBySutherlandHodgman();
        }
        poly.draw();
        glFlush();
        point.clear();
    }
}

void processMenuEvents(int option) {
    //option�����Ǵ��ݹ�����value��ֵ��
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
        case SutherlandHodgman:
            type = SutherlandHodgman;
            break;
        case fill:
            type = fill;
            break;
        case new_window: {
            Point a(200, 125), b(600, 125);
            Line line(a, b);
            line.drawByBresenham();
            a.set(600, 375);
            line.set(a, b);
            line.drawByBresenham();
            b.set(200, 375);
            line.set(a, b);
            line.drawByBresenham();
            a.set(200, 125);
            line.set(a, b);
            line.drawByBresenham();
            glFlush();
            type = TODO;
            break;
        }
        case CohenSutherland:
            type = CohenSutherland;
            break;
        case RED:
            pen.setColor(255, 0, 0);
            break;
        case GREEN:
            pen.setColor(0, 255, 0);
            break;
        case BLUE:
            pen.setColor(0, 0, 255);
            break;
        case CLEAR:
            type = TODO;
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // (or whatever buffer you want to clear)
            glFlush();
            glReadPixels(0, 0, winWidth, winHeight, GL_RGB, GL_UNSIGNED_BYTE, winColor);
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
    int submenu_Line;
    int color_menu;
    //�����Ӳ˵�
    submenu_Line = glutCreateMenu(processMenuEvents);
    //�����Ŀ
    glutAddMenuEntry("DDA", line_DDA);
    glutAddMenuEntry("midpoint", line_midpoint);
    glutAddMenuEntry("Bresenhem", line_Bre);
    glutAddMenuEntry("CohenSutherland", CohenSutherland);
    color_menu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("RED", RED);
    glutAddMenuEntry("GREEN", GREEN);
    glutAddMenuEntry("BLUE", BLUE);
    //�����˵�������GLUT��processMenuEvents����˵��¼���
    menu = glutCreateMenu(processMenuEvents);
    //���˵�������Ŀ
    glutAddSubMenu("Line", submenu_Line);
    glutAddMenuEntry("Cirlce",circle_mid);
    glutAddMenuEntry("Polygen", polygen);
    glutAddMenuEntry("SutherlandHodgman", SutherlandHodgman);
    glutAddMenuEntry("Fill", fill);
    glutAddSubMenu("Color", color_menu);
    glutAddMenuEntry("New Window", new_window);
    glutAddMenuEntry("clear",CLEAR);
    glutAddMenuEntry("Help", help);
    
    //�Ѳ˵�������Ҽ�����������
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
