//
//  Calculator.cpp
//  3D visualisation
//
//  Created by Мирослав Николов on 10.03.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#include "Calculator.hpp"
#include <limits>

bool Calculator::isVisible2d(Camera camera, Point point) {
    if(point.x < 0 || point.x > camera.displayPlaneHorizontalSize ||
       point.y < 0 || point.y > camera.displayPlaneVerticalSize) {
        return false;
    }
    return true;
}
bool Calculator::isVisible3d(Camera camera, Point point) {
    //    if(90 < angleBetweenPoints2d(point, camera.position, camera.direction) ||
    //       -90 > angleBetweenPoints2d(point, camera.position, camera.direction)) {
    //        return false;
    //    }
    
    //    if(angleBetweenPoints2d(point, camera.position, camera.direction) > 0) {
    //        return false;
    //    }
    if(distance3d(point, camera.position) < distance3d(point, camera.direction)) {
        return false;
    }
    else if(angleBetweenPoints3d(point, camera.direction, camera.position) < 90) {
        return false;
    }
    return true;
}
bool Calculator::areEqual(double num1, double num2) {
    double diff = fabs(num1 - num2);
    double epsilon = 0.0000001;
    return diff < epsilon;
}
Point Calculator::normalizeVector(Point p) {
    double distance = distance3d(p);
    return Point(p.x/distance, p.y/distance, p.z/distance);
}

double Calculator::normalizeAngle(double angle) {
    if(angle > 180) return angle - 360;
    if(angle < -180) return angle + 360;
    else return angle;
}
double Calculator::degreeToRadian(double degree) {
    return degree * M_PI / 180.0;
}
double Calculator::radianToDegree(double radian) {
    return fmod((radian * 180.0/ M_PI),360);
}

double Calculator::angleBetweenPointsInRadians2d(Point p1, Point center, Point p2) {
//    double a = (center.x-p1.x)*(center.x-p1.x) + (center.y-p1.y)*(center.y-p1.y);
//    double b = (center.x-p2.x)*(center.x-p2.x) + (center.y-p2.y)*(center.y-p2.y);
//    double c = (p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y);
//    return acos( (a+b-c) / sqrt(4*a*b) ) * 180/M_PI;
    
    double a = pow(center.x-p1.x,2) + pow(center.y - p1.y,2);
    double b = pow(center.x-p2.x,2) + pow(center.y-p2.y,2);
    double c = pow(p2.x-p1.x,2) + pow(p2.y-p1.y,2);
    return acos( (a+b-c) / sqrt(4*a*b) );
}

//M_PI
double Calculator::angleBetweenPoints2d(Point p1, Point center, Point p2) {
    Point v1(center.x - p1.x, center.y - p1.y,0);
    Point v2 (center.x - p2.x, center.y - p2.y,0);
    
    double angleRad = atan2(v1.y, v1.x) - atan2(v2.y, v2.x);
    double andleDegree = normalizeAngle(radianToDegree(angleRad));
    
    return andleDegree;
}

double Calculator::angleBetweenPoints2d(double p1X, double p1Y, double centerX, double centerY, double p2X, double p2Y) {
    Point p1(p1X,p1Y,0);
    Point center(centerX,centerY,0);
    Point p2(p2X,p2Y,0);
    
    return angleBetweenPoints2d(p1,center,p2);
}

double Calculator::angleBetweenPoints3d(Point p1, Point center, Point p2) {
    Point v1(p1.x - center.x, p1.y - center.y, p1.z - center.z);
    Point v2(p2.x - center.x, p2.y - center.y, p2.z - center.z);
    
    double v1mag = sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
    Point v1norm(v1.x / v1mag, v1.y / v1mag, v1.z / v1mag);
    
    double v2mag = sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
    Point v2norm(v2.x / v2mag, v2.y / v2mag, v2.z / v2mag);
    
    double res = v1norm.x * v2norm.x + v1norm.y * v2norm.y + v1norm.z * v2norm.z;
    double angle = acos(res)*180.0/M_PI;
    return angle;
}

//double Calculator::angleBetweenPoints3d(double p1X, double p1Y, double centerX, double centerY, double p2X, double p2Y) {
//    Point p1(p1X,p1Y,0);
//    Point center(centerX,centerY,0);
//    Point p2(p2X,p2Y,0);
//    
//    return angleBetweenPoints3d(p1,center,p2);
//}


double Calculator::distance2d(Point p1, Point p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}
double Calculator::distance2d(Point p1) {
    Point p2(0,0,0);
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

double Calculator::distance3d(Point p1, Point p2) {
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) + (p1.z - p2.z)*(p1.z - p2.z));
}

double Calculator::distance3d(Point p1) {
    Point p2(0,0,0);
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) + (p1.z - p2.z)*(p1.z - p2.z));
}

Point Calculator::nextPointOfParametricEquation(Point lineP1, Point lineP2, double t) {
    double a = lineP1.x - lineP2.x;
    double b = lineP1.y - lineP2.y;
    double c = lineP1.z - lineP2.z;
    
    double newX = lineP2.x + t*a;
    double newY = lineP2.y + t*b;
    double newZ = lineP2.z + t*c;
    return Point(newX, newY, newZ);
}
Point Calculator::rotate(Point center, Point target, double verticalAngleAmendment, double horizonstalAngleAmendment) {
    double currentVerticalAngle = Calculator::angleBetweenPoints3d(Point(center.x,center.y,center.z + 1), center, target);
    double currentHorizontalAngle = Calculator::angleBetweenPoints2d(target.x, target.y, center.x, center.y, center.x + 1, center.y);
    
    double newVerticalAngle = currentVerticalAngle + verticalAngleAmendment;
    double newHorizontalAngle = currentHorizontalAngle + horizonstalAngleAmendment;
    
    double radius = Calculator::distance3d(center, target);
    
    double cosOfNewHorizontalAngle = cos(degreeToRadian(newHorizontalAngle));
    double sinOfNewHorizontalAngle = sin(degreeToRadian(newHorizontalAngle));
    double cosOfNewVerticalAngle = cos(degreeToRadian(newVerticalAngle));
    double sinOfNewVerticalAngle = sin(degreeToRadian(newVerticalAngle));
    
    double newX = center.x + radius*cosOfNewHorizontalAngle*sinOfNewVerticalAngle;
    double newY = center.y + radius*sinOfNewHorizontalAngle*sinOfNewVerticalAngle;
    double newZ = center.z + radius*cosOfNewVerticalAngle;
    
    Point newTarget(newX, newY, newZ);
    return newTarget;
}
Point Calculator::rotateByX(Point p, double angle) {
    double radianOfAngle = degreeToRadian(angle);
    double Xprim = p.x;
    double Yprim = p.y*cos(radianOfAngle) - p.z*sin(radianOfAngle);
    double Zprim = p.y*sin(radianOfAngle) + p.z*cos(radianOfAngle);
    return Point(Xprim,Yprim,Zprim);
}
Point Calculator::rotateByY(Point p, double angle) {
    double radianOfAngle = degreeToRadian(angle);
    double Xprim = p.z*cos(radianOfAngle) - p.x*sin(radianOfAngle);;
    double Yprim = p.y;
    double Zprim = p.z*sin(radianOfAngle) + p.x*cos(radianOfAngle);
    return Point(Xprim,Yprim,Zprim);
}
Point Calculator::rotateByZ(Point p, double angle) {
    double radianOfAngle = degreeToRadian(angle);
    double Xprim = p.x*cos(radianOfAngle) - p.y*sin(radianOfAngle);
    double Yprim = p.x*sin(radianOfAngle) + p.y*cos(radianOfAngle);
    double Zprim = p.z;
    return Point(Xprim,Yprim,Zprim);
}

//Point Calculator::perpendicularVector(Point p1, Point p2) {
//    
//}
//Point Calculator::horizontalPerpendicular(Point center, Point target, double direction, double length) {
//    double Zposition = center.z;
//    target.z = 0;
//    center.z = direction;
//    
//    Point crossProduct = Calculator::crossProduct(center, target);
//    crossProduct.z = Zposition;
//    
//    double distance = distance2d(center, crossProduct);
//    double coef = distance / length;
//    
//    Point newPoint = pointOfLineByScalar3d(center, crossProduct, coef);
//    return newPoint;
//}
Point Calculator::horizontalPerpendicular(Point center, Point target, bool rightDirection, double length) {
    Point rotatedPoint = rightDirection ? rotate(center, target, 0, 90) : rotate(center, target, 0, -90);
    double distance = distance2d(center, rotatedPoint);
    double coef = length / distance;
    
    Point newPoint = pointOfLineByScalar3d(center, rotatedPoint, coef);
    return newPoint;
}

Point Calculator::horizontalLeftPerpendicular(Point center, Point direction, double length) {
    return horizontalPerpendicular(center,direction, 0, length);
}
Point Calculator::horizontalRightPerpendicular(Point center, Point direction, double length) {
    return horizontalPerpendicular(center,direction, 1, length);
}

double Calculator::YOnLineByPoints2d(double x, Point p1, Point p2) {
    double coef1 = (p2.y - p1.y)/(p2.x - p1.x);
    double coef2 = p1.y - p1.x*(p2.y - p1.y)/(p2.x - p1.x);
    return x*coef1 + coef2;
}

double Calculator::XOnLineByPoints2d(double y, Point p1, Point p2) {
    return (y - p1.y)*(p2.x - p1.x)/(p2.y - p1.y) + p1.x;
}

//Point Calculator::minPointInRangeOnLine2d(Point lineP1, Point lineP2, double minX, double minY) {
//    double currentMinY = YOnLineByPoints2d(minX, lineP1, lineP2);
//    Point newPoint(minX, currentMinY, 0);
//    if(currentMinY < minY) {
//        newPoint.x = XOnLineByPoints2d(minY, lineP1, lineP2);
//        newPoint.y = minY;
//    }
//    
//    return newPoint;
//}
//
//Point Calculator::maxPointInRangeOnLine2d(Point lineP1, Point lineP2, double maxX, double maxY) {
//    double currentMaxY = YOnLineByPoints2d(maxX, lineP1, lineP2);
//    Point newPoint(maxX, currentMaxY, 0);
//    if(currentMaxY < maxY) {
//        newPoint.x = XOnLineByPoints2d(maxY, lineP1, lineP2);
//        newPoint.y = maxY;
//    }
//    
//    return newPoint;
//}

Point Calculator::visibleAlternativeOnPointOfLine(Point lineP1, Point lineP2, Point target, Camera camera) {
    Point bestVisiblePoint = target;
    if(isVisible2d(camera, target)) {
        return target;
    }
    else {
        double bestDistanceToTarget = std::numeric_limits<double>::max();
        double maxX = camera.displayPlaneHorizontalSize;
        double minX = 0;
        double maxY = camera.displayPlaneVerticalSize;
        double minY = 0;
        Point p1(maxX, YOnLineByPoints2d(maxX, lineP1, lineP2), 0);
        Point p2(minX, YOnLineByPoints2d(minX, lineP1, lineP2), 0);
        Point p3(XOnLineByPoints2d(minY, lineP1, lineP2), minY, 0);
        Point p4(XOnLineByPoints2d(maxY, lineP1, lineP2), maxY, 0);
        
        if(isVisible2d(camera, p1) && bestDistanceToTarget > distance2d(target, p1)) {
            bestDistanceToTarget = distance2d(target, p1);
            bestVisiblePoint = p1;
        }
        if(isVisible2d(camera, p2) && bestDistanceToTarget > distance2d(target, p2)) {
            bestDistanceToTarget = distance2d(target, p2);
            bestVisiblePoint = p2;
        }
        if(isVisible2d(camera, p3) && bestDistanceToTarget > distance2d(target, p3)) {
            bestDistanceToTarget = distance2d(target, p3);
            bestVisiblePoint = p3;
        }
        if(isVisible2d(camera, p4) && bestDistanceToTarget > distance2d(target, p4)) {
            bestDistanceToTarget = distance2d(target, p4);
            bestVisiblePoint = p4;
        }
        return bestVisiblePoint;
    }
}

std::pair<Point, Point> Calculator::visibleEdgesOnLine(Point lineP1, Point lineP2) {
    Point bestAlternativeOnP1 = visibleAlternativeOnPointOfLine(lineP1, lineP2, lineP1);
    Point bestAlternativeOnP2 = visibleAlternativeOnPointOfLine(lineP1, lineP2, lineP2);
    return std::pair<Point,Point>(bestAlternativeOnP1,bestAlternativeOnP2);
}

std::function<double (double)> Calculator::lineFuncByPoints2d(Point p1, Point p2) {
    double coef1 = (p2.y - p1.y)/(p2.x - p1.x);
    double coef2 = p1.y - p1.x*(p2.y - p1.y)/(p2.x - p1.x);
    
    return [coef1,coef2](double x) { return x*coef1 + coef2;};
}

std::function<Point (double)> Calculator::scalarFuncOnLine3d(Point p1, Point p2) {
    return [p1,p2](double coef) {
        double newX = p1.x + coef*(p2.x - p1.x);
        double newY = p1.y + coef*(p2.y - p1.y);
        double newZ = p1.z + coef*(p2.z - p1.z);
        return Point(newX,newY, newZ);
    };
}
Point Calculator::pointOfLineByScalar3d(Point p1, Point p2, double coef) {
    double newX = p1.x + coef*(p2.x - p1.x);
    double newY = p1.y + coef*(p2.y - p1.y);
    double newZ = p1.z + coef*(p2.z - p1.z);
    return Point(newX,newY,newZ);
}
//std::function<Point (double)> Calculator::lineFuncByPoints3d(Point p1, Point p2) {
//    return [p1,p2](double t) {
////        return x*coef1 + coef2;
//    };
//}

void Calculator::lineFuncCoefByPoints2d(Point p1, Point p2, double &coef1, double &coef2) {
    coef1 = (p2.y - p1.y)/(p2.x - p1.x);
    coef2 = p1.y - p1.x*(p2.y - p1.y)/(p2.x - p1.x);
}

std::vector<Point> Calculator::makeLine2d(Point p1, Point p2) {
    double distance = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
    double coef = fabs(p1.x - p2.x)/distance;
    std::vector<Point> result;
    
    if(!areEqual(p1.x, p2.x)) {
        if(p1.x > p2.x) {
            std::swap(p1, p2);
        }
        for (double x = p1.x; x < p2.x; x+=coef) {
            double y = YOnLineByPoints2d(x,p1, p2 );
            result.push_back(Point(x,y,0));
        }
    }
    else {
        coef = fabs(p1.y - p2.y)/distance;
        if(p1.y > p2.y) {
            std::swap(p1, p2);
        }
        
        for (double y = p1.y; y < p2.y; y+=coef) {
            double x = XOnLineByPoints2d(y,p1, p2 );
            result.push_back(Point(x,y,0));
        }
    }
    return result;
}

std::vector<Point> Calculator::makeLine2d(Point p1, Point p2, double maxX, double minX, double maxY, double minY) {
    double distance = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
    double coef = fabs(p1.x - p2.x)/distance;
    std::vector<Point> result;
    
    if(!areEqual(p1.x, p2.x)) {
        if(p1.x > p2.x) {
            std::swap(p1, p2);
        }
        
        for (double x = p1.x; x < p2.x; x+=coef) {
            double y = YOnLineByPoints2d(x,p1, p2 );
            result.push_back(Point(x,y,0));
        }
    }
    else { // vertical draw
        coef = fabs(p1.y - p2.y)/distance;
        if(p1.y > p2.y) {
            std::swap(p1, p2);
        }
        
        for (double y = p1.y; y < p2.y; y+=coef) {
            double x = XOnLineByPoints2d(y,p1, p2 );
            result.push_back(Point(x,y,0));
        }
    }
    return result;
}


std::vector<Point> Calculator::makeLine2dFromCanonic(Point p1, Point p2) {
    double distance = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
    double coefForNext = fabs(p1.x - p2.x)/distance;
    std::vector<Point> result;
    if (p1.x < p2.x) {
        for (double x = p1.x; x < p2.x; x+=coefForNext) {
            double coef = (x - p1.x)/(p2.x - p1.x);
            double y = coef*(p2.y - p1.y) + p1.y;
            result.push_back(Point(x,y,0));
        }
    }
    else {
        
        for (double x = p2.x; x < p1.x; x+=coefForNext) {
            double coef = (x - p1.x)/(p2.x - p1.x);
            double y = coef*(p2.y - p1.y) + p1.y;
            result.push_back(Point(x,y,0));
        }
    }
    return result;
}

std::vector<Point> Calculator::makeLine2dFromParametric(Point p1, Point p2) {
    double distance = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
    double coef = 1/distance;
    std::vector<Point> result;
    
    for (double lambda = 0; lambda <= 1; lambda+=coef) {
        double x = p1.x + lambda*(p2.x - p1.x);
        double y = p1.y + lambda*(p2.y - p1.y);
        result.push_back(Point(x,y,0));
    }
    
    return result;
}

std::vector<Point> Calculator::makeLine3d(Point p1, Point p2) {
    double distance = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
    double coefForNext = fabs(p1.x - p2.x)/distance;
    std::vector<Point> result;
    if (p1.x < p2.x) {
        for (double x = p1.x; x < p2.x; x+=coefForNext) {
            double coef = (x - p1.x)/(p2.x - p1.x);
            double y = coef*(p2.y - p1.y) + p1.y;
            double z = coef*(p2.z - p1.z) + p1.z;
            result.push_back(Point(x,y,z));
        }
    }
    else {
        
        for (double x = p2.x; x < p1.x; x+=coefForNext) {
            double coef = (x - p1.x)/(p2.x - p1.x);
            double y = coef*(p2.y - p1.y) + p1.y;
            double z = coef*(p2.z - p1.z) + p1.z;
            result.push_back(Point(x,y,z));
        }
    }
    return result;
}


//https://www.youtube.com/watch?v=9wznbg_aKOo
//consider perpendicular plane
double Calculator::distanceToLine(Point lineP1, Point lineP2, Point target) {
    double a = lineP2.x - lineP1.x;
    double b = lineP2.y - lineP1.y;
    double c = lineP2.z - lineP1.z;
    
    double d = a*target.x + b*target.y + c*target.z;
    double t = -(a*lineP1.x + b*lineP1.y + c*lineP1.z - d)/(a*a + b*b + c*c);
    Point intersect(lineP1.x + t*a, lineP1.y + t*b, lineP1.z + t*c);
    
    double distance = distance3d(target, intersect);
    return distance;
}

double Calculator::distanceOfIntersectToDirection(Camera camera, Point target) {
    Point cameraPosition = camera.position;
    Point cameraDirection = camera.direction;
    
    double distanceOfCameraToTarget = distance3d(cameraPosition, target);
    double distanceOfTargetToDirectionLine = distanceToLine(cameraPosition, cameraDirection, target);
    
    double distanceOfCameraToIntersectWithTargetPerpendicular =
        sqrt(distanceOfCameraToTarget*distanceOfCameraToTarget - distanceOfTargetToDirectionLine*distanceOfTargetToDirectionLine);
//    return distanceOfCameraToTarget * distanceOfTargetToDirectionLine / distanceOfCameraToIntersectWithTargetPerpendicular;
    double distanceOfCameraToDirection = distance3d(cameraPosition, cameraDirection);
    double result = distanceOfCameraToDirection * distanceOfTargetToDirectionLine / distanceOfCameraToIntersectWithTargetPerpendicular;

    if (distanceOfCameraToIntersectWithTargetPerpendicular == 0) {
        return result = distanceOfCameraToTarget; // when target and position are different only one one OS
    }
    return result;
}

Point Calculator::intersectLineAndPerpendicularPlane(Point lineP1, Point lineP2, Point target) {
    double a = lineP2.x - lineP1.x;
    double b = lineP2.y - lineP1.y;
    double c = lineP2.z - lineP1.z;
    double d = a*target.x + b*target.y + c*target.z;
    
    double t = -(a*lineP1.x + b*lineP1.y + c*lineP1.z - d)/(a*a + b*b + c*c);
    Point intersect(lineP1.x + t*a, lineP1.y + t*b, lineP1.z + t*c);
    return intersect;
}

Point Calculator::crossProduct(Point p1, Point p2) {
    return Point(p1.y*p2.z - p1.z*p2.y, p1.z*p2.x - p1.x*p2.z, p1.x*p2.y - p1.y*p2.x);
}
double Calculator::dotProduct(Point p1, Point p2) {
    return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}

Point Calculator::perspective2d(Camera camera, Point target) {
    Point cameraPosition = camera.position;
    Point cameraDirection = camera.direction;
    
    double distanceOfTargetIntersectToDirection = distanceOfIntersectToDirection(camera,target); //hippotenusa
    double newTargetZ = intersectLineAndPerpendicularPlane(cameraPosition, cameraDirection, target).z;
    Point newTargetDirection(target.x, target.y, newTargetZ);
    
    double distanceOfOldToNewDirection = distanceOfIntersectToDirection(camera,newTargetDirection); //horizontal katet
    //vertical katet
    double distanceOfTargetIntersectToNewDirection =
        sqrt(fabs(distanceOfTargetIntersectToDirection*distanceOfTargetIntersectToDirection -distanceOfOldToNewDirection*distanceOfOldToNewDirection));

    double displayPlanePointX = 0;
    double displayPlanePointY = distanceOfTargetIntersectToNewDirection;
    
    double angleTargetPositionDirection = angleBetweenPoints3d(target, camera.position, camera.direction);
    if(angleTargetPositionDirection > 90) { //camera position is after target in area
        distanceOfOldToNewDirection += distanceToLine(cameraPosition, cameraDirection, newTargetDirection);
        displayPlanePointY += distanceToLine(cameraPosition, newTargetDirection, target);
    }
    
    if (newTargetDirection.z > target.z) {
        displayPlanePointY = -displayPlanePointY;
    }
    if (newTargetDirection.z == target.z) {
        displayPlanePointY = 0;
    }
    
    
    displayPlanePointY += camera.displayPlaneVerticalSize/2;
    
    
    double angleBeetwenTargetAndDirection2d = angleBetweenPoints2d(newTargetDirection, cameraPosition, cameraDirection);
    if(angleBeetwenTargetAndDirection2d > 0) {
        displayPlanePointX = camera.displayPlaneHorizontalSize/2 + distanceOfOldToNewDirection;
    }
    else if(angleBeetwenTargetAndDirection2d < 0){
        displayPlanePointX = camera.displayPlaneHorizontalSize/2 - distanceOfOldToNewDirection;
    }
    else {
        displayPlanePointX = camera.displayPlaneHorizontalSize/2;
    }
    
    if(displayPlanePointY != displayPlanePointY) {
//        throw new std::invalid_argument("NaN");
    }
    
    return Point(displayPlanePointX,displayPlanePointY,0);
}












