//
//  Cube.cpp
//  3D visualisation
//
//  Created by Мирослав Николов on 9.03.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#include "Cube.hpp"

Cube::Cube(): startPoint(50,50,50) {
    this->angle = 0;
    this->height = 100;
    //    weight = 50;
}

Cube::Cube(Point startPoint, double height): startPoint(startPoint), height(height) {
    this->angle = 0;
    //        this->height = 100;
    //    weight = 50;
}
void Cube::setBody(unsigned char* bitmap, double sizeY, double sizeX) {
    Canvas c(bitmap, sizeX, sizeY);
    
    Point p1,p2,p3,p4,p5,p6,p7,p8;
    getPoints(p1, p2, p3, p4, p5, p6, p7, p8);

    
    Paint::setLine3d(c, p1, p3, 0, 255, 50);
    Paint::setLine3d(c, p1, p5, 0, 255, 125);
    Paint::setLine3d(c, p3, p7, 0, 255, 200);
    Paint::setLine3d(c, p5, p7, 0, 255, 255);

    Paint::setLine3d(c, p1, p2, 255, 0, 50);
    Paint::setLine3d(c, p3, p4, 255, 0, 125);
    Paint::setLine3d(c, p5, p6, 255, 0, 200);
    Paint::setLine3d(c, p7, p8, 255, 0, 255);

    Paint::setLine3d(c, p2, p4, 255, 255, 0);
    Paint::setLine3d(c, p4, p8, 255, 255, 0);
    Paint::setLine3d(c, p6, p8, 255, 255, 0);
    Paint::setLine3d(c, p2, p6, 255, 255, 0);
}

void Cube::getPoints(Point &p1, Point &p2, Point &p3, Point &p4, Point &p5, Point &p6, Point &p7, Point &p8) {
    p1 = startPoint;
    
    p2 = startPoint;
    p2.x += height;
    
    p3 = startPoint;
    p3.y += height;
    
    p4 = p2;
    p4.y += height;
    
    p5 = p1;
    p5.z += height;
    
    p6 = p2;
    p6.z += height;
    
    p7 = p3;
    p7.z += height;
    
    p8 = p4;
    p8.z += height;
}

/*
 x:670   y:366   z:0
 x:690   y:362   z:0
 x:730   y:366   z:0
 x:710   y:362   z:0
 x:670   y:426   z:0
 x:690   y:382   z:0
 x:730   y:426   z:0
 x:150   y:50   z:110
 
 
 
 
 
 x:12   y:-200   z:-200
 x:412   y:-200   z:-200
 x:12   y:200   z:-200
 x:412   y:200   z:-200
 x:12   y:-200   z:200
 x:412   y:-200   z:200
 x:12   y:200   z:200
 x:412   y:200   z:200
 */







