//
//  Paint.hpp
//  3D visualisation
//
//  Created by Мирослав Николов on 10.03.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef Paint_hpp
#define Paint_hpp

#include <stdio.h>
#include <math.h>
#include <vector>
#include "Calculator.hpp"
#include "Paint.hpp"

#include "Point.h"
#include "Canvas.h"

class Paint {
public:
    static void setLine2d(Canvas &canvas, Point p1, Point p2);
    static void setLine2d(Canvas &canvas, Point p1, Point p2, char red, char green, char blue);
    static void setLine3d(Canvas &canvas, Point p1, Point p2);
    static void setLine3d(Canvas &canvas, Point p1, Point p2, char red, char green, char blue);
    static void setPoint3d(Canvas &canvas, Point p);
    static void setPoint3d(Canvas &canvas, Point p, char red, char green, char blue);
};

#endif /* Paint_hpp */
