//
//  Camera.cpp
//  3D visualisation
//
//  Created by Мирослав Николов on 15.03.18 г..
//  Copyright © 2018 г. Мирослав Николов. All rights reserved.
//

#include "Camera.hpp"
#include "Calculator.hpp"

Camera::Camera() {
    
}

Camera::Camera(Point position, Point direction, double displayPlaneVerticalSize, double displayPlaneHorizontalSize):
position(position),
direction(direction),
displayPlaneVerticalSize(displayPlaneVerticalSize),
displayPlaneHorizontalSize(displayPlaneHorizontalSize) {
}

Camera* Camera::getCamera() {
    return camera;
}

Camera* Camera::setCamera(Point position, Point direction, double displayPlaneVerticalSize, double displayPlaneHorizontalSize) {
    if (!camera) {
        camera = new Camera();
    }
    camera->position = position;
    camera->direction = direction;
    camera->displayPlaneVerticalSize = displayPlaneVerticalSize;
    camera->displayPlaneHorizontalSize = displayPlaneHorizontalSize;
    
    return camera;
}

void Camera::move(double coef) {
//    std::cout<<std::endl;
////    direction.Print();
//    Point p1(direction.x,direction.y,0);
//    Point p2(position.x,position.y,-1);
//    Point p3(position.x,position.y,1);
//    
//    Point p12Dot = Calculator::crossProduct(p1, p2);
//    Point p13Dot = Calculator::crossProduct(p1, p3);
//    p12Dot.Print();
//    p13Dot.Print();
////    Calculator::crossProduct( Point(direction.x,direction.y,0), Point(position.x,position.y,position.z - 1)).Print();
////    Calculator::crossProduct(direction, Point(position.x,position.y,position.z + 1)).Print();
//    std::cout<<std::endl;
    
    //    this->position.x += coef;
    //    this->direction.x += coef;
    double distance = Calculator::distance3d(this->position, this->direction);
    double subtractCoef = coef/distance;
    Point newPosition = Calculator::nextPointOfParametricEquation(this->position, this->direction, 1 + subtractCoef);
    Point newDistination = Calculator::nextPointOfParametricEquation(this->position, this->direction, subtractCoef);
    this->position = newPosition;
    this->direction = newDistination;
}

void Camera::moveLeft(double coef) {
    Point newPosition = Calculator::horizontalLeftPerpendicular(position, direction, coef);
    Point newDirection = Calculator::horizontalRightPerpendicular(direction, position, coef);
    newPosition.z = this->position.z;
    newDirection.z = this->direction.z;
    std::cout<<"old pos:   ";
    position.Print();
    std::cout<<"new pos:   ";
    newPosition.Print();
    std::cout<<"old dir:   ";
    direction.Print();
    std::cout<<"new dir:   ";
    newDirection.Print();
    std::cout<<std::endl;
    
    this->position = newPosition;
    this->direction = newDirection;
//    this->position.y -= coef;
//    this->direction.y -= coef;
}

void Camera::moveRight(double coef) {
//    Point newPosition = Calculator::horizontalRightPerpendicular(position, direction, coef);
//    Point newDirection = Calculator::horizontalLeftPerpendicular(direction, position, coef);
    
    Point newPosition = Calculator::horizontalRightPerpendicular(position, direction, coef);
    Point newDirection = Calculator::horizontalLeftPerpendicular(direction, position, coef);
    newPosition.z = this->position.z;
    newDirection.z = this->direction.z;

    
    std::cout<<"old pos:   ";
    position.Print();
    std::cout<<"new pos:   ";
    newPosition.Print();
    std::cout<<"old dir:   ";
    direction.Print();
    std::cout<<"new dir:   ";
    newDirection.Print();
    std::cout<<std::endl;
    
    this->position = newPosition;
    this->direction = newDirection;
//    this->position.y += coef;
//    this->direction.y += coef;
}

void Camera::moveTop(double coef) {
    this->position.z += coef;
    this->direction.z += coef;
}

void Camera::moveBot(double coef) {
    this->position.z -= coef;
    this->direction.z -= coef;
}
void Camera::rotateLeft(double coef) {
//    this->direction.y -= coef;
//    this->direction = Calculator::rotateByZ(this->direction, -1);
    this->direction = Calculator::rotate(position, direction, 0, -coef);
}
void Camera::rotateRight(double coef) {
//    this->direction = Calculator::rotateByZ(this->direction, 1);
    this->direction = Calculator::rotate(position, direction, 0, coef);
}

void Camera::rotateTop(double coef) {
//    this->direction.z += coef;
    this->direction = Calculator::rotate(position, direction, -coef, 0);
}
void Camera::rotateBot(double coef) {
//    this->direction.z -= coef;
    this->direction = Calculator::rotate(position, direction, coef, 0);
}

Camera* Camera::camera = NULL;




