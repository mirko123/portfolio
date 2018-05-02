//
//  main.cpp
//  3D visualisation
//
//  Created by Мирослав Николов on 9.03.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <GLUT/glut.h>
#include <vector>

#include "IShape.h"
#include "Cube.hpp"
#include "Test.h"

#define windowWidth 1400
#define windowHeight 750
GLubyte image[windowHeight][windowWidth][3];

static GLint height;

double moveCoef = 50;
double rotateCoef = 1;
std::vector<IShape*> shapes;

void initImage(void)
{
    int i, j, c;
    
    for (i = 0; i < windowHeight; i++) {
        for (j = 0; j < windowWidth; j++) {
            c = 0;
//            c = 255;
            image[i][j][0] = (GLubyte) c;
            image[i][j][1] = (GLubyte) c;
            image[i][j][2] = (GLubyte) c;
        }
    }
}

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    initImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}
void display(void)
{
    initImage();
    for(auto &&shape: shapes) {
        shape->setBody(&image[0][0][0], windowHeight, windowWidth);
    }
    
    glClear(GL_COLOR_BUFFER_BIT);
    glRasterPos2i(0, 0);
    glDrawPixels(windowWidth, windowHeight, GL_RGB,
                 GL_UNSIGNED_BYTE, image);
    glFlush();
}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    height = (GLint) h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble) w, 0.0, (GLdouble) h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'r':
        case 'R':
            Camera::setCamera(Point(0,0,0), Point(950,0,0), windowHeight, windowWidth);
            glutPostRedisplay();
            printf ("Reset\n");
            break;
            
        case 'w':
            Camera::getCamera()->move(-moveCoef);
            break;
        case 's':
            Camera::getCamera()->move(moveCoef);
            break;
        case 'a':
            Camera::getCamera()->moveLeft(moveCoef);
            break;
        case 'd':
            Camera::getCamera()->moveRight(moveCoef);
            break;
        case 't':
            Camera::getCamera()->moveTop(moveCoef);
            break;
        case 'g':
            Camera::getCamera()->moveBot(moveCoef);
            break;
        case 'i':
            Camera::getCamera()->rotateTop(rotateCoef);
            break;
        case 'k':
            Camera::getCamera()->rotateBot(rotateCoef);
            break;
        case 'j':
            Camera::getCamera()->rotateLeft(rotateCoef);
            break;
        case 'l':
            Camera::getCamera()->rotateRight(rotateCoef);
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
    display();
}

int main(int argc, char** argv)
{
    Point camera(0,0,0);
    Point direction(950,0,0);
    Camera::setCamera(camera, direction, windowHeight, windowWidth);

    shapes.push_back(new Cube(Point(5050,-2000,-500),4000));
    shapes.push_back(new Cube(Point(6050,-1000,-200),1100));
//    shapes.push_back(new Cube(Point(5700,-1700,-510),700));
    
//    test();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//    glutInitWindowSize(250, 250);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
//    glutMotionFunc(motion);
    glutMainLoop();
    
    return 0; 
}
