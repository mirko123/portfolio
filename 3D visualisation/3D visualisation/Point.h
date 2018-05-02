//
//  Point.h
//  3D visualisation
//
//  Created by Мирослав Николов on 10.03.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef Point_h
#define Point_h

#include <iostream>

class Point {
public:
    double x;
    double y;
    double z;
    
    Point() {
        x = 5;
        y = 5;
        z = 5;
    }
    Point(double x, double y, double z): x(x),y(y),z(z) { }
    Point(const Point &other): x(other.x),y(other.y),z(other.z) { }
    
    void Print() { std::cout<<"x:" << x << "   y:" << y << "   z:" << z <<std::endl; }
    bool operator!=(const Point& rhs){ return (this->x != rhs.x || this->y != rhs.y || this->z != rhs.z); }
};

#endif /* Point_h */
