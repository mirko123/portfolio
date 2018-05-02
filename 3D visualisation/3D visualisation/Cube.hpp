//
//  Cube.hpp
//  3D visualisation
//
//  Created by Мирослав Николов on 9.03.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef Cube_hpp
#define Cube_hpp

#include <stdio.h>
#include "Point.h"
#include "IShape.h"

#include "Paint.hpp"
#include "Canvas.h"
#include <iostream>

class Cube : public IShape
{
    Point startPoint;
    double height;
    double angle;
//    double angle;
//    int weight;
public:
    Cube();
    Cube(Point startPoint, double height);
    
    void setBody(unsigned char* mat, double height, double width);
    void getPoints(Point &p1, Point &p2, Point &p3, Point &p4, Point &p5, Point &p6, Point &p7, Point &p8);
};

#endif /* Cube_hpp */
