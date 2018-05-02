//
//  Paint.cpp
//  3D visualisation
//
//  Created by Мирослав Николов on 10.03.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#include "Paint.hpp"

void Paint::setLine2d(Canvas &canvas, Point p1, Point p2) {
    setLine2d(canvas, p1, p2, 0, 0, 0);
}

void Paint::setLine2d(Canvas &canvas, Point p1, Point p2, char red, char green, char blue) {
    std::vector<Point> line = Calculator::makeLine2d(p1,p2);
    
    for(auto point: line) {
        canvas.set(point.x, point.y, 0 , red);
        canvas.set(point.x, point.y, 1 , green);
        canvas.set(point.x, point.y, 2 , blue);
    }
}

void Paint::setLine3d(Canvas &canvas, Point p1, Point p2) {
    setLine3d(canvas, p1, p2, 0, 0, 0);
}

void Paint::setLine3d(Canvas &canvas, Point p1, Point p2, char red, char green, char blue) {
    if(!Calculator::isVisible3d(*Camera::getCamera(), p1) && !Calculator::isVisible3d(*Camera::getCamera(), p2)) {
        return;
    }
    Point p1In2d = Calculator::perspective2d(*Camera::getCamera(), p1);
    Point p2In2d = Calculator::perspective2d(*Camera::getCamera(), p2);
    
    Point visibleP1 = Calculator::visibleAlternativeOnPointOfLine(p1In2d, p2In2d, p1In2d);
    Point visibleP2 = Calculator::visibleAlternativeOnPointOfLine(p1In2d, p2In2d, p2In2d);
    std::vector<Point> line = Calculator::makeLine2d(visibleP1,visibleP2);
    for(auto point: line) {
//        if(!Calculator::isVisible3d(*Camera::getCamera(), point)) {
//            continue;
//        }
        canvas.set(point.x, point.y, 0 , red);
        canvas.set(point.x, point.y, 1 , green);
        canvas.set(point.x, point.y, 2 , blue);
    }

}


void Paint::setPoint3d(Canvas &canvas, Point p) {
    setPoint3d(canvas, p, 0, 0, 0);
}
void Paint::setPoint3d(Canvas &canvas, Point p, char red, char green, char blue) {
    Point point2d = Calculator::perspective2d(*Camera::getCamera(), p);
    
    canvas.set(point2d.x, point2d.y, 0 , red);
    canvas.set(point2d.x, point2d.y, 1 , green);
    canvas.set(point2d.x, point2d.y, 2 , blue);
    
    canvas.set(point2d.x+1, point2d.y, 0 , red);
    canvas.set(point2d.x+1, point2d.y, 1 , green);
    canvas.set(point2d.x+1, point2d.y, 2 , blue);
    
    canvas.set(point2d.x, point2d.y+1, 0 , red);
    canvas.set(point2d.x, point2d.y+1, 1 , green);
    canvas.set(point2d.x, point2d.y+1, 2 , blue);
    
    canvas.set(point2d.x+1, point2d.y+1, 0 , red);
    canvas.set(point2d.x+1, point2d.y+1, 1 , green);
    canvas.set(point2d.x+1, point2d.y+1, 2 , blue);
}









