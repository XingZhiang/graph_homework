#include <GL/glut.h>
#include <iostream>
#include "Line.h"
#include "Circle.h"
#include "Oval.h"
#include <vector>

// Oval oval1(200,200,500,100);

std::vector<Point> point;
enum drawType {line_DDA, line_midpoint, line_Bre, circle_mid,CLEAR};
drawType type = line_Bre;
GLsizei winWidth = 800, winHeight = 500;
// ��դλ�ò���
GLint xRaster = 25, yRaster = 150;
GLint x = 30;


void init( ) {
    // ��ɫ����
    glEnable(GL_BLEND);
    glClearColor(1.0, 1.0, 1.0, 1.0);
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

    init();

    glutMouseFunc(mouseCB);
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
    if(point.size()==2){
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
                Line line(start,end);
                line.drawByDDA();
                point.clear();
            }
        }
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
            case CLEAR:
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // (or whatever buffer you want to clear)
            default:
                type = line_Bre;
    }
}

void createGLUTMenus() {
    int menu;
    //�����˵�������GLUT��processMenuEvents����˵��¼���
    menu = glutCreateMenu(processMenuEvents);
    //���˵�������Ŀ
    glutAddMenuEntry("DDA",line_DDA);
    glutAddMenuEntry("midpoint",line_midpoint);
    glutAddMenuEntry("Bresenhem",line_Bre);
    glutAddMenuEntry("Cirlce",circle_mid);
    glutAddMenuEntry("clear",CLEAR);
    //�Ѳ˵�������Ҽ�����������
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
