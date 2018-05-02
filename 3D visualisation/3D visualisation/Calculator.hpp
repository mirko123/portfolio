//
//  Calculator.h
//  3D visualisation
//
//  Created by Мирослав Николов on 10.03.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#ifndef Calculator_hpp
#define Calculator_hpp

#include <vector>
#include <functional>

#include "Point.h"
#include "Camera.hpp"
#include <math.h>

class Calculator {
public:
    static bool isVisible2d(Camera, Point);
    static bool isVisible3d(Camera, Point);
    static bool areEqual(double num1, double num2);
    static Point normalizeVector(Point point);
    static double normalizeAngle(double degree);
    static double degreeToRadian(double degree);
    static double radianToDegree(double degree);
    static double angleBetweenPointsInRadians2d(Point p1, Point center, Point p2);
    static double angleBetweenPoints2d(Point p1, Point center, Point p2);
    static double angleBetweenPoints2d(double p1X, double p1Y, double centerX, double centerY, double p2X, double p2Y);
    static double angleBetweenPoints3d(Point p1, Point center, Point p2);
//    static double angleBetweenPoints3d(double p1X, double p1Y, double centerX, double centerY, double p2X, double p2Y);
    static double distance2d(Point p1, Point p2);
    static double distance2d(Point p1);
    static double distance3d(Point p1, Point p2);
    static double distance3d(Point p1);
    static Point nextPointOfParametricEquation(Point lineP1, Point lineP2, double t);
    static Point rotate(Point center, Point target, double verticalAngleAmendment, double horizonstalAngleAmendment);
    static Point rotateByX(Point p, double angle);
    static Point rotateByY(Point p, double angle);
    static Point rotateByZ(Point p, double angle);
//    static Point perpendicularVector(Point p1, Point p2);
    static Point horizontalPerpendicular(Point center, Point target, bool leftDirection, double length);
    static Point horizontalLeftPerpendicular(Point center, Point target, double length);
    static Point horizontalRightPerpendicular(Point center, Point target, double length);
    static double YOnLineByPoints2d(double x, Point lineP1, Point lineP2);
    static double XOnLineByPoints2d(double y, Point lineP1, Point lineP2);
//    static Point minPointInRangeOnLine2d(Point lineP1, Point lineP2, double minX, double minY);
//    static Point maxPointInRangeOnLine2d(Point lineP1, Point lineP2, double maxX, double maxY);
    static Point visibleAlternativeOnPointOfLine(Point lineP1, Point lineP2, Point target, Camera camera = *Camera::getCamera());
    static std::pair<Point, Point> visibleEdgesOnLine(Point lineP1, Point lineP2);
    static std::function<double (double)> lineFuncByPoints2d(Point p1, Point p2);
    static std::function<Point (double)> scalarFuncOnLine3d(Point p1, Point p2);
    static Point pointOfLineByScalar3d(Point p1, Point p2, double coeficient);
//    static std::function<Point (double)> lineFuncByPoints3d(Point p1, Point p2);
    static void lineFuncCoefByPoints2d(Point p1, Point p2, double &coef1, double &coef2);
    static std::vector<Point> makeLine2d(Point p1, Point p2);
    static std::vector<Point> makeLine2d(Point p1, Point p2, double maxX, double minX, double maxY, double minY);
    static std::vector<Point> makeLine2dFromCanonic(Point p1, Point p2);
    static std::vector<Point> makeLine2dFromParametric(Point p1, Point p2);
    static std::vector<Point> makeLine3d(Point p1, Point p2);
    static double distanceToLine(Point lineP1, Point lineP2, Point target);

    static Point crossProduct(Point p1, Point p2);
    static double dotProduct(Point p1, Point p2);
    
    static Point perspective2d(Camera camera, Point target);
    
    static double distanceOfIntersectToDirection(Camera camera, Point target);
    static Point intersectLineAndPerpendicularPlane(Point lineP1, Point lineP2, Point target);
};
#endif /* Calculator_h */
